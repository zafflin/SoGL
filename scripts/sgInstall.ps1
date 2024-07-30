# Store the script directory (SoGL/SoGL_x64/scripts) in a variable
$SG_SCR_DIR = Get-Location

# Append the script directory to the PATH
$currentPath = [Environment]::GetEnvironmentVariable("PATH", [EnvironmentVariableTarget]::User)
$newPath = $currentPath + ";" + $SG_SCR_DIR
[Environment]::SetEnvironmentVariable("PATH", $newPath, [EnvironmentVariableTarget]::User)

# Move up one directory to set the SoGL base directory (SoGL/SoGL_x64)
Set-Location ..

# Store SoGL base directory in a variable
$SG_DIR = Get-Location

# Set the SG_DIR environment variable
[Environment]::SetEnvironmentVariable("SG_DIR", $SG_DIR, [EnvironmentVariableTarget]::User)

# Set the SG_INC_DIR environment variable (SoGL/SoGL_x64/include)
$SG_INC_DIR = Join-Path $SG_DIR -ChildPath "include"
[Environment]::SetEnvironmentVariable("SG_INC_DIR", $SG_INC_DIR, [EnvironmentVariableTarget]::User)

# Set the SG_LIB_DIR environment variable (SoGL/SoGL_x64/lib)
$SG_LIB_DIR = Join-Path $SG_DIR -ChildPath "lib"
[Environment]::SetEnvironmentVariable("SG_LIB_DIR", $SG_LIB_DIR, [EnvironmentVariableTarget]::User)

# Set the PATH variable with the new contents
[Environment]::SetEnvironmentVariable("PATH", $newPath, [EnvironmentVariableTarget]::User)

# Display the updated PATH for verification
Write-Host "a simple PATH was set :: $newPath"

Read-Host -Prompt "simply press enter to continue . . ."
