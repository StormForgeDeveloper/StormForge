#
PROTO_BUILD=../../../bin/SFProtocolCompiler.exe



OUTPUT_PATH=../../Src/Protocol/Protocol/Message
OUTPUT_DOC_PATH=../../../Doc/Protocol
OUTPUT_CPP_PATH=$(OUTPUT_PATH)
OUTPUT_SHARPCPP_PATH=../../Src/SFEngineDLL/SharpCPP
OUTPUT_SHARP_PATH=../../Src/SFEngineDLL/Sharp

PROTO_BUILD_PARAM_CPP=+outCPP=$(OUTPUT_CPP_PATH) +outSharp=$(OUTPUT_SHARP_PATH) +VariableMapParser=true +gen=MessageClassBuilder  +gen=MessageParsingMapBuilder  +gen=MessageDebugBuilder  
PROTO_BUILD_PARAM_CPP_POLICY=+outCPP=../../Src/Protocol/Protocol/Policy +gen=MessageNetPolicyBuilder
PROTO_BUILD_PARAM_SHARP=+outCPP=$(OUTPUT_SHARPCPP_PATH) +outSharp=$(OUTPUT_SHARP_PATH) +VariableMapParser=true  +gen=MessageAdapterCSharpBuilder +gen=MessageIDCSharpBuilder
PROTO_BUILD_PARAM_DOC=+out=$(OUTPUT_DOC_PATH) +gen=MessageGithubDocBuilder


SOURCES=ProtocolGame.xml \
	ProtocolLogin.xml \
	ProtocolPlayInstance.xml


SOURCES_POSTFIXED=$(SOURCES:.xml=.h)
TARGET_FILES=$(SOURCES_POSTFIXED:%=$(OUTPUT_PATH)/%)


.PHONY = build clean


$(OUTPUT_PATH)/%.h: %.xml $(PROTO_BUILD)
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_CPP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_CPP_POLICY) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_SHARP) +in=$<
	$(PROTO_BUILD) $(PROTO_BUILD_PARAM_DOC) +in=$<
 

build: $(SOURCES) $(TARGET_FILES) 
	@echo Done


clean:
	rm $(OUTPUT_PATH)/*.h
	rm $(OUTPUT_PATH)/*.cpp
	rm -R Temp/*