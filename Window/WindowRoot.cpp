#ifndef WL_WINDOW_ROOT_CPP
#define WL_WINDOW_ROOT_CPP

#include <WinLib/Window/WindowRoot.hpp>

namespace Window
{
	CWindowRoot::CWindowRoot()
	{
		Style.  Init(this, &CWindowRoot::getStyle,   &CWindowRoot::setStyle,   &CWindowRoot::setMixStyle);
		ExStyle.Init(this, &CWindowRoot::getExStyle, &CWindowRoot::setExStyle, &CWindowRoot::setMixExStyle);

		Width. Init(this, &CWindowRoot::getWidth,  &CWindowRoot::setWidth,  &CWindowRoot::setMixWidth);
		Height.Init(this, &CWindowRoot::getHeight, &CWindowRoot::setHeight, &CWindowRoot::setMixHeight);
		Left.  Init(this, &CWindowRoot::getLeft,   &CWindowRoot::setLeft,   &CWindowRoot::setMixLeft);
		Top.   Init(this, &CWindowRoot::getTop,    &CWindowRoot::setTop,    &CWindowRoot::setMixTop);
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
		union
		{
			CREATESTRUCT * CrStruct;
			WINDOWPOS    * PosStruct;
			STYLESTRUCT  * StStruct;

		} MsgData;

		switch (Event->Message)
		{
		case WM_NCCREATE:
			MsgData.CrStruct = ((CREATESTRUCT*)Event->LParam);
			m_Left    = MsgData.CrStruct->x;
			m_Top     = MsgData.CrStruct->y;
			m_Width   = MsgData.CrStruct->cx;
			m_Height  = MsgData.CrStruct->cy;
			m_Style   = MsgData.CrStruct->style;
			m_ExStyle = MsgData.CrStruct->dwExStyle;
			Event->Result = TRUE;
			break;

		case WM_WINDOWPOSCHANGED:
			MsgData.PosStruct = ((WINDOWPOS*)Event->LParam);
			if (!(MsgData.PosStruct->flags & SWP_NOMOVE))
			{
				m_Left = MsgData.PosStruct->x;
				m_Top  = MsgData.PosStruct->y;
			}

			if (!(MsgData.PosStruct->flags & SWP_NOSIZE))
			{
				m_Width  = MsgData.PosStruct->cx;
				m_Height = MsgData.PosStruct->cy;
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
			MsgData.StStruct = (STYLESTRUCT*)Event->LParam;
			if (Event->WParam == GWL_STYLE)
				m_Style = MsgData.StStruct->styleNew;

			if (Event->WParam == GWL_EXSTYLE)
				m_ExStyle = MsgData.StStruct->styleNew;

			Event->Result = 0;
			break;
		}
	}
}

#endif // !WL_WINDOW_ROOT_CPP