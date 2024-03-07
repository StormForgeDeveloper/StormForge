#
PROTO_BUILD=../../../bin/net8.0/SFProtocolCompiler.exe
TYPE_DEF=+TypeDef=ProtocolTypes.xml


OUTPUT_PATH=../../Src/Protocol/Protocol
OUTPUT_DOC_PATH=../../../Doc/Protocol
OUTPUT_STRING_PATH=../stringcrc
OUTPUT_CPP_PATH=$(OUTPUT_PATH)
OUTPUT_FLATBUFFER_PATH=../ProtocolDef
OUTPUT_SHARPCPP_PATH=../../Src/SFEngineDLL/SharpCPP
OUTPUT_SHARP_PATH=../../Src/SFProtocolSharp/Protocol


PROTO_BUILD_PARAM_CPP=$(TYPE_DEF) +out=$(OUTPUT_CPP_PATH) +VariableMapParser=true +gen=MessageClassBuilder +gen=MessageParsingMapBuilder +gen=MessageDebugBuilder +gen=MessageIDCppBuilder
PROTO_BUILD_PARAM_CPP_POLICY=$(TYPE_DEF) +out=$(OUTPUT_CPP_PATH) +gen=MessageNetPolicyBuilder
PROTO_BUILD_PARAM_SHARP=$(TYPE_DEF) +out=$(OUTPUT_SHARP_PATH) +VariableMapParser=true +gen=MessageAdapterCSharpBuilder +gen=MessageIDCSharpBuilder +CSharpProtocolNamespace=SF.MessageProtocol
PROTO_BUILD_PARAM_SHARP_CPP=$(TYPE_DEF) +out=$(OUTPUT_SHARPCPP_PATH) +VariableMapParser=true +gen=MessageAdapterCSharpCPPBuilder
PROTO_BUILD_PARAM_DOC=$(TYPE_DEF) +out=$(OUTPUT_DOC_PATH) +gen=MessageGithubDocBuilder
PROTO_BUILD_PARAM_STRING=$(TYPE_DEF) +out=$(OUTPUT_STRING_PATH) +gen=MessageStringTableBuilder
PROTO_BUILD_PARAM_FLAT=$(TYPE_DEF) +out=$(OUTPUT_FLATBUFFER_PATH) +gen=MessageFlatbufferBuilder



SOURCES=ProtocolGeneric.xml \
    ProtocolLogin.xml \
	ProtocolGame.xml \
	ProtocolPlayInstance.xml \
	ProtocolTelemetry.xml 


SOURCES_POSTFIXED=$(SOURCES:.xml=.h)
TARGET_FILES=$(SOURCES_POSTFIXED:%=$(OUTPUT_PATH)/%)


.PHONY = build clean


$(OUTPUT_PATH)/%.h: %.xml $(PROTO_BUILD)
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_CPP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_CPP_POLICY) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_SHARP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_SHARP_CPP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_DOC) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_STRING) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_FLAT) +in=$<


build: $(SOURCES) $(TARGET_FILES) 
	@echo Done


clean:
	rm -R $(OUTPUT_PATH)/*.h
	rm -R $(OUTPUT_PATH)/*.cpp
