//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region Shape.fsh
MEDUSA_CONTENT_BEGIN;
const static char _Shape_fsh[] = "\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
varying lowp vec4 vColor;\n\
\n\
void main (void)\n\
{\n\
	gl_FragColor =vColor;\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_Shape_fsh(FileIdRef("Shape.fsh"),_Shape_fsh);
static void Register_Shape_fsh(){MemoryFileAutoRegister::Register(FileIdRef("Shape.fsh"),_Shape_fsh);}
MEDUSA_CONTENT_END;
#pragma endregion Shape.fsh

