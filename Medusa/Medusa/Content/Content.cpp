// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Content.h"

#include "Content/Wrapper/FS/Color_fsh.cpp"
#include "Content/Wrapper/FS/Texture_fsh.cpp"
#include "Content/Wrapper/FS/POD_fsh.cpp"
#include "Content/Wrapper/FS/Shape_fsh.cpp"
#include "Content/Wrapper/FS/Label_TTF_Text_fsh.cpp"
#include "Content/Wrapper/FS/Label_TTF_Outline_fsh.cpp"
#include "Content/Wrapper/FS/Label_TTF_OutlineText_fsh.cpp"

#include "Content/Wrapper/VS/Position_vsh.cpp"
#include "Content/Wrapper/VS/Texture_vsh.cpp"
#include "Content/Wrapper/VS/POD_vsh.cpp"
#include "Content/Wrapper/VS/Shape_vsh.cpp"

#include "Content/Wrapper/Other/arial22_0_png.cpp"
#include "Content/Wrapper/Other/arial22_fnt.cpp"

MEDUSA_CONTENT_BEGIN;

void RegisterToFileSystem()
{
	Register_Color_fsh();
	Register_Texture_fsh();
	Register_Shape_fsh();
	Register_POD_fsh();

	Register_Label_TTF_Text_fsh();
	Register_Label_TTF_Outline_fsh();
	Register_Label_TTF_OutlineText_fsh();


	Register_Position_vsh();
	Register_Texture_vsh();
	Register_Shape_vsh();
	Register_POD_vsh();


	Register_arial22_0_png();
	Register_arial22_fnt();

}

MEDUSA_CONTENT_END;
