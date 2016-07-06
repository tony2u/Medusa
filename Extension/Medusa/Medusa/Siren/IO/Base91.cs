// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
/*
 * Copyright (c) 2000-2006 Joachim Henke
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  - Neither the name of Joachim Henke nor the names of his contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Medusa.Siren.IO
{
    class Base91
    {
        private static readonly char[] mEncodeTable = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$',
            '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=',
            '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '\''
        };

        private static readonly Dictionary<byte, int> mDecodeTable=new Dictionary<byte, int>();

        static Base91()
        {
            InitDecodeTable();
        }

        private static void InitDecodeTable()
        {
            for (int i = 0; i < 255; i++)
            {
                mDecodeTable[(byte)i] = -1;
            }
            for (int i = 0; i < mEncodeTable.Length; i++)
            {
                mDecodeTable[(byte)mEncodeTable[i]] = i;
            }
        }

        public static string Encode(byte[] input)
        {
            StringBuilder output=new StringBuilder();
            int b = 0;
            int n = 0;

            foreach (byte t in input)
            {
                b |= t << n;
                n += 8;
                if (n > 13)
                {
                    var v = b & 8191;
                    if (v > 88)
                    {
                        b >>= 13;
                        n -= 13;
                    }
                    else
                    {
                        v = b & 16383;
                        b >>= 14;
                        n -= 14;
                    }
                    output.Append(mEncodeTable[v % 91]);
                    output.Append(mEncodeTable[v / 91]);
                }
            }
            if (n != 0)
            {
                output.Append(mEncodeTable[b % 91]);
                if (n > 7 || b > 90)
                    output.Append(mEncodeTable[b / 91]);
            }
            return output.ToString();
        }

        public static byte[] Decode(string input)
        {
            MemoryStream stream = new MemoryStream();

            int v = -1;
            int b = 0;
            int n = 0;
            foreach (char t in input)
            {
                var c = mDecodeTable[(byte)t];
                if (c == -1) continue;
                if (v < 0)
                {
                    v = c;
                }
                else
                {
                    v += c * 91;
                    b |= v << n;
                    n += (v & 8191) > 88 ? 13 : 14;
                    do
                    {
                        stream.WriteByte((byte)(b & 255));
                        b >>= 8;
                        n -= 8;
                    } while (n > 7);
                    v = -1;
                }
            }
            if (v + 1 != 0)
            {
                stream.WriteByte((byte)((b | v << n) & 255));
            }
            stream.Flush();
            return stream.ToArray();
        }

    }
}
