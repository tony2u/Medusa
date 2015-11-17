// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "CorePlatform/CorePlatform.h"
MEDUSA_BEGIN;
namespace Socket
{
	class AddressInfo;
	
	class ClientSocket;
	
	class HostInfo;
	
	class ISocket;
	
	class ProtocolInfo;
	
	class ServerSocket;
	
	class ServiceInfo;
	
}
namespace placeholder
{
	template <int N>
	struct TPlaceHolder;
	
}
class MedusaCoreScript;

class ActionFactory;

template<typename TArg>
class ArgDelegateAction;

template<typename TTarget>
class BaseActionRunner;

class BaseFiniteAction;

class BaseFiniteRepeatableAction;

class BaseFiniteRepeatableCountDownDelayAction;

class BaseInfiniteAction;

class BaseInstantAction;

class DelayAction;

class DelegateAction;

class IAction;

struct IActionRunnable;

template<typename T>
class IncreaseAction;

class BaseDoubleCompositeFiniteAction;

class BaseDoubleCompositeInfiniteAction;

class BaseMultipleCompositeFiniteAction;

class BaseMultipleCompositeInfiniteAction;

class BaseSingleCompositeFiniteAction;

class BaseSingleCompositeInfiniteAction;

class BlendAction;

class CountDownAction;

class ParallelAction;

class RepeatedAction;

class RepeatedForeverAction;

class ReverseAction;

class SelectAction;

class SequenceAction;

class SpeedAction;

class SpeedToAction;

class TimePollingAction;

class BackEaseInAction;

class BackEaseInOutAction;

class BackEaseOutAction;

class BaseTweenAction;

class BezierAction;

class BounceEaseInAction;

class BounceEaseInOutAction;

class BounceEaseOutAction;

class CircularEaseInAction;

class CircularEaseInOutAction;

class CircularEaseOutAction;

class CubicEaseInAction;

class CubicEaseInOutAction;

class CubicEaseOutAction;

class ElasticEaseInAction;

class ElasticEaseInOutAction;

class ElasticEaseOutAction;

class ExponentialEaseInAction;

class ExponentialEaseInOutAction;

class ExponentialEaseOutAction;

class QuadraticEaseInAction;

class QuadraticEaseInOutAction;

class QuadraticEaseOutAction;

class QuarticEaseInAction;

class QuarticEaseInOutAction;

class QuarticEaseOutAction;

class QuinticEaseInAction;

class QuinticEaseInOutAction;

class QuinticEaseOutAction;

class RateEaseInAction;

class RateEaseInOutAction;

class RateEaseOutAction;

class SinusoidalEaseInAction;

class SinusoidalEaseInOutAction;

class SinusoidalEaseOutAction;

class Algorithm;

template<typename T>
struct InnerTypes;

class IKSolver2D;

struct Bone;

class GuillotineBinPack;

class SkylineBinPack;

struct Skyline;

template<typename TGraph, typename TNode, typename TUserData>
class DijkstraPathFinder;

class CoderChain;

class CoderFactory;

class CoderInfo;

class ICoder;

class Aes256Decoder;

class Aes256Encoder;

class Base64Decoder;

class Base64Encoder;

class Base91Decoder;

class Base91Encoder;

class LZ4Decoder;

class LZ4Encoder;

class LZMADecoder;

class LZMAEncoder;

class LZMASeqInStream;

class LZMASeqOutStream;

class XORDecoder;

class XOREncoder;

class XXTEADecoder;

class XXTEAEncoder;

template<size_t TSize>
class BitArray;

template<typename T,typename TPtr>
class Enumerator;

template<typename T>
struct ICollection;

template<typename TKey,typename TValue,typename TKeyValuePair >
struct IDictionary;

template<typename T>
struct IEnumerable;

template<typename T,typename TPtr>
struct IEnumerator;

template<typename T>
struct LinkedListNode;

template<typename T >
class ILinkedList;

template<typename T>
class IList;

template<typename T,typename TCompare >
struct ISet;

template<typename T>
class ISortedList;

template<typename TKey, typename TValue, typename TKeyHashCoder , typename TValueHashCoder >
struct KeyValuePair;

class Linq;

