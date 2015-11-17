// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using GameKit.Resource;
using Medusa;

namespace GameKit.Publish
{
    public class FileId
    {
        public FileId(Medusa.CoreProto.FileId data)
        {
            mData = data;
        }

        private readonly Medusa.CoreProto.FileId mData;
        public string Name { get { return mData.Name; } set { mData.Name = value; } }
        public uint Order { get { return mData.Order; } set { mData.Order = value; } }
        public int Tag { get { return mData.Tag; } set { mData.Tag = value; } }

        public PublishInfo PublishInfo
        {
            get
            {
                return new PublishInfo(Tag);
            }
        }

        public string FullName
        {
            get
            {
                var rawName = Path.GetFileNameWithoutExtension(Name);
                var ext = Path.GetExtension(Name);
                if (Order != 0)
                {
                    return rawName + PublishInfo + "-" + Order + ext;
                }
                return rawName + PublishInfo + ext;
            }
        }

        public static FileId ParseFrom(string fullName)
        {
            var data = new Medusa.CoreProto.FileId
                {
                    Name = FileListFile.GetResourceName(fullName),
                    Order = FileListFile.GetResourceOrder(fullName),
                    Tag = PublishInfo.GetPublishInfo(fullName).Tag
                };
            return new FileId(data);
        }
    }
}
