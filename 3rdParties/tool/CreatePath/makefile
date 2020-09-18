

SRC_LIST = Program.cs Properties/AssemblyInfo.cs



build :
	mcs $(SHARP_FLAGS) $(SRC_LIST) -r:$(BASE_PATH)tool/bin/toolLib.dll -out:$(BASE_PATH)tool/bin/createpath.exe

