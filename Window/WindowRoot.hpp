#ifndef WL_WINDOW_ROOT_H
#define WL_WINDOW_ROOT_H

#include <Windows.h>
#include <WinLib/Utility.hpp>
#include <WinLib/System.hpp>
#include <WinLib/Window/WindowDecl.hpp>
#include <WinLib/Window/WindowHandle.hpp>

namespace Window
{
    class WL_NOVTABLE CWindowRoot : public CWindowDecl
    {
    public:
		CWindowRoot() {WL_CTOR_TRACE;}
		bool Create(CWindowHandle * Parent, WndInfo& WndInfo);
		bool Create(CWindowHandle & Parent, WndInfo& WndInfo);

		~CWindowRoot();
    };
}
#endif //!WL_WINDOW_ROOT_H