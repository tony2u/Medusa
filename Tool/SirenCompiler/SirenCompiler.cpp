// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
// SirenCompiler.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include "Core/String/StringParser.h"
#include "Core/System/System.h"
#include "Core/Log/Log.h"
#include "Core/Pattern/FlagsPattern.h"
#include "docopt/docopt.h"
#include "Core/IO/File.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/StringParser.h"
#include "Core/Log/win/WindowsConsoleLogger.h"
#include "Core/Siren/Siren.h"
#include "Core/IO/FileId.h"
#include "Core/IO/FileSystem.h"
#include "Generator/SirenCppGenerator.h"

using namespace Medusa;

bool AddToAssembly(SirenAssembly& assembly, const List<HeapString>& filePaths)
{
	for (const auto& path : filePaths)
	{
		List<HeapString> outFiles;
		Directory::SearchFiles(path, outFiles);
		for (auto outFile : outFiles)
		{
			if (FileInfo::ExtractType(outFile) == FileType::mp)
			{
				FileInfo fileInfo(outFile);
				RETURN_FALSE_IF_FALSE(assembly.Parse(fileInfo.FullName()));
			}
		}

	}

	return true;
}


SirenAssembly* CreateAssembly(const StringRef& assemblyName, size_t index = 0)
{
	SirenAssembly* assembly = new SirenAssembly();

	HeapString name = Path::GetFileName(assemblyName);
	assembly->SetName(name);
	return assembly;
}

