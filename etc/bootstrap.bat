@echo off
where.exe /q wt
IF ERRORLEVEL 1 (
    pwsh.exe -Command "& '%~dpn0.ps1'"
) ELSE (
    wt.exe -w 0 -d %~dp0 pwsh.exe -Command "& '%~dpn0.ps1'"
)
