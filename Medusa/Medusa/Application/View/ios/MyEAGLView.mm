// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#import <QuartzCore/QuartzCore.h>
#import "MyEAGLView.h"
#include "Application.h"
#include "Node/Input/Touch.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/InputManager.h"
#include "Application/ApplicationStatics.h"
#include "Graphics/ResolutionAdapter.h"
#include "Rendering/RenderEngine.h"

#include "Graphics/GraphicsTypes.h"
#include "Graphics/GraphicsContext.h"
#include "Core/Log/Log.h"
#include "Graphics/Render/RenderExtensionNames.h"

using namespace Medusa;

#define IOS_MAX_TOUCHES_COUNT     10

@interface MyEAGLView (Private)
- (BOOL) setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup;
@end

@implementation MyEAGLView

@synthesize IsAnimating;

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (void) dealloc
{
    // Tear down GL
    if (mDefaultFrameBuffer)
    {
        glDeleteFramebuffers(1, &mDefaultFrameBuffer);
        mDefaultFrameBuffer = 0;
    }
    
    if (mColorRenderBuffer)
    {
        glDeleteRenderbuffers(1, &mColorRenderBuffer);
        mColorRenderBuffer = 0;
    }
    
    if( mDepthBuffer )
    {
        glDeleteRenderbuffers(1, &mDepthBuffer );
        mDepthBuffer = 0;
    }
    if( mStencilBuffer )
    {
        glDeleteRenderbuffers(1, &mStencilBuffer );
        mStencilBuffer = 0;
    }
    
    if ( mMSAAColorBuffer)
    {
        glDeleteRenderbuffers(1, &mMSAAColorBuffer);
        mMSAAColorBuffer = 0;
    }
    
    if ( mMSAAFrameBuffer)
    {
        glDeleteRenderbuffers(1, &mMSAAFrameBuffer);
        mMSAAFrameBuffer = 0;
    }
    
    // Tear down context
    if ([EAGLContext currentContext] == mContext)
        [EAGLContext setCurrentContext:nil];
    
    
    mContext = nil;
    //self.keyboardShowNotification = nullptr; // implicit release
}

- (id) initWithFrame:(CGRect)frame
{
    return [self initWithFrame:frame sharegroup:nil];
}


