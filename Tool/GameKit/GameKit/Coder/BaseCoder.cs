// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System.Text;
using Medusa.CoreProto;

namespace GameKit.Coder
{
    public abstract class BaseCoder:ICoder
    {
        public abstract FileList.FileCoder CoderInfo { get; }
        public abstract byte[] Code(byte[] data);

        public static string ByteArrayToString(byte[] ba)
        {
            StringBuilder hex = new StringBuilder(ba.Length * 2);
            foreach (byte b in ba)
                hex.AppendFormat("0x{0:x2},", b);
            return hex.ToString();
        }

    }
}