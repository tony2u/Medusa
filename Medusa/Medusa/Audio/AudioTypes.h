// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Pattern/TuplePattern.h"
#include "Core/Geometry/Point3.h"

#ifdef MEDUSA_AL
#if defined(MEDUSA_WINDOWS)||defined(MEDUSA_ANDROID)
#define AL_LIBTYPE_STATIC

#include "Lib/Common/OpenAL/al.h"
#include "Lib/Common/OpenAL/alc.h"
#else
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif
#endif

MEDUSA_BEGIN;

#ifdef MEDUSA_AL

enum class AudioErrorCode
{
	Success = AL_NO_ERROR,
	InvalidName = AL_INVALID_NAME,
	InvalidEnum = AL_INVALID_ENUM,
	InvalidValue = AL_INVALID_VALUE,
	InvalidOperation = AL_INVALID_OPERATION,
	OutOfMemory = AL_OUT_OF_MEMORY
};

enum class AudioContextErrorCode
{
	Success = ALC_NO_ERROR,
	InvalidDevice = ALC_INVALID_DEVICE,
	InvalidEnum = ALC_INVALID_ENUM,
	InvalidValue = ALC_INVALID_VALUE,
	InvalidContext = ALC_INVALID_CONTEXT,
	OutOfMemory = ALC_OUT_OF_MEMORY
};

enum class AudioFormat
{
	Mono8 = AL_FORMAT_MONO8,
	Mono16 = AL_FORMAT_MONO16,
	Stereo8 = AL_FORMAT_STEREO8,
	Stereo16 = AL_FORMAT_STEREO16
};

enum class AudioContextAttribute
{
	Frequency = ALC_FREQUENCY,
	MonoSources = ALC_MONO_SOURCES,
	StereoSources = ALC_STEREO_SOURCES,
	RefreshHz = ALC_REFRESH,
	IsSync = ALC_SYNC
};

enum class AudioBooleanName
{
	None = 0
};

enum class AudioBooleanArrayName
{
	None = 0
};


enum class AudioFloatName
{
	DopplerFactor = AL_DOPPLER_FACTOR,
	SpeedOfSound = AL_SPEED_OF_SOUND
};

enum class AudioFloatArrayName
{
	None = 0
};

enum class AudioIntegerName
{
	DistanceModel = AL_DISTANCE_MODEL
};


enum class AudioIntegerArrayName
{
	None = 0
};

enum class AudioStringName
{
	Vendor = AL_VENDOR,
	Version = AL_VERSION,
	Renderer = AL_RENDERER,
	Extensions = AL_EXTENSIONS
};

enum class AudioContextStringName
{
	DefaultDeviceName = ALC_DEFAULT_DEVICE_SPECIFIER,
	DefaultCaptureDeviceName = ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER,
	AllDeviceNames = ALC_DEVICE_SPECIFIER,
	AllCaptureDeviceNames = ALC_CAPTURE_DEVICE_SPECIFIER,
	Extensions = ALC_EXTENSIONS
};


enum class AudioContextIntegerName
{
	MajorVersion = ALC_MAJOR_VERSION,
	MinorVersion = ALC_MINOR_VERSION,
	AttributeSize = ALC_ATTRIBUTES_SIZE,
	CaptureSampleCount = ALC_CAPTURE_SAMPLES,
	MonoSourceCount = ALC_MONO_SOURCES,
	StereoSourceCount = ALC_STEREO_SOURCES
};

enum class AudioContextIntegerArrayName
{
	Attributes = ALC_ALL_ATTRIBUTES
};
/**
 * Distance attenuation model.
 * Type:    ALint
 * Range:   [AL_NONE, AL_INVERSE_DISTANCE, AL_INVERSE_DISTANCE_CLAMPED,
 *           AL_LINEAR_DISTANCE, AL_LINEAR_DISTANCE_CLAMPED,
 *           AL_EXPONENT_DISTANCE, AL_EXPONENT_DISTANCE_CLAMPED]
 * Default: AL_INVERSE_DISTANCE_CLAMPED
 *
 * The model by which sources attenuate with distance.
 *
 * None     - No distance attenuation.
 * Inverse  - Doubling the distance halves the source gain.
 * Linear   - Linear gain scaling between the reference and max distances.
 * Exponent - Exponential gain dropoff.
 *
 * Clamped variations work like the non-clamped counterparts, except the
 * distance calculated is clamped between the reference and max distances.
 */
enum class AudioDistanceModel
{
	None = AL_NONE,
	Inverse = AL_INVERSE_DISTANCE,
	InverseClamped = AL_INVERSE_DISTANCE_CLAMPED,
	Linear = AL_LINEAR_DISTANCE,
	LinearClamped = AL_LINEAR_DISTANCE_CLAMPED,
	Exponent = AL_EXPONENT_DISTANCE,
	ExponentClamped = AL_EXPONENT_DISTANCE_CLAMPED
};



enum class AudioBufferProperty
{
	Frequency = AL_FREQUENCY,
	BitsPerSample = AL_BITS,
	ChannelCount = AL_CHANNELS,
	DataSize = AL_SIZE
};

enum class AudioSourceType
{
	Static = AL_STATIC,	//A Source is Static if a Buffer has been attached using AL_BUFFER.
	Streaming = AL_STREAMING,	//A Source is Streaming if one or more Buffers have been attached using alSourceQueueBuffers
	ChannelCount = AL_UNDETERMINED
};	//A Source is Undetermined when it has the nullptr buffer attached using AL_BUFFER);

enum class AudioSourceBooleanProperty
{
	IsRelative = AL_SOURCE_RELATIVE,
	IsLooping = AL_LOOPING
};


enum class AudioSourceIntegerProperty
{
	Buffer = AL_BUFFER,
	SourceState = AL_SOURCE_STATE,
	BufferQueuedCount = AL_BUFFERS_QUEUED,
	BufferProcessedCount = AL_BUFFERS_PROCESSED,
	SecondOffset = AL_SEC_OFFSET,
	SampleOffset = AL_SAMPLE_OFFSET,
	ByteOffset = AL_BYTE_OFFSET,
	SourceType = AL_SOURCE_TYPE
};

enum class AudioSourceFloatProperty
{
	Pitch = AL_PITCH,
	Gain = AL_GAIN,
	MinGain = AL_MIN_GAIN,
	MaxGain = AL_MAX_GAIN,
	MaxDistance = AL_MAX_DISTANCE,
	RolloffFactor = AL_ROLLOFF_FACTOR,
	ConeInnerAngle = AL_CONE_INNER_ANGLE,
	ConneOuterAngle = AL_CONE_OUTER_ANGLE,
	ConeOuterGain = AL_CONE_OUTER_GAIN,
	ReferenceDistance = AL_REFERENCE_DISTANCE
};

enum class AudioSourceFloatArrayProperty
{
	Position = AL_POSITION,
	Velocity = AL_VELOCITY,
	Direction = AL_DIRECTION
};

enum class AudioSourceState
{
	Initial = AL_INITIAL,
	Playing = AL_PLAYING,
	Paused = AL_PAUSED,
	Stopped = AL_STOPPED
};

MEDUSA_TUPLE_2(AudioListenerOrientation, Vector3F, Forward, Vector3F, Up);

#endif

MEDUSA_END;