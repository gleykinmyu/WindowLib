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
#define WL_SETWNDPOS_NOFLAGS SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER

    class CWindowRoot : public CWindowDecl
    {
		typedef Utility::CProperty<Utility::RW, int,         CWindowRoot> rwINT;
		typedef CWndStylePropertyT<WNDSTYLE, EWndStyles,     CWindowRoot> rwSTYLE;
		typedef CWndStylePropertyT<WNDEXSTYLE, EWndExStyles, CWindowRoot> rwEXSTYLE;

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

		WNDSTYLE   m_Style;
		WNDEXSTYLE m_ExStyle;

		inline int getTop()    const;
		inline int getLeft()   const;
		inline int getWidth()  const;
		inline int getHeight() const;

		inline WNDSTYLE   getStyle()  const;
		inline WNDEXSTYLE getExStyle() const;

		inline void setTop   (int Top);
		inline void setMixTop(int Top);

		inline void setLeft   (int Left);
		inline void setMixLeft(int Left);

		inline void setWidth   (int Width);
		inline void setMixWidth(int Width);

		inline void setHeight   (int Height);
		inline void setMixHeight(int Height);

		inline void setStyle     (WNDSTYLE   Style);
		inline void setMixStyle  (WNDSTYLE   Style);

		inline void setExStyle   (WNDEXSTYLE ExStyle);
		inline void setMixExStyle(WNDEXSTYLE ExStyle);

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

	inline WNDSTYLE CWindowRoot::getStyle() const
	{
		return m_Style;
	}

	inline WNDEXSTYLE CWindowRoot::getExStyle() const
	{
		return m_ExStyle;
	}

	inline void CWindowRoot::setTop(int Top)
	{
		setPos(HWND_TOPMOST, m_Left, Top, 0, 0, SWP_NOSIZE | WL_SETWNDPOS_NOFLAGS);
	}

	inline void CWindowRoot::setMixTop(int Top)
	{
		setPos(HWND_TOPMOST, m_Left, Top + m_Top, 0, 0, SWP_NOSIZE | WL_SETWNDPOS_NOFLAGS);
	}

	inline void CWindowRoot::setLeft(int Left)
	{
		setPos(HWND_TOPMOST, Left, m_Top, 0, 0, SWP_NOSIZE | WL_SETWNDPOS_NOFLAGS);
	}

	inline void CWindowRoot::setMixLeft(int Left)
	{
		setPos(HWND_TOPMOST, Left + m_Left, m_Top, 0, 0, SWP_NOSIZE | WL_SETWNDPOS_NOFLAGS);
	}

	inline void CWindowRoot::setWidth(const int Width)
	{
		setPos(HWND_TOPMOST, 0, 0, Width, m_Height, SWP_NOMOVE | WL_SETWNDPOS_NOFLAGS);
	}

	inline void CWindowRoot::setMixWidth(int Width)
	{
		setPos(HWND_TOPMOST, 0, 0, m_Width + Width, m_Height, SWP_NOMOVE | WL_SETWNDPOS_NOFLAGS);

	}

	inline void CWindowRoot::setHeight(int Height)
	{
		setPos(HWND_TOPMOST, 0, 0, m_Width, Height, SWP_NOMOVE | WL_SETWNDPOS_NOFLAGS);
	}

	inline void CWindowRoot::setMixHeight(int Height)
	{
		setPos(HWND_TOPMOST, 0, 0, m_Width, Height + m_Height, SWP_NOMOVE | WL_SETWNDPOS_NOFLAGS);
	}

	inline void CWindowRoot::setStyle(WNDSTYLE Style)
	{
		CWindowDecl::setStyle(CWndStyle().setValue(Style));
	}

	inline void CWindowRoot::setMixStyle(WNDSTYLE Style)
	{
		CWindowDecl::setStyle(CWndStyle().setValue(Style | m_Style));
	}

	inline void CWindowRoot::setExStyle(WNDEXSTYLE ExStyle)
	{
		CWindowDecl::setExStyle(CWndExStyle().setValue(ExStyle));
	}

	inline void CWindowRoot::setMixExStyle(WNDEXSTYLE ExStyle)
	{
		CWindowDecl::setExStyle(CWndExStyle().setValue(ExStyle | m_ExStyle));
	}
}
#endif //!WL_WINDOW_ROOT_H