#ifndef WL_DESKTOP_H
#define WL_DESKTOP_H

#include <WinLib/Window/WindowHandle.hpp>

namespace System
{
    class CDesktop : public Window::CWindowHandle
    {
    public:
        CDesktop() : CWindowHandle(GetDesktopWindow()) {}
    };

    CDesktop  Desktop ;
}


#endif // !WL_DESKTOP_H