#
RESULT_BUILD=../../../bin/SFResultCodeCompiler.exe



COREBASE_OUTPUT_PATH=../../Src/SFCore/ResultCode
COREBASE_SOURCES=ResultCodeLibrary.xml \


ENGINE_OUTPUT_PATH=../../Src/SFEngine/ResultCode
ENGINE_SOURCES=ResultCodeEngine.xml \


ENGINE_SHARP_OUTPUT_PATH=../../Src/SFEngineDLL/Sharp/ResultCode


	
COREBASE_SOURCES_POSTFIXED=$(COREBASE_SOURCES:.xml=.h)
COREBASE_TARGET_FILES=$(COREBASE_SOURCES_POSTFIXED:%=$(COREBASE_OUTPUT_PATH)/SF%)


$(COREBASE_OUTPUT_PATH)/SF%.h: %.xml $(RESULT_BUILD)
	$(RESULT_BUILD) +out=$(COREBASE_OUTPUT_PATH)/ +facility=ResultFacility.xml +outSharp=$(ENGINE_SHARP_OUTPUT_PATH) +in=$<
 

ENGINE_SOURCES_POSTFIXED=$(ENGINE_SOURCES:.xml=.h)
ENGINE_TARGET_FILES=$(ENGINE_SOURCES_POSTFIXED:%=$(ENGINE_OUTPUT_PATH)/SF%)


$(ENGINE_OUTPUT_PATH)/SF%.h: %.xml $(RESULT_BUILD)
	$(RESULT_BUILD) +out=$(ENGINE_OUTPUT_PATH)/ +facility=ResultFacility.xml +outSharp=$(ENGINE_SHARP_OUTPUT_PATH) +in=$<
 

build: $(COREBASE_SOURCES) $(ENGINE_SOURCES) $(COREBASE_TARGET_FILES) $(ENGINE_TARGET_FILES) 
	@echo Done


clean:
	rm $(COREBASE_TARGET_FILES) $(ENGINE_TARGET_FILES) 

