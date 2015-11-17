//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region POD.vsh
MEDUSA_CONTENT_BEGIN;
const static char _POD_vsh[] = "\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
attribute highp vec3	aVertex;\n\
attribute mediump vec2	aTexCoord;\n\
attribute mediump vec3	aNormal;\n\
uniform mediump mat4	uWorldViewProjectMatrix;\n\
uniform mediump vec3	uModelLightDirection;\n\
varying mediump vec2	vTexCoord;\n\
varying mediump float	vDot;\n\
void main(void)\n\
{\n\
	gl_Position = uWorldViewProjectMatrix * vec4(aVertex,1.0);\n\
	vTexCoord = aTexCoord;\n\
	vDot=dot(aNormal,-uModelLightDirection);\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_POD_vsh(FileIdRef("POD.vsh"),_POD_vsh);
static void Register_POD_vsh(){MemoryFileAutoRegister::Register(FileIdRef("POD.vsh"),_POD_vsh);}
MEDUSA_CONTENT_END;
#pragma endregion POD.vsh

