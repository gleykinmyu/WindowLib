#pragma once
#include <windows.h>
#include "WindowHandle.h"
#include "WindowEvents.h"
#include "Module.h"


namespace wl
{
    /*========================================================================================================================================
    ClassInfo - Help you to change some window class parmeters instead changing all parmeters in once.

    USING: foo(ClassInfo&) - foo(ClassInfo().ClassName(TEXT("BlaBla").Style(0). ... )
    /\
    ||
    Enter here setters, you need.

    ============================================================================================================

    ADVICE: If you create new window class - inherited from CBaseWindowR, use next syntax in your constructors:
    class CYourClass : public CBaseClass
    {
    CYourClass(ClassInfo& ClassInfo) : CBaseClass(ClassInfo.ClassName(TEXT("CYourClass")) {...}
    /\
    ||
    Write here name of your class. Windows needs it, to create your Window.
    ============================================================================================================
    */
    class ClassInfo
    {
    private:
        struct CLASSINFOEX
        {
            UINT        Style;

            HICON       hIcon;
            HICON       hIconSm;
            HCURSOR     hCursor;
            HBRUSH      Background;

            LPCTSTR     MenuName;
            LPCTSTR     ClassName;

            HINSTANCE   Instance;
        };
    public:
        CLASSINFOEX ClassStruct;

        ClassInfo()
        {
            ClassStruct.Style = CS_HREDRAW | CS_VREDRAW;
            ClassStruct.hIcon = 0;
            ClassStruct.hCursor = LoadCursor(0, IDC_ARROW);
            ClassStruct.Background = HBRUSH(COLOR_WINDOW);
            ClassStruct.MenuName = 0;
            ClassStruct.ClassName = TEXT("DefaultClass");
            ClassStruct.hIconSm = 0;
        }
        //====================================================================================================
        inline ClassInfo& NStyle    (UINT        _Style     ) { ClassStruct.Style      = _Style;     return *this; }
        inline ClassInfo& Style     (UINT        _Style     ) { ClassStruct.Style     |= _Style;     return *this; }
        //====================================================================================================
        inline ClassInfo& ClassName (LPCTSTR     _ClassName ) { ClassStruct.ClassName  = _ClassName; return *this; }
        inline ClassInfo& Icon      (HICON       _Icon      ) { ClassStruct.hIcon      = _Icon;      return *this; }
        inline ClassInfo& IconSm    (HICON       _IconSm    ) { ClassStruct.hIconSm    = _IconSm;    return *this; }
        inline ClassInfo& Cursor    (HCURSOR     _Cursor    ) { ClassStruct.hCursor    = _Cursor;    return *this; }
        inline ClassInfo& Background(HBRUSH      _Brush     ) { ClassStruct.Background = _Brush;     return *this; }
        inline ClassInfo& MenuName  (LPCTSTR     _MenuName  ) { ClassStruct.MenuName   = _MenuName;  return *this; }
        inline ClassInfo& Instance  (HINSTANCE   _Instance) { ClassStruct.Instance     = _Instance;  return *this; }
    };

    //CBaseWindowR : R - Register - this class add Registering in CBaseWindowH
    class  CBaseWindowR : public CBaseWindowM
    {
    public:
        CBaseWindowR(ClassInfo& ClsInfo, WNDPROC WndProc);
      
        inline ATOM    GetWndAtom()      const;
        inline LPCTSTR GetWndClassName() const;
        //=================================================================================================
    private:
        ATOM    ClassAtom;
        LPCTSTR ClassName;

    };

    CBaseWindowR::CBaseWindowR(ClassInfo& ClsInfo, WNDPROC WndProc)
    {
        WNDCLASSEX WindowStruct = {};

        WndProc ? WindowStruct.lpfnWndProc = WndProc : WindowStruct.lpfnWndProc = StartWindowProcedure;

        WindowStruct.style = ClsInfo.ClassStruct.Style;

        WindowStruct.lpszClassName = ClsInfo.ClassStruct.ClassName;
        ClassName = ClsInfo.ClassStruct.ClassName;

        WindowStruct.hIcon = ClsInfo.ClassStruct.hIcon;
        WindowStruct.hIconSm = ClsInfo.ClassStruct.hIconSm;

        WindowStruct.hCursor = ClsInfo.ClassStruct.hCursor;
        WindowStruct.hbrBackground = ClsInfo.ClassStruct.Background;
        WindowStruct.lpszMenuName = ClsInfo.ClassStruct.MenuName;
        WindowStruct.hInstance = ClsInfo.ClassStruct.Instance;

        WindowStruct.cbSize = sizeof(WNDCLASSEX);

        WindowStruct.cbWndExtra = sizeof(this);
        WindowStruct.cbClsExtra = 0;

        ClassAtom = RegisterClassEx(&(WindowStruct));
    }

    inline ATOM    CBaseWindowR::GetWndAtom()      const 
    { 
        return ClassAtom; 
    }
    inline LPCTSTR CBaseWindowR::GetWndClassName() const 
    { 
        return ClassName; 
    }
}