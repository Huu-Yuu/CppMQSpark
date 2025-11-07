@echo off

REM CppMQSpark Build Script (Windows)
echo === CppMQSpark Build Script ===

REM Create build directory
set BUILD_DIR=build
if not exist "%BUILD_DIR%" (
    echo Creating build directory...
    mkdir "%BUILD_DIR%"
)

REM Enter build directory
cd "%BUILD_DIR%"

REM Configure project
echo Configuring project...
cmake ..

REM Check if configuration succeeded
if %ERRORLEVEL% neq 0 (
    echo Configuration failed!
    echo Please make sure CMake is properly installed.
    pause
    exit /b 1
)

REM Build project
echo Building project...
cmake --build . --config Release

REM Store build result
set "BUILD_SUCCESS=false"
if %ERRORLEVEL% equ 0 (
    set "BUILD_SUCCESS=true"
    echo Build successful!
    
    REM Run tests (optional)
    set /p run_test=Run tests? (y/n)
    if /i "%run_test%" == "y" (
        echo Running tests...
        if exist "Release\mqspark_tests.exe" (
            cd Release
            mqspark_tests.exe
            cd ..
        ) else if exist "mqspark_tests.exe" (
            mqspark_tests.exe
        ) else if exist "..\bin\mqspark_tests.exe" (
            ..\bin\mqspark_tests.exe
        ) else (
            echo Warning: Test executable not found, skipping tests
        )
    ) else (
        echo Tests skipped.
    )
)

REM Show final result based on stored build status
if "%BUILD_SUCCESS%" == "true" (
    echo Build process completed successfully!
) else (
    echo Build failed!
    pause
    exit /b 1
)

cd ..
pause