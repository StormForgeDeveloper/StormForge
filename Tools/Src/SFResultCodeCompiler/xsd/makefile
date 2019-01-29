#


OUTPUT_PATH=../SFResultCodeCompiler
SYNC_PATH=../../LibSharp/CommonSharp/ResultCode



SOURCES=SFResultCode.xsd \
	SFResultCodeFacility.xsd 



SOURCES_POSTFIXED=$(SOURCES:.xsd=.cs)
TARGET_FILES=$(SOURCES_POSTFIXED:%=$(OUTPUT_PATH)/%)
TARGET_XSDS=$(SOURCES:%=$(SYNC_PATH)/%)


$(OUTPUT_PATH)/%.cs: %.xsd
	xsd -c -namespace:SF.Table $< /out:"..\SFResultCodeCompiler"
	@echo cp $< $@


$(SYNC_PATH)/%.xsd: %.xsd
	cp $< $@


build: $(TARGET_FILES) $(TARGET_XSDS)
	@echo Done


clean:
	rm $(TARGET_FILES)
