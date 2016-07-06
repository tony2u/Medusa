// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.


//inspired by:
/*
*
* Copyright (c) 2014, Danilo Treffiletti <urban82@gmail.com>
* All rights reserved.
*
*     This file is part of Aes256.
*
*     Aes256 is free software: you can redistribute it and/or modify
*     it under the terms of the GNU Lesser General Public License as
*     published by the Free Software Foundation, either version 2.1
*     of the License, or (at your option) any later version.
*
*     Aes256 is distributed in the hope that it will be useful,
*     but WITHOUT ANY WARRANTY; without even the implied warranty of
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*     GNU Lesser General Public License for more details.
*
*     You should have received a copy of the GNU Lesser General Public
*     License along with Aes256.
*     If not, see <http://www.gnu.org/licenses/>.
*/



#include "MedusaCorePreCompiled.h"
#include "Aes256Encoder.h"
#include "Core/String/HeapString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Math/Random/Random.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Core/Log/Log.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;

#define FE(x)  (((x) << 1) ^ ((((x)>>7) & 1) * 0x1b))
#define FD(x)  (((x) >> 1) ^ (((x) & 1) ? 0x8d : 0))

inline unsigned char rj_xtime(unsigned char x)
{
	return (x & 0x80) ? ((x << 1) ^ 0x1b) : (x << 1);
}


const unsigned char Aes256Encoder::sbox[256] =
{
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
	0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
	0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
	0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
	0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
	0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
	0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
	0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
	0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
	0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
	0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
	0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
	0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
	0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
	0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
	0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
	0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};


Aes256Encoder::Aes256Encoder(const MemoryData& key, Random* random /*= nullptr*/)
	: mRandom(random),
	mKey(key.Clone())
{
    uint maxSize=KeyMaxSize;
	Log::AssertFormat(mKey.Size() <= maxSize, "Too bigger key size:{} > Max support:{}", mKey.Size(), maxSize);
}

Aes256Encoder::Aes256Encoder(const IEventArg& e)
	:Aes256Encoder(((const UserDataEventArg<MemoryData>&)e).Data(), &Random::Global())
{
}

size_t Aes256Encoder::GuessResultSize(const IStream& input) const
{
	size_t inputLength = input.LeftLength();
	size_t outputLength = inputLength;

	// Calculate padding
	if (inputLength % BlockSize != 0)
		outputLength += (BlockSize - (inputLength % BlockSize));

	// Add salt
	outputLength += KeyMaxSize - mKey.Size();	//salt size

	// Add 1 bytes for padding size
	++outputLength;

	return outputLength;
}

size_t Aes256Encoder::OnCode(const MemoryData& input, MemoryData& output) const
{
	MemoryStream inputStream(input);
	MemoryStream outputStream(output);

	size_t inputLength = input.Size();

	MemoryData salt = MemoryData::Alloc(KeyMaxSize - mKey.Size());
	salt.ClearZero();

	// Generate salt
	if (mRandom!=nullptr)
	{
		mRandom->NextBytes(salt);
	}

	MemoryData rkey = MemoryData::Alloc(KeyMaxSize);

	// Calculate padding
	size_t padding = 0;
	if (inputLength % BlockSize != 0)
		padding = (BlockSize - (inputLength % BlockSize));

	// Add salt
	outputStream.WriteData(salt);

	// Add 1 bytes for padding size
	outputStream.WriteChar((char)(padding & 0xFF));

	// Reset buffer
	byte buffer[3 * BlockSize];
	size_t bufferPos = 0;

	MemoryData bufferData = MemoryData::FromStatic(buffer, BlockSize);
	while (!inputStream.IsEnd())
	{
		bufferPos += inputStream.ReadDataTo(bufferData);

		if (bufferPos == BlockSize)
		{
			Encrypt(rkey, mKey, salt, buffer);
			outputStream.WriteData(bufferData);
			bufferPos = 0;
		}
	}

	if (bufferPos > 0)
	{
		//padding with 0
		Memory::SetZero(buffer + bufferPos, BlockSize - bufferPos);

		Encrypt(rkey,mKey, salt, buffer);
		outputStream.WriteData(bufferData);
	}

	return outputStream.Position();
}

void Aes256Encoder::Encrypt(MemoryData& rkey, const MemoryData& key,const MemoryData& salt, unsigned char* buffer)
{
	unsigned char i, rcon;

	copy_key(rkey, key, salt);
	add_round_key(rkey.MutableData(), buffer, 0);
	for (i = 1, rcon = 1; i < RoundCount; ++i)
	{
		sub_bytes(buffer);
		shift_rows(buffer);
		mix_columns(buffer);
		if (!(i & 1))
			expand_enc_key(rkey.MutableData(), &rcon);
		add_round_key(rkey.MutableData(), buffer, i);
	}
	sub_bytes(buffer);
	shift_rows(buffer);
	expand_enc_key(rkey.MutableData(), &rcon);
	add_round_key(rkey.MutableData(), buffer, i);
}

void Aes256Encoder::expand_enc_key(byte* rkey, unsigned char* rc)
{
	unsigned char i;

	rkey[0] = rkey[0] ^ sbox[rkey[29]] ^ (*rc);
	rkey[1] = rkey[1] ^ sbox[rkey[30]];
	rkey[2] = rkey[2] ^ sbox[rkey[31]];
	rkey[3] = rkey[3] ^ sbox[rkey[28]];
	*rc = FE(*rc);

	for (i = 4; i < 16; i += 4) {
		rkey[i] = rkey[i] ^ rkey[i - 4];
		rkey[i + 1] = rkey[i + 1] ^ rkey[i - 3];
		rkey[i + 2] = rkey[i + 2] ^ rkey[i - 2];
		rkey[i + 3] = rkey[i + 3] ^ rkey[i - 1];
	}
	rkey[16] = rkey[16] ^ sbox[rkey[12]];
	rkey[17] = rkey[17] ^ sbox[rkey[13]];
	rkey[18] = rkey[18] ^ sbox[rkey[14]];
	rkey[19] = rkey[19] ^ sbox[rkey[15]];

	for (i = 20; i < 32; i += 4) {
		rkey[i] = rkey[i] ^ rkey[i - 4];
		rkey[i + 1] = rkey[i + 1] ^ rkey[i - 3];
		rkey[i + 2] = rkey[i + 2] ^ rkey[i - 2];
		rkey[i + 3] = rkey[i + 3] ^ rkey[i - 1];
	}
}

void Aes256Encoder::sub_bytes(unsigned char* buffer)
{
	unsigned char i = KeyMaxSize / 2;

	while (i--)
		buffer[i] = sbox[buffer[i]];
}

void Aes256Encoder::copy_key(MemoryData& rkey, const MemoryData& key, const MemoryData& salt)
{
	Memory::SafeCopy(rkey.MutableData(), key.Size(), key.Data(), key.Size());
	Memory::SafeCopy(rkey.MutableData() + key.Size(), salt.Size(), salt.Data(), salt.Size());
}

void Aes256Encoder::add_round_key(const byte* rkey, unsigned char* buffer, const unsigned char round)
{
	 unsigned char i = KeyMaxSize / 2;

	while (i--)
		buffer[i] ^= rkey[(round & 1) ? i + 16 : i];
}

void Aes256Encoder::shift_rows(unsigned char* buffer)
{
	 unsigned char i, j, k, l; /* to make it potentially parallelable :) */

	i = buffer[1];
	buffer[1] = buffer[5];
	buffer[5] = buffer[9];
	buffer[9] = buffer[13];
	buffer[13] = i;

	j = buffer[10];
	buffer[10] = buffer[2];
	buffer[2] = j;

	k = buffer[3];
	buffer[3] = buffer[15];
	buffer[15] = buffer[11];
	buffer[11] = buffer[7];
	buffer[7] = k;

	l = buffer[14];
	buffer[14] = buffer[6];
	buffer[6] = l;
}

void Aes256Encoder::mix_columns(unsigned char* buffer)
{
	 unsigned char i, a, b, c, d, e;

	for (i = 0; i < 16; i += 4)
	{
		a = buffer[i];
		b = buffer[i + 1];
		c = buffer[i + 2];
		d = buffer[i + 3];

		e = a ^ b ^ c ^ d;

		buffer[i] ^= e ^ rj_xtime(a^b);
		buffer[i + 1] ^= e ^ rj_xtime(b^c);
		buffer[i + 2] ^= e ^ rj_xtime(c^d);
		buffer[i + 3] ^= e ^ rj_xtime(d^a);
	}
}

#undef FE
#undef FD
constexpr uint Aes256Encoder::KeyMaxSize;
MEDUSA_END;