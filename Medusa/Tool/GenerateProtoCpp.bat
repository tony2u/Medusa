..\..\Release\sc create ..\Proto\Core.mpb ..\Proto\Core
..\..\Release\sc create ..\Proto\Engine.mpb ..\Proto\Engine -r ..\Proto\Core.mpb

..\..\Release\sc gen cpp ..\Proto\Core.mpb -t MedusaCoreTemplate -o ..\MedusaCore
..\..\Release\sc gen cpp ..\Proto\Engine.mpb -t MedusaTemplate -o ..\Medusa
pause