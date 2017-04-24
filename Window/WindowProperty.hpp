#ifndef WL_PROPERTY_WINDOW_H
#define WL_PROPERTY_WINDOW_H

#include <Windows.h>

namespace Window
{
	template<class TAncestor, bool ReDraw = true>
    class CWindowProperty : public TAncestor
    {
        typedef Utility::CProperty<Utility::RW, int,         CWindowProperty<TAncestor, ReDraw>> rwINT;
        typedef Utility::CProperty<Utility::RW, CWndStyle,   CWindowProperty<TAncestor, ReDraw>> rwSTYLE;
		typedef Utility::CProperty<Utility::RW, CWndExStyle, CWindowProperty<TAncestor, ReDraw>> rwEXSTYLE;
        typedef Utility::CProperty<Utility::RW, bool,        CWindowProperty<TAncestor, ReDraw>> rwBOOL;

    public:
		CWindowProperty();

        rwINT Top;
        rwINT Left;
        rwINT Height;
        rwINT Width;

        rwSTYLE    Style;
        rwEXSTYLE  ExStyle;

        rwBOOL   Enabled;
        rwBOOL   Visible;

    private:
		void InitProperties();

        void setEnabled(bool Enabled);
        void setVisible(bool Visible);
    };

	template<class TAncestor, bool ReDraw = true>
	CWindowProperty<TAncestor, ReDraw>::CWindowProperty()
	{
		InitProperties();
	}

	template<class TAncestor, bool ReDraw = true>
	void CWindowProperty<TAncestor, ReDraw>::InitProperties()
	{
		Style.  Init(this, &CWindowProperty<TAncestor, ReDraw>::getStyle,   &CWindowProperty<TAncestor, ReDraw>::setStyle);
		ExStyle.Init(this, &CWindowProperty<TAncestor, ReDraw>::getExStyle, &CWindowProperty<TAncestor, ReDraw>::setExStyle);

		Top.   Init(this, &CWindowProperty<TAncestor, ReDraw>::getTop,    &CWindowProperty<TAncestor, ReDraw>::setTop);
		Left.  Init(this, &CWindowProperty<TAncestor, ReDraw>::getLeft,   &CWindowProperty<TAncestor, ReDraw>::setLeft);
		Height.Init(this, &CWindowProperty<TAncestor, ReDraw>::getHeight, &CWindowProperty<TAncestor, ReDraw>::setHeight);
		Width. Init(this, &CWindowProperty<TAncestor, ReDraw>::getWidth,  &CWindowProperty<TAncestor, ReDraw>::setWidth);

		Enabled.Init(this, &CWindowProperty<TAncestor, ReDraw>::isEnabled, &CWindowProperty<TAncestor, ReDraw>::setEnabled);
		Visible.Init(this, &CWindowProperty<TAncestor, ReDraw>::isVisible, &CWindowProperty<TAncestor, ReDraw>::setVisible);
	}

	template<class TAncestor, bool ReDraw = true>
	void CWindowProperty<TAncestor, ReDraw>::setEnabled(bool Enabled)
	{
		TAncestor::Enable(Enabled);
	}

	template<class TAncestor, bool ReDraw = true>
	void CWindowProperty<TAncestor, ReDraw>::setVisible(bool Visible)
	{
		if (Visible)
			TAncestor::Show(SW_SHOW);
		else
			TAncestor::Show(SW_HIDE);
	}
}
#endif //!WL_PROPERTY_WINDOW_H