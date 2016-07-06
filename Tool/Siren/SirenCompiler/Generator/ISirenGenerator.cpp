// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "ISirenGenerator.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/IO/Directory.h"



ISirenGenerator::ISirenGenerator(SirenAssembly& assembly)
	:mAssembly(assembly)
{

}

bool ISirenGenerator::Run() const
{

	if (mTypeName != nullptr)
	{
		auto* type = mAssembly.FindCustomType(mTypeName);
		if (type == nullptr)
		{
			Log::FormatError("Cannot find type:{}", mTypeName);
			return false;
		}

		return GenerateType(*type);
	}
	else
	{
		//generate all type
		for (auto typePair : mAssembly.Types())
		{
			RETURN_FALSE_IF_FALSE(GenerateType(*typePair.Value));
		}
	}

	return true;
}

void ISirenGenerator::SetTemplateName(StringRef val)
{
	mTemplateName = val;
}

void ISirenGenerator::UpdateFile(StringRef path, StringRef content)
{
	if (!File::Exists(path))
	{
		Directory::CreateDirectoryForFile(path);

		File::WriteAllText(path, content);
		Log::FormatInfo("Generate:{0}", path);
		return;
	}

	auto oldText = File::ReadAllText(path);
	if (oldText != content)
	{
		File::WriteAllText(path, content);
		Log::FormatInfo("Generate:{0}", path);
	}
	else
	{
		Log::FormatInfo("Same:{0}", path);
	}
}

void ISirenGenerator::ReplaceBeginEnd(HeapString& text, StringRef begin, StringRef end, StringRef content)
{
	if (content.IsEmpty())
	{
		return;
	}

	intp index1 = text.IndexOf(begin);
	if (index1 < 0)
	{
		return;
	}


	intp index2 = text.IndexOf(end);
	if (index2 < 0 || index2 < index1)
	{
		return;
	}

	text.RemoveAt(index1 + begin.Length(), index2 - index1 - begin.Length());
	text.Insert(index1 + begin.Length(), content);
}

