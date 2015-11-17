// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Core/Log/Log.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Core/IO/FileIdRef.h"
#include "Audio/AudioTypes.h"
#include "Core/Task/FrameTask.h"

MEDUSA_BEGIN;

class AudioEngine:public Singleton<AudioEngine>,public FrameTask
{
	friend class Singleton<AudioEngine>;
protected:
	AudioEngine(void);
	~AudioEngine(void);

public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	IAudioSource* FindSource(const StringRef& sourceName)const;
	AudioSourceState GetSourceState(const StringRef& sourceName)const;

	bool IsEffectEnabled() const { return mEffectEnabled; }
	void EnableEffect(bool val) { mEffectEnabled = val; }

	bool IsMusicEnabled() const { return mMusicEnabled; }
	void EnableMusic(bool val) { mMusicEnabled = val; }
public:

#pragma region Effect
	StaticAudioSource* PlayEffect(const FileIdRef& fileId,bool isRepeat=false,bool isPlay=true,const StringRef& sourceName=StringRef::Empty);
	StaticAudioSource* PlayEffectSequence(const List<FileIdRef>& names,bool isRepeat=false,bool isPlay=true,const StringRef& sourceName=StringRef::Empty);
	StaticAudioSource* PlayEffectSequence(const FileIdRef& fileId1,const FileIdRef& fileId2,bool isRepeat=false,bool isPlay=true,const StringRef& sourceName=StringRef::Empty);
	StaticAudioSource* PlayEffectSequence(const FileIdRef& fileId1,const FileIdRef& fileId2,const FileIdRef& fileId3,bool isRepeat=false,bool isPlay=true,const StringRef& sourceName=StringRef::Empty);


	StaticAudioSource* FindEffect(const StringRef& sourceName)const;
	void PauseAllEffect();
	void ResumeAllEffect();
	void StopAllEffect();
	AudioSourceState GetEffectState(const StringRef& sourceName)const;
#pragma endregion Effect

#pragma region Music

	StreamAudioSource* PlayMusic(const FileIdRef& fileId,bool isRepeat=false,bool isPlay=true,const StringRef& sourceName=StringRef::Empty);
	StreamAudioSource* FindMusic(const StringRef& sourceName)const;

	void PauseAllMusic();
	void ResumeAllMusic();
	void StopAllMusic();

	AudioSourceState GetMusicState(const StringRef& sourceName)const;

#pragma endregion Music
protected:
	void OnUpdate(float dt)override;


protected:
	List<StaticAudioSource*> mEffectSources;
	Dictionary<HeapString,StaticAudioSource*> mEffectSourceDict;
	List<size_t> mEffectDeadSourceIndexes;

	List<StreamAudioSource*> mMusicSources;
	Dictionary<HeapString,StreamAudioSource*> mMusicSourceDict;
	List<size_t> mMusicDeadSourceIndexes;

	bool mEffectEnabled;
	
	bool mMusicEnabled;
	
};

MEDUSA_END;