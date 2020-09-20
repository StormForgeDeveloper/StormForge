


###################################################

ifndef BASE_PATH
	error BASE_PATH need to be defined
endif

###################################################

BUILD_LIBS = toolLib CreatePath copyfile shellbridge, httpget
SHARP_FLAGS = 

ifeq ($(BUILD_CONFIGURATION), 'DEBUG')
	SHARP_FLAGS = -debug
endif	

export SHARP_FLAGS

	
build : 
	for buildTool in $(BUILD_LIBS); do \
		$(MAKE) -C $$buildTool build; \
	done



