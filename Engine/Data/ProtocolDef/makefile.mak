#

FLAC_COMPILER=../../../3rdParties/Linux/Release/bin/flatc

OUTPUT_CSHARP_PATH=../../Src/SFProtocolSharp
OUTPUT_CPP_PATH=../../Src/Protocol/SFFlat

PARAMETER_CSHARP=-o $(OUTPUT_CSHARP_PATH) --csharp
PARAMETER_CPP=-o $(OUTPUT_CPP_PATH) --cpp --cpp-str-flex-ctor --cpp-std c++17 --cpp-static-reflection


SOURCES=SFTypes.fbs \
	LocalTypes.fbs \
	Generic.fbs \
	Login.fbs \
	Telemetry.fbs \
	Game.fbs \
	PlayInstance.fbs


SOURCES_POSTFIXED=$(SOURCES:.fbs=.h)
TARGET_FILES=$(SOURCES_POSTFIXED:%=$(OUTPUT_CPP_PATH)/%)


$(OUTPUT_CPP_PATH)/%.h: %.fbs $(FLAC_COMPILER)
	$(FLAC_COMPILER) $(PARAMETER_CSHARP) $<
	$(FLAC_COMPILER) $(PARAMETER_CPP) $<


build: $(TARGET_FILES) 
	@echo Done


clean:
	@echo $(OUTPUT_CPP_PATH)
	rm -R --f $(OUTPUT_CSHARP_PATH)/SF/Flat/*

