[Setup]
AppName=Serial Forge
AppVersion=0.1
DefaultDirName={autopf}\Serial Forge
DefaultGroupName=Serial Forge
OutputDir=.\installer
OutputBaseFilename=SerialForge_Setup
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
SetupIconFile=app_icon.ico

[Files]
Source: "dist\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\Serial Forge"; Filename: "{app}\serial-forge.exe"
Name: "{autodesktop}\Serial Forge"; Filename: "{app}\serial-forge.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
