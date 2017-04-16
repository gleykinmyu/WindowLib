#ifndef WL_WINDOW_IMPL_H
#define WL_WINDOW_IMPL_H

#include <Windows.h>
#include <WinLib/Utility.hpp>
#include <WinLib/System.hpp>
#include <WinLib/Window/WindowHandle.hpp>

namespace Window
{
    enum EWndStyles
    {
        wsNone         = 0,
        wsOverlapped   = WS_OVERLAPPED,
        wsPopup        = WS_POPUP,
        wsChild        = WS_CHILD,
        wsMinimize     = WS_MINIMIZE,
        wsMaximize     = WS_MAXIMIZE,
        wsVsible       = WS_VISIBLE,
        wsDisabled     = WS_DISABLED,
        wsClipChildren = WS_CLIPCHILDREN,
        wsCaption      = WS_CAPTION,
        wsBorder       = WS_BORDER,
        wsVScroll      = WS_VSCROLL,
        wsHScroll      = WS_HSCROLL,
        //================================
        wsOverlappedWindow = WS_OVERLAPPEDWINDOW
    };

    enum EWndExStyles
    {
        wesNone = 0
    };

    typedef DWORD WNDEXSTYLE;    
    typedef DWORD WNDSTYLE;
    
    DECLARE_BIT_MASK_SAFE_CLASS(CWndStyle, WNDSTYLE, EWndStyles)
    DECLARE_BIT_MASK_SAFE_CLASS(CWndExStyle, WNDEXSTYLE, EWndExStyles)
    
    //=============================================================================================

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
            WNDSTYLE     wiStyle;
            WNDEXSTYLE   wiExStyle;
            LPCTSTR      wiWindowName;
            int          wiTop;
            int          wiLeft;
            int          wiWidth;
            int          wiHeight;
            HMENU        wiMenu;
            HINSTANCE    wiInstance;
        };

    public:
        WNDINFOEX WindowStruct;

        WndInfo();
        //============================================================================================================
        inline WndInfo& NStyle    (const CWndStyle & _Style  );
        inline WndInfo& NExStyle  (const CWndExStyle & _Style);
        //============================================================================================================
        inline WndInfo& Style     (const CWndStyle & _Style  );
        inline WndInfo& ExStyle   (const CWndExStyle & _Style);
        //============================================================================================================
        inline WndInfo& WindowName(LPCTSTR _WindowName       );
        //============================================================================================================
        inline WndInfo& Top       (int _Top                  );
        inline WndInfo& Left      (int _Left                 );
        inline WndInfo& Pos       (int _Top, int _Left       );
        //============================================================================================================
        inline WndInfo& Width     (int _Width                );
        inline WndInfo& Height    (int _Height               );
        inline WndInfo& Size      (int _Width, int _Height   );
        //============================================================================================================
        inline WndInfo& Menu      (HMENU _Menu               );
        inline WndInfo& Instance  (HINSTANCE _Instance       );
    };

    class WL_NOVTABLE CWindowImpl : public CWindow
    {
    public:
		CWindowImpl() {WL_CTOR_TRACE;}
		bool Create(CWindowHandle* Parent, LPCTSTR ClassName, WndInfo& WndInfo, LPVOID lpParam = 0);
		bool Create(CWindowHandle& Parent, LPCTSTR ClassName, WndInfo& WndInfo, LPVOID lpParam = 0);
    };
}
#endif //!WL_WINDOW_IMPL_H