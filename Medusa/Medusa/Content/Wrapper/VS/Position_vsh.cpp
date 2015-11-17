//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region Position.vsh
MEDUSA_CONTENT_BEGIN;
const static char _Position_vsh[] = "\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
attribute highp vec3	aVertex;\n\
uniform  highp mat4	uWorldViewProjectMatrix;\n\
void main(void)\n\
{\n\
	gl_Position = uWorldViewProjectMatrix * vec4(aVertex, 1.0);\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_Position_vsh(FileIdRef("Position.vsh"),_Position_vsh);
static void Register_Position_vsh(){MemoryFileAutoRegister::Register(FileIdRef("Position.vsh"),_Position_vsh);}
MEDUSA_CONTENT_END;
#pragma endregion Position.vsh

