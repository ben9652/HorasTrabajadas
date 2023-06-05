function Add-Path($Path) {
    $Path = [Environment]::GetEnvironmentVariable("Path", "User") + [IO.Path]::PathSeparator + $Path
    [Environment]::SetEnvironmentVariable( "Path", $Path, "User" )
}

# Truncar la cadena $pwd desde el final para atrás hasta encontrar el tercer '\' y guardar el resultado en $SolutionDir
$SolutionDir = Split-Path (Split-Path (Split-Path $PSScriptRoot))

$new_path = "$SolutionDir\vendor\curl\builds\libcurl-vc14-x64-release-dll-ipv6-sspi-schannel\bin"
$current_path = [Environment]::GetEnvironmentVariable("Path", "User")
if($current_path -notlike "*$new_path*") {
    Add-Path($new_path)
}