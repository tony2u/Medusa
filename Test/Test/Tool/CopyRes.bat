



del /f /s /q /a ..\Data\Animation\*.*
xcopy /Y  /E  "..\Art\Animation\*.*" "..\Data\Animation\*.*"
xcopy /Y  /E  "..\Data\Animation\*.*" "..\Dev\Resource\Animation\*.*"

del /f /s /q /a ..\Data\Atlas\*.*
xcopy /Y  /E  "..\Art\Atlas\*.*" "..\Data\Atlas\*.*"
xcopy /Y  /E  "..\Data\Atlas\*.*" "..\Dev\Resource\Atlas\*.*"

del /f /s /q /a ..\Data\Audio\*.*
xcopy /Y  /E  "..\Art\Audio\*.*" "..\Data\Audio\*.*"
xcopy /Y  /E  "..\Data\Audio\*.*" "..\Dev\Resource\Audio\*.*"


del /f /s /q /a ..\Data\Config\*.*
xcopy /Y  /E  "..\Art\Config\*.*" "..\Data\Config\*.*"
xcopy /Y  /E  "..\Data\Config\*.*" "..\Dev\Resource\Config\*.*"

del /f /s /q /a ..\Data\Editor\*.*
xcopy /Y  /E  "..\Art\Editor\*.*" "..\Data\Editor\*.*"
xcopy /Y  /E  "..\Data\Editor\*.*" "..\Dev\Resource\Editor\*.*"


del /f /s /q /a ..\Data\Font\*.*
xcopy /Y  /E  "..\Art\Font\*.*" "..\Data\Font\*.*"
xcopy /Y  /E  "..\Data\Font\*.*" "..\Dev\Resource\Font\*.*"

del /f /s /q /a ..\Data\Images\*.*
xcopy /Y  /E  "..\Art\Images\*.*" "..\Data\Images\*.*"
xcopy /Y  /E  "..\Data\Images\*.*" "..\Dev\Resource\Images\*.*"

del /f /s /q /a ..\Data\Model\*.*
xcopy /Y  /E  "..\Art\Model\*.*" "..\Data\Model\*.*"
xcopy /Y  /E  "..\Data\Model\*.*" "..\Dev\Resource\Model\*.*"

del /f /s /q /a ..\Data\Other\*.*
xcopy /Y  /E  "..\Art\Other\*.*" "..\Data\Other\*.*"
xcopy /Y  /E  "..\Data\Other\*.*" "..\Dev\Resource\Other\*.*"

del /f /s /q /a ..\Data\Script\Medusa\*.*
xcopy /Y  /E  "..\..\..\Medusa\Script\*.*" "..\Data\Script\*.*"
xcopy /Y  /E  "..\Data\Script\*.*" "..\Dev\Resource\Script\*.*"


del /f /s /q /a ..\Dev\Debug\Resource\*.*
xcopy /Y  /E  "..\Dev\Resource\*.*" "..\Dev\Debug\Resource\*.*"

del /f /s /q /a ..\..\..\Medusa\Debug\Resource\*.*
xcopy /Y  /E  "..\Dev\Resource\*.*" "..\..\..\Medusa\Debug\Resource\*.*"