//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region IScene.cs
MEDUSA_CONTENT_BEGIN;
const static char _IScene_cs[] = "\
#include \"INode.cs\"\n\
class IScene:INode\n\
{\n\
    IScene(const HeapString name)\n\
    {\n\
        @mScene = @Medusa::IScene(name);\n\
        @mNode = @mScene;\n\
    }\n\
\n\
    ~IScene()\n\
    {\n\
\n\
    }\n\
\n\
    Medusa::IScene@ mScene;\n\
\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_IScene_cs(FileIdRef("IScene.cs"),_IScene_cs);
static void Register_IScene_cs(){MemoryFileAutoRegister::Register(FileIdRef("IScene.cs"),_IScene_cs);}
MEDUSA_CONTENT_END;
#pragma endregion IScene.cs

