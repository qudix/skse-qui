Set-Location ".."
cmake --preset vs2022-windows-vcpkg
Write-Host -NoNewLine 'Press any key to continue...';
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');
