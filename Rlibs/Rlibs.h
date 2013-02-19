#ifndef __RLIBS_DLLEXPORT_INCLUDED_H__
#define __RLIBS_DLLEXPORT_INCLUDED_H__

#ifdef RLIBS_EXPORTS
#define RLIBS_API __declspec(dllexport)
#else
#define RLIBS_API __declspec(dllimport)
#endif

#define __rip	// input parameter
#define __rop	// output parameter
#define __riop	// input & output parameter

#include "Rlibs_file.h"

#endif // __RLIBS_DLLEXPORT_INCLUDED_H__
