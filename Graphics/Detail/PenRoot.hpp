#ifndef WL_PEN_ROOT_HPP
#define WL_PEN_ROOT_HPP

#include <WinLib/Utility.hpp>
#include <WinLib/Graphics/ObjectHandleWraps.hpp>
#include <WinLib/Graphics/Color.hpp>

namespace GraphicsDetail
{
	class CPenObject : public Graphics::CPenHandle
	{
	public:
		~CPenObject();
	};

	CPenObject::~CPenObject()
	{
		WL_ASSERT(isNull() == true);
	}

	class CPenG : public CPenObject
	{
	public:
		Graphics::CColor    getColor() const;
		Graphics::EPenStyle getStyle() const;
		int                 getWidth() const;
		Graphics::EPenStyle wl_ConvertToStyle(UINT Style) const;
	};

	Graphics::CColor CPenG::getColor() const
	{
		LOGPEN logPen = {};
		getInfo(&logPen);
		return Graphics::CColor(logPen.lopnColor);
	}

	Graphics::EPenStyle CPenG::getStyle() const
	{
		LOGPEN logPen = {};
		getInfo(&logPen);
		return wl_ConvertToStyle(logPen.lopnStyle);
	}

	int CPenG::getWidth() const
	{
		LOGPEN logPen = {};
		getInfo(&logPen);
		return logPen.lopnWidth.x;
	}

	Graphics::EPenStyle CPenG::wl_ConvertToStyle(UINT Style) const
	{
		switch (Style)
		{
		case PS_SOLID:      return Graphics::psSolid;
		case PS_DASH:       return Graphics::psDash;
		case PS_DOT:        return Graphics::psDot;
		case PS_DASHDOT:    return Graphics::psDashDot;
		case PS_DASHDOTDOT: return Graphics::psDasDotDot;
		case PS_NULL:       return Graphics::psNull;
		default: WL_TRACE("There is no suitable conversion from PENSTYLE to EPenStyle!!!");
		}
		return Graphics::psNull;
	}

	class CPenS : public CPenG
	{
	public:
		CPenS(Graphics::CDeviceContext & DC);
		void setColor(const Graphics::CColor & Color);
		void setStyle(const Graphics::EPenStyle & Style);
		void setWidth(int Width);
		Graphics::CDeviceContext & m_OwnDC;
	
	protected:
		void setMixWidth(int Width);

	private:
		void wl_Replace(LOGPEN * LogPen);
	};

	inline CPenS::CPenS(Graphics::CDeviceContext & DC) : m_OwnDC(DC)
	{
	}

	void CPenS::setColor(const Graphics::CColor & Color)
	{
		LOGPEN logPen = {};
		getInfo(&logPen);
		logPen.lopnColor = Color;
		wl_Replace(&logPen);
	}

	void CPenS::setStyle(const Graphics::EPenStyle & Style)
	{
		LOGPEN logPen = {};
		getInfo(&logPen);
		logPen.lopnStyle = Style;
		wl_Replace(&logPen);
	}

	void CPenS::setWidth(int Width)
	{
		WL_ASSERT(Width >= 0);
		LOGPEN logPen = {};
		getInfo(&logPen);
		logPen.lopnWidth.x = Width;
		logPen.lopnWidth.y = 0;
		wl_Replace(&logPen);
	}

	inline void CPenS::setMixWidth(int Width)
	{
		LOGPEN logPen = {};
		getInfo(&logPen);
		logPen.lopnWidth.x += Width;
		WL_ASSERT(logPen.lopnWidth.x >= 0);
		logPen.lopnWidth.y = 0;
		wl_Replace(&logPen);
	}

	void CPenS::wl_Replace(LOGPEN * LogPen)
	{
		CPenHandle NewPen;
		if (NewPen.CreateIndirect(LogPen) == true)
		{
			Delete();
			Attach(NewPen.Detach());
			m_OwnDC.selectPen(getHandle());
		}
	}

}

#endif //!WL_PEN_ROOT_HPP