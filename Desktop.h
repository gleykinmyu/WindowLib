#pragma once

#include "window.h"
namespace wl
{
    class CDesktop : public CWindow
    {
    public:
        CDesktop() : CWindow() { SetHandle(GetDesktopWindow()); }
    };
    CDesktop  m_Desktop;
    CDesktop* Desktop = &m_Desktop;
}
