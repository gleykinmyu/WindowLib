#ifndef WL_WINDOW_ROOT_H
#define WL_WINDOW_ROOT_H

#include <Windows.h>
#include <Windowsx.h>
#include <WinLib/Utility.hpp>
#include <WinLib/System.hpp>
#include <WinLib/Window/WindowDecl.hpp>
#include <WinLib/Window/WindowHandle.hpp>

namespace Window
{
    class WL_NOVTABLE CWindowRoot : public CWindowDecl
    {
		typedef Utility::CProperty<Utility::RW, int,         CWindowRoot> rwINT;
		typedef Utility::CProperty<Utility::RW, CWndStyle,   CWindowRoot> rwSTYLE;
		typedef Utility::CProperty<Utility::RW, CWndExStyle, CWindowRoot> rwEXSTYLE;

    public:
		CWindowRoot();
		bool Create(CWindowHandle Parent, WndInfo & WndInfo);

		rwSTYLE   Style;
		rwEXSTYLE ExStyle;

		rwINT Width;
		rwINT Height;
		rwINT Left;
		rwINT Top;

		~CWindowRoot();

	private:
		int m_Left, m_Top, m_Width, m_Height;

		CWndStyle   m_Style;
		CWndExStyle m_ExStyle;

		inline int getTop()    const;
		inline int getLeft()   const;
		inline int getWidth()  const;
		inline int getHeight() const;

		inline CWndStyle   getStyle()  const;
		inline CWndExStyle getExStyle() const;

		inline void setTop   (int Top);
		inline void setLeft  (int Left);
		inline void setWidth (int Width);
		inline void setHeight(int Height);

		inline void setStyle  (const CWndStyle   & Style);
		inline void setExStyle(const CWndExStyle & ExStyle);

		virtual void WindowParamsChangingProcessor(System::CMessage * Event);
    };

	inline int CWindowRoot::getTop() const
	{
		return m_Top;
	}

	inline int CWindowRoot::getLeft() const
	{
		return m_Left;
	}

	inline int CWindowRoot::getWidth() const
	{
		return m_Width;
	}

	inline int CWindowRoot::getHeight() const
	{
		return m_Height;
	}

	inline CWndStyle CWindowRoot::getStyle() const
	{
		return m_Style;
	}

	inline CWndExStyle CWindowRoot::getExStyle() const
	{
		return m_ExStyle;
	}

	inline void CWindowRoot::setTop(int Top)
	{
		setPos(HWND_TOPMOST, m_Left, Top, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
	}

	inline void CWindowRoot::setLeft(int Left)
	{
		setPos(HWND_TOPMOST, Left, m_Top, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
	}

	inline void CWindowRoot::setWidth(const int Width)
	{
		setPos(HWND_TOPMOST, 0, 0, m_Width, Width, SWP_NOMOVE | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
	}

	inline void CWindowRoot::setHeight(int Height)
	{
		setPos(HWND_TOPMOST, 0, 0, m_Width, Height, SWP_NOMOVE | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
	}

	inline void CWindowRoot::setStyle(const CWndStyle & Style)
	{
		CWindowDecl::setStyle(Style);
	}

	inline void CWindowRoot::setExStyle(const CWndExStyle & ExStyle)
	{
		CWindowDecl::setExStyle(ExStyle);
	}
}
#endif //!WL_WINDOW_ROOT_H