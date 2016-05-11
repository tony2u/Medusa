..\..\..\Release\mp create main.mpk -c LZ4 -c AES256 -k 123456 --whole -e
..\..\..\Release\mp rule main.mpk -k 123456 .png -c AES256
..\..\..\Release\mp add main.mpk -r ../Dev/Resource -k 123456

del /f  /q "../Dev\Resource\*.*"
rmdir /S /Q "../Dev\Resource\"
mkdir "../Dev\Resource\"
move  main.mpk "../Dev\Resource\main.mpk"