- (id) initWithFrame:(CGRect)frame sharegroup:(EAGLSharegroup*)sharegroup;
{
    self = [super initWithFrame:frame];
    if(!self)
    {
        return self;
    }
    mDisplayLink=nil;
    
    NSString* formatStr=nil;
    GraphicsContextPixelFormat format= GraphicsContext::Instance().PixelFormat();
    switch (format) {
        case GraphicsContextPixelFormat::RGBA8:
            formatStr=kEAGLColorFormatRGBA8;
            break;
        case GraphicsContextPixelFormat::RGB565:
            formatStr=kEAGLColorFormatRGB565;
            break;
        case GraphicsContextPixelFormat::SRGBA8:
            formatStr=kEAGLColorFormatSRGBA8;
            break;
        default:
            break;
    }
    
    //config layer
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:YES], kEAGLDrawablePropertyRetainedBacking,
                                    formatStr, kEAGLDrawablePropertyColorFormat, nil];
    
    if (GraphicsContext::Instance().API()==GraphicsAPI::OpenGLES3)
    {
        if( ! sharegroup )
            mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
        else
            mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3 sharegroup:sharegroup];
        
        if (!mContext)
        {
            //fallback to ES2
            GraphicsContext::Instance().SetAPI(GraphicsAPI::OpenGLES2);
        }
    }
    
    if (GraphicsContext::Instance().API()==GraphicsAPI::OpenGLES2)
    {
        if( ! sharegroup )
            mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        else
            mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 sharegroup:sharegroup];
        
    }
    
    if (!mContext || ![EAGLContext setCurrentContext:mContext] )
    {
        Log::AssertFailed("Cannot create EAGLContext with OpenGLES2");
        return nil;
    }
    
    
    self.contentScaleFactor = [[UIScreen mainScreen] scale];
    
    RenderEngine::Instance().Initialize();
    
    mDiscardFramebufferSupported=Render::Instance().IsExtensionSupported(RenderExtensionNames::EXT_discard_framebuffer);
    
    
    // Create default framebuffer object. The backing will be allocated for the current layer in -resizeFromLayer
    glGenFramebuffers(1, &mDefaultFrameBuffer);
    NSAssert( mDefaultFrameBuffer, @"Can't create default frame buffer");
    
    glGenRenderbuffers(1, &mColorRenderBuffer);
    NSAssert( mColorRenderBuffer, @"Can't create default render buffer");
    
    glBindFramebuffer(GL_FRAMEBUFFER, mDefaultFrameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mColorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mColorRenderBuffer);
    
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, mRenderBufferSize.Width, mRenderBufferSize.Height);
    [mContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];  //do something internally, so we cannot replace it with glRenderbufferStorage
    
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &mRenderBufferSize.Width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &mRenderBufferSize.Height);
    //NSLog(@"RenderBufferSize:%d,%d",mRenderBufferSize.Width,mRenderBufferSize.Height);
    
    if (GraphicsContext::Instance().NeedMultipleSampling())
    {
        GLint maxSamplesAllowed;
        glGetIntegerv(GL_MAX_SAMPLES, &maxSamplesAllowed);
        maxSamplesAllowed = MIN(maxSamplesAllowed,GraphicsContext::Instance().SampleCount());
        GraphicsContext::Instance().SetSampleCount(maxSamplesAllowed);
        
        /* Create the MSAA framebuffer (offscreen) */
        glGenFramebuffers(1, &mMSAAFrameBuffer);
        NSAssert( mMSAAFrameBuffer, @"Can't create default MSAA frame buffer");
        glBindFramebuffer(GL_FRAMEBUFFER, mMSAAFrameBuffer);
        
        /* Create the offscreen MSAA color buffer.
         After rendering, the contents of this will be blitted into ColorRenderbuffer */
        glGenRenderbuffers(1, &mMSAAColorBuffer);
        NSAssert(mMSAAColorBuffer, @"Can't create MSAA color buffer");
        glBindRenderbuffer(GL_RENDERBUFFER, mMSAAColorBuffer);
        
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, maxSamplesAllowed, (uint)format , mRenderBufferSize.Width, mRenderBufferSize.Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mMSAAColorBuffer);
        
        
    }
    
    auto depthFormat= GraphicsContext::Instance().DepthFormat();
    auto stencilFormat= GraphicsContext::Instance().StencilFormat();
    auto depthStencilFormat= GraphicsContext::Instance().DepthStencilFormat();
    
    if (depthStencilFormat==GraphicsRenderBufferInternalFormat::None)
    {
        if (depthFormat!=GraphicsRenderBufferInternalFormat::None)
        {
            glGenRenderbuffers(1, &mDepthBuffer);
            NSAssert(mDepthBuffer, @"Can't create depth buffer");
            glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
            
            if( GraphicsContext::Instance().NeedMultipleSampling() )
                glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, GraphicsContext::Instance().SampleCount(), (uint)depthFormat,mRenderBufferSize.Width, mRenderBufferSize.Height);
            else
                glRenderbufferStorage(GL_RENDERBUFFER, (uint)depthFormat, mRenderBufferSize.Width, mRenderBufferSize.Height);
            
            //attach to framebuffer
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);
            
        }
        
        if (stencilFormat!=GraphicsRenderBufferInternalFormat::None)
        {
            glGenRenderbuffers(1, &mStencilBuffer);
            NSAssert(mStencilBuffer, @"Can't create stencil buffer");
            glBindRenderbuffer(GL_RENDERBUFFER, mStencilBuffer);
            
            if( GraphicsContext::Instance().NeedMultipleSampling() )
                glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, GraphicsContext::Instance().SampleCount(), (uint)stencilFormat,mRenderBufferSize.Width, mRenderBufferSize.Height);
            else
                glRenderbufferStorage(GL_RENDERBUFFER, (uint)stencilFormat, mRenderBufferSize.Width, mRenderBufferSize.Height);
            
            //attach to framebuffer
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mStencilBuffer);
            
        }
    }
    else
    {
        glGenRenderbuffers(1, &mDepthBuffer);
        mStencilBuffer=mDepthBuffer;
        NSAssert(mDepthBuffer, @"Can't create depth and stencil buffer");
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
        
        if( GraphicsContext::Instance().NeedMultipleSampling() )
            glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, GraphicsContext::Instance().SampleCount(), (uint)depthStencilFormat,mRenderBufferSize.Width, mRenderBufferSize.Height);
        else
            glRenderbufferStorage(GL_RENDERBUFFER, (uint)depthStencilFormat, mRenderBufferSize.Width, mRenderBufferSize.Height);
        
        //attach to framebuffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);
        
    }
    
    // rebind color buffer
    glBindRenderbuffer(GL_RENDERBUFFER, mColorRenderBuffer);
    
    GLenum error;
    if( (error=glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
    {
        NSLog(@"Failed to make complete framebuffer object 0x%X", error);
        return nil;
    }
    
    Render::Instance().SetViewPort(Rect2I(0, 0, mRenderBufferSize.Width, mRenderBufferSize.Height));

    
    return self;
}


- (void) layoutSubviews
{
    
    // Allocate color buffer backing based on the current layer size
    glBindRenderbuffer(GL_RENDERBUFFER, mColorRenderBuffer);
    
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, mRenderBufferSize.Width, mRenderBufferSize.Height);
    if( ! [mContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer] )
    {
        NSLog(@"failed to call context");
        return;
    }
    
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &mRenderBufferSize.Width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &mRenderBufferSize.Height);
    //NSLog(@"RenderBufferSize:%d,%d",mRenderBufferSize.Width,mRenderBufferSize.Height);
    
    
    
    if (GraphicsContext::Instance().NeedMultipleSampling())
    {
        glBindRenderbuffer(GL_RENDERBUFFER, mMSAAColorBuffer);
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, GraphicsContext::Instance().SampleCount(), (uint)GraphicsContext::Instance().PixelFormat() , mRenderBufferSize.Width, mRenderBufferSize.Height);
    }
    
    auto depthFormat= GraphicsContext::Instance().DepthFormat();
    auto stencilFormat= GraphicsContext::Instance().StencilFormat();
    auto depthStencilFormat= GraphicsContext::Instance().DepthStencilFormat();
    
    if (depthStencilFormat==GraphicsRenderBufferInternalFormat::None)
    {
        if (depthFormat!=GraphicsRenderBufferInternalFormat::None)
        {
            if( GraphicsContext::Instance().NeedMultipleSampling() )
                glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, GraphicsContext::Instance().SampleCount(), (uint)depthFormat,mRenderBufferSize.Width, mRenderBufferSize.Height);
            else
                glRenderbufferStorage(GL_RENDERBUFFER, (uint)depthFormat, mRenderBufferSize.Width, mRenderBufferSize.Height);
        }
        
        if (stencilFormat!=GraphicsRenderBufferInternalFormat::None)
        {
            if( GraphicsContext::Instance().NeedMultipleSampling() )
                glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, GraphicsContext::Instance().SampleCount(), (uint)stencilFormat,mRenderBufferSize.Width, mRenderBufferSize.Height);
            else
                glRenderbufferStorage(GL_RENDERBUFFER, (uint)stencilFormat, mRenderBufferSize.Width, mRenderBufferSize.Height);
        }
        
    }
    else
    {
        
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
        
        if( GraphicsContext::Instance().NeedMultipleSampling() )
            glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, GraphicsContext::Instance().SampleCount(), (uint)depthStencilFormat,mRenderBufferSize.Width, mRenderBufferSize.Height);
        else
            glRenderbufferStorage(GL_RENDERBUFFER, (uint)depthStencilFormat, mRenderBufferSize.Width, mRenderBufferSize.Height);
        glBindRenderbuffer(GL_RENDERBUFFER, mColorRenderBuffer);
    }
    
    Render::Instance().SetViewPort(Rect2I(0, 0, mRenderBufferSize.Width, mRenderBufferSize.Height));
    
    ResolutionAdapter::Instance().SetWinSize(mRenderBufferSize);
}

- (void) SwapBuffers
{
    if (GraphicsContext::Instance().NeedMultipleSampling())
    {
        /* Resolve from msaaFramebuffer to resolveFramebuffer */
        glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, mMSAAFrameBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, mDefaultFrameBuffer);
        glResolveMultisampleFramebufferAPPLE();
    }
    
    if(mDiscardFramebufferSupported)
    {
        GLenum attachments[3]={GL_COLOR_ATTACHMENT0, 0,0};
        uint count=0;
        if (GraphicsContext::Instance().NeedDepthBuffer())
        {
            attachments[++count]=GL_DEPTH_ATTACHMENT;
        }
        
        if (GraphicsContext::Instance().NeedStencilBuffer())
        {
            attachments[++count]=GL_STENCIL_ATTACHMENT;
        }
        
        if (GraphicsContext::Instance().NeedMultipleSampling())
        {
            glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, count+1, attachments);
            glBindRenderbuffer(GL_RENDERBUFFER, mColorRenderBuffer);
            
        }
        else
        {
            glDiscardFramebufferEXT(GL_FRAMEBUFFER, count+1, attachments);
        }
    }
    
    
    if(![mContext presentRenderbuffer:GL_RENDERBUFFER])
    {
        NSLog(@"Cannot render in background");
    }
    
    
    
    // We can safely re-bind the framebuffer here, since this will be the
    // 1st instruction of the new main loop
    if( GraphicsContext::Instance().NeedMultipleSampling() )
        glBindFramebuffer(GL_FRAMEBUFFER, mMSAAFrameBuffer);
    else
        glBindFramebuffer(GL_FRAMEBUFFER, mDefaultFrameBuffer);
}


