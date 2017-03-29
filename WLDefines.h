#pragma once
#define WL_ASSERT(expression) do { assert(expression); } while(0)
#define WL_TRACE(...) do { printf("WL_TRACE called in file: %s\nline: %d\nfunc: %s\nMESSAGE:" , __FILE__, __LINE__, __FUNCSIG__); printf(__VA_ARGS__); } while(0)
#define NULLHWND (HWND)0
#define NOFLAGS 0