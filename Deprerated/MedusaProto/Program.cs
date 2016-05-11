// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.


using System;
using System.IO;
using Siren;
using Siren.Generator;

namespace Medusa
{
    class Program
    {
        private static void Main(string[] args)
        {
            IGenerator generator = new CppGenerator();

            DirectoryInfo curDir = new DirectoryInfo(Environment.CurrentDirectory);
            curDir = curDir.Parent.Parent.Parent;
            generator.WorkingDirectory = curDir;
            generator.Generate();
        }

    }
}
