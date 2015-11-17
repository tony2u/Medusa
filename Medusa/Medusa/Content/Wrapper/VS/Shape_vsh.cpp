//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region Shape.vsh
MEDUSA_CONTENT_BEGIN;
const static char _Shape_vsh[] = "\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
attribute highp vec3	aVertex;\n\
attribute lowp vec4	aColor;\n\
uniform  highp mat4	uWorldViewProjectMatrix;\n\
varying lowp vec4 vColor;\n\
void main(void)\n\
{\n\
	gl_Position = uWorldViewProjectMatrix * vec4(aVertex, 1.0);\n\
	vColor=aColor;\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_Shape_vsh(FileIdRef("Shape.vsh"),_Shape_vsh);
static void Register_Shape_vsh(){MemoryFileAutoRegister::Register(FileIdRef("Shape.vsh"),_Shape_vsh);}
MEDUSA_CONTENT_END;
#pragma endregion Shape.vsh

