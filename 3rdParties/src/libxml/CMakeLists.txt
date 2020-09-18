

include_directories(AFTER 
	./
)

set(SRC_FILES
	libxml2/buf.c 
	libxml2/c14n.c 
	libxml2/catalog.c 
	libxml2/chvalid.c 
	libxml2/debugXML.c 
	libxml2/dict.c 
	libxml2/DOCBparser.c 
	libxml2/encoding.c 
	libxml2/entities.c 
	libxml2/error.c 
	libxml2/globals.c 
	libxml2/hash.c 
	libxml2/HTMLparser.c 
	libxml2/HTMLtree.c 
	libxml2/legacy.c 
	libxml2/list.c 
	libxml2/nanoftp.c 
	libxml2/nanohttp.c 
	libxml2/parser.c 
	libxml2/parserInternals.c 
	libxml2/pattern.c 
	libxml2/relaxng.c 
	libxml2/SAX2.c 
	libxml2/SAX.c 
	libxml2/schematron.c 
	libxml2/threads.c 
	libxml2/tree.c 
	libxml2/uri.c 
	libxml2/valid.c 
	libxml2/xinclude.c 
	libxml2/xlink.c 
	libxml2/xmlIO.c 
	libxml2/xmlmemory.c 
	libxml2/xmlreader.c 
	libxml2/xmlregexp.c 
	libxml2/xmlmodule.c 
	libxml2/xmlsave.c 
	libxml2/xmlschemas.c 
	libxml2/xmlschemastypes.c 
	libxml2/xmlunicode.c 
	libxml2/xmlwriter.c 
	libxml2/xpath.c 
	libxml2/xpointer.c 
	libxml2/xmlstring.c
)






add_library(xml2 ${SRC_FILES})


install (TARGETS xml2
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)




