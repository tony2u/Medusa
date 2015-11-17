// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/Render/RenderExtensionNames.h"
MEDUSA_BEGIN;


namespace RenderExtensionNames
{
	const StringRef IMG_texture_compression_pvrtc="GL_IMG_texture_compression_pvrtc";
	const StringRef IMG_texture_compression_pvrtc2="GL_IMG_texture_compression_pvrtc2";
	const StringRef OES_texture_half_float="GL_OES_texture_half_float";
	const StringRef OES_texture_float="GL_OES_texture_float";
	const StringRef EXT_multi_draw_arrays="GL_EXT_multi_draw_arrays";
	const StringRef OES_mapbuffer="GL_OES_mapbuffer";
	const StringRef OES_vertex_array_object="GL_OES_vertex_array_object";
	const StringRef IMG_multisampled_render_to_texture="GL_IMG_multisampled_render_to_texture";
	const StringRef EXT_discard_framebuffer="GL_EXT_discard_framebuffer";


#ifdef MEDUSA_IOS
	const StringRef IMG_texture_format_BGRA8888="GL_APPLE_texture_format_BGRA8888";
    const StringRef OES_compressed_ETC1_RGB8_texture="GL_OES_compressed_ETC1_RGB8_texture";
#else
	const StringRef IMG_texture_format_BGRA8888="GL_IMG_texture_format_BGRA8888";
	const StringRef OES_compressed_ETC1_RGB8_texture="GL_OES_compressed_ETC1_RGB8_texture";

#endif
	
}


MEDUSA_END;