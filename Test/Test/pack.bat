mp create Res/res.mpk -c LZ4 -c AES256 -k 123456 --whole -e
pause
mp rule Res/res.mpk -k 123456 .png -c AES256
pause
mp add Res/res.mpk -r Resource -k 123456
pause
mp info Res/res.mpk -k 123456
pause
mp list Res/res.mpk -k 123456
pause
														  