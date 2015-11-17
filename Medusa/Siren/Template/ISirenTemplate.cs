// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
namespace Siren.Template
{
    public interface ISirenTemplate
    {
        string HeaderTemplate { get; }
        string BodyTemplate { get; }
        string RootDirectory { get; }

    }
}
