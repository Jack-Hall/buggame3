@echo off
echo Building Bug Game 3...

REM Clean build directory if it exists
if exist build (
    echo Cleaning previous build...
    rmdir /s /q build
)

mkdir build
cd build

REM Try different generators in order of preference
echo Configuring with CMake...
cmake .. -G "Visual Studio 16 2019" -A x64 2>nul
if errorlevel 1 (
    echo Visual Studio 2019 not found, trying Visual Studio 17 2022...
    cmake .. -G "Visual Studio 17 2022" -A x64 2>nul
    if errorlevel 1 (
        echo Visual Studio generators not found, trying MinGW...
        cmake .. -G "MinGW Makefiles" 2>nul
        if errorlevel 1 (
            echo Trying default generator...
            cmake ..
            if errorlevel 1 (
                echo CMake configuration failed with all generators!
                pause
                exit /b 1
            )
        )
    )
)

echo Building project...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
echo.
if exist Release\BugGame3.exe (
    echo Run Release\BugGame3.exe to start the game
) else if exist BugGame3.exe (
    echo Run BugGame3.exe to start the game
) else (
    echo Executable created, check the build directory
)
pause