SirenAssembly* OpenAssembly(const StringRef& assemblyName, size_t index = 0)
{
	SirenAssembly* assembly = new SirenAssembly();

	if (FileSystem::Instance().ExistsFile(assemblyName))
	{
		FileStream fs(assemblyName, FileOpenMode::ReadOnly, FileDataType::Text);
		if (!assembly->LoadFromFileSystem(assemblyName))
		{
			Log::FormatError("Cannot open exists assembly:{}", assemblyName);
			SAFE_DELETE(assembly);
		}
	}
	else
	{
		HeapString name = Path::GetFileName(assemblyName);
		assembly->SetName(name);
	}
	return assembly;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Log::Initialize();
	Log::AddLogger(new WindowsConsoleLogger());
	Log::EnableLogHeader(false);
	Log::SetLevel(LogLevel::Info);

	FileSystem::Instance().Initialize();

	//http://docopt.org/
	static const char USAGE[] =
		R"(
Usage:sc
 sc create <assembly> [<file>]... [-i <include>]... [-r <reference>]...
 sc add <assembly> [<file>]... [-i <include>]... [-r <reference>]...
 sc gen <language> <assembly> [-c <class>] [-o <output>] [-t <template>] [-i <include>]...
 sc info <assembly> 
 sc merge <assembly> <assembly>...
 sc conv <assembly> <language> <type> <data>

						 sc -h | --help
 sc --version

										Options:
 -h --help  Show this screen.
 --version  Show version.
 -i <include> --include=<include>  Set include path
 -r <reference> --reference=<reference>  reference other assemblies
 -c <class> --class=<class>  only generate specified class
 -o <output> --output=<output>  Set output path
 -t <template> --template=<template>  use template

						)";

	std::map<std::string, docopt::value> args
		= docopt::docopt(USAGE,
		{ argv + 1, argv + argc },
			true,               // show help if requested
			"Medusa Siren Compiler 1.0");  // version string

	if (args["create"].asBool())
	{
		//convert text schema to binary
		HeapString assemblyName = args["<assembly>"].asStringList()[0];
		SirenAssembly* assembly = CreateAssembly(assemblyName);
		RETURN_ZERO_IF_NULL(assembly);

		auto includePaths = args["--include"].asStringList();
		for (const auto& filePath : includePaths)
		{
			FileSystem::Instance().AddDirectory(filePath);
		}


		auto references = args["--reference"].asStringList();
		for (const auto& referenceItem : references)
		{
			if (assembly->AddReference(referenceItem))
			{
				Log::FormatInfo("Load reference assembly:{}", referenceItem);
			}
			else
			{
				Log::FormatError("Cannot load reference assembly:{}", referenceItem);
				return false;
			}
		}

		auto fileStrs = args["<file>"].asStringList();
		List<HeapString> filePaths;
		for (const auto& filePath : fileStrs)
		{
			filePaths.Add(filePath);

			if (Path::IsDirectory(filePath))
			{
				FileSystem::Instance().AddDirectory(filePath);
			}
		}


		if (!filePaths.IsEmpty())
		{
			if (!AddToAssembly(*assembly, filePaths))
			{
				SAFE_DELETE(assembly);
				return false;
			}
		}

		assembly->Link();
		assembly->Execute();

		FileStream fs(assemblyName, FileOpenMode::DestoryWriteOrCreate);
		assembly->SaveTo(fs);
		SAFE_DELETE(assembly);

		Log::FormatInfo("Create assembly:{}", assemblyName);
	}
	else if (args["add"].asBool())
	{
		//convert text schema to binary
		auto includePaths = args["--include"].asStringList();
		for (const auto& filePath : includePaths)
		{
			FileSystem::Instance().AddDirectory(filePath);
		}

		HeapString assemblyName = args["<assembly>"].asStringList()[0];
		SirenAssembly* assembly = OpenAssembly(assemblyName);
		RETURN_ZERO_IF_NULL(assembly);

		auto references = args["--reference"].asStringList();
		for (const auto& referenceItem : references)
		{
			if (assembly->AddReference(referenceItem))
			{
				Log::FormatInfo("Load reference assembly:{}", referenceItem);
			}
			else
			{
				Log::FormatError("Cannot load reference assembly:{}", referenceItem);
				return false;
			}
		}

		auto fileStrs = args["<file>"].asStringList();
		List<HeapString> filePaths;
		for (const auto& filePath : fileStrs)
		{
			filePaths.Add(filePath);
			if (Path::IsDirectory(filePath))
			{
				FileSystem::Instance().AddDirectory(filePath);
			}
		}
		if (!filePaths.IsEmpty())
		{
			if (!AddToAssembly(*assembly, filePaths))
			{
				SAFE_DELETE(assembly);
				return false;
			}
		}

		assembly->Link();
		assembly->Execute();

		FileStream fs(assemblyName, FileOpenMode::DestoryWriteOrCreate);
		assembly->SaveTo(fs);
		SAFE_DELETE(assembly);

		Log::FormatInfo("Add to assembly:{}", assemblyName);

	}
	else if (args["info"].asBool())
	{
		HeapString assemblyName = args["<assembly>"].asStringList()[0];
		SirenAssembly* assembly = OpenAssembly(assemblyName);
		RETURN_ZERO_IF_NULL(assembly);
		assembly->Print();
		SAFE_DELETE(assembly);


	}
	else if (args["gen"].asBool())
	{
		auto includePaths = args["--include"].asStringList();
		for (const auto& filePath : includePaths)
		{
			FileSystem::Instance().AddDirectory(filePath);
		}

		HeapString assemblyName = args["<assembly>"].asStringList()[0];
		SirenAssembly* assembly = OpenAssembly(assemblyName);
		RETURN_ZERO_IF_NULL(assembly);
		HeapString languageName = args["<language>"].asString();
		HeapString className = args["--class"] ? args["--class"].asString() : "";
		HeapString templateName = args["--template"] ? args["--template"].asString() : "";
		HeapString outdirName = args["--output"] ? args["--output"].asString() : "";

	

		if (languageName == "cpp")
		{
			SirenCppGenerator generator(*assembly);
			generator.SetOutputPath(outdirName);
			generator.SetTemplateName(templateName);
			generator.SetTypeName(className);
			generator.Run();
		}
		else if (languageName == "c#")
		{
		}
		else
		{
			//not supported
			return -1;
		}



		SAFE_DELETE(assembly);
	}
	else if (args["merge"].asBool())
	{
		HeapString assemblyName = args["<assembly>"].asStringList()[0];
		SirenAssembly* mainAssembly = OpenAssembly(assemblyName);
		RETURN_ZERO_IF_NULL(mainAssembly);

		auto assemblyList = args["<assembly>"].asStringList();
		uint count = assemblyList.size();

		List<SirenAssembly*> assemblies;
		FOR_EACH_SIZE_BEGIN_END(i, 1, count - 1)
		{
			auto name = assemblyList[i];
			SirenAssembly* subAssembly = OpenAssembly(name);
			RETURN_ZERO_IF_NULL(subAssembly);
			assemblies.Add(subAssembly);
		}

		for (auto assembly : assemblies)
		{
			if (!mainAssembly->Merge(*assembly))
			{
				Log::FormatError("Cannot merge assembly:{}", assembly->Name());
				SAFE_DELETE(mainAssembly);
				SAFE_DELETE_COLLECTION(assemblies);
				return -1;
			}
		}

		SAFE_DELETE_COLLECTION(assemblies);
		FileStream fs(assemblyName, FileOpenMode::DestoryWriteOrCreate);
		mainAssembly->SaveTo(fs);

	}
	return 0;
}