template<typename TKey,typename TValue,typename TSorter >
class SortedDictionary;

template<typename T>
struct STLMapLessPtr;

template<typename T>
struct STLMapLessPtrForPointer;

template<typename T>
struct DefaultCompare;

template<typename T>
struct CustomCompare;

template<typename T>
struct DefaultCompareForPointer;

template<typename T>
struct CustomCompareForPointer;

template<typename T>
struct InverseCompare;

template<typename T>
struct InverseCustomCompare;

template<typename T>
struct NoCompare;

template<typename T>
struct EqualCompare;

template<typename T>
struct ObjectEqualCompare;

template<typename T>
struct PointerEqualCompare;

template<typename T>
struct DefaultHashCoder;

template<typename T>
struct SafeEnumHashCoder;

template<typename T>
struct NoHashCoder;

template<typename T>
struct DefaultPointerHashCoder;

template<typename T>
struct DefaultDeleter;

template<typename T>
struct DefaultPointerDeleter;

template<typename T>
struct DefaultPointerReleaser;

template<typename T>
struct NoDeleter;

template<typename TObject>
struct DefaultNewer;

template<typename TId,typename TObject>
struct DefaultNewerById;

class CommandPool;

struct DelegateCommand;

struct ICommand;

class IWaitableCommand;

class SleepCommand;

class IEventArg;

class TriggerEventArg;

template<typename T>
class UserDataEventArg;

class BaseFrameCommandProcessor;

template<typename TLock>
class BaseMainCommandProcessor;

class BaseThreadCommandProcessor;

class MainCommandProcessor;

template<typename TLock>
class QueueCommandProcessor;

class SimpleMainCommandProcessor;

class ThreadCommandProcessor;

class ITrigger;

class ZipReader;

struct ZipFileInfo;

class AppCompatibility;

class ConfigManager;

class PackageInfo;

class ServerConfig;

class ServerConfigItem;

class ServerList;

class ServerListItem;

class ServerUsageItem;

class UpdateServer;

template<typename T,template<typename T1> class TPoint>
class AABBBox_t;

class Color3F;

class Color3B;

class Color4F;

class Color4B;

template<typename T>
class Cube;

template<typename T>
class Ellipse;

class Quaternion;

class Matrix3;

class EulerAngle;

class Geometry;

class GeometryAlgorithm;

class GeometryFactory;

template<typename T>
class Line2;

template<typename T>
class Line3;

class Matrix;

class Matrix2;

class Matrix4;

class Matrix43;

template<typename T>
class Padding4;

template<typename T>
class Point2;

template<typename T>
class Point3;

template<typename T>
class Point4;

template<typename T>
class Polygon;

template<typename T>
class Quad;

template<typename T>
class Range;

template<typename T>
class Rect2;

template<typename T>
class Rotation2;

template<typename T>
class Rotation3;

template<typename T>
class Scale2;

template<typename T>
class Scale3;

struct ScrollDirection;

template<typename T>
class Segment;

template<typename T>
class Size2;

template<typename T>
class Size3;

template<typename T>
class Thickness;

template<typename T,template<typename T1> class TPoint>
class Triangle_t;

class Graph;

class GraphCapabilityEdge;

class GraphEdge;

class GraphNode;

class GraphPath;

class GridCell;

template<typename TCell, typename TCellCompare >
class GridMap;

class BoneMoveable;

class DefaultMoveable;

class MatrixMoveable;

class Mover;

class SRTMoveable;

class TransformFactory;

class ShapeVertex;

class TextureNormalVertex;

class TextureVertex;

class CRC32C;

class HasherFactory;

class IHasher;

class MD5;

class SHA1;

class Directory;

class File;

class FileId;

class FileIdRef;

class FileInfo;

class FileSystem;

class IFileLoadable;

class MemoryFileAutoRegister;

class Path;

class FileMapNameItem;

class FileMapOrderItem;

class FileMapTagItem;

class DirectoryPackage;

class IPackage;

class MemoryPackage;

class PackageFactory;

class ZipPackage;

class BinaryBlockReadStream;

class BinaryBlockWriteStream;

class BinaryPackage;

struct BinaryPackageBlockHeader;

struct BinaryPackageHeader;

