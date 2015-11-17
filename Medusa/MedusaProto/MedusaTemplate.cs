// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Siren;
using Siren.Template;

namespace Medusa
{
    public class MedusaTemplate : ISirenTemplate
    {

        public string HeaderTemplate
        {
            get
            {
                return @"#pragma once
#include ""MedusaPreDeclares.h""
#include ""Core/Siren/SirenHeader.h""
<SIREN_HEADER_INCLUDE>
MEDUSA_BEGIN;

<SIREN_HEADER>
MEDUSA_END;";
            }
        }

        public string BodyTemplate
        {
            get
            {
                return @"#include ""MedusaPreCompiled.h""
<SIREN_BODY_INCLUDE>
MEDUSA_BEGIN;

<SIREN_BODY>
MEDUSA_END;";
            }
        }

        public string RootDirectory
        {
            get { return "Medusa"; }
        }


    }
}
