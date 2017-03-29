#pragma once
#include <windows.h>
#include "Window.h"
#include "WindowEvent.h"
#include "Module.h"
#include "WLDefines.h"
#include <stdio.h>

namespace wl
{
    /*========================================================================================================================================
    ClsInfo - Help you to change some window class parmeters instead changing all parmeters in once.

    USING: foo(ClsInfo&) - foo(ClsInfo().ClassName(TEXT("BlaBla").Style(0). ... )
    /\
    ||
    Enter here setters, you need.

    ============================================================================================================

    ADVICE: If you create new window class - inherited from CWindowDecl, use next syntax in your constructors:
    class CYourClass : public CBaseClass
    {
    CYourClass(ClsInfo& ClsInfo) : CBaseClass(ClsInfo.ClassName(TEXT("CYourClass")) {...}
    /\
    ||
    Write here name of your class. Windows needs it, to create your Window.
    ============================================================================================================
    */
    class ClsInfo
    {
    private:
        struct CLASSINFOEX
        {
            UINT        s_Style;

            HICON       s_Icon;
            HICON       s_IconSm;
            HCURSOR     s_Cursor;
            HBRUSH      s_Background;

            LPCTSTR     s_MenuName;
            LPCTSTR     s_ClassName;

            HINSTANCE   s_Instance;
        };
    public:
        CLASSINFOEX ClsStruct;
        ClsInfo()
        {
            ClsStruct.s_Style      = CS_HREDRAW | CS_VREDRAW;
            ClsStruct.s_Icon       = 0;
            ClsStruct.s_Cursor     = LoadCursor(0, IDC_ARROW);
            ClsStruct.s_Background = HBRUSH(COLOR_WINDOW);
            ClsStruct.s_MenuName   = 0;
            ClsStruct.s_ClassName  = NULL;
            ClsStruct.s_IconSm     = 0;
            ClsStruct.s_Instance   = Module->Instance;
        }
        //====================================================================================================
        inline ClsInfo& NStyle    (UINT        _Style     ) { ClsStruct.s_Style      = _Style;     return *this; }
        inline ClsInfo& Style     (UINT        _Style     ) { ClsStruct.s_Style     |= _Style;     return *this; }
        //====================================================================================================
        inline ClsInfo& ClassName (LPCTSTR     _ClassName ) { ClsStruct.s_ClassName  = _ClassName; return *this; }
        inline ClsInfo& Icon      (HICON       _Icon      ) { ClsStruct.s_Icon       = _Icon;      return *this; }
        inline ClsInfo& IconSm    (HICON       _IconSm    ) { ClsStruct.s_IconSm     = _IconSm;    return *this; }
        inline ClsInfo& Cursor    (HCURSOR     _Cursor    ) { ClsStruct.s_Cursor     = _Cursor;    return *this; }
        inline ClsInfo& Background(HBRUSH      _Brush     ) { ClsStruct.s_Background = _Brush;     return *this; }
        inline ClsInfo& MenuName  (LPCTSTR     _MenuName  ) { ClsStruct.s_MenuName   = _MenuName;  return *this; }
        inline ClsInfo& Instance  (HINSTANCE   _Instance  ) { ClsStruct.s_Instance   = _Instance;  return *this; }
    };

    class  CWindowDecl : public CWindowEvent
    {
    public:
        ClsInfo ClassInfo;
        static inline bool ClassExist(HINSTANCE Instance, LPCTSTR ClassName);
    protected:
        void RegisterWndClass();
    private:
        CHAR m_AutoName[20] = {};
        LPCTSTR FormatClassName(LPCTSTR Name);
    };

    inline bool CWindowDecl::ClassExist(HINSTANCE Instance, LPCTSTR ClassName)
    {
        WNDCLASSEX WndStruct;
        return (GetClassInfoEx(Instance, ClassName, &WndStruct) != 0);
    }

    void CWindowDecl::RegisterWndClass()
    {
        WNDCLASSEX WndStruct;
       
        if (ClassExist(ClassInfo.ClsStruct.s_Instance, ClassInfo.ClsStruct.s_ClassName))
            return;

        ClassInfo.ClsStruct.s_ClassName = FormatClassName(ClassInfo.ClsStruct.s_ClassName);

        WndStruct.cbSize        = sizeof(WNDCLASSEX);
        WndStruct.hbrBackground = ClassInfo.ClsStruct.s_Background;

        WndStruct.hCursor       = ClassInfo.ClsStruct.s_Cursor;

        WndStruct.hIcon         = ClassInfo.ClsStruct.s_Icon;
        WndStruct.hIconSm       = ClassInfo.ClsStruct.s_IconSm;

        WndStruct.hInstance     = ClassInfo.ClsStruct.s_Instance;
        WndStruct.lpfnWndProc   = CWindowEvent::StartWindowProcedure;
        
        WndStruct.lpszClassName = ClassInfo.ClsStruct.s_ClassName;
        WndStruct.lpszMenuName  = ClassInfo.ClsStruct.s_MenuName;
        WndStruct.style         = ClassInfo.ClsStruct.s_Style;

        WndStruct.cbClsExtra    = 0;
        WndStruct.cbWndExtra    = sizeof(this);

        ATOM Atom = RegisterClassEx(&WndStruct);
        
        if (Atom == 0)
        {
            WL_TRACE("WL couldn't register class: %s", ClassInfo.ClsStruct.s_ClassName);
            WL_ASSERT(0);
        }
    }

    LPCTSTR CWindowDecl::FormatClassName(LPCTSTR Name)
    {
        if (Name == NULL)
        {
            snprintf(m_AutoName, 20, "WL::%p", this);
            return m_AutoName;
        }
            return Name;
    }
}