class DirectoryEntry;

class FileAttribute;

class FileEntry;

class FileStorage;

class BlockReadStream;

class BlockWriteStream;

class BufferStream;

class BlockCodeReadStream;

class BlockCodeWriteStream;

class FileStream;

class HashStream;

class IStream;

class MemoryStream;

class SpanStream;

class CallbackLogger;

class FileLogger;

class ILogger;

class Log;

class AndroidTraceLogger;

class IOSConsoleLogger;

class LinuxConsoleLogger;

class WindowsConsoleLogger;

class WindowsTraceLogger;

class MathStrategy;

class NormalDistribution;

class IScrollMathModel;

class SpringScrollMathModel;

class StaticScrollMathModel;

class Random;

class RandomAlgorithm;

template<typename T>
struct DefaultProbalityFunc;

template<typename T, typename TUserData>
struct DefaultPredicateFunc;

class ByteBuffer;

template<typename T>
class MemoryData;

class BaseCustomMessage;

template<typename TRequest,typename TResponse>
class BaseMessage;

template<typename TRequest,typename TResponse>
class BaseRequestMessage;

class IMessage;

class MessageDispatcher;

class MessageEventArg;

class MessageFactory;

class IMessageHandler;

class MessageHandlerFactory;

class MockMessageHandler;

class TcpMessageHandler;

class GlobalDownloadingProgressEventArg;

class HTTPClient;

class HTTPFileDownloader;

class HTTPMemoryDownloader;

class IHTTPDownloader;

class SingleDownloadingProgressEventArg;

template<typename T, bool TIsAtomic >
struct AutoIncreaseId;

template <typename T>
class Delegate;

template<class R, class ...A>
class Delegate<R(A...)>;

template<typename FuncSignature>
class Event;

template<typename T>
struct IClone;

template<typename T>
struct ICopyFrom;

class IInitializable;

template<typename T>
struct INonCopyable;

class ISerializable;

class ISettings;

template<bool TIsAtomic >
class ISharable;

template<bool TIsAtomic >
class ISharableWithName;

struct IUpdatable;

template<typename T>
class IVisitor;

template<typename T>
class LazyValue;

template<typename T>
class Nullable;

template<typename T, uint TIndex>
class OverrideValue;

template<typename T>
class Singleton;

class StaticConstructor;

template<typename T>
class SwapValue;

template<typename T>
class Sweeper;

template<typename T>
class VaryValue;

class BehaviorConfig;

class BehaviorFactory;

class IActBehavior;

class IBehavior;

struct IfBehavior;

class IPredicateBehavior;

struct SwitchBehavior;

class BrainCache;

class BrainFactory;

class IBrain;

class IBrainBody;

class IBrainMemory;

class ComponentFactory;

class IComponent;

class IEntity;

class IScriptComponent;

class DeprecationManager;

template<size_t TSize, typename TId, typename FuncSignature, bool IsPoolEnabled >
class ArrayObjectFactory;

template<size_t TSize, typename TId, typename TBase, typename... TArgs, bool IsPoolEnabled>
class ArrayObjectFactory<TSize, TId, TBase*(TArgs...), IsPoolEnabled>;

template <typename TId, typename TObject, typename TKeyHashCoder , typename TObjectHashCoder , typename TKeyCompare >
class IdObjectCache;

template <typename TId, typename TObject, typename TObjectNewer , typename THashCoder , typename TKeyCompare , typename TObjectCompare >
class IdSingleObjectPool;

template<typename TId, typename FuncSignature, typename THashCoder , bool IsPoolEnabled >
class MapObjectFactory;

template<typename TId, typename TBase, typename... TArgs, typename THashCoder, bool IsPoolEnabled>
class MapObjectFactory<TId, TBase*(TArgs...), THashCoder, IsPoolEnabled>;

template <typename T>
class ObjectStack;

template<typename T>
class SharableObjectFactory;

template <typename TObject, typename TObjectCompare , typename TObjectNewer >
class SingleObjectPool;

struct AndPredicate;

struct FalsePredicate;

struct IPredicate;

struct NotPredicate;

struct OrPredicate;

class PredicateConfig;

class PredicateFactory;

struct TruePredicate;

struct XorPredicate;

template<typename TDevided, typename T, size_t TSize>
class EmbededPropertyUnit;

template<typename T>
struct INotifyPropertyChanged;

template<typename T>
class IProperty;

template<typename TClass, typename T>
class IPropertyPtr;

class PropertyChangedEventArg;

template<typename TKey, typename TValue, typename TKeyHashCoder , typename TValueHashCoder , typename TKeyCompare , typename TValueCompare >
class PropertySet;

template<typename TIndex, typename T, size_t TSize, typename TCompare >
class PropertyUnit;

class StringPropertySet;

template<typename T, typename TDeleter >
class LazyStrongPtr;

template<typename T>
class NotNullPtr;

class RTTIClass;

class RTTIObject;

class DefaultRunnable;

struct IRunnable;

class IState;

class IStateConnector;

class StateAutoConnector;

class StateEventConnector;

class StateFactory;

class StateMachine;

class StateMachineModel;

class StateMachineModelConfig;

class AutoStopWatch;

class PerformanceCounter;

class ProfileManager;

class ProfileNode;

class ProfileSample;

class StopWatch;

class ScriptEngine;

class ScriptModule;

class ScriptObject;

template<typename T,bool TIsResetKey>
class SecurityValueAutoUnlock;

template<typename T,bool TIsResetKey>
class SecurityValue;

template<typename T>
class ISirenConfig;

template <typename TStream>
class BaseBinaryReader;

class BaseBinarySizeCounter;

template <typename TStream>
class BaseBinaryWriter;

template <typename TStream>
class CompactBinaryReader;

class CompactBinarySizeCounter;

template <typename TStream>
class CompactBinaryWriter;

template <typename TStream>
class FastBinaryReader;

class FastBinarySizeCounter;

template <typename TStream>
class FastBinaryWriter;

template <typename TStream>
class JsonInputStream;

template <typename TStream>
class JsonOutputStream;

template <typename TStream>
class JsonReader;

template <typename TStream>
class JsonWriter;

template<typename TProperty>
class BasicPropertyMetadata;

struct DynamicSchemaVisitor;

struct StaticSchemaVisitor;

template<typename TProperty>
class StructPropertyMetadata;

template<typename T>
class BaseString;

template<typename T>
class TIStringWrapper;

template<typename T>
class THeapString;

template<typename T, size_t TBufferSize, bool TIsInitNULL>
class TStackString;

template< size_t TBufferSize, bool TIsInitNULL>
class StackString;

template< size_t TBufferSize, bool TIsInitNULL>
class WStackString;

template<typename T>
class TStringRef;

class FuckyString;

class FuckyStringNode;

class StringPool;

class WStringPool;

class RandomNameConfig;

class RandomNameConfigItem;

class IdStringTable;

class StringId;

class StringNameItem;

class StringTable;

class Environment;

class PublishTarget;

class System;

struct MyStreamInfoStruct;

class FrameTask;

class FrameTaskStage;

class Task;

class TaskStage;

class FramePulseThread;

class IWaitable;

class Mutex;

class NonRecursiveMutex;

class NoMutex;

class PooledThread;

class PulseThread;

class ReadWriteLock;

class ScopedLock;

class ScopedNoLock;

class ScopedUnlock;

class ScopedUnlockThenLock;

class Semaphore;

class Thread;

class ThreadEvent;

class MutexImp;

class SemaphoreImp;

class ReadWriteLockImp;

class ThreadImp;

template<typename THost>
class NoThreadingLockPolicy;

class Lock;

template<typename THost>
class ClassThreadingLockPolicy;

template<typename THost>
class ObjectThreadingLockPolicy;

class ThreadPool;

class ThreadPoolTimer;

class ThreadPoolWait;

class ThreadPoolWork;

class ThreadEventImp;

struct ThreadEventMultipleWaiter;

struct ThreadEventMultipleWaiterIndex;

class ThreadPoolImp;

class ThreadPoolTimerImp;

class ThreadPoolWaitImp;

class ThreadPoolWorkImp;

class DateTime;

class Guid;

class TimeSpan;

class Version;

