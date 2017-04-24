#ifndef WL_WLDEFINES_H
#define WL_WLDEFINES_H

#include <Windows.h>

#include <assert.h>
#include <stdio.h>

namespace WL_DEFINES_NAMESPACE__DO_NOT_USE_IT
{
    void trace_printf(char* FormatStr, ...)
    {

    }
}

#define WL_NOVTABLE __declspec(novtable)

#ifndef WL_RELEASE
#define WL_TRACE(...) do { printf("WL_TRACE called in file: %s\n\nline: %d\n\nfunc: %s\n\nMESSAGE:" , __FILE__, __LINE__, __FUNCSIG__); printf(__VA_ARGS__); printf("\n\n\n"); } while(0)
#else
#define WL_TRACE(...)
#endif

#define WL_CTOR_TRACE WL_TRACE("Ctor, this = %p", this)
#define WL_DTOR_TRACE WL_TRACE("Dtor, this = %p", this)

#ifndef WL_RELEASE
	#define WL_ASSERT(expression) do { if (!(expression)) {WL_TRACE("Assertation faled!!! Expr:%s", #expression); DebugBreak();} } while(0)
#else
	#define WL_ASSERT(expression)
#endif

#ifndef WL_DOT_NO_ASSERT_STRINGS_LENGTH_IN_WINAPI_FUNCTIONS
	#define WL_ASSERT_STRLEN(length) WL_ASSERT(length)
#else
	#define WL_ASSERT_STRLEN(length)
#endif

#define WL_TODO

#define NULLHWND (HWND)0
#define NOFLAGS 0

#endif //!WL_WLDEFINES_H