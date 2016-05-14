#pragma once
#include "CorePlatform/CorePlatform.h"
MEDUSA_BEGIN;
namespace placeholder
{
	template <int N>
	struct TPlaceHolder;
	
}
class MedusaCoreModule;

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

class SirenLuaExtension;

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

class ConfigManager;

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

class ApplePropertyListNode;

struct BinaryHeader;

class ApplePropertyListReader;

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

class BlockCodeReadStream;

class BlockCodeWriteStream;

class BlockReadStream;

class BlockWriteStream;

class BufferStream;

class FileCodeWriteStream;

class FileStream;

class HashStream;

class IStream;

class IStreamable;

class MemoryStream;

class SpanStream;

class StringStream;

class CallbackLogger;

class FileLogger;

class ILogger;

class Log;

class AndroidTraceLogger;

class IOSConsoleLogger;

class LinuxConsoleLogger;

class WindowsConsoleLogger;

class WindowsTraceLogger;

class ILuaObject;

template<typename TClass>
class LuaClass;

template<typename TEnum>
class LuaEnum;

class LuaMachine;

class LuaModule;

template<typename T>
struct LuaCustomObjectPtr;

template<typename T>
class LuaObjectPtr;

template<typename T>
class LuaObjectValue;

class LuaRef;

class LuaSelector;

class LuaStack;

class LuaStackAutoReset;

class LuaState;

class LuaTable;

template<typename TDerived>
class TLuaTable;

class MathStrategy;

class NormalDistribution;

class Random;

class RandomAlgorithm;

template<typename T>
struct DefaultProbalityFunc;

template<typename T, typename TUserData>
struct DefaultPredicateFunc;

class ByteBuffer;

template<typename T>
class TMemoryData;

struct DelegateModule;

class IModule;

class GlobalDownloadingProgressEventArg;

class HTTPClient;

class HTTPFileDownloader;

class HTTPMemoryDownloader;

class IHTTPDownloader;

class SingleDownloadingProgressEventArg;

template<typename TRequest,typename TResponse>
class BaseMessage;

template<typename TRequest,typename TResponse>
class BaseRequestMessage;

class IMessage;

class MessageDispatcher;

class MessageEventArg;

class MessageFactory;

class BaseSocketService;

class BaseThreadService;

class IService;

class MockService;

class ServerConfig;

class ServerConfigItem;

class ServiceFactory;

class ServiceInfo;

class TcpClientService;

class AddressInfo;

class HostInfo;

class ProtocolInfo;

class Socket;

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

template<typename TId, typename FuncSignature, typename THashCoder >
class StaticObjectFactory;

template<typename TId, typename TBase, typename... TArgs, typename THashCoder>
class StaticObjectFactory<TId, TBase*(TArgs...), THashCoder>;

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

class AutoStopWatch;

class PerformanceCounter;

class ProfileManager;

class ProfileNode;

class ProfileSample;

class StopWatch;

class ScriptEngine;

template<typename T,bool TIsResetKey>
class SecurityValueAutoUnlock;

template<typename T,bool TIsResetKey>
class SecurityValue;

template<typename T>
class ISirenConfig;

class SirenObject;

class BaseSirenBinaryReader;

class BaseSirenBinarySizeCounter;

class BaseSirenBinaryWriter;

class SirenCompactBinaryReader;

class SirenCompactBinarySizeCounter;

class SirenCompactBinaryWriter;

class SirenFastBinaryReader;

class SirenFastBinarySizeCounter;

class SirenFastBinaryWriter;

class SirenJsonInputStream;

class SirenJsonOutputStream;

class SirenJsonReader;

class SirenJsonWriter;

class SirenLuaReader;

class SirenLuaWriter;

class SirenAssembly;

template<typename TField>
class SirenBasicFieldMetadata;

class SirenMachine;

template<typename TField>
class SirenStructFieldMetadata;

class SirenTextParser;

class ISirenAttribute;

class SirenClassAttribute;

class SirenEnumAttribute;

class SirenFieldAttribute;

class SirenField;

class ISirenFunction;

class SirenAttributeFunction;

class BaseSirenCustomType;

class ISirenType;

class SirenBuildinDictionary;

class SirenBuildinList;

class SirenBuildinType;

class SirenBuildinBool;

class SirenBuildinInt8;

class SirenBuildinUInt8;

class SirenBuildinInt16;

class SirenBuildinUInt16;

class SirenBuildinInt32;

class SirenBuildinUInt32;

class SirenBuildinInt64;

class SirenBuildinUInt64;

class SirenBuildinFloat;

class SirenBuildinDouble;

class SirenBuildinString;

class SirenBuildinBlob;

class SirenCustomClass;

class SirenCustomEnum;

class ISirenReader;

class ISirenSizeCounter;

class ISirenWriter;

class SirenObjectDeserializer;

class SirenObjectSerializer;

class SirenReaderWriter;

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

class RecursiveMutex;

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
typedef TMemoryData<short> MemoryShortData;
typedef TMemoryData<byte> MemoryData;
typedef TMemoryData<char> MemoryCharData;
typedef TMemoryData<wchar_t> MemoryWCharData;
typedef TMemoryData<int> MemoryIntData;
typedef TMemoryData<uint> MemoryUIntData;
typedef TMemoryData<float> MemoryFloatData;
typedef TMemoryData<byte> Blob;
typedef Delegate<void()> Action0;
typedef Delegate<void(void*)> Action1;
typedef Delegate<bool()> PredicateFunc;
typedef SecurityValue<int,false> SecurityInt;
typedef SecurityValue<int,true> StrongSecurityInt;
typedef THeapString<char> HeapString;
typedef THeapString<wchar_t> WHeapString;
typedef TStringRef<char> StringRef;
typedef TStringRef<wchar_t> WStringRef;
#pragma endregion typedef
MEDUSA_END;
//MANUAL_BEGIN
MEDUSA_BEGIN;
#ifdef MEDUSA_LUA
typedef LuaRef ScriptObject;
typedef LuaState ScriptState;
typedef LuaMachine ScriptMachine;
#endif
MEDUSA_END;
//MANUAL_END