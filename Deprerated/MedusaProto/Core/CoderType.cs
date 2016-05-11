// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/Coder", EnumUnderType = "byte")]
    public enum CoderType
    {
        None = 0,

        Encoder_Begin = 0,
        Encoder_LZMA= 1,
        Encoder_XOR = 2,
        Encoder_LZ4 = 3,
        Encoder_XXTEA = 4,
        Encoder_Base64 = 5,
        Encoder_Base91 = 6,
        Encoder_Aes256 = 7,

        Decoder_Begin = 128,

        Decoder_LZMA = Decoder_Begin + Encoder_LZMA,
        Decoder_XOR = Decoder_Begin + Encoder_XOR,
        Decoder_LZ4 = Decoder_Begin + Encoder_LZ4,
        Decoder_XXTEA = Decoder_Begin + Encoder_XXTEA,
        Decoder_Base64 = Decoder_Begin + Encoder_Base64,
        Decoder_Base91 = Decoder_Begin + Encoder_Base91,
        Decoder_Aes256 = Decoder_Begin + Encoder_Aes256,

      
    };


}
