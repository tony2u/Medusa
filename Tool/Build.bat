::Packer
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Packer\Packer.vcxproj /p:Configuration=Release;Platform=Win32
copy Packer\Release\mp.exe ..\Release\mp.exe
rmdir /s /q Packer\Release
pause


::IndexGenerator
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" IndexGenerator\IndexGenerator\IndexGenerator.csproj /p:Configuration=Release;Platform=AnyCPU
copy IndexGenerator\IndexGenerator\bin\Release\IndexGenerator.exe ..\Release\IndexGenerator.exe
rmdir /s /q IndexGenerator\IndexGenerator\bin
rmdir /s /q IndexGenerator\IndexGenerator\obj
pause


::FileWrapper
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" FileWrapper\FileWrapper\FileWrapper.csproj /p:Configuration=Release;Platform=AnyCPU
copy FileWrapper\FileWrapper\bin\Release\FileWrapper.exe ..\Release\FileWrapper.exe
rmdir /s /q FileWrapper\FileWrapper\bin
rmdir /s /q FileWrapper\FileWrapper\obj
pause


::SirenCompiler
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" SirenCompiler\SirenCompiler.vcxproj /p:Configuration=Release;Platform=Win32
copy SirenCompiler\Release\sc.exe ..\Release\sc.exe
rmdir /s /q SirenCompiler\Release
pause
