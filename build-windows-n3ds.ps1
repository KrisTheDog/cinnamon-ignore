[CmdletBinding()]
param(
    [string]$BuildDir = "build\n3ds",
    [string]$Configuration = "Release",
    [switch]$NoPause
)

$ErrorActionPreference = "Stop"

$cmakeExe = "C:\devkitPro\msys2\usr\bin\cmake.exe"
$msysBin = "C:\devkitPro\msys2\usr\bin"
$toolchainFile = "/opt/devkitpro/cmake/3DS.cmake"

try {
    if (-not (Test-Path $cmakeExe)) {
        throw "devkitPro CMake was not found at '$cmakeExe'. Install devkitPro with the MSYS2 tools first."
    }

    $env:PATH = "$msysBin;$env:PATH"

    & $cmakeExe --fresh -S . -B $BuildDir -G "Unix Makefiles" `
        "-DCMAKE_TOOLCHAIN_FILE=$toolchainFile" `
        -DPLATFORM=n3ds `
        "-DCMAKE_BUILD_TYPE=$Configuration"
    if ($LASTEXITCODE -ne 0) {
        throw "3DS CMake configure failed."
    }

    & $cmakeExe --build $BuildDir
    if ($LASTEXITCODE -ne 0) {
        throw "3DS build failed."
    }

    Write-Host ""
    Write-Host "3DS build completed successfully." -ForegroundColor Green
}
catch {
    Write-Host ""
    Write-Host "3DS build failed." -ForegroundColor Red
    Write-Host $_
    exit 1
}
finally {
    if (-not $NoPause) {
        Write-Host ""
        Read-Host "Press Enter to close"
    }
}
