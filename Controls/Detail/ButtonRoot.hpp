#ifndef WL_BUTTON_ROOT_HPP
#define WL_BUTTON_ROOT_HPP

#include <WinLib/Window.hpp>
#include <WinLib/Controls/Detail/StdControlRoot.hpp>
#include <WinLib/Utility.hpp>

namespace Controls
{
    enum EButtonStyles
    {
        bsLeftText  = BS_LEFTTEXT,
        bsText      = BS_TEXT,
        bsIcon      = BS_ICON,
        bsBitmap    = BS_BITMAP,
        bsLeft      = BS_LEFT,
        bsCenter    = BS_CENTER,
        bsTop       = BS_TOP,
        bsBottom    = BS_BOTTOM,
        bsVCenter   = BS_VCENTER,
        bsPushLike  = BS_PUSHLIKE,
        bsMultiLine = BS_MULTILINE,
        bsNotify    = BS_NOTIFY,
        bsFlat      = BS_FLAT
    };

    typedef Window::WNDSTYLE BTNSTYLE;
    DECLARE_BIT_MASK_SAFE_CLASS(CBtnStyle, BTNSTYLE, EButtonStyles);
}

namespace ControlsDetail
{
    enum EButtonTypes
    {
        btPushBtn      = BS_PUSHBUTTON,
        btDefPushBtn   = BS_DEFPUSHBUTTON,
        btCheckBox     = BS_CHECKBOX,
        btAutoCheckBox = BS_AUTOCHECKBOX,
        btRadioBtn     = BS_RADIOBUTTON,
        btAutoRadioBtn = BS_AUTORADIOBUTTON,
        bt3State       = BS_3STATE,
        btAuto3State   = BS_AUTO3STATE,
        btGroupBox     = BS_GROUPBOX,
        btUserBtn      = BS_USERBUTTON,
        btPushBox      = BS_PUSHBOX
    };

    class BtnInfo : public CtrlInfo
    {
    public:
        BtnInfo();
        BtnInfo & BtnStyle(const Controls::CBtnStyle* Style);
    };

    class CStdButtonRoot : public CStdControlRoot
    {
    public:
        inline CStdButtonRoot();
        inline bool Create(Window::CWindow* Parent, EButtonTypes BtnType,  BtnInfo & Info);
    };

    inline CStdButtonRoot::CStdButtonRoot() : CStdControlRoot(TEXT("BUTTON"))
    {
    }

    inline bool CStdButtonRoot::Create(Window::CWindow* Parent, BtnInfo& Info)
    {
        return CStdControlRoot::Create(Parent, Info);
    }
}
#endif //!WL_BUTTON_ROOT_HPP