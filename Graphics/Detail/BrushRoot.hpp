#ifndef WL_BRUSH_DETAIL_HPP
#define WL_BRUSH_DETAIL_HPP

#include <Windows.h>
#include <WinLib/Graphics/ObjectHandleWraps.hpp>
#include <WinLib/Utility.hpp>

namespace GraphicsDetail
{
	class CBrushObject : public Graphics::CBrushHandle
	{
	public:
		~CBrushObject();
	};

	CBrushObject::~CBrushObject()
	{
		WL_ASSERT(isNull() == true);
	}

	class CBrushG : public CBrushObject
	{
	public:
		Graphics::CColor      getColor() const;
		Graphics::EBrushStyle getStyle() const;

	private:
		Graphics::EBrushStyle wl_ConvertFromLogBrush(const LOGBRUSH* LogBrush) const;
	};

	Graphics::CColor CBrushG::getColor() const
	{
		LOGBRUSH logBrush = {};
		getInfo(&logBrush);
		return Graphics::CColor(logBrush.lbColor);
	}

	Graphics::EBrushStyle CBrushG::getStyle() const
	{
		LOGBRUSH logBrush = {};
		getInfo(&logBrush);
		return wl_ConvertFromLogBrush(&logBrush);
	}

	Graphics::EBrushStyle CBrushG::wl_ConvertFromLogBrush(const LOGBRUSH* LogBrush) const
	{
		switch (LogBrush->lbStyle)
		{
		case BS_SOLID: return Graphics::bsSolid;

		case BS_HATCHED:
			switch (LogBrush->lbHatch)
			{
			case HS_BDIAGONAL:  return Graphics::bsBDiagonal;
			case HS_CROSS:      return Graphics::bsCross;
			case HS_DIAGCROSS:  return Graphics::bsDiagCross;
			case HS_FDIAGONAL:  return Graphics::bsFDiagonal;
			case HS_HORIZONTAL: return Graphics::bsHorizontal;
			case HS_VERTICAL:   return Graphics::bsVertical;
			default: WL_TRACE("There is no suitable conversion from LOGBRUSH to EBrushStyle!!!"); WL_ASSERT(0); break;
			}
			break;
		case BS_HOLLOW: return Graphics::bsHollow;
		default: WL_TRACE("There is no suitable conversion from LOGBRUSH to EBrushStyle!!!"); WL_ASSERT(0); break;
		}
		return Graphics::bsHollow;
	}

	class CBrushS : public CBrushG
	{
	public:
		CBrushS(Graphics::CDeviceContext & DC);
		void setColor(const Graphics::CColor & Color);
		void setStyle(const Graphics::EBrushStyle & Style);
		
	private:
		Graphics::CDeviceContext & m_OwnDC;
		void            wl_ConvertToLogBrush(LOGBRUSH* LogBrush, Graphics::EBrushStyle Style);
		void            wl_Replace(const LOGBRUSH* LogBrush);
	};

	void CBrushS::wl_ConvertToLogBrush(LOGBRUSH* LogBrush, Graphics::EBrushStyle Style)
	{
		switch (Style)
		{
		case Graphics::bsHollow:     LogBrush->lbStyle = BS_HOLLOW;                                     break;
		case Graphics::bsSolid:      LogBrush->lbStyle = BS_SOLID;                                      break;
		case Graphics::bsHorizontal: LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_HORIZONTAL; break;
		case Graphics::bsVertical:   LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_VERTICAL;   break;
		case Graphics::bsFDiagonal:  LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_FDIAGONAL;  break;
		case Graphics::bsBDiagonal:  LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_BDIAGONAL;  break;
		case Graphics::bsCross:      LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_CROSS;      break;
		case Graphics::bsDiagCross:  LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_DIAGCROSS;  break;
		}
	}

	void CBrushS::wl_Replace(const LOGBRUSH * LogBrush)
	{
		CBrushHandle NewBrush;
		if (NewBrush.CreateIndirect(LogBrush) == true)
		{
			Delete();
			Attach(NewBrush.Detach());
			m_OwnDC.selectBrush(getHandle());
		}
	}


	inline CBrushS::CBrushS(Graphics::CDeviceContext & DC) : m_OwnDC(DC)
	{
	}

	void CBrushS::setColor(const Graphics::CColor & Color)
	{
		LOGBRUSH logBrush = {};
		getInfo(&logBrush);
		logBrush.lbColor = Color;
		wl_Replace(&logBrush);
	}

	void CBrushS::setStyle(const Graphics::EBrushStyle & Style)
	{
		LOGBRUSH logBrush = {};
		getInfo(&logBrush);
		wl_ConvertToLogBrush(&logBrush, Style);
		wl_Replace(&logBrush);
	}
}

#endif //!WL_BRUSH_DETAIL_HPP