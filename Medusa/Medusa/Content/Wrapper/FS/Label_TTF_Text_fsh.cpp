//This file was created by FileWrapper 1.0.0.0
//DO NOT EDIT
#include "MedusaPreCompiled.h"
#include "Core/IO/MemoryFileAutoRegister.h"
#pragma region Label_TTF_Text.fsh
MEDUSA_CONTENT_BEGIN;
const static char _Label_TTF_Text_fsh[] = "\
#version 100\n\
#ifndef GL_ES \n\
#define lowp\n\
#define mediump\n\
#define highp\n\
#endif\n\
\n\
\n\
\n\
precision mediump float;\n\
\n\
uniform sampler2D uTextureSampler;\n\
uniform highp vec4 uTextColor;\n\
\n\
varying  mediump vec2	vTexCoord;\n\
varying lowp vec4 vColor;\n\
\n\
void main (void)\n\
{\n\
	lowp vec4 texColor=texture2D(uTextureSampler,vTexCoord);	//a:text\n\
	gl_FragColor=vColor*uTextColor*texColor.a;\n\
}\n\
";
//const static MemoryFileAutoRegister mRegister_Label_TTF_Text_fsh(FileIdRef("Label_TTF_Text.fsh"),_Label_TTF_Text_fsh);
static void Register_Label_TTF_Text_fsh(){MemoryFileAutoRegister::Register(FileIdRef("Label_TTF_Text.fsh"),_Label_TTF_Text_fsh);}
MEDUSA_CONTENT_END;
#pragma endregion Label_TTF_Text.fsh

