#ifndef WL_WINDOW_ROOT_CPP
#define WL_WINDOW_ROOT_CPP

#include <WinLib/Window/WindowRoot.hpp>

namespace Window
{
	CWindowRoot::CWindowRoot() : m_Style(wsNone), m_ExStyle(wesNone)
	{
		Style.  Init(this, &CWindowRoot::getStyle,   &CWindowRoot::setStyle);
		ExStyle.Init(this, &CWindowRoot::getExStyle, &CWindowRoot::setExStyle);

		Width. Init(this, &CWindowRoot::getWidth,  &CWindowRoot::setWidth);
		Height.Init(this, &CWindowRoot::getHeight, &CWindowRoot::setHeight);
		Left.  Init(this, &CWindowRoot::getLeft,   &CWindowRoot::setLeft);
		Top.   Init(this, &CWindowRoot::getTop,    &CWindowRoot::setTop);
	}

	bool CWindowRoot::Create(CWindowHandle Parent, WndInfo & Info)
    {
		WL_ASSERT(Parent != NULL);
		return 	CWindowEvent::Create(Parent, getClassName(), Info);
    }
	
	CWindowRoot::~CWindowRoot()
	{
		WL_ASSERT(isNull() == true);		
	}

	void CWindowRoot::WindowParamsChangingProcessor(System::CMessage * Event)
	{
		switch (Event->Message)
		{
		case WM_NCCREATE:
			CREATESTRUCT * CrStruct;
			CrStruct = ((CREATESTRUCT*)Event->LParam);
			m_Left   = CrStruct->x;
			m_Top    = CrStruct->y;
			m_Width  = CrStruct->cx;
			m_Height = CrStruct->cy;
			Event->Result = TRUE;
			break;

		case WM_WINDOWPOSCHANGED:
			WINDOWPOS * PosStruct;
			PosStruct = ((WINDOWPOS*)Event->LParam);
			if (!(PosStruct->flags & SWP_NOMOVE))
			{
				m_Left = PosStruct->x;
				m_Top  = PosStruct->y;
			}

			if (!(PosStruct->flags & SWP_NOSIZE))
			{
				m_Width  = PosStruct->cx;
				m_Height = PosStruct->cy;
			}
			Event->Result = 0;
			break;

		case WM_SIZE:
			m_Width  = GET_X_LPARAM(Event->LParam);
			m_Height = GET_Y_LPARAM(Event->LParam);
			Event->Result = 0;
			break;

		case WM_MOVE:
			m_Left = GET_X_LPARAM(Event->LParam);
			m_Top  = GET_Y_LPARAM(Event->LParam);
			Event->Result = 0;
			break;

		case WM_STYLECHANGED:
			STYLESTRUCT * StStruct = (STYLESTRUCT*)Event->LParam;

			if (Event->WParam == GWL_STYLE)
				m_Style.SetValue(StStruct->styleNew);

			if (Event->WParam == GWL_EXSTYLE)
				m_ExStyle.SetValue(StStruct->styleNew);

			Event->Result = 0;
			break;
		}
	}
}

#endif // !WL_WINDOW_ROOT_CPP