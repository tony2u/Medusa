// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Aes256Decoder.h"
#include "Core/String/HeapString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Math/Random/Random.h"
#include "Core/Command/EventArg/UserDataEventArg.h"
#include "Core/Log/Log.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Aes256Encoder.h"

MEDUSA_BEGIN;

#define FE(x)  (((x) << 1) ^ ((((x)>>7) & 1) * 0x1b))
#define FD(x)  (((x) >> 1) ^ (((x) & 1) ? 0x8d : 0))

inline unsigned char rj_xtime(unsigned char x)
{
	return (x & 0x80) ? ((x << 1) ^ 0x1b) : (x << 1);
}


const unsigned char Aes256Decoder::sboxinv[256] =
{
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
	0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
	0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
	0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
	0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
	0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
	0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
	0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
	0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
	0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
	0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
	0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
	0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
	0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
	0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
	0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
	0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

Aes256Decoder::Aes256Decoder(const MemoryData& key)
	: mKey(key.Clone())
{
    uint maxSize=Aes256Encoder::KeyMaxSize;
	Log::AssertFormat(mKey.Size() <= maxSize, "Too bigger key size:{} > Max support:{}", mKey.Size(), maxSize);
}

Aes256Decoder::Aes256Decoder(const IEventArg& e)
	:Aes256Decoder(((const UserDataEventArg<MemoryData>&)e).Data())
{
}

size_t Aes256Decoder::GuessResultSize(const IStream& input) const
{
	uintp pos = input.Position();

	size_t inputLength = input.LeftLength();
	size_t outputLength = inputLength;

	size_t saltSize = Aes256Encoder::KeyMaxSize - mKey.Size();

	outputLength -= saltSize;	//

	--outputLength;	//padding size
	input.SetPosition(saltSize);
	
	byte padding = (byte)input.ReadChar();	//padding data
	outputLength -= padding;
	input.SetPosition(pos);

	return outputLength;
}

size_t Aes256Decoder::OnCode(const MemoryData& input, MemoryData& output) const
{
	MemoryStream inputStream(input);
	MemoryStream outputStream(output);

	size_t saltSize = Aes256Encoder::KeyMaxSize - mKey.Size();
	size_t paddingSize = 0;

	// Read salt
	MemoryData salt = inputStream.ReadData(saltSize);
	MemoryData rkey = MemoryData::Alloc(Aes256Encoder::KeyMaxSize);

	//read padding size
	paddingSize = inputStream.ReadChar();

	// Reset buffer
	byte buffer[3 * Aes256Encoder::BlockSize];
	size_t bufferPos = 0;
	size_t resultSize = 0;

	MemoryData bufferData= MemoryData::FromStatic(buffer, Aes256Encoder::BlockSize);
	while (!inputStream.IsEnd())
	{
		bufferPos += inputStream.ReadDataTo(bufferData);

		if (bufferPos == Aes256Encoder::BlockSize)
		{
			Decrypt(rkey, mKey,salt, buffer);
			outputStream.WriteData(bufferData);	//may exceed buffer size
			bufferPos = 0;
			resultSize += Aes256Encoder::BlockSize;
		}
	}

	resultSize -= paddingSize; //so reduce back padding size

	return resultSize;
}

void Aes256Decoder::Decrypt(MemoryData& rkey, const MemoryData& key,const MemoryData& salt, unsigned char* buffer)
{
	unsigned char i, rcon = 1;

	Aes256Encoder::copy_key(rkey, key,salt);
	for (i = Aes256Encoder::RoundCount / 2; i > 0; --i)
		Aes256Encoder::expand_enc_key(rkey.MutableData(), &rcon);

	Aes256Encoder::add_round_key(rkey.MutableData(), buffer, Aes256Encoder::RoundCount);
	shift_rows_inv(buffer);
	sub_bytes_inv(buffer);

	for (i = Aes256Encoder::RoundCount, rcon = 0x80; --i;)
	{
		if ((i & 1))
			expand_dec_key(rkey.MutableData(), &rcon);
		Aes256Encoder::add_round_key(rkey.MutableData(), buffer, i);
		mix_columns_inv(buffer);
		shift_rows_inv(buffer);
		sub_bytes_inv(buffer);
	}
	Aes256Encoder::add_round_key(rkey.MutableData(), buffer, i);
}


void Aes256Decoder::expand_dec_key(byte* rkey, unsigned char* rc)
{
	
	unsigned char i;

	for (i = 28; i > 16; i -= 4) {
		rkey[i + 0] = rkey[i + 0] ^ rkey[i - 4];
		rkey[i + 1] = rkey[i + 1] ^ rkey[i - 3];
		rkey[i + 2] = rkey[i + 2] ^ rkey[i - 2];
		rkey[i + 3] = rkey[i + 3] ^ rkey[i - 1];
	}

	rkey[16] = rkey[16] ^ Aes256Encoder::sbox[rkey[12]];
	rkey[17] = rkey[17] ^ Aes256Encoder::sbox[rkey[13]];
	rkey[18] = rkey[18] ^ Aes256Encoder::sbox[rkey[14]];
	rkey[19] = rkey[19] ^ Aes256Encoder::sbox[rkey[15]];

	for (i = 12; i > 0; i -= 4) {
		rkey[i + 0] = rkey[i + 0] ^ rkey[i - 4];
		rkey[i + 1] = rkey[i + 1] ^ rkey[i - 3];
		rkey[i + 2] = rkey[i + 2] ^ rkey[i - 2];
		rkey[i + 3] = rkey[i + 3] ^ rkey[i - 1];
	}

	*rc = FD(*rc);
	rkey[0] = rkey[0] ^ Aes256Encoder::sbox[rkey[29]] ^ (*rc);
	rkey[1] = rkey[1] ^ Aes256Encoder::sbox[rkey[30]];
	rkey[2] = rkey[2] ^ Aes256Encoder::sbox[rkey[31]];
	rkey[3] = rkey[3] ^ Aes256Encoder::sbox[rkey[28]];
}

void Aes256Decoder::sub_bytes_inv(unsigned char* buffer)
{
	unsigned char i = Aes256Encoder::KeyMaxSize / 2;

	while (i--)
		buffer[i] = sboxinv[buffer[i]];
}

void Aes256Decoder::shift_rows_inv(unsigned char* buffer)
{
	unsigned char i, j, k, l; /* same as above :) */

	i = buffer[1];
	buffer[1] = buffer[13];
	buffer[13] = buffer[9];
	buffer[9] = buffer[5];
	buffer[5] = i;

	j = buffer[2];
	buffer[2] = buffer[10];
	buffer[10] = j;

	k = buffer[3];
	buffer[3] = buffer[7];
	buffer[7] = buffer[11];
	buffer[11] = buffer[15];
	buffer[15] = k;

	l = buffer[6];
	buffer[6] = buffer[14];
	buffer[14] = l;
}

void Aes256Decoder::mix_columns_inv(unsigned char* buffer)
{
	 unsigned char i, a, b, c, d, e, x, y, z;

	for (i = 0; i < 16; i += 4)
	{
		a = buffer[i];
		b = buffer[i + 1];
		c = buffer[i + 2];
		d = buffer[i + 3];

		e = a ^ b ^ c ^ d;
		z = rj_xtime(e);
		x = e ^ rj_xtime(rj_xtime(z^a^c));  y = e ^ rj_xtime(rj_xtime(z^b^d));

		buffer[i] ^= x ^ rj_xtime(a^b);
		buffer[i + 1] ^= y ^ rj_xtime(b^c);
		buffer[i + 2] ^= x ^ rj_xtime(c^d);
		buffer[i + 3] ^= y ^ rj_xtime(d^a);
	}
}



#undef FE
#undef FD

MEDUSA_END;