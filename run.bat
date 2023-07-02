@echo off
SETLOCAL

REM Get the port number from the command line argument
SET PORT=%1

REM Get the build option from the command line argument
SET BUILD_OPTION=%2

REM Get the current target
for /f "tokens=2 delims==" %%a in ('findstr /b CONFIG_IDF_TARGET_ESP32 sdkconfig') do set current_target=%%~a

REM Check if the target is esp32
IF "%current_target%"=="y" (
    echo "Target is already set to esp32"
) ELSE (
    echo "Setting target to esp32"
    idf.py set-target esp32
)

REM Build the project
echo "Building the project"

IF "%BUILD_OPTION%"=="clean" (
    idf.py fullclean build
) ELSE (
    idf.py build
)
IF %errorlevel% NEQ 0 (
    echo "Build failed"
    exit /b 1
)


IF "%PORT%"=="" (
    echo "No port number provided"
    exit /b 1
)

REM Flash the firmware
echo "Flashing the firmware"
idf.py -p %PORT% flash
IF %errorlevel% NEQ 0 (
    echo "Flashing failed"
    exit /b 1
)

echo "Done"
ENDLOCAL
