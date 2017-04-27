#ifndef WL_CONTROLS_ENUMS_HPP
#define WL_CONTROLS_ENUMS_HPP

#include <Windows.h>

namespace Controls
{
	enum EButtonStyles
	{
		bsNone = 0,
		bsLeftText = BS_LEFTTEXT,
		bsText = BS_TEXT,
		bsIcon = BS_ICON,
		bsBitmap = BS_BITMAP,
		bsLeft = BS_LEFT,
		bsCenter = BS_CENTER,
		bsTop = BS_TOP,
		bsBottom = BS_BOTTOM,
		bsVCenter = BS_VCENTER,
		bsPushLike = BS_PUSHLIKE,
		bsMultiLine = BS_MULTILINE,
		bsNotify = BS_NOTIFY,
		bsFlat = BS_FLAT
	};

	/*
	+--------------------+------------------+--------------------+
	| bsIcon or bsBitmap | SetImage called? |       Result       |
	+--------------------+------------------+--------------------+
	|        YES         |       YES        | Show icon only     |
	+--------------------+------------------+--------------------+
	|        NO          |       YES        | Show icon and text |
	+--------------------+------------------+--------------------+
	|        YES         |       NO         | Show text only     |
	+--------------------+------------------+--------------------+
	|        NO          |       NO         | Show text only     |
	+--------------------+------------------+--------------------+
	*/

	typedef Window::WNDSTYLE BTNSTYLE;
	DECLARE_BIT_MASK_SAFE_CLASS(CBtnStyle, BTNSTYLE, EButtonStyles)

	class BtnInfo : public Window::WndInfo
	{
	public:
		BtnInfo();
		BtnInfo(Window::WndInfo & Info);
		BtnInfo & BtnStyle (const CBtnStyle & Style);
		BtnInfo & BtnNStyle(const CBtnStyle & Style);
	};

	inline BtnInfo::BtnInfo() : WndInfo()
	{
	}

	inline BtnInfo::BtnInfo(Window::WndInfo & Info) : WndInfo(Info)
	{
	}

	inline BtnInfo & BtnInfo::BtnStyle (const CBtnStyle & Style) { WindowStruct.wiStyle.addValue(Style); return *this; }
	inline BtnInfo & BtnInfo::BtnNStyle(const CBtnStyle & Style) { WindowStruct.wiStyle.setValue(Style); return *this; }
}


#endif //!WL_CONTROLS_ENUMS_HPP