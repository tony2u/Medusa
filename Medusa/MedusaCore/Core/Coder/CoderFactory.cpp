// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Coder/CoderFactory.h"
#include "Core/Coder/LZMA/LZMADecoder.h"
#include "Core/Coder/LZMA/LZMAEncoder.h"
#include "Core/Coder/XOR/XORDecoder.h"
#include "Core/Coder/XOR/XOREncoder.h"
#include "Core/Coder/LZ4/LZ4Decoder.h"
#include "Core/Coder/LZ4/LZ4Encoder.h"

#include "Core/Coder/XXTEA/XXTEADecoder.h"
#include "Core/Coder/XXTEA/XXTEAEncoder.h"

#include "Core/Coder/Crypt/Base64Decoder.h"
#include "Core/Coder/Crypt/Base64Encoder.h"
#include "Core/Coder/Crypt/Base91Decoder.h"
#include "Core/Coder/Crypt/Base91Encoder.h"

#include "Core/Coder/Crypt/Aes256Decoder.h"
#include "Core/Coder/Crypt/Aes256Encoder.h"


MEDUSA_BEGIN;


CoderFactory::CoderFactory()
{
	Register<XOREncoder>(CoderType::Encoder_XOR);
	Register<XORDecoder>(CoderType::Decoder_XOR);

#ifdef MEDUSA_LZMA

	Register<LZMADecoder>(CoderType::Decoder_LZMA);
	Register<LZMAEncoder>(CoderType::Encoder_LZMA);

#endif

#ifdef MEDUSA_LZ4

	Register<LZ4Decoder>(CoderType::Decoder_LZ4);
	Register<LZ4Encoder>(CoderType::Encoder_LZ4);
#endif

	Register<XXTEADecoder>(CoderType::Decoder_XXTEA);
	Register<XXTEAEncoder>(CoderType::Encoder_XXTEA);

	Register<Base64Decoder>(CoderType::Decoder_Base64);
	Register<Base64Encoder>(CoderType::Encoder_Base64);

	Register<Base91Decoder>(CoderType::Decoder_Base91);
	Register<Base91Encoder>(CoderType::Encoder_Base91);

	Register<Aes256Decoder>(CoderType::Decoder_Aes256);
	Register<Aes256Encoder>(CoderType::Encoder_Aes256);
}

CoderType CoderFactory::ParseCoderType(const StringRef& str)
{
	if (str.Compare("AES256", true) == 0)
	{
		return CoderType::Encoder_Aes256;
	}

	if (str.Compare("LZ4", true) == 0)
	{
		return CoderType::Encoder_LZ4;
	}

	if (str.Compare("LZMA", true) == 0)
	{
		return CoderType::Encoder_LZMA;
	}

	if (str.Compare("Base91", true) == 0)
	{
		return CoderType::Encoder_Base91;
	}

	if (str.Compare("Base64", true) == 0)
	{
		return CoderType::Encoder_Base64;
	}

	if (str.Compare("XXTEA", true) == 0)
	{
		return CoderType::Encoder_XXTEA;
	}

	if (str.Compare("XOR", true) == 0)
	{
		return CoderType::Encoder_XOR;
	}

	return CoderType::None;
}

bool CoderFactory::RequireKey(CoderType coderType)
{
	switch (coderType)
	{
	case CoderType::Encoder_XOR:
	case CoderType::Encoder_XXTEA:
	case CoderType::Encoder_Aes256:
	case CoderType::Decoder_XOR:
	case CoderType::Decoder_XXTEA:
	case CoderType::Decoder_Aes256:
		return true;
	default:
		return false;
	}
}



MEDUSA_END;

