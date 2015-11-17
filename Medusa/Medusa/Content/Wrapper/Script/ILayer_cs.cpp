//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region ILayer.cs
MEDUSA_CONTENT_BEGIN;
const static char _ILayer_cs[] = "\
#include \"INode.cs\"\n\
class ILayer:INode\n\
{\n\
    ILayer(const HeapString name)\n\
    {\n\
        mLayer = @Medusa::ILayer(name);\n\
        @mNode = mLayer;\n\
    }\n\
\n\
    ~ILayer()\n\
    {\n\
\n\
    }\n\
    Medusa::ILayer@ mLayer;\n\
\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_ILayer_cs(FileIdRef("ILayer.cs"),_ILayer_cs);
static void Register_ILayer_cs(){MemoryFileAutoRegister::Register(FileIdRef("ILayer.cs"),_ILayer_cs);}
MEDUSA_CONTENT_END;
#pragma endregion ILayer.cs

