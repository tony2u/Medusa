::Box2D
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Box2D\Box2D\Build\vs2015\Box2D.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Box2D\Box2D\Build\vs2015\Box2D.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Box2D\Box2D\Build\vs2015\Box2D.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Box2D\Box2D\Build\vs2015\Box2D.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
pause
rmdir /s /q Box2D\Box2D\Build\vs2015\Debug
rmdir /s /q Box2D\Box2D\Build\vs2015\Release
rmdir /s /q Box2D\Box2D\Build\vs2015\x64
pause


::lua
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" lua\win\lua.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" lua\win\lua.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" lua\win\lua.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" lua\win\lua.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
pause
rmdir /s /q lua\win\Debug
rmdir /s /q lua\win\Release
rmdir /s /q lua\win\x64
rmdir /s /q lua\Debug
rmdir /s /q lua\Release
rmdir /s /q lua\x64
pause

::luajit
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" luajit\win\luajit.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" luajit\win\luajit.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" luajit\win\luajit.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" luajit\win\luajit.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
pause
rmdir /s /q luajit\win\Debug
rmdir /s /q luajit\win\Release
rmdir /s /q luajit\win\x64
rmdir /s /q luajit\Debug
rmdir /s /q luajit\Release
rmdir /s /q luajit\x64
pause


::curl
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" curl\win\curl.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" curl\win\curl.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" curl\win\curl.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" curl\win\curl.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
rmdir /s /q curl\win\Debug
rmdir /s /q curl\win\Release
rmdir /s /q curl\win\x64
rmdir /s /q curl\Debug
rmdir /s /q curl\Release
rmdir /s /q curl\x64

::zlib
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" zlib\win\zlib.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" zlib\win\zlib.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" zlib\win\zlib.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" zlib\win\zlib.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
rmdir /s /q zlib\win\Debug
rmdir /s /q zlib\win\Release
rmdir /s /q zlib\win\x64
rmdir /s /q zlib\Debug
rmdir /s /q zlib\Release
rmdir /s /q zlib\x64

::Lzma
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Lzma\win\Lzma.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Lzma\win\Lzma.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Lzma\win\Lzma.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Lzma\win\Lzma.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
rmdir /s /q Lzma\win\Debug
rmdir /s /q Lzma\win\Release
rmdir /s /q Lzma\win\x64
rmdir /s /q Lzma\Debug
rmdir /s /q Lzma\Release
rmdir /s /q Lzma\x64

::unzip
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" unzip\win\unzip.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" unzip\win\unzip.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" unzip\win\unzip.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" unzip\win\unzip.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
rmdir /s /q unzip\win\Debug
rmdir /s /q unzip\win\Release
rmdir /s /q unzip\win\x64
rmdir /s /q unzip\Debug
rmdir /s /q unzip\Release
rmdir /s /q unzip\x64

::lz4
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" lz4\win\lz4.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" lz4\win\lz4.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" lz4\win\lz4.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" lz4\win\lz4.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\MedusaCore\CoreLib\Bin\win\x64\
rmdir /s /q lz4\win\Debug
rmdir /s /q lz4\win\Release
rmdir /s /q lz4\win\x64
rmdir /s /q lz4\Debug
rmdir /s /q lz4\Release
rmdir /s /q lz4\x64

::jpeg
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" jpeg\win\jpeg.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" jpeg\win\jpeg.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" jpeg\win\jpeg.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" jpeg\win\jpeg.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
xcopy /Q /E /Y jpeg\*.h ..\..\..\Medusa\Medusa\Lib\Common\jpeg\*.h
rmdir /s /q jpeg\win\Debug
rmdir /s /q jpeg\win\Release
rmdir /s /q jpeg\win\x64
rmdir /s /q jpeg\Debug
rmdir /s /q jpeg\Release
rmdir /s /q jpeg\x64


::ogg
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" ogg\win\ogg.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" ogg\win\ogg.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" ogg\win\ogg.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" ogg\win\ogg.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
rmdir /s /q ogg\win\Debug
rmdir /s /q ogg\win\Release
rmdir /s /q ogg\win\x64
rmdir /s /q ogg\Debug
rmdir /s /q ogg\Release
rmdir /s /q ogg\x64

::openal
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" openal\win\openal.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" openal\win\openal.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" openal\win\openal.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" openal\win\openal.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
rmdir /s /q openal\win\Debug
rmdir /s /q openal\win\Release
rmdir /s /q openal\win\x64
rmdir /s /q openal\Debug
rmdir /s /q openal\Release
rmdir /s /q openal\x64

::png
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" png\win\png.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" png\win\png.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" png\win\png.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" png\win\png.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
rmdir /s /q png\win\Debug
rmdir /s /q png\win\Release
rmdir /s /q png\win\x64
rmdir /s /q png\Debug
rmdir /s /q png\Release
rmdir /s /q png\x64

::freetype
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" freetype\win\freetype.vcxproj /p:Configuration=Debug;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" freetype\win\freetype.vcxproj /p:Configuration=Release;Platform=Win32;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x86\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" freetype\win\freetype.vcxproj /p:Configuration=Debug;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" freetype\win\freetype.vcxproj /p:Configuration=Release;Platform=x64;OutDir=..\..\..\Medusa\Medusa\Lib\Bin\win\x64\
rmdir /s /q freetype\win\Debug
rmdir /s /q freetype\win\Release
rmdir /s /q freetype\win\x64
rmdir /s /q freetype\Debug
rmdir /s /q freetype\Release
rmdir /s /q freetype\x64

