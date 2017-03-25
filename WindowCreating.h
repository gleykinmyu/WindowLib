#pragma once
#include <windows.h>
#include "WindowHandle.h"
#include "WindowEvents.h"
#include "ClassRegistering.h"


namespace wl
{
    //WndInfo - Help you to change some window parmeters instead changing all parmeters in once.
    //USING: foo(WndInfo&) - foo(WndInfo().Top(10).Left(112). .... )
    //                                                           /\ 
    //                                                           ||
    //                                                       Enter here setters, you need. 

    class WndInfo
    {
    private:
        struct WNDINFOEX
        {
            DWORD        Style;
            DWORD        ExStyle;
            LPCTSTR      WindowName;
            int          Top;
            int          Left;
            int          Width;
            int          Height;
            HMENU        Menu;
            HINSTANCE    Instance;
        };
    public:
        WNDINFOEX WindowStruct;

        WndInfo()
        {
            WindowStruct.Style = WS_CLIPCHILDREN | WS_VISIBLE;
            WindowStruct.ExStyle = 0;

            WindowStruct.WindowName = TEXT("Default Window Name");

            WindowStruct.Top = 20;
            WindowStruct.Left = 20;
            WindowStruct.Width = 50;
            WindowStruct.Height = 50;

            WindowStruct.Menu = 0;
            WindowStruct.Instance = Module->Instance;
        }
        //============================================================================================================
        inline WndInfo& NStyle(DWORD _Style) { WindowStruct.Style = _Style;               return *this; }
        inline WndInfo& NExStyle(DWORD _ExStyle) { WindowStruct.ExStyle = _ExStyle;             return *this; }
        //============================================================================================================
        inline WndInfo& Style(DWORD _Style) { WindowStruct.Style |= _Style;              return *this; }
        inline WndInfo& ExStyle(DWORD _ExStyle) { WindowStruct.ExStyle |= _ExStyle;            return *this; }
        //============================================================================================================
        inline WndInfo& WindowName(LPCTSTR _WindowName) { WindowStruct.WindowName = _WindowName;       return *this; }
        //============================================================================================================
        inline WndInfo& Top(int _Top) { WindowStruct.Top = _Top;              return *this; }
        inline WndInfo& Left(int _Left) { WindowStruct.Left = _Left;             return *this; }
        inline WndInfo& Pos(int _Top, int _Left) {
            WindowStruct.Top = _Top;
            WindowStruct.Left = _Left;             return *this;
        }
        //============================================================================================================
        inline WndInfo& Width(int _Width) { WindowStruct.Width = _Width;            return *this; }
        inline WndInfo& Height(int _Height) { WindowStruct.Height = _Height;           return *this; }
        inline WndInfo& Size(int _Width, int _Height) {
            WindowStruct.Width = _Width;
            WindowStruct.Height = _Height;           return *this;
        }
        //============================================================================================================
        inline WndInfo& Menu(HMENU _Menu) { WindowStruct.Menu = _Menu;             return *this; }
        inline WndInfo& Instance(HINSTANCE _Instance) { WindowStruct.Instance = _Instance;         return *this; }
    };


    //CBaseWindowC : C - Createing - this class add Create function in CBaseWindowH
    class CBaseWindowC : public CBaseWindowR
    {
    public:
        CBaseWindowC(ClassInfo& ClassInfo, WNDPROC WndProc);
        inline bool Create(CBaseWindowH* Parent, WndInfo& WndInfo);
    };

    CBaseWindowC::CBaseWindowC(ClassInfo& ClassInfo, WNDPROC WndProc) : CBaseWindowR(ClassInfo, WndProc)
    {

    }

    inline bool CBaseWindowC::Create(CBaseWindowH* Parent, WndInfo& WndInfo)
    {
        return CBaseWindowH::Create(
            WndInfo.WindowStruct.ExStyle,
            GetWndClassName(),
            WndInfo.WindowStruct.WindowName,
            WndInfo.WindowStruct.Style,
            WndInfo.WindowStruct.Left,
            WndInfo.WindowStruct.Top,
            WndInfo.WindowStruct.Width,
            WndInfo.WindowStruct.Height,
            Parent,
            WndInfo.WindowStruct.Menu,
            WndInfo.WindowStruct.Instance,
            this);
    }
}