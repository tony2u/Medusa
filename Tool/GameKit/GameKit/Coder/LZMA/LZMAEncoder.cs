// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.IO;
using Medusa.CoreProto;
using SevenZip;
using SevenZip.Compression.LZMA;

namespace GameKit.Coder.LZMA
{
    public class LZMAEncoder : LZMACoder
    {
        public LZMAEncoder(byte[] key)
            : base(key)
        {
        }

        public override FileList.FileCoder CoderInfo
        {
            get { return new FileList.FileCoder { Info = 0, Type = FileList.FileCoder.FileCoderType.LZMAEncoder }; }
        }

        public override byte[] Code(Byte[] data)
        {
            
            int dictionary = 1 << 23;
            Int32 posStateBits = 2;
            Int32 litContextBits = 3; // for normal files
            // UInt32 litContextBits = 0; // for 32-bit data
            Int32 litPosBits = 0;
            // UInt32 litPosBits = 2; // for 32-bit data
            Int32 algorithm = 2;
            Int32 numFastBytes = 128;

            CoderPropID[] propIDs = 
				{
					CoderPropID.DictionarySize,
					CoderPropID.PosStateBits,
					CoderPropID.LitContextBits,
					CoderPropID.LitPosBits,
					CoderPropID.Algorithm,
					CoderPropID.NumFastBytes,
					CoderPropID.MatchFinder,
					CoderPropID.EndMarker
				};
            object[] properties = 
				{
					(Int32)(dictionary),
					(Int32)(posStateBits),
					(Int32)(litContextBits),
					(Int32)(litPosBits),
					(Int32)(algorithm),
					(Int32)(numFastBytes),
					"bt4",
					false
				};


            MemoryStream inpuMemoryStream = new MemoryStream(data);
            MemoryStream outputMemoryStream = new MemoryStream();
            SevenZip.Compression.LZMA.Encoder encoder = new Encoder();
            encoder.SetCoderProperties(propIDs, properties);
            encoder.WriteCoderProperties(outputMemoryStream);
            Int64 fileSize = inpuMemoryStream.Length;
            for (int i = 0; i < 8; i++)
            {
                byte b = (Byte) (fileSize >> (8*i));
                outputMemoryStream.WriteByte(b);
            }
            
            encoder.Code(inpuMemoryStream, outputMemoryStream, -1, -1, null);
            var outBuffer = outputMemoryStream.ToArray();
           
            return outBuffer;
            //int keyIndex = 0;

            //for (uint i = 0; i < data.Length; ++i)
            //{
            //    data[i] ^= mKey[keyIndex];
            //    if (keyIndex < mKey.Length - 1)
            //    {
            //        ++keyIndex;
            //    }
            //    else
            //    {
            //        keyIndex = 0;
            //    }
            //}

            //return data;
        }

    }
}