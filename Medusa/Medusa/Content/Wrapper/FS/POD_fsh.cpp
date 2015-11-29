//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region POD.fsh
MEDUSA_CONTENT_BEGIN;
const static char _POD_fsh[] = "\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
uniform sampler2D uTextureSampler;\n\
varying mediump vec2	vTexCoord;\n\
varying lowp float		vDot;\n\
void main (void)\n\
{\n\
	gl_FragColor=texture2D(uTextureSampler,vTexCoord);\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_POD_fsh(FileIdRef("POD.fsh"),_POD_fsh);
static void Register_POD_fsh(){MemoryFileAutoRegister::Register(FileIdRef("POD.fsh"),_POD_fsh);}
MEDUSA_CONTENT_END;
#pragma endregion POD.fsh

