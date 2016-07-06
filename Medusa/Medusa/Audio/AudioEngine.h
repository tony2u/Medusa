// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_AL
#include "Core/Pattern/Singleton.h"
#include "Core/Log/Log.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Core/IO/FileIdRef.h"
#include "Audio/AudioTypes.h"
#include "Core/Task/FrameTask.h"
#include "StaticAudioSource.h"
#include "StreamAudioSource.h"


MEDUSA_BEGIN;

class AudioEngine :public Singleton<AudioEngine>, public FrameTask
{
	friend class Singleton<AudioEngine>;
protected:
	AudioEngine(void);
	~AudioEngine(void);

public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	Share<IAudioSource> FindSource(const StringRef& sourceName)const;
	AudioSourceState GetSourceState(const StringRef& sourceName)const;

	bool IsEffectEnabled() const { return mEffectEnabled; }
	void EnableEffect(bool val) { mEffectEnabled = val; }

	bool IsMusicEnabled() const { return mMusicEnabled; }
	void EnableMusic(bool val) { mMusicEnabled = val; }
public:

#pragma region Effect
	Share<StaticAudioSource> PlayEffect(const FileIdRef& fileId, bool isRepeat = false, bool isPlay = true, const StringRef& sourceName = StringRef::Empty);
	Share<StaticAudioSource> PlayEffectSequence(const List<FileIdRef>& names, bool isRepeat = false, bool isPlay = true, const StringRef& sourceName = StringRef::Empty);
	Share<StaticAudioSource> PlayEffectSequence(const FileIdRef& fileId1, const FileIdRef& fileId2, bool isRepeat = false, bool isPlay = true, const StringRef& sourceName = StringRef::Empty);
	Share<StaticAudioSource> PlayEffectSequence(const FileIdRef& fileId1, const FileIdRef& fileId2, const FileIdRef& fileId3, bool isRepeat = false, bool isPlay = true, const StringRef& sourceName = StringRef::Empty);


	Share<StaticAudioSource> FindEffect(const StringRef& sourceName)const;
	void PauseAllEffect();
	void ResumeAllEffect();
	void StopAllEffect();
	AudioSourceState GetEffectState(const StringRef& sourceName)const;
#pragma endregion Effect

#pragma region Music

	Share<StreamAudioSource> PlayMusic(const FileIdRef& fileId, bool isRepeat = false, bool isPlay = true, const StringRef& sourceName = StringRef::Empty);
	Share<StreamAudioSource> FindMusic(const StringRef& sourceName)const;

	void PauseAllMusic();
	void ResumeAllMusic();
	void StopAllMusic();

	AudioSourceState GetMusicState(const StringRef& sourceName)const;

#pragma endregion Music
protected:
	void OnUpdate(float dt)override;


protected:
	List<Share<StaticAudioSource>> mEffectSources;
	Dictionary<HeapString, Share<StaticAudioSource>> mEffectSourceDict;
	List<size_t> mEffectDeadSourceIndexes;

	List<Share<StreamAudioSource>> mMusicSources;
	Dictionary<HeapString, Share<StreamAudioSource>> mMusicSourceDict;
	List<size_t> mMusicDeadSourceIndexes;

	bool mEffectEnabled;

	bool mMusicEnabled;

};

MEDUSA_END;
#endif