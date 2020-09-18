

include_directories(AFTER 
	./
	yaml-0.1.7/include
	yaml-0.1.7/src
)

set(SRC_FILES
    yaml-0.1.7/src/api.c
    yaml-0.1.7/src/dumper.c
	yaml-0.1.7/src/emitter.c
	yaml-0.1.7/src/loader.c
	yaml-0.1.7/src/parser.c
	yaml-0.1.7/src/reader.c
	yaml-0.1.7/src/scanner.c
	yaml-0.1.7/src/writer.c
	yaml-0.1.7/src/yaml_private.h
)



add_library(yaml ${SRC_FILES})

install (TARGETS yaml
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



