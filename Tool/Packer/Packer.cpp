// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
// Packer.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include "Core/IO/Stream/FileStream.h"
#include "Core/String/StringParser.h"
#include "Core/System/System.h"
#include "Core/Log/Log.h"
#include "Core/Pattern/FlagsPattern.h"
#include "docopt/docopt.h"
#include "Core/IO/File.h"
#include "Core/IO/Package/Binary/BinaryPackage.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Coder/CoderFactory.h"
#include "Core/String/StringParser.h"
#include "Core/Log/win/WindowsConsoleLogger.h"
#include "Core/IO/FileSystem.h"

using namespace Medusa;

bool AddToPackage(BinaryPackage& package, const List<HeapString>& filePaths, bool recursively = true, bool isReadonly = false, bool overwrite = true, bool deleteOriginalFile = false)
{
	for (const auto& path : filePaths)
	{
		RETURN_FALSE_IF_FALSE(package.SearchFilesToAdd(path, nullptr, recursively, isReadonly, overwrite, deleteOriginalFile));
	}


	return true;
}

BinaryPackage* OpenPackage(std::map<std::string, docopt::value> &args, size_t index = 0)
{
	std::string packageName = args["<package>"].asStringList()[index];

	BinaryPackage* package = nullptr;
	if (File::Exists(packageName))
	{
		package = new BinaryPackage(packageName, PackagePriority::Downloaded, 0);
		if (args["--key"])
		{
			std::string keyStr = args["--key"].asString();
			MemoryData keyData = MemoryData::FromStatic((const byte*)keyStr.c_str(), keyStr.size());
			package->SetKey(keyData);
		}

		if (!package->Initialize())
		{
			Log::FormatError("Cannot open exists package:{}", packageName);
			SAFE_DELETE(package);
			return nullptr;
		}

		return package;
	}
	else
	{
		//error
		Log::FormatError("Cannot open find package:{}", packageName);
		return nullptr;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	Log::Initialize();
	Log::AddLogger(new WindowsConsoleLogger());
	Log::EnableHeader(false);
	Log::SetLevel(LogLevel::Info);

	//http://docopt.org/
	static const char USAGE[] =
		R"(
Usage:mp
 mp create <package> [-e] [-d] [-r] [--readonly] [--salt] [--whole] [--block=<block>] [-k <key>] [-c <coder>]...  [<file>]...
 mp rule <package> [-k <key>] <ext>... [-c <coder>]...
 mp add <package> [-o] [-d] [-r] [--readonly] [-k <key>] <file>...
 mp remove <package> [-r] [-k <key>] <file>...
 mp info <package> [-k <key>]
 mp list <package> [-k <key>]
 mp extract <package> [-r] [-k <key>] [--output=<outdir>] [<file>]...
 mp compact <package>
 mp diff [-k <key>] <package> <package> <file>
 mp merge [-k <key>] <package> <package>...
 mp -h | --help
 mp --version

Options:
 -h --help  Show this screen.
 --version  Show version.
 -o --overwrite  Over write file
 --readonly  Make file readonly
 -r --recursive    Recurse subdirectories
 -d --delete    Delete files after add
 -e --encrypt    Encrypt file names too
 --salt			Write salt data
 --whole  Whole file coding
 -k <key> --key=<key>  Set key
 -c <coder> --coder=<coder>  Add coder
 --output=<outdir> Set output dir
 -b <block> --block=<block>  Set block size[default: 1024]
)";

	std::map<std::string, docopt::value> args
		= docopt::docopt(USAGE,
		{ argv + 1, argv + argc },
			true,               // show help if requested
			"Medusa packer 1.0");  // version string

	if (args["create"].asBool())
	{
		//add a package
		std::string packageName = args["<package>"].asStringList()[0];
		File::Delete(packageName);
		std::unique_ptr<BinaryPackage> package(new BinaryPackage(packageName, PackagePriority::Downloaded, 0));


		auto sizeStr = args["--block"].asString();
		int size = StringParser::StringTo<int>(StringRef(sizeStr));
		if (size <= 0)
		{
			Log::FormatError("Block size:{} cannot <=0", size);
			return -1;
		}

		package->SetBlockSize((uint)size);

		if (args["--key"])
		{
			std::string keyStr = args["--key"].asString();
			MemoryData keyData = MemoryData::FromStatic((const byte*)keyStr.c_str(), keyStr.size());
			package->SetKey(keyData);
		}

		if (args["--coder"])
		{
			auto coderList = args["--coder"].asStringList();
			if (coderList.size() > 8)
			{
				Log::FormatError("Only support <=8 coders");
				return -1;
			}

			uint64 coders = 0;
			for (auto coderStr : coderList)
			{
				CoderType coderType = CoderFactory::ParseCoderType(coderStr);
				if (coderType == CoderType::None)
				{
					Log::FormatError("CoderType:{} unknown.Supported:LZ4,LZMA,AES256,Base91,Base64,XXTEA,XOR", coderStr);
					return -1;
				}

				coders = CoderChain::AddCoders(coders, coderType);
			}

			package->SetCoders(coders);
		}

		bool encryptFileNames = args["--encrypt"].asBool();
		package->EnableEncryptFileNames(encryptFileNames);

		bool writeSaltData = args["--salt"].asBool();
		package->EnableWriteSaltData(writeSaltData);

		bool wholeFileCoding = args["--whole"].asBool();
		package->EnableWholeFileCoding(wholeFileCoding);

		if (!package->Initialize())
		{
			Log::FormatError("cannot create {}", packageName);
			package.reset();
			File::Delete(packageName);
			return -1;
		}

		bool recursive = args["--recursive"].asBool();
		bool deleteOriginalFiles = args["--delete"].asBool();
		bool isReadonly = args["--readonly"].asBool();


		auto fileStrs = args["<file>"].asStringList();
		List<HeapString> filePaths;
		for (const auto& filePath : fileStrs)
		{
			filePaths.Add(filePath);
		}
		if (!filePaths.IsEmpty())
		{
			if (!AddToPackage(*package, filePaths, recursive, isReadonly, true, deleteOriginalFiles))
			{
				return -1;
			}
		}

		package->Save();

	}
	else if (args["rule"].asBool())
	{
		auto* package = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(package, -1);
		auto fileExtensions = args["<ext>"].asStringList();


		uint64 coders = 0;
		if (args["--coder"])
		{
			auto coderList = args["--coder"].asStringList();
			if (coderList.size() > 8)
			{
				Log::FormatError("Only support <=8 coders");
				return -1;
			}

			for (auto coderStr : coderList)
			{
				CoderType coderType = CoderFactory::ParseCoderType(coderStr);
				if (coderType == CoderType::None)
				{
					Log::FormatError("CoderType:{} unknown.Supported:LZ4,LZMA,AES256,Base91,Base64,XXTEA,XOR", coderStr);
					return -1;
				}

				coders = CoderChain::AddCoders(coders, coderType);
			}
		}

		for (const auto& fileExt:fileExtensions)
		{
			package->AddCoderRule(fileExt, coders);
		}

		package->Save();
	}
	else if (args["add"].asBool())
	{
		auto* package = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(package, -1);

		bool recursive = args["--recursive"].asBool();;
		bool deleteOriginalFiles = args["--delete"].asBool();;
		bool isReadonly = args["--readonly"].asBool();
		bool isOverwrite = args["--overwrite"].asBool();

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

		if (!AddToPackage(*package, filePaths, recursive, isReadonly, isOverwrite, deleteOriginalFiles))
		{
			return -1;
		}

		package->Save();
	}
	else if (args["info"].asBool())
	{
		auto* package = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(package, -1);

		const auto& header = package->Header();
		Log::FormatInfo("FormatVersion:{}", header.FormatVersion());
		Log::FormatInfo("ContentVersion:{}", header.ContentVersion());
		Log::FormatInfo("BlockSize:{}", header.BlockSize());
		Log::FormatInfo("BlockCount:{}", header.BlockCount());
		Log::FormatInfo("FreeBlockCount:{}", header.FreeBlockCount());
		Log::FormatInfo("SpaceUsage:{:f3}%", 100.f*package->SpaceUsage());
		uint outFreeSpace = 0;
		float usage = package->CalculateSpaceUsageExactly(outFreeSpace);
		Log::FormatInfo("ExactlySpaceUsage:{:f3}%--{}", 100.f*usage, outFreeSpace);

		Log::FormatInfo("Hasher:{}", header.Hasher());
		Log::FormatInfo("Coders:{}", header.Coders());

	}
	else if (args["list"].asBool())
	{
		auto* package = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(package, -1);

		package->RootDir().Print(StringRef::Empty, true);
	}
	else if (args["extract"].asBool())
	{
		auto* package = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(package, -1);
		bool recursive = args["--recursive"].asBool();;

		auto fileStrs = args["<file>"].asStringList();
		List<HeapString> filePaths;
		for (const auto& filePath : fileStrs)
		{
			filePaths.Add(filePath);
		}

		HeapString outDir;
		if (args["--output"])
		{
			outDir = args["--output"].asString();
		}

		if (filePaths.IsEmpty())
		{
			package->ExtractAll(outDir);
		}
		else
		{
			for (auto& path : filePaths)
			{
				package->SearchFilesToExtract(path, recursive, outDir);
			}
		}


	}
	else if (args["remove"].asBool())
	{
		auto* package = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(package, -1);
		bool recursive = args["--recursive"].asBool();
		auto fileStrs = args["<file>"].asStringList();
		for (const auto& filePath : fileStrs)
		{
			package->SearchFilesToRemove(filePath, recursive);
		}
		package->Save();

	}
	else if (args["compact"].asBool())
	{
		auto* package = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(package, -1);

		package->Compact();
		package->Save();
	}
	else if (args["diff"].asBool())
	{
		auto* mainPackage = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(mainPackage, -1);

		auto* otherPackage = OpenPackage(args, 1);
		RETURN_OBJECT_IF_NULL(otherPackage, -1);

		auto fileStrs = args["<file>"].asStringList();
		auto diffPackage = mainPackage->CreateDiff(*otherPackage, fileStrs[0]);
		diffPackage->Save();

	}
	else if (args["merge"].asBool())
	{
		uintp packageCount = args["<package>"].asStringList().size();
		auto* mainPackage = OpenPackage(args);
		RETURN_OBJECT_IF_NULL(mainPackage, -1);

		List<BinaryPackage*> otherPackages;
		FOR_EACH_SIZE_BEGIN_END(i, 1, packageCount - 1)
		{
			auto* package = OpenPackage(args, i);
			RETURN_OBJECT_IF_NULL(package, -1);
			otherPackages.Add(package);
		}

		for (auto* package : otherPackages)
		{
			mainPackage->Merge(*package);
		}

		mainPackage->Save();

	}
	return 0;
}
