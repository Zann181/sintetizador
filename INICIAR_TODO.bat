@echo off
title TR-808 Algorithmic Station
color 0B
echo ========================================================
echo INICIANDO TR-808 ALGORITHMIC STATION
echo ========================================================
echo.
echo Iniciando puente de Ableton Link...
start cmd /k "run_bridge.bat"
echo.
echo Iniciando el motor de sintesis BAZZ...
start cmd /k "bazz.exe"
echo.
echo La interfaz deberia abrirse en el navegador automaticamente.
echo (http://localhost:8000)
echo.
echo NOTA: Para que suene, recuerda marcar los pads (pasos) 
echo en el secuenciador de la pagina web.
pause
