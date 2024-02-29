#
PROTO_BUILD=../../../bin/net8.0/SFProtocolCompiler.exe
TYPE_DEF=+TypeDef=ProtocolTypes.xml


OUTPUT_PATH=../../Src/Protocol/Protocol
OUTPUT_DOC_PATH=../../../Doc/Protocol
OUTPUT_STRING_PATH=../stringcrc
OUTPUT_CPP_PATH=$(OUTPUT_PATH)
OUTPUT_SHARPCPP_PATH=../../Src/SFEngineDLL/SharpCPP
OUTPUT_SHARP_PATH=../../Src/SFEngineSharp/SFEngine

PROTO_BUILD_PARAM_CPP=$(TYPE_DEF) +outCPP=$(OUTPUT_CPP_PATH) +outSharp=$(OUTPUT_SHARP_PATH) +VariableMapParser=true +gen=MessageClassBuilder  +gen=MessageParsingMapBuilder  +gen=MessageDebugBuilder  
PROTO_BUILD_PARAM_CPP_POLICY=$(TYPE_DEF) +outCPP=../../Src/Protocol/Protocol +gen=MessageNetPolicyBuilder
PROTO_BUILD_PARAM_SHARP=$(TYPE_DEF) +outCPP=$(OUTPUT_SHARPCPP_PATH) +outSharp=$(OUTPUT_SHARP_PATH) +VariableMapParser=true  +gen=MessageAdapterCSharpBuilder +gen=MessageIDCSharpBuilder
PROTO_BUILD_PARAM_DOC=$(TYPE_DEF) +out=$(OUTPUT_DOC_PATH) +gen=MessageGithubDocBuilder
PROTO_BUILD_PARAM_STRING=$(TYPE_DEF) +out=$(OUTPUT_STRING_PATH) +gen=MessageStringTableBuilder



SOURCES=ProtocolGame.xml \
	ProtocolPlayInstance.xml \
    ProtocolGeneric.xml


SOURCES_POSTFIXED=$(SOURCES:.xml=.h)
TARGET_FILES=$(SOURCES_POSTFIXED:%=$(OUTPUT_PATH)/%)


.PHONY = build clean


$(OUTPUT_PATH)/%.h: %.xml $(PROTO_BUILD)
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_CPP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_CPP_POLICY) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_SHARP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_DOC) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_STRING) +in=$<


build: $(SOURCES) $(TARGET_FILES) 
	@echo Done


clean:
	rm $(OUTPUT_PATH)/*.h
	rm $(OUTPUT_PATH)/*.cpp
	rm -R Temp/*
