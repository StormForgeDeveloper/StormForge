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


PROTO_BUILD_PARAM_CPP=$(TYPE_DEF) +out=$(OUTPUT_CPP_PATH) +gen=MessageIDCppBuilder +gen=ProtocolRPCCppBuilder +gen=ProtocolMessageLogCppBuilder 

PROTO_BUILD_PARAM_SHARP=$(TYPE_DEF) +out=$(OUTPUT_SHARP_PATH) +gen=ProtocolRPCCSharpBuilder +gen=MessageIDCSharpBuilder+CSharpProtocolNamespace=SF.MessageProtocol
PROTO_BUILD_PARAM_DOC=$(TYPE_DEF) +out=$(OUTPUT_DOC_PATH) +gen=MessageGithubDocBuilder
PROTO_BUILD_PARAM_STRING=$(TYPE_DEF) +out=$(OUTPUT_STRING_PATH) +gen=MessageStringTableBuilder
PROTO_BUILD_PARAM_FLAT=$(TYPE_DEF) +out=$(OUTPUT_FLATBUFFER_PATH) +gen=MessageFlatbufferBuilder  +include=SFTypes.fbs
PROTO_BUILD_PARAM_FLAT_CPP=$(TYPE_DEF) +out=$(OUTPUT_CPP_PATH) +gen=MessageIDCppBuilder


SOURCES=Generic.xml \
	Game.xml \
	PlayInstance.xml

SOURCES_POSTFIXED=$(SOURCES:.xml=RPCSendAdapter.h)
TARGET_CPP_FILES=$(SOURCES_POSTFIXED:%=$(OUTPUT_PATH)/%)

$(OUTPUT_PATH)/%RPCSendAdapter.h: %.xml $(PROTO_BUILD)
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_CPP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_CPP_POLICY) +in=$<


MESSAGEBUS_SOURCES=Generic.xml \
    Login.xml \
	Game.xml \
	PlayInstance.xml \
	Telemetry.xml 

MESSAGEBUS_SOURCES_POSTFIXED=$(MESSAGEBUS_SOURCES:.xml=.fbs)
MESSAGEBUS_TARGET_FILES=$(MESSAGEBUS_SOURCES_POSTFIXED:%=$(OUTPUT_FLATBUFFER_PATH)/%)

$(OUTPUT_FLATBUFFER_PATH)/%.fbs: %.xml $(PROTO_BUILD)
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_FLAT) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_FLAT_CPP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_SHARP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_SHARP_CPP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_DOC) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_STRING) +in=$<




.PHONY = build clean




build: $(SOURCES) $(TARGET_CPP_FILES) $(MESSAGEBUS_TARGET_FILES)
	@echo Done


clean:
	rm -R $(OUTPUT_PATH)/*.h
	rm -R $(OUTPUT_PATH)/*.cpp