#pragma region typedef
typedef Delegate<void(void* sender, IEventArg&)> EventHandler;
typedef Delegate<void(void*, IEventArg)> DummyEventHandler;
typedef Cube<uint32> CubeI;
typedef Cube<float> CubeF;
typedef CubeF BoundingBox;
typedef LazyValue<BoundingBox> LazyBoundingBox;
typedef Ellipse<int> EllipseI;
typedef Ellipse<uint> EllipseU;
typedef Ellipse<float> EllipseF;
typedef Line2<int> Line2I;
typedef Line2<float> Line2F;
typedef Line3<int> Line3I;
typedef Line3<float> Line3F;
typedef LazyValue<Matrix> LazyMatrix;
typedef LazyValue<Matrix3> LazyMatrix3;
typedef LazyValue<Matrix4> LazyMatrix4;
typedef LazyValue<Matrix43> LazyMatrix43;
typedef Padding4<int> Padding4I;
typedef Padding4<float> Padding4F;
typedef Point2<int> Point2I;
typedef Point2<uint> Point2U;
typedef Point2<float> Point2F;
typedef Point2I Vector2I;
typedef Point2F Vector2F;
typedef Point3<int> Point3I;
typedef Point3<float> Point3F;
typedef Point3I Vector3I;
typedef Point3F Vector3F;
typedef Point4<int> Point4I;
typedef Point4<uint> Point4U;
typedef Point4<float> Point4F;
typedef Point4I Vector4I;
typedef Point4U Vector4U;
typedef Point4F Vector4F;
typedef Polygon<int> PolygonI;
typedef Polygon<float> PolygonF;
typedef Quad<Color4F> QuadColor;
typedef Quad<Point2<float> > QuadTexCoord;
typedef Quad<Point3<float> > QuadVertex3;
typedef Quad<Point2<float> > QuadVertex2;
typedef Quad<TextureVertex> QuadTextureVertex;
typedef Quad<TextureNormalVertex> QuadTextureNormalVertex;
typedef Quad<ShapeVertex> QuadShapeVertex;
typedef Range<int> RangeI;
typedef Range<uint32> RangeU;
typedef Range<size_t> RangeS;
typedef Range<float> RangeF;
typedef Rect2<int> Rect2I;
typedef Rect2<uint> Rect2U;
typedef Rect2<float> Rect2F;
typedef Rect2F BoundingBox2;
typedef LazyValue<BoundingBox2> LazyBoundingBox2;
typedef Rotation2<float> Rotation2F;
typedef Rotation3<float> Rotation3F;
typedef Scale2<float> Scale2F;
typedef Scale3<int> Scale3I;
typedef Scale3<float> Scale3F;
typedef Segment<int> SegmentI;
typedef Segment<uint32> SegmentU;
typedef Segment<size_t> SegmentS;
typedef Segment<float> SegmentF;
typedef Size2<int> Size2I;
typedef Size2<uint32> Size2U;
typedef Size2<float> Size2F;
typedef Size3<uint32> Size3U;
typedef Size3<int> Size3I;
typedef Size3<float> Size3F;
typedef Thickness<float> ThicknessF;
typedef Triangle_t<int,Point2> Triangle2I;
typedef Triangle_t<float,Point2> Triangle2F;
typedef Triangle_t<int,Point3> Triangle3I;
typedef Triangle_t<float,Point3> Triangle3F;
typedef Triangle3I Triangle;
typedef Triangle3F TriangleF;
typedef MemoryData<short> MemoryShortData;
typedef MemoryData<byte> MemoryByteData;
typedef MemoryData<char> MemoryCharData;
typedef MemoryData<wchar_t> MemoryWCharData;
typedef MemoryData<int> MemoryIntData;
typedef MemoryData<uint> MemoryUIntData;
typedef MemoryData<byte> Blob;
typedef Delegate<void()> Action0;
typedef Delegate<void(void*)> Action1;
typedef SecurityValue<int,false> SecurityInt;
typedef SecurityValue<int,true> StrongSecurityInt;
typedef THeapString<char> HeapString;
typedef THeapString<wchar_t> WHeapString;
typedef TStringRef<char> StringRef;
typedef TStringRef<wchar_t> WStringRef;
#pragma endregion typedef
MEDUSA_END;
