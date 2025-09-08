#!/usr/bin/env pwsh

Write-Host "Building Bug Game 3..." -ForegroundColor Green

# Clean build directory if it exists
if (Test-Path "build") {
    Write-Host "Cleaning previous build..." -ForegroundColor Yellow
    Remove-Item -Recurse -Force "build"
}

# Create build directory
New-Item -ItemType Directory -Name "build" | Out-Null
Set-Location "build"

# Try different generators in order of preference
Write-Host "Configuring with CMake..." -ForegroundColor Cyan

$generators = @(
    @{Name="Visual Studio 17 2022"; Args=@("..", "-G", "Visual Studio 17 2022", "-A", "x64")},
    @{Name="Visual Studio 16 2019"; Args=@("..", "-G", "Visual Studio 16 2019", "-A", "x64")},
    @{Name="MinGW Makefiles"; Args=@("..", "-G", "MinGW Makefiles")},
    @{Name="Default"; Args=@("..")}
)

$configured = $false
foreach ($generator in $generators) {
    Write-Host "Trying $($generator.Name)..." -ForegroundColor Gray
    
    $result = Start-Process -FilePath "cmake" -ArgumentList $generator.Args -Wait -PassThru -WindowStyle Hidden
    if ($result.ExitCode -eq 0) {
        Write-Host "Successfully configured with $($generator.Name)" -ForegroundColor Green
        $configured = $true
        break
    }
}

if (-not $configured) {
    Write-Host "CMake configuration failed with all generators!" -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}

# Build the project
Write-Host "Building project..." -ForegroundColor Cyan
$buildResult = Start-Process -FilePath "cmake" -ArgumentList @("--build", ".", "--config", "Release") -Wait -PassThru -WindowStyle Hidden

if ($buildResult.ExitCode -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}

Write-Host "Build completed successfully!" -ForegroundColor Green
Write-Host ""

# Find the executable
$exePaths = @("Release\BugGame3.exe", "BugGame3.exe")
$exeFound = $false

foreach ($path in $exePaths) {
    if (Test-Path $path) {
        Write-Host "Run $path to start the game" -ForegroundColor Yellow
        $exeFound = $true
        break
    }
}

if (-not $exeFound) {
    Write-Host "Executable created, check the build directory" -ForegroundColor Yellow
}

Read-Host "Press Enter to exit"
