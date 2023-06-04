function Add-Path($Path) {
    $Path = [Environment]::GetEnvironmentVariable("Path", "User") + [IO.Path]::PathSeparator + $Path
    [Environment]::SetEnvironmentVariable( "Path", $Path, "User" )
}

$new_path = "C:\curl\builds\libcurl-vc14-x64-release-dll-ipv6-sspi-schannel\bin"
$current_path = [Environment]::GetEnvironmentVariable("Path", "User")
if($current_path -notlike "*$new_path*") {
    Add-Path($new_path)
}