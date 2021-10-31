robocopy "%~dp0../build/Release/" "%~dp0package/SKSE/Plugins/" "*.dll"
robocopy "%~dp0../res/" "%~dp0package/SKSE/Plugins/" "*.toml"
robocopy "%~dp0../src/swf/" "%~dp0package/Interface/" "*.swf"
tar -a --cd "package" -c -f "QUI-0.2.1.zip" "*.*"
rmdir /q /s package
