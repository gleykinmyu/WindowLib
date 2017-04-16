#ifndef WL_WINDOW_DECL_H
#define WL_WINDOW_DECL_H

#include <Windows.h>
#include <WinLib/Window/WindowHandle.hpp>
#include <WinLib/Window/WindowEvent.hpp>
#include <WinLib/System.hpp>
#include <WinLib/Utility.hpp>

namespace Window
{
    enum EClsStyles
    {
        csNone = 0,
        csVRedraw = CS_VREDRAW,
        csHRedraw = CS_HREDRAW,
        csOwnDC   = CS_OWNDC,
        csDblClks = CS_DBLCLKS
    };

    typedef UINT CLSSTYLE;

    DECLARE_BIT_MASK_SAFE_CLASS(CClsStyle, CLSSTYLE, EClsStyles)

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
            CLSSTYLE    ciStyle;

            HICON       ciIcon;
            HICON       ciIconSm;

            HCURSOR     ciCursor;

            HBRUSH      ciBackground;

            LPCTSTR     ciMenuName;
            LPCTSTR     ciClassName;

            HINSTANCE   ciInstance;

			WNDPROC     ciWndProc;
        };

    public:
        CLASSINFOEX ClsStruct;
        ClsInfo();

        inline ClsInfo& NStyle    (const CClsStyle & _Style);
        inline ClsInfo& Style     (const CClsStyle & _Style);

        inline ClsInfo& ClassName (LPCTSTR     _ClassName  );
        inline ClsInfo& Icon      (HICON       _Icon       );
        inline ClsInfo& IconSm    (HICON       _IconSm     );
        inline ClsInfo& Cursor    (HCURSOR     _Cursor     );
        inline ClsInfo& Background(HBRUSH      _Brush      );
        inline ClsInfo& MenuName  (LPCTSTR     _MenuName   );
        inline ClsInfo& Instance  (HINSTANCE   _Instance   );
		inline ClsInfo& WndProc   (WNDPROC     _WndProc    );
    };

    class WL_NOVTABLE CWindowDecl : public CWindowEvent
    {
    public:
		CWindowDecl() {WL_CTOR_TRACE;}
        virtual LPCTSTR getClassName() = 0;

    protected:
        LPCTSTR wl_RegisterWindowClass(const ClsInfo& Info);

    private:
        inline bool wl_ClassExist(HINSTANCE Instance, LPCTSTR ClassName);
        CHAR    m_AutoName[20] = {};
        LPCTSTR wl_FormatClassName();
    };

#define DECLARE_WINDOW_CLASS(ClassInfo) \
    LPCTSTR getClassName() \
    { \
        static LPCTSTR wl_DeclaredClassName = wl_RegisterWindowClass(ClassInfo); \
        return wl_DeclaredClassName; \
    }
        
}
#endif //!WL_WINDOW_DECL_H