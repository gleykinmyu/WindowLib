#ifndef WL_PROPERTY_WINDOW_H
#define WL_PROPERTY_WINDOW_H

#include <Windows.h>
#include <Winlib/Window/WindowRoot.hpp>

namespace Window
{
	template<class TAncestor>
    class CWindowProperty : public TAncestor
    {
        typedef Utility::CProperty<Utility::RW, int,      CWindowProperty> rwINT;
        typedef Utility::CProperty<Utility::RW, LONG_PTR, CWindowProperty> rwSTYLE;
        typedef Utility::CProperty<Utility::RW, bool,     CWindowProperty> rwBOOL;

    public:
		CWindowProperty();

        rwINT Top;
        rwINT Left;
        rwINT Height;
        rwINT Width;

        rwSTYLE  Style;
        rwSTYLE  ExStyle;

        rwBOOL   Enabled;
        rwBOOL   Visible;

    private:
		void InitProperties();

        int  getTop    () const;
        int  getLeft   () const;
        int  getWidth  () const;
        int  getHeight () const;
        HWND getHandle () const;

        void setEnabled(bool Enabled);
        void setVisible(bool Visible);
        void setTop    (const int Top);
        void setLeft   (const int Left);
        void setWidth  (const int Width);
        void setHeight (const int Height);
    };

	template<class TAncestor>
	CWindowProperty<TAncestor>::CWindowProperty()
	{
		InitProperties();
	}

	template<class TAncestor>
	void CWindowProperty<TAncestor>::InitProperties()
	{
		Style.Init(this, &CWindowProperty<TAncestor>::getStyle, &CWindowProperty<TAncestor>::setStyle);
		ExStyle.Init(this, &CWindowProperty<TAncestor>::getExStyle, &CWindowProperty<TAncestor>::setExStyle);

		Top.Init(this, &CWindowProperty<TAncestor>::getTop, &CWindowProperty<TAncestor>::setTop);
		Left.Init(this, &CWindowProperty<TAncestor>::getLeft, &CWindowProperty<TAncestor>::setLeft);
		Height.Init(this, &CWindowProperty<TAncestor>::getHeight, &CWindowProperty<TAncestor>::setHeight);
		Width.Init(this, &CWindowProperty<TAncestor>::getWidth, &CWindowProperty<TAncestor>::setWidth);

		Enabled.Init(this, &CWindowProperty<TAncestor>::isEnabled, &CWindowProperty<TAncestor>::setEnabled);
		Visible.Init(this, &CWindowProperty<TAncestor>::isVisible, &CWindowProperty<TAncestor>::setVisible);
	}

	template<class TAncestor>
	int CWindowProperty<TAncestor>::getTop() const
	{
		RECT Rect = {};
		getRect(&Rect);
		return Rect.top;
	}

	template<class TAncestor>
	int CWindowProperty<TAncestor>::getLeft() const
	{
		RECT Rect = {};
		getRect(&Rect);
		return Rect.left;
	}

	template<class TAncestor>
	int CWindowProperty<TAncestor>::getWidth() const
	{
		RECT Rect = {};
		getRect(&Rect);
		return Rect.right - Rect.left;
	}

	template<class TAncestor>
	int CWindowProperty<TAncestor>::getHeight() const
	{
		RECT Rect = {};
		getRect(&Rect);
		return Rect.bottom - Rect.top;
	}

	template<class TAncestor>
	HWND CWindowProperty<TAncestor>::getHandle() const
	{
		return *((CWindowHandle*)this);
	}

	template<class TAncestor>
	void CWindowProperty<TAncestor>::setEnabled(bool Enabled)
	{
		Enable(Enabled);
	}

	template<class TAncestor>
	void CWindowProperty<TAncestor>::setVisible(bool Visible)
	{
		if (Visible)
			CWindow::Show(SW_SHOW);
		else
			CWindow::Show(SW_HIDE);
	}

	template<class TAncestor>
	void CWindowProperty<TAncestor>::setTop(const int Top)
	{
		setPos(NULL, getLeft(), Top, 0, 0, SWP_NOSIZE);
	}

	template<class TAncestor>
	void CWindowProperty<TAncestor>::setLeft(const int Left)
	{
		setPos(NULL, Left, getTop(), 0, 0, SWP_NOSIZE);
	}

	template<class TAncestor>
	void CWindowProperty<TAncestor>::setWidth(const int Width)
	{
		setPos(NULL, 0, 0, Width, getHeight(), SWP_NOMOVE);
	}

	template<class TAncestor>
	void CWindowProperty<TAncestor>::setHeight(const int Height)
	{
		setPos(NULL, 0, 0, getWidth(), Height, SWP_NOMOVE);
	}
}
#endif //!WL_PROPERTY_WINDOW_H