mp create Resource/main.mpk -c LZ4 -c AES256 -k 123456 --whole -e
pause
mp rule Resource/main.mpk -k 123456 .png -c AES256
pause
mp add Resource/main.mpk -r Res -k 123456
pause
mp info Resource/main.mpk -k 123456
pause
mp list Resource/main.mpk -k 123456
pause
														  