//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region FntFont.fsh
MEDUSA_CONTENT_BEGIN;
const static char _FntFont_fsh[] = "\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
uniform sampler2D uTextureSampler;\n\
varying  mediump vec2	vTexCoord;\n\
varying lowp vec4 vColor;\n\
void main (void)\n\
{\n\
	lowp vec4 texColor=texture2D(uTextureSampler,vTexCoord);\n\
	gl_FragColor =texColor*vColor;\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_FntFont_fsh(FileIdRef("FntFont.fsh"),_FntFont_fsh);
static void Register_FntFont_fsh(){MemoryFileAutoRegister::Register(FileIdRef("FntFont.fsh"),_FntFont_fsh);}
MEDUSA_CONTENT_END;
#pragma endregion FntFont.fsh

