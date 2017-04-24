#ifndef WL_DESKTOP_H
#define WL_DESKTOP_H

#include <WinLib/Window.hpp>
#include <WinLib/Utility.hpp>

namespace System
{
	class CDesktop : public Window::CWindowHandle
	{
		typedef Utility::CProperty<Utility::RO, int, CDesktop> roINT;
	public:
		CDesktop();
		roINT Width;
		roINT Height;

	private:
		inline int getWidth()  const;
		inline int getHeight() const;
		int m_Width, m_Height;
	};

	CDesktop::CDesktop()
	{
		Attach(::GetDesktopWindow());
		RECT Rect = {};
		getRect(&Rect);
		m_Width  = Rect.right - Rect.left;
		m_Height = Rect.bottom - Rect.top;
		Width. Init(this, &CDesktop::getWidth);
		Height.Init(this, &CDesktop::getHeight);
	}

	inline int CDesktop::getWidth() const
	{
		return m_Width;
	}

	inline int CDesktop::getHeight() const
	{
		return m_Height;
	}

	CDesktop  m_Desktop;
	CDesktop * Desktop = &m_Desktop;
}


#endif // !WL_DESKTOP_H