



del /f /s /q /a ..\Data\Animation\*.*
del /f /s /q /a ..\Dev\Resource\Animation\*.*
xcopy /Y  /E  "..\Art\Animation\*.*" "..\Data\Animation\*.*"
xcopy /Y  /E  "..\Data\Animation\*.*" "..\Dev\Resource\Animation\*.*"

del /f /s /q /a ..\Data\Atlas\*.*
del /f /s /q /a ..\Dev\Resource\Atlas\*.*
xcopy /Y  /E  "..\Art\Atlas\*.*" "..\Data\Atlas\*.*"
xcopy /Y  /E  "..\Data\Atlas\*.*" "..\Dev\Resource\Atlas\*.*"

del /f /s /q /a ..\Data\Audio\*.*
del /f /s /q /a ..\Dev\Resource\Audio\*.*
xcopy /Y  /E  "..\Art\Audio\*.*" "..\Data\Audio\*.*"
xcopy /Y  /E  "..\Data\Audio\*.*" "..\Dev\Resource\Audio\*.*"


del /f /s /q /a ..\Data\Config\*.*
del /f /s /q /a ..\Dev\Resource\Config\*.*
xcopy /Y  /E  "..\Art\Config\*.*" "..\Data\Config\*.*"
xcopy /Y  /E  "..\Data\Config\*.*" "..\Dev\Resource\Config\*.*"

del /f /s /q /a ..\Data\Editor\*.*
del /f /s /q /a ..\Dev\Resource\Editor\*.*
xcopy /Y  /E  "..\Art\Editor\*.*" "..\Data\Editor\*.*"
xcopy /Y  /E  "..\Data\Editor\*.*" "..\Dev\Resource\Editor\*.*"


del /f /s /q /a ..\Data\Font\*.*
del /f /s /q /a ..\Dev\Resource\Font\*.*
xcopy /Y  /E  "..\Art\Font\*.*" "..\Data\Font\*.*"
xcopy /Y  /E  "..\Data\Font\*.*" "..\Dev\Resource\Font\*.*"

del /f /s /q /a ..\Data\Images\*.*
del /f /s /q /a ..\Dev\Resource\Images\*.*
xcopy /Y  /E  "..\Art\Images\*.*" "..\Data\Images\*.*"
xcopy /Y  /E  "..\Data\Images\*.*" "..\Dev\Resource\Images\*.*"

del /f /s /q /a ..\Data\Model\*.*
del /f /s /q /a ..\Dev\Resource\Model\*.*
xcopy /Y  /E  "..\Art\Model\*.*" "..\Data\Model\*.*"
xcopy /Y  /E  "..\Data\Model\*.*" "..\Dev\Resource\Model\*.*"

del /f /s /q /a ..\Data\Other\*.*
del /f /s /q /a ..\Dev\Resource\Other\*.*
xcopy /Y  /E  "..\Art\Other\*.*" "..\Data\Other\*.*"
xcopy /Y  /E  "..\Data\Other\*.*" "..\Dev\Resource\Other\*.*"

del /f /s /q /a ..\Data\Script\Medusa\*.*
del /f /s /q /a ..\Dev\Resource\Script\*.*
xcopy /Y  /E  "..\..\..\Medusa\Script\*.*" "..\Data\Script\*.*"
xcopy /Y  /E  "..\Data\Script\*.*" "..\Dev\Resource\Script\*.*"


del /f /s /q /a ..\Dev\Debug\Resource\*.*
xcopy /Y  /E  "..\Dev\Resource\*.*" "..\Dev\Debug\Resource\*.*"

del /f /s /q /a ..\..\..\Medusa\Debug\Resource\*.*
xcopy /Y  /E  "..\Dev\Resource\*.*" "..\..\..\Medusa\Debug\Resource\*.*"