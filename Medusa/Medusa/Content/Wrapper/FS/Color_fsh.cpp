//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region Color.fsh
MEDUSA_CONTENT_BEGIN;
const static char _Color_fsh[] = "\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
uniform highp vec3 uLightDiffuse;	// Color and ID passed in from vertex.\n\
void main()\n\
{\n\
	// Simply assigns the color and ID number of the object it renders.\n\
	gl_FragColor = vec4(uLightDiffuse,1.0);\n\
}\n\
\n\
";
//const static MemoryFileAutoRegister mRegister_Color_fsh(FileIdRef("Color.fsh"),_Color_fsh);
static void Register_Color_fsh(){MemoryFileAutoRegister::Register(FileIdRef("Color.fsh"),_Color_fsh);}
MEDUSA_CONTENT_END;
#pragma endregion Color.fsh

