#pragma once




//#ifndef WIN32
//#define WITH_LIBDL 1
//#define HAVE_REGEX 1
//#define HAVE_STRNDUP 1
//#else
//#endif


//#define WITH_ZLIB 1
//#define WITH_SNAPPY 1
//#define WITH_ZSTD 1
/* zstd is linked dynamically on Windows, but the dynamic library provides
 * the experimental/advanced API, just as the static builds on *nix */
//#define WITH_ZSTD_STATIC 1
//#define WITH_SASL_SCRAM 1
//#define WITH_SASL_OAUTHBEARER 1
//#define ENABLE_DEVEL 0
//#define WITH_PLUGINS 1
//#define WITH_HDRHISTOGRAM 1


//#ifndef WIN32
//#define SOLIB_EXT ".dll"
//#else
//#define SOLIB_EXT ".so"
//#endif

 /* Notice: Keep up to date */
#define BUILT_WITH "ZLIB SNAPPY PLUGINS HDRHISTOGRAM"
