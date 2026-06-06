@echo off
cd /d "%~dp0"
if exist venv\Scripts\activate.bat (
    call venv\Scripts\activate.bat
    python gui.py
) else (
    echo El entorno virtual no existe. Por favor, instalalo primero.
    pause
)
