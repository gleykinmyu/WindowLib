#ifndef WL_WINDOW_IMPL_H
#define WL_WINDOW_IMPL_H

#include <Windows.h>
#include <WinLib/Utility.hpp>
#include <WinLib/System.hpp>
#include <WinLib/Window/WindowHandle.hpp>

namespace Window
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
			WNDINFOEX();
            CWndStyle    wiStyle;
            CWndExStyle  wiExStyle;
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
        inline WndInfo& NStyle    (const CWndStyle   & _Style);
        inline WndInfo& NExStyle  (const CWndExStyle & _Style);
        //============================================================================================================
        inline WndInfo& Style     (const CWndStyle   & _Style);
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

    class CWindowImpl : public CWindow
    {
    public:
		CWindowImpl() {WL_CTOR_TRACE;}
		bool Create(CWindowHandle Parent, LPCTSTR ClassName, WndInfo & WndInfo, LPVOID lpParam = 0);
    };
}
#endif //!WL_WINDOW_IMPL_H