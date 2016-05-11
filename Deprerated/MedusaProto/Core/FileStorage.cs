// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/IO/Storage", EnumUnderType = "byte")]
    [Flags]
    public enum EntryOperation : byte
    {
        None = 0,
        Add = 1,
        Delete = 2,
        Update = 4,
    };

    [SirenClass(typeof(MedusaCoreTemplate), "Core/IO/Storage")]
    [Flags]
    public enum FilePermission
    {
        None = 0,
        Read = 0x0100,  //S_IREAD
        Write = 0x0080, //S_IWRITE
        All = Read | Write,
    };


    [SirenClass(typeof(MedusaCoreTemplate), "Core/IO/Storage", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class DirectoryEntry
    {
        [SirenProperty(SirenPropertyModifier.Optional)]
        public string Name { get; set; }

        [SirenProperty(SirenPropertyModifier.Optional, 0)]
        public EntryOperation Operations { get; set; }   //deleted or not,operation

        [SirenProperty(SirenPropertyModifier.Optional, ForceValueToPtr = true)]
        public List<DirectoryEntry> Dirs { get; set; }   //path id

        [SirenProperty(SirenPropertyModifier.Optional, ForceValueToPtr = true)]
        public List<FileEntry> Files { get; set; }  //name id
    }

    [SirenClass(typeof(MedusaCoreTemplate), "Core/IO/Storage", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class FileEntry
    {
        [SirenProperty(SirenPropertyModifier.Optional)]
        public string Name { get; set; }

        [SirenProperty(SirenPropertyModifier.Optional, FilePermission.All)]
        public FilePermission Permission { get; set; }   //0 to not use any coder,max to use default coders

        [SirenProperty(SirenPropertyModifier.Optional, 0xFFFFFFFF)]
        public uint FirstBlockId { get; set; }

        [SirenProperty(SirenPropertyModifier.Optional, 0)]
        public uint OriginalSize { get; set; }   //size before coding

        [SirenProperty(SirenPropertyModifier.Optional, 0)]
        public uint Size { get; set; }

        [SirenProperty(SirenPropertyModifier.Optional)]
        public string Signature { get; set; }   //for hash check

        [SirenProperty(SirenPropertyModifier.Optional, 0)]
        public EntryOperation Operations { get; set; }   //deleted or not,operation

        [SirenProperty(SirenPropertyModifier.Optional)]
        public List<uint> CoderOffsets { get; set; }  //coders only apply to current file
    }

    [SirenClass(typeof(MedusaCoreTemplate), "Core/IO/Storage", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class FileStorage
    {
        [SirenProperty]
        public DirectoryEntry RootDir { get; set; }

        [SirenProperty(SirenPropertyModifier.Optional)]
        public Dictionary<string,UInt64> CodeRules { get; set; }    //file extention-coder list
    }


}
