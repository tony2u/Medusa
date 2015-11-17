// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

MEDUSA_BEGIN;

enum class CoderType:byte
{
	None = 0,
	Encoder_Begin = 0,
	Encoder_LZMA = 1,
	Encoder_XOR = 2,
	Encoder_LZ4 = 3,
	Encoder_XXTEA = 4,
	Encoder_Base64 = 5,
	Encoder_Base91 = 6,
	Encoder_Aes256 = 7,
	Decoder_Begin = 128,
	Decoder_LZMA = 129,
	Decoder_XOR = 130,
	Decoder_LZ4 = 131,
	Decoder_XXTEA = 132,
	Decoder_Base64 = 133,
	Decoder_Base91 = 134,
	Decoder_Aes256 = 135,
};

MEDUSA_END;