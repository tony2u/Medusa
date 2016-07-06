// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_AL
#include "AudioEngine.h"
#include "Audio/Device/AudioDevice.h"
#include "Audio/IAudioSource.h"
#include "Core/Collection/Linq.h"
#include "Audio/StaticAudioSource.h"
#include "Audio/FileStreamAudioSource.h"
#include "Resource/Audio/AudioFactory.h"
#include "Core/IO/FileSystem.h"


MEDUSA_BEGIN;

AudioEngine::AudioEngine(void)
{
	mEffectEnabled=true;
	mMusicEnabled=true;
}

AudioEngine::~AudioEngine(void)
{
}

bool AudioEngine::Initialize()
{
	return true;
}


bool AudioEngine::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(FrameTask::Uninitialize());

	StopAllEffect();
	StopAllMusic();

	mEffectSources.Clear();
	mEffectSourceDict.Clear();

	mMusicSources.Clear();
	mMusicSourceDict.Clear();

	return true;
}

void AudioEngine::OnUpdate(float dt)
{
	{
		//effect
		size_t sourceCount=mEffectSources.Count();
		RETURN_IF_ZERO(sourceCount);
		FOR_EACH_SIZE(i,sourceCount)
		{
			auto source=mEffectSources[i];
			if (source->IsEnd())
			{
				source->FireEndEvent();
				//fire event
				if (!source->IsShared())
				{
					mEffectDeadSourceIndexes.Add(i);
					const StringRef& sourceName=source->Name();
					mEffectSourceDict.RemoveOtherKey(sourceName,sourceName.HashCode());
					source->Release();
				}
			}

			
		}

		Linq::DeleteIndexes(mEffectSources,mEffectDeadSourceIndexes);
		mEffectDeadSourceIndexes.Clear();
	}
	{
		//music
		size_t sourceCount=mMusicSources.Count();
		RETURN_IF_ZERO(sourceCount);
		FOR_EACH_SIZE(i,sourceCount)
		{
			auto source=mMusicSources[i];
			if (!source->IsShared()&&source->IsEnd())
			{
				mMusicDeadSourceIndexes.Add(i);
				const StringRef& sourceName=source->Name();
				mMusicSourceDict.RemoveOtherKey(sourceName,sourceName.HashCode());

				source->Release();
			}
		}

		Linq::DeleteIndexes(mMusicSources,mMusicDeadSourceIndexes);
		mMusicDeadSourceIndexes.Clear();
	}


}

Share<IAudioSource> AudioEngine::FindSource(const StringRef& sourceName) const
{
	auto source=FindEffect(sourceName);
	RETURN_SELF_IF_NOT_NULL(source);
	return FindMusic(sourceName);
}


AudioSourceState AudioEngine::GetSourceState(const StringRef& sourceName) const
{
	auto source=FindSource(sourceName);
	if (source!=nullptr)
	{
		return source->GetState();
	}
	return AudioSourceState::Initial;
}

#pragma region Effect

Share<StaticAudioSource> AudioEngine::PlayEffect( const FileIdRef& fileId,bool isRepeat/*=false*/ ,bool isPlay/*=true*/,const StringRef& sourceName/*=StringRef::Empty*/)
{
	RETURN_NULL_IF_FALSE(mEffectEnabled);
	RETURN_NULL_IF_FALSE(fileId.IsValid());
	auto buffer=AudioFactory::Instance().CreateFromFile(fileId);
	Share<StaticAudioSource> source=new StaticAudioSource(sourceName);
	source->SetIsLooping(isRepeat);
	source->SetBuffer(buffer);

	mEffectSources.Add(source);
	if (!sourceName.IsEmpty())
	{
		mEffectSourceDict.Add(sourceName,source);
	}
	if (isPlay)
	{
		source->Play();
	}
	return source;
}

Share<StaticAudioSource> AudioEngine::PlayEffectSequence( const List<FileIdRef>& names ,bool isRepeat/*=false*/,bool isPlay/*=true*/,const StringRef& sourceName/*=StringRef::Empty*/)
{
	RETURN_NULL_IF_FALSE(mEffectEnabled);
	Share<StaticAudioSource> source=new StaticAudioSource(sourceName);
	source->SetIsLooping(isRepeat);

	for (auto fileId : names)
	{
		auto buffer=AudioFactory::Instance().CreateFromFile(fileId);
		source->AddBuffer(buffer);
	}

	mEffectSources.Add(source);
	if (!sourceName.IsEmpty())
	{
		mEffectSourceDict.Add(sourceName,source);
	}

	if (isPlay)
	{
		source->Play();
	}
	return source;

}

