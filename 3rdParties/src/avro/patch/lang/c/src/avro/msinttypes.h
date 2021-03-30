// ISO C9x  compliant inttypes.h for Microsoft Visual Studio
// Based on ISO/IEC 9899:TC2 Committee draft (May 6, 2005) WG14/N1124 
// 
//  Copyright (c) 2006 Alexander Chemeris
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//   1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
// 
//   2. Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
// 
//   3. The name of the author may be used to endorse or promote products
//      derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_INTTYPES_H_ // [
#define _MSC_INTTYPES_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////
// Start AVRO specific modifications
//////////////////////////////////////
#include "msstdint.h"

// Modification for AVRO of inttypes.h
#define __STDC_FORMAT_MACROS (1)

//////////////////////////////////////
// End AVRO specific modifications
//////////////////////////////////////

// Blue3k-MOD

// 7.8.1 Macros for format specifiers

// 7.8.2 Functions for greatest-width integer types

// 7.8.2.1 The imaxabs function
#define imaxabs _abs64

// 7.8.2.2 The imaxdiv function


// 7.8.2.3 The strtoimax and strtoumax functions
#define strtoimax _strtoi64
#define strtoumax _strtoui64

// 7.8.2.4 The wcstoimax and wcstoumax functions
#define wcstoimax _wcstoi64
#define wcstoumax _wcstoui64


#endif // _MSC_INTTYPES_H_ ]