- (bool) Start
{
    if(IsAnimating)
    {
        return true;
    }
    
    mDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(OnUpdate:)];
    [mDisplayLink setFrameInterval:60*Application::Instance().FrameInterval()];
    [mDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    IsAnimating=true;
    return true;
}

- (bool) Stop
{
    if(!IsAnimating)
    {
        return true;
    }
    
    [mDisplayLink invalidate];
    mDisplayLink = nil;
    IsAnimating=false;
    
    return true;
}


- (bool) Pause
{
	return [self Stop];
}

- (bool) Resume
{
	return [self Start];
}


- (void) OnUpdate:(id)sender
{
    float dt=mDisplayLink.duration*Application::Instance().FrameInterval()*60.f;
    Application::Instance().UpdateAndDraw(dt);
    
}
#pragma mark MyEAGLView - Point conversion


- (void)didMoveToWindow;
{
    /*
     [[NSNotificationCenter defaultCenter] addObserver:self
     selector:@selector(onUIKeyboardNotification:)
     name:UIKeyboardWillShowNotification object:nil];
     
     [[NSNotificationCenter defaultCenter] addObserver:self
     selector:@selector(onUIKeyboardNotification:)
     name:UIKeyboardDidShowNotification object:nil];
     [[NSNotificationCenter defaultCenter] addObserver:self
     selector:@selector(onUIKeyboardNotification:)
     name:UIKeyboardWillHideNotification object:nil];
     
     [[NSNotificationCenter defaultCenter] addObserver:self
     selector:@selector(onUIKeyboardNotification:)
     name:UIKeyboardDidHideNotification object:nil];
     */
}

// Pass the touches to the superview
#pragma mark MyEAGLView - Touch Delegate
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    float height=self.bounds.size.height*self.contentScaleFactor;
    TouchEventArg e(TouchPhase::Began);
    
    List<Touch>& worldTouches=e.MutableWorldActiveTouches();
    for( UITouch* touch in [event allTouches])
    {
        Touch& newTouch=worldTouches.NewAdd();
        newTouch.Phase=TouchPhase::Began;
        newTouch.Id=(intp)touch;
        newTouch.Timestamp=[touch timestamp];
        newTouch.TapCount=(uint)[touch tapCount];
        
        CGPoint pos=[touch locationInView:self];
        CGPoint prevPos=[touch previousLocationInView:self];
        
        newTouch.Pos.X=pos.x*self.contentScaleFactor;
        newTouch.Pos.Y=height-pos.y*self.contentScaleFactor;
        
        newTouch.PrevPos.X=prevPos.x*self.contentScaleFactor;
        newTouch.PrevPos.Y=height-prevPos.y*self.contentScaleFactor;
    }
    
    List<Touch>& currentTouches=e.MutableWorldCurrentTouches();
    for (UITouch *touch in touches)
    {
        Touch& newTouch=currentTouches.NewAdd();
        newTouch.Phase=TouchPhase::Began;
        newTouch.Id=(intp)touch;
        newTouch.Timestamp=[touch timestamp];
        newTouch.TapCount=(uint)[touch tapCount];
        
        CGPoint pos=[touch locationInView:self];
        CGPoint prevPos=[touch previousLocationInView:self];
        
        newTouch.Pos.X=pos.x*self.contentScaleFactor;
        newTouch.Pos.Y=height-pos.y*self.contentScaleFactor;
        
        newTouch.PrevPos.X=prevPos.x*self.contentScaleFactor;
        newTouch.PrevPos.Y=height-prevPos.y*self.contentScaleFactor;
        
        ApplicationStatics::Instance().SetDebugTouch(newTouch.Pos);
    }
    
    InputManager::Instance().TouchesBegan(e);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    float height=self.bounds.size.height*self.contentScaleFactor;
    TouchEventArg e(TouchPhase::Moved);
    
    List<Touch>& worldTouches=e.MutableWorldActiveTouches();
    for( UITouch* touch in [event allTouches])
    {
        Touch& newTouch=worldTouches.NewAdd();
        newTouch.Phase=TouchPhase::Moved;
        newTouch.Id=(intp)touch;
        newTouch.Timestamp=[touch timestamp];
        newTouch.TapCount=(uint)[touch tapCount];
        
        CGPoint pos=[touch locationInView:self];
        CGPoint prevPos=[touch previousLocationInView:self];
        newTouch.Pos.X=pos.x*self.contentScaleFactor;
        newTouch.Pos.Y=height-pos.y*self.contentScaleFactor;
        
        newTouch.PrevPos.X=prevPos.x*self.contentScaleFactor;
        newTouch.PrevPos.Y=height-prevPos.y*self.contentScaleFactor;
    }
    
    List<Touch>& currentTouches=e.MutableWorldCurrentTouches();
    for (UITouch *touch in touches)
    {
        Touch& newTouch=currentTouches.NewAdd();
        newTouch.Phase=TouchPhase::Moved;
        newTouch.Id=(intp)touch;
        newTouch.Timestamp=[touch timestamp];
        newTouch.TapCount=(uint)[touch tapCount];
        
        CGPoint pos=[touch locationInView:self];
        CGPoint prevPos=[touch previousLocationInView:self];
        
        newTouch.Pos.X=pos.x*self.contentScaleFactor;
        newTouch.Pos.Y=height-pos.y*self.contentScaleFactor;
        
        newTouch.PrevPos.X=prevPos.x*self.contentScaleFactor;
        newTouch.PrevPos.Y=height-prevPos.y*self.contentScaleFactor;
        
        ApplicationStatics::Instance().SetDebugTouch(newTouch.Pos);
    }
    
    InputManager::Instance().TouchesMoved(e);
    
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    float height=self.bounds.size.height*self.contentScaleFactor;
    TouchEventArg e(TouchPhase::Ended);
    
    List<Touch>& worldTouches=e.MutableWorldActiveTouches();
    for( UITouch* touch in [event allTouches])
    {
        Touch& newTouch=worldTouches.NewAdd();
        newTouch.Phase=TouchPhase::Ended;
        newTouch.Id=(intp)touch;
        newTouch.Timestamp=[touch timestamp];
        newTouch.TapCount=(uint)[touch tapCount];
        
        CGPoint pos=[touch locationInView:self];
        CGPoint prevPos=[touch previousLocationInView:self];
        
        newTouch.Pos.X=pos.x*self.contentScaleFactor;
        newTouch.Pos.Y=height-pos.y*self.contentScaleFactor;
        
        newTouch.PrevPos.X=prevPos.x*self.contentScaleFactor;
        newTouch.PrevPos.Y=height-prevPos.y*self.contentScaleFactor;
    }
    
    List<Touch>& currentTouches=e.MutableWorldCurrentTouches();
    for (UITouch *touch in touches)
    {
        Touch& newTouch=currentTouches.NewAdd();
        newTouch.Phase=TouchPhase::Ended;
        newTouch.Id=(intp)touch;
        newTouch.Timestamp=[touch timestamp];
        newTouch.TapCount=(uint)[touch tapCount];
        
        CGPoint pos=[touch locationInView:self];
        CGPoint prevPos=[touch previousLocationInView:self];
        
        newTouch.Pos.X=pos.x*self.contentScaleFactor;
        newTouch.Pos.Y=height-pos.y*self.contentScaleFactor;
        
        newTouch.PrevPos.X=prevPos.x*self.contentScaleFactor;
        newTouch.PrevPos.Y=height-prevPos.y*self.contentScaleFactor;
        
        ApplicationStatics::Instance().SetDebugTouch(newTouch.Pos);
    }
    
    InputManager::Instance().TouchesEnded(e);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    float height=self.bounds.size.height*self.contentScaleFactor;
    TouchEventArg e(TouchPhase::Cancelled);
    
    List<Touch>& worldTouches=e.MutableWorldActiveTouches();
    for( UITouch* touch in [event allTouches])
    {
        Touch& newTouch=worldTouches.NewAdd();
        newTouch.Phase=TouchPhase::Cancelled;
        newTouch.Id=(intp)touch;
        newTouch.Timestamp=[touch timestamp];
        newTouch.TapCount=(uint)[touch tapCount];
        
        CGPoint pos=[touch locationInView:self];
        CGPoint prevPos=[touch previousLocationInView:self];
        
        newTouch.Pos.X=pos.x*self.contentScaleFactor;
        newTouch.Pos.Y=height-pos.y*self.contentScaleFactor;
        
        newTouch.PrevPos.X=prevPos.x*self.contentScaleFactor;
        newTouch.PrevPos.Y=height-prevPos.y*self.contentScaleFactor;
    }
    
    List<Touch>& currentTouches=e.MutableWorldCurrentTouches();
    for (UITouch *touch in touches)
    {
        Touch& newTouch=currentTouches.NewAdd();
        newTouch.Phase=TouchPhase::Cancelled;
        newTouch.Id=(intp)touch;
        newTouch.Timestamp=[touch timestamp];
        newTouch.TapCount=(uint)[touch tapCount];
        
        CGPoint pos=[touch locationInView:self];
        CGPoint prevPos=[touch previousLocationInView:self];
        
        newTouch.Pos.X=pos.x*self.contentScaleFactor;
        newTouch.Pos.Y=height-pos.y*self.contentScaleFactor;
        
        newTouch.PrevPos.X=prevPos.x*self.contentScaleFactor;
        newTouch.PrevPos.Y=height-prevPos.y*self.contentScaleFactor;
        
        ApplicationStatics::Instance().SetDebugTouch(newTouch.Pos);
    }
    
    InputManager::Instance().TouchesCancelled(e);
}

@end