Share<StaticAudioSource> AudioEngine::PlayEffectSequence(const FileIdRef& fileId1,const FileIdRef& fileId2,bool isRepeat/*=false*/,bool isPlay/*=true*/,const StringRef& sourceName/*=StringRef::Empty*/)
{
	RETURN_NULL_IF_FALSE(mEffectEnabled);
	Share<StaticAudioSource> source=new StaticAudioSource(sourceName);
	source->SetIsLooping(isRepeat);

	{
		auto buffer=AudioFactory::Instance().CreateFromFile(fileId1);
		source->AddBuffer(buffer);
	}

	{
		auto buffer=AudioFactory::Instance().CreateFromFile(fileId2);
		source->AddBuffer(buffer);
	}

	mEffectSources.Add(source);
	if (!sourceName.IsEmpty())
	{
		mEffectSourceDict.Add(sourceName,source);
	}

	if (isPlay)
	{
		source->Play();
	}
	return source;
}

Share<StaticAudioSource> AudioEngine::PlayEffectSequence(const FileIdRef& fileId1,const FileIdRef& fileId2,const FileIdRef& fileId3,bool isRepeat/*=false*/,bool isPlay/*=true*/,const StringRef& sourceName/*=StringRef::Empty*/)
{
	RETURN_NULL_IF_FALSE(mEffectEnabled);
	Share<StaticAudioSource> source=new StaticAudioSource(sourceName);
	source->SetIsLooping(isRepeat);

	{
		auto buffer=AudioFactory::Instance().CreateFromFile(fileId1);
		source->AddBuffer(buffer);
	}

	{
		auto buffer=AudioFactory::Instance().CreateFromFile(fileId2);
		source->AddBuffer(buffer);
	}

	{
		auto buffer=AudioFactory::Instance().CreateFromFile(fileId3);
		source->AddBuffer(buffer);
	}

	mEffectSources.Add(source);
	if (!sourceName.IsEmpty())
	{
		mEffectSourceDict.Add(sourceName,source);
	}

	if (isPlay)
	{
		source->Play();
	}
	return source;
}

Share<StaticAudioSource> AudioEngine::FindEffect(const StringRef& sourceName)const
{
	return mEffectSourceDict.GetOptionalByOtherKey(sourceName,sourceName.HashCode(),nullptr);
}

void AudioEngine::PauseAllEffect()
{
	FOR_EACH_TO(mEffectSources, Pause());
}

void AudioEngine::ResumeAllEffect()
{
	RETURN_IF_FALSE(mEffectEnabled);
	FOR_EACH_TO(mEffectSources, Resume());
}

void AudioEngine::StopAllEffect()
{
	FOR_EACH_TO(mEffectSources, Stop());
}

AudioSourceState AudioEngine::GetEffectState(const StringRef& sourceName) const
{
	auto source=FindEffect(sourceName);
	if (source!=nullptr)
	{
		return source->GetState();
	}
	return AudioSourceState::Initial;
}



#pragma endregion Effect
#pragma region Music

Share<StreamAudioSource> AudioEngine::PlayMusic( const FileIdRef& fileId,bool isRepeat/*=false*/ ,bool isPlay/*=true*/,const StringRef& sourceName/*=StringRef::Empty*/)
{
	RETURN_NULL_IF_FALSE(mMusicEnabled);
	Share<FileStreamAudioSource> source=new FileStreamAudioSource(sourceName);
	source->SetIsLooping(isRepeat);
	if(!source->OpenFile(fileId))
	{
		source = nullptr;
		return nullptr;
	}

	mMusicSources.Add(source);
	if (!sourceName.IsEmpty())
	{
		mMusicSourceDict.Add(sourceName,source);
	}
	if (isPlay)
	{
		source->Play();
	}
	return source;
}
Share<StreamAudioSource> AudioEngine::FindMusic(const StringRef& sourceName) const
{
	return mMusicSourceDict.GetOptionalByOtherKey(sourceName,sourceName.HashCode(),nullptr);
}

void AudioEngine::PauseAllMusic()
{
	FOR_EACH_TO(mMusicSources, Pause());
}

void AudioEngine::ResumeAllMusic()
{
	RETURN_IF_FALSE(mMusicEnabled);
	FOR_EACH_TO(mMusicSources, Resume());
}

void AudioEngine::StopAllMusic()
{
	FOR_EACH_TO(mMusicSources, Stop());
}

AudioSourceState AudioEngine::GetMusicState(const StringRef& sourceName) const
{
	auto source=FindMusic(sourceName);
	if (source!=nullptr)
	{
		return source->GetState();
	}
	return AudioSourceState::Initial;
}

#pragma endregion Music

MEDUSA_END;
#endif