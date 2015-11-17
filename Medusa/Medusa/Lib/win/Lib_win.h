// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#ifdef MEDUSA_GLEW
#define GLEW_STATIC

//#pragma comment(lib,"opengl32.lib")
//#pragma comment(lib,"glew32s.lib")

#endif

#ifdef MEDUSA_GLES
//#pragma comment(lib,"libEGL.lib")
//#pragma comment(lib,"libGLESv2.lib")
#endif

#ifdef MEDUSA_DIRECTX
#endif

//#pragma comment(lib,"freetype.lib")
//#pragma comment(lib,"ogg.lib")
//#pragma comment(lib,"png.lib")
//#pragma comment(lib,"jpeg.lib")


#ifdef MEDUSA_AL
//#pragma comment(lib,"openal.lib")
#endif
