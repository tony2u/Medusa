//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region Texture.fsh
MEDUSA_CONTENT_BEGIN;
const static char _Texture_fsh[] = "\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
\n\
\n\
uniform sampler2D uTextureSampler;\n\
varying  mediump vec2	vTexCoord;\n\
varying lowp vec4 vColor;\n\
\n\
void main (void)\n\
{\n\
	lowp vec4 texColor=texture2D(uTextureSampler,vTexCoord);\n\
	gl_FragColor =texColor*vColor;\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_Texture_fsh(FileIdRef("Texture.fsh"),_Texture_fsh);
static void Register_Texture_fsh(){MemoryFileAutoRegister::Register(FileIdRef("Texture.fsh"),_Texture_fsh);}
MEDUSA_CONTENT_END;
#pragma endregion Texture.fsh

