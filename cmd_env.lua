
local MONO = "\"C:/Program Files (x86)/Mono/bin/setmonopath.bat\"";

local VC = "\"C:/Program Files (x86)/Microsoft Visual Studio 12.0/"..
"Common7/Tools/VsDevCmd.bat\""

os.execute(
	"start \"Rigby CMD\" cmd /k".."\""..
	MONO.." & "..VC..
	"\"");