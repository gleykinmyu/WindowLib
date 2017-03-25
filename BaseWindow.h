#pragma once
#include <windows.h>
#include "WindowHandle.h"
#include "WindowEvents.h"
#include "ClassRegistering.h"
#include "WindowCreating.h"

namespace wl
{
    class CBaseWindow : public CBaseWindowC
    {
    public:
        CBaseWindow(ClassInfo& ClsInfo);
        bool Create(CBaseWindowH* Parent, WndInfo& Info);
    };
    CBaseWindow::CBaseWindow(ClassInfo& ClsInfo) : CBaseWindowC(ClsInfo, 0) 
    {

    }
    bool CBaseWindow::Create(CBaseWindowH* Parent, WndInfo& Info) 
    { 
        return CBaseWindowC::Create(Parent, Info);
    }
}