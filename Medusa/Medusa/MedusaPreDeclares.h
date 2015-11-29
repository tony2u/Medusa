#pragma once
#include "Platform/Platform.h"
MEDUSA_BEGIN;
class MedusaScript;

class Application;

class ApplicationStatics;

class FrameAutoStopWatch;

class BaseRenderView;

class IView;

class ViewFactory;

class AndroidEGLView;

class IOSEGLView;

class WinEGLView;

class WinGLView;

class IWindow;

class WindowFactory;

class AndroidWindow;

class IOSWindow;

class WinWindow;

class AudioEngine;

class AudioListener;

class  BaseAudioRecorder;

class FileStreamAudioSource;

class IAudioSource;

class StaticAudioSource;

class StreamAudioSource;

class AudioDevice;

class IAudioDevice;

class OpenALDevice;

class IGame;

class DropPool;

class DropPoolConditionItem;

class DropPoolConfig;

class DropPoolGroup;

class DropPoolItem;

class DropPoolItemLimit;

class DropPoolRandomItem;

struct DropPoolRandomItemProbalityFunc;

struct DropPoolRandomItemProbalityFuncForPointer;

class IPlayer;

class IGameClientSettings;

class IGameServerSettings;

class IJsonGameClientSettings;

class IJsonSettings;

class IScriptGameClientSettings;

class IScriptGameServerSettings;

class IScriptSettings;

class GraphicsContext;

struct GraphicsSupportAPI;

class ResolutionAdapter;

class ColorGraphicsBuffer;

class FrameBuffer;

class IGraphicsBuffer;

class IndexGraphicsBuffer;

template<typename T, uint32 TSizeLimit >
class ListGraphicsBuffer;

template<typename T>
class MemoryArrayGraphicsBuffer;

template<typename T>
class MemoryGraphicsBuffer;

template<typename T>
class MemoryIndexGraphicsBuffer;

class NormalGraphicsBuffer;

class QuadIndexGraphicsBuffer;

class RenderBuffer;

class TexCoordGraphicsBuffer;

class VertexGraphicsBuffer;

class IRender;

class OpenGLES2Render;

class OpenGLES3Render;

class Render;

class ArrayBufferRenderState;

class BaseBufferRenderState;

class BlendRenderState;

class DepthStencilRenderState;

class ElementArrayBufferRenderState;

class FeatureRenderState;

class IRenderState;

class PixelStoreRenderState;

class ProgramRenderState;

class RasterizerRenderState;

class RenderStateMachine;

class RenderStateSet;

class RenderTargetRenderState;

class SamplerRenderState;

class ScissorRenderState;

class BaseRenderStateTreeNode;

class RenderStateTree;

class RenderStateTreeCompositeNode;

class RenderStateTreeLeafNode;

class INode;

class NodeFactory;

class NodeSweeper;

class AnimationManager;

class IAnimation;

class SkeletonAnimation;

class SkeletonSlotAttachmentNameTimeline;

class SkeletonSlotVertexTimeline;

class BlinkAction;

class DeleteSelfAction;

class FadeBySpeedAction;

class FadeInAction;

class FadeOutAction;

class HideAction;

template<typename T>
class TMoveByAction;

template<typename T>
class TMoveBySpeedAction;

template<typename T>
class TMoveToAction;

class ProgressByAction;

class ProgressToAction;

template<typename T>
class TScrollByAction;

template<typename T>
class TScrollByPageAction;

template<typename T>
class TScrollBySpeedAction;

template<typename T>
class TScrollToAction;

template<typename T>
class TScrollToPageAction;

class ShowAction;

class ColorTimeline;

class ITimeline;

class MeshTimeline;

class PODCameraFOVTimeline;

class PODLighTimeline;

class RenderingObjectTimeline;

class RotationTimeline;

class ScaleTimeline;

class TextureFileIdTimeline;

class TimelineFactory;

class TranslateTimeline;

class ParallaxComponent;

class ParallaxScrollComponent;

class ScrollComponent;

class IButton;

class LabelButton;

class NodeButton;

class TextureButton;

class BaseMultipleLineEditBox;

class BaseSingleLineEditBox;

class IEditBox;

class MultipleLineEditBox;

class SingleLineEditBox;

class FntLabel;

class ILabel;

class ListBox;

class ListBoxItem;

class IProgressBar;

class ShapeProgressBar;

class TextureProgressBar;

class BaseMultipleListDataSource;

class BaseSingleListDataSource;

class IDataSource;

class IListDataSource;

class StringListDataSource;

template<typename T>
class UserDataSource;

class ISceneEditor;

class SceneEditorFactory;

class CustomSceneEditor;

class XAMLSceneEditor;

class IInputHandler;

class IMEHandler;

class InputDispatcher;

class InputManager;

class KeyboardHandler;

class Touch;

class BaseKeyEventArg;

class CharInputEventArg;

class KeyboardEventArg;

class KeyDownEventArg;

class KeyUpEventArg;

class ScrollEventArg;

class TouchEventArg;

class DoubleTapGestureRecognizer;

class DragGestureRecognizer;

class IGestureRecognizer;

class LongPressGestureRecognizer;

class PanGestureRecognizer;

class PinchGestureRecognizer;

class RotationGestureRecognizer;

class SwipeGestureRecognizer;

class TapGestureRecognizer;

class BaseGestureEventArg;

class DoubleTapGestureEventArg;

class DragBeganGestureEventArg;

class DragEndGestureEventArg;

class DragFailedGestureEventArg;

class DragingGestureEventArg;

class LongPressBeganGestureEventArg;

class LongPressFailedGestureEventArg;

class PanBeginGestureEventArg;

class PanEndGestureEventArg;

class PanGestureEventArg;

class PinchGestureEventArg;

class SwipeBeginGestureEventArg;

class SwipeFailedGestureEventArg;

class SwipeMovedGestureEventArg;

class SwipeSuccessGestureEventArg;

class TapGestureEventArg;

class IItemTemplate;

class LabelItemTemplate;

class ILayer;

class LayerFactory;

class NormalLayer;

class ILayoutable;

class CanvasPanel;

class DockPanel;

class GridPanel;

class IPanel;

class ListPanel;

class PanelFactory;

class RelativePanel;

class ScrollPanel;

class StackPanel;

class UniformGridPanel;

class ViewPanel;

class WrapPanel;

class IParticle;

class IParticleEmitter;

class ParticleManager;

class ParticleSystem;

class Base2DScene;

class Base3DScene;

class ChangedNodeCollector;

class IScene;

class SceneFactory;

class SceneManager;

class SceneSweeper;

class ISceneGraph;

class UISceneGraph;

class IShape;

class ISkeleton;

class SkeletonBone;

class SkeletonIK;

class SkeletonSlot;

class SpineSkeleton;

class NineGridSprite;

class Sprite;

struct IDrawable;

class IRenderable;

struct IRenderGroup;

class RenderDevice;

class RenderEngine;

class RenderingContext;

class RenderingObject;

class RenderingObjectFactory;

class RenderingStatics;

class BaseBufferRenderBatch;

class BatchGroup;

struct BatchNewerById;

class BatchPool;

class CustomDrawMeshRenderBatch;

class IRenderBatch;

struct IRenderBatchCompareToBatchGroup;

class MultipleRenderBatch;

class SingleRenderBatch;

class IRenderingCommand;

class BaseBatchRenderingCommand;

class BaseNodeRenderingCommand;

class EffectRenderGroup;

class EffectRenderGroupPool;

class MaterialRenderGroup;

class MaterialRenderGroupPool;

class IRenderQueue;

struct IRenderableCompareByRenderingPriority;

class BaseMultipleBatchRenderQueue;

class UIRenderQueue;

class BaseSingleBatchRenderQueue;

class SingleBatchRenderQueue;

class SceneRenderGroup;

class StateRenderGroup;

class StateRenderGroupPool;

template<typename T>
class BaseResourceFactory;

class IResource;

template<typename TKey,typename TValue>
class IResourceFactory;

class IResourceManageable;

class ResourceManager;

class AudioFactory;

class IAudio;

class OggAudio;

class PcmAudio;

class WavAudio;

class Camera;

class CameraFactory;

class EffectFactory;

class EffectTechnique;

class EffectTechniqueGroup;

class IEffect;

class PFXEffect;

class IRenderPass;

class RenderPassCreater;

struct RenderPassDescription;

class RenderPassFactory;

class BaseCustomRenderPass;

class RenderToTextureRenderPass;

class BaseProgramRenderPass;

class IShader;

struct STLMapShaderLessPtr;

class ShaderCreater;

class ShaderFactory;

class IShaderParameter;

class ShaderAttribute;

class ShaderConstant;

class ShaderConstantInitializer;

class BasePixelShader;

class BaseVertexShader;

class BMPFont;

struct FontKerning;

class FontChar;

struct FontCharVertex;

class FontFactory;

class FontId;

class IFont;

class TTFFont;

class TextLayouter;

class DynamicAtlasRGBAImage;

class IImage;

class ImageFactory;

class JpegImage;

class PngImage;

struct PVRImageHeader;

struct PVRImageMetaDataBlock;

struct PVRFontHeader;

class PVRImage;

class RGBAImage;

class DirectionalLight;

class ILight;

class LightFactory;

class PointLight;

class SpotLight;

class ITiledLayer;

class ITiledMap;

class TiledAnimationFrame;

class TiledImage;

class TiledImageLayer;

class TiledMapFactory;

class TiledObject;

class TiledObjectLayer;

class TiledTerrain;

class TiledTile;

class TiledTileLayer;

struct TiledTileRef;

class TiledTileset;

class TmxTiledMap;

class IMaterial;

class MaterialFactory;

class PODMaterial;

template<typename TMaterial>
class BaseMultipleModel;

template<typename TMesh,typename TMaterial>
class BaseSingleModel;

template<typename TMesh>
class BaseSingleTextureModel;

class IModel;

class IModelNode;

class ModelFactory;

class QuadModel;

class TriangleModel;

class BaseCameraModelNode;

class PODCameraModelNode;

class BaseFontModel;

class MultipleLineFontModel;

class SingleLineFontModel;

class BaseLightModelNode;

class PODLightModelNode;

class IMesh;

class IMeshModelNode;

struct MeshComponentVersions;

class MeshFactory;

template<typename TMesh>
class MeshModelNode;

class ShapeQuadMesh;

class ShapeTriangleMesh;

class TextureNineGridMesh;

class TextureQuadMesh;

class TextureTriangleMesh;

class BaseFontMesh;

class FntTextMesh;

class GeneralMesh;

struct PODData;

struct PODBoneBatches;

class PODMesh;

class ShapeGeneralMesh;

class TextureGeneralMesh;

class BaseSceneModel;

struct PODScale;

struct PODNode;

class PODModel;

class VirtualModelNode;

class CustomRenderTarget;

class DefaultRenderTarget;

class IRenderTarget;

class RenderTargetFactory;

class ISkeletonModel;

class SkeletonAnimationModel;

class SkeletonAvatarModel;

class SkeletonBoneModel;

class SkeletonIKModel;

class SkeletonModelFactory;

class SkeletonSlotModel;

class SkeletonTriggerModel;

class SpineSkeletonModel;

class BaseSkeletonTextureAttachmentModel;

class ISkeletonAttachmentModel;

class SkeletonBoundingBoxAttachmentModel;

class SkeletonMeshAttachmentModel;

class SkeletonRegionAttachmentModel;

class SkeletonSkinnedMeshAttachmentModel;

class GPUTexture;

class ImageTexture;

class ITexture;

class TextureFactory;

class TextureAtlas;

class TextureAtlasFactory;

class TextureAtlasPage;

class TextureAtlasRegion;

class ColorTimelineModel;

class DrawOrderTimelineModel;

class IdentityTimelineModel;

class IKTimelineModel;

struct TimelineFrame;

class ITimelineModel;

class MeshTimelineModel;

template<typename T>
class OnceTimelineModel;

class PODCameraFOVTimelineModel;

class PODJointTimelineModel;

class PODLightTimelineModel;

class RenderingObjectTimelineModel;

class RotationTimelineModel;

class ScaleTimelineModel;

class StringTimelineModel;

class TextureFileIdTimelineModel;

class TimelineModelFactory;

class TranslateTimelineModel;

class TriggerTimelineModel;

class VertexTimelineModel;

#pragma region typedef
typedef TMoveByAction<INode> MoveByAction;
typedef TMoveBySpeedAction<INode> MoveBySpeedAction;
typedef TMoveToAction<INode> MoveToAction;
typedef TMoveToAction<ParallaxComponent> ParallaxComponentMoveToAction;
typedef TMoveByAction<ParallaxComponent> ParallaxComponentMoveByAction;
typedef TMoveBySpeedAction<INode> ParallaxComponentMoveBySpeedAction;
typedef TScrollToAction<ScrollComponent> ScrollComponentScrollToAction;
typedef TScrollByAction<ScrollComponent> ScrollComponentScrollByAction;
typedef TScrollBySpeedAction<ScrollComponent> ScrollComponentScrollBySpeedAction;
typedef TScrollByPageAction<ScrollComponent> ScrollComponentScrollByPageAction;
typedef TScrollToPageAction<ScrollComponent> ScrollComponentScrollToPageAction;
typedef Delegate<void (IProgressBar* sender, float percent)> ProgressChangedDelegate;
typedef Event<void (IProgressBar* sender,float percent)> ProgressChangedEvent;
typedef Delegate<void (void* sender)> ProgressCompletedDelegate;
typedef Delegate<void(INode* sender, CharInputEventArg&)> CharInputDelegate;
typedef Event<void(INode* sender, CharInputEventArg&)> CharInputEvent;
typedef Delegate<void(INode* sender, KeyboardEventArg&)> KeyboardWillShowDelegate;
typedef Event<void(INode* sender, KeyboardEventArg&)> KeyboardWillShowEvent;
typedef Delegate<void(INode* sender, KeyboardEventArg&)> KeyboardShowedDelegate;
typedef Event<void(INode* sender, KeyboardEventArg&)> KeyboardShowedEvent;
typedef Delegate<void(INode* sender, KeyboardEventArg&)> KeyboardWillHideDelegate;
typedef Event<void(INode* sender, KeyboardEventArg&)> KeyboardWillHideEvent;
typedef Delegate<void(INode* sender, KeyboardEventArg&)> KeyboardHidedDelegate;
typedef Event<void(INode* sender, KeyboardEventArg&)> KeyboardHidedEvent;
typedef Delegate<void(INode* sender, KeyDownEventArg&)> KeyDownDelegate;
typedef Event<void(INode* sender, KeyDownEventArg&)> KeyDownEvent;
typedef Delegate<void(INode* sender, KeyUpEventArg&)> KeyUpDelegate;
typedef Event<void(INode* sender, KeyUpEventArg&)> KeyUpEvent;
typedef Delegate<void (INode* sender,DoubleTapGestureEventArg&)> DoubleTapDelegate;
typedef Event<void (INode* sender,DoubleTapGestureEventArg&)> DoubleTapEvent;
typedef Delegate<void (INode* sender,DragBeganGestureEventArg&)> DragBeganDelegate;
typedef Event<void (INode* sender,DragBeganGestureEventArg&)> DragBeganEvent;
typedef Delegate<void (INode* sender,DragEndGestureEventArg&)> DragEndDelegate;
typedef Event<void (INode* sender,DragEndGestureEventArg&)> DragEndEvent;
typedef Delegate<void (INode* sender,DragFailedGestureEventArg&)> DragFailedDelegate;
typedef Event<void (INode* sender,DragFailedGestureEventArg&)> DragFailedEvent;
typedef Delegate<void (INode* sender,DragingGestureEventArg&)> DragingDelegate;
typedef Event<void (INode* sender,DragingGestureEventArg&)> DragingEvent;
typedef Delegate<void (INode* sender,LongPressBeganGestureEventArg&)> LongPressBeganDelegate;
typedef Event<void (INode* sender,LongPressBeganGestureEventArg&)> LongPressBeganEvent;
typedef Delegate<void (INode* sender,LongPressFailedGestureEventArg&)> LongPressFailedDelegate;
typedef Event<void (INode* sender,LongPressFailedGestureEventArg&)> LongPressFailedEvent;
typedef Delegate<void (INode* sender,PanBeginGestureEventArg&)> PanBeginDelegate;
typedef Event<void (INode* sender,PanBeginGestureEventArg&)> PanBeginEvent;
typedef Delegate<void (INode* sender,PanEndGestureEventArg&)> PanEndDelegate;
typedef Event<void (INode* sender,PanEndGestureEventArg&)> PanEndEvent;
typedef Delegate<void (INode* sender,PanGestureEventArg&)> PanDelegate;
typedef Event<void (INode* sender,PanGestureEventArg&)> PanEvent;
typedef Delegate<void (INode* sender,PinchGestureEventArg&)> PinchDelegate;
typedef Event<void (INode* sender,PinchGestureEventArg&)> PinchEvent;
typedef Delegate<void (INode* sender,SwipeBeginGestureEventArg&)> SwipeBeginDelegate;
typedef Event<void (INode* sender,SwipeBeginGestureEventArg&)> SwipeBeginEvent;
typedef Delegate<void (INode* sender,SwipeFailedGestureEventArg&)> SwipeFailedDelegate;
typedef Event<void (INode* sender,SwipeFailedGestureEventArg&)> SwipeFailedEvent;
typedef Delegate<void (INode* sender,SwipeMovedGestureEventArg&)> SwipeMovedDelegate;
typedef Event<void (INode* sender,SwipeMovedGestureEventArg&)> SwipeMovedEvent;
typedef Delegate<void (INode* sender,SwipeSuccessGestureEventArg&)> SwipeSuccessDelegate;
typedef Event<void (INode* sender,SwipeSuccessGestureEventArg&)> SwipeSuccessEvent;
typedef Delegate<void (INode* sender,TapGestureEventArg&)> TapDelegate;
typedef Event<void (INode* sender,TapGestureEventArg&)> TapEvent;
typedef Delegate<void(INode* sender)> TapFailedDelegate;
typedef Event<void(INode* sender)> TapFailedEvent;
typedef Quad<FontCharVertex> FontCharQuad;
#pragma endregion typedef
MEDUSA_END;
