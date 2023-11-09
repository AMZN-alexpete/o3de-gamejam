@echo off
REM use the O3DE CLI to export the project, build Tools and make a Windows release executable

setlocal ENABLEDELAYEDEXPANSION


set CURRENT_PATH=%~dp0
set O3DE_PATH=D:\git\o3de-stab-worktree
set O3DE_CMAKE_PATH=!O3DE_PATH!\cmake
set O3DE_PROJECT_PATH=!CURRENT_PATH!Game
set O3DE_TOOLS_BUILD_PATH=!CURRENT_PATH!Tools
set O3DE_EXPORT_SCRIPT_PATH=!O3DE_PATH!\scripts\o3de\ExportScripts\export_source_build_project.py
set O3DE_PROJECT_SEEDLIST=!O3DE_PROJECT_PATH!\AssetBundling\SeedLists\GameSeedList.seed
set OUTPUT_PATH=!CURRENT_PATH!Releases

set CMD=!O3DE_PATH!\scripts\o3de.bat export-project -es !O3DE_EXPORT_SCRIPT_PATH! --project-path !O3DE_PROJECT_PATH! --log-level INFO --build-tools --tools-build-path !O3DE_TOOLS_BUILD_PATH! -assets -noserver -nounified --platform pc --config release --archive-output zip --seedlist !O3DE_PROJECT_SEEDLIST! -out !OUTPUT_PATH! --cmake-configure-arg "-DCMAKE_MODULE_PATH=!O3DE_CMAKE_PATH! -DO3DE_BUILD_WITH_DEBUG_SYMBOLS_RELEASE=1 " --cmake-build-arg "-- /m:16 /p:CL_MPCount=32"
echo !CMD!
powershell -Command "Measure-Command {!CMD! | OUT-Default}" 

