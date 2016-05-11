// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreDeclares.h"

#ifdef MEDUSA_IOS
#import <UIKit/UIKit.h>

#import <CoreFoundation/CoreFoundation.h>
#include "Geometry/Size2.h"


@interface MyEAGLView : UIView
{
	CADisplayLink* mDisplayLink;
    
    Medusa::Size2I mRenderBufferSize;
    
    bool mDiscardFramebufferSupported;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
    GLuint mDefaultFrameBuffer;
    GLuint mColorRenderBuffer;
    GLuint mDepthBuffer;
     GLuint mStencilBuffer;
    
    
    //buffers for MSAA
    GLuint mMSAAFrameBuffer;
    GLuint mMSAAColorBuffer;
    
    EAGLContext *mContext;
}


@property (readonly, nonatomic) BOOL IsAnimating;

- (id) initWithFrame:(CGRect)frame; //These also set the current context

/** CCEAGLView uses double-buffer. This method swaps the buffers */
-(void) SwapBuffers;

- (bool) Start;
- (bool) Stop;
-(bool)Pause;
-(bool)Resume;
- (void) OnUpdate:(id)sender;
@end

#endif
