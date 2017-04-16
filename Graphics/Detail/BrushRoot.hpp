#ifndef WL_BRUSH_DETAIL_HPP
#define WL_BRUSH_DETAIL_HPP

#include <Windows.h>

namespace GraphicsDetail
{
    class CBrushRoot
    {
    private:
        HBRUSH m_Brush = NULL;

    public:
        ~CBrushRoot();

        inline operator HBRUSH();

        inline void Attach(HBRUSH NewBrush);
        inline HBRUSH Detach();

        inline HBRUSH getHandle() const;

        inline bool CreateSolid(COLORREF Color);
        inline bool CreateHatch(int Hatch, COLORREF Color);
        inline bool CreateIndirect(const LOGBRUSH* BrushInfo);
               bool Delete();

        inline int getInfo(LOGBRUSH* LogBrush) const;
    };

    inline CBrushRoot::~CBrushRoot()
    {
        WL_ASSERT(m_Brush == NULL);
    }

    inline CBrushRoot::operator HBRUSH()
    {
        return m_Brush;
    }

    inline void CBrushRoot::Attach(HBRUSH NewBrush)
    {
        WL_ASSERT(m_Brush == NULL);
        WL_ASSERT(NewBrush != NULL);
        m_Brush = NewBrush;
    }

    inline HBRUSH CBrushRoot::Detach()
    {
        HBRUSH RetBrush = m_Brush;
        m_Brush = NULL;
        return RetBrush;
    }

    inline HBRUSH CBrushRoot::getHandle() const
    {
        return m_Brush;
    }

    inline bool CBrushRoot::CreateSolid(COLORREF Color)
	{
        WL_ASSERT(m_Brush == NULL);
		m_Brush = ::CreateSolidBrush(Color);
        return true && m_Brush;
	}
	
    inline bool CBrushRoot::CreateHatch(int Hatch, COLORREF Color)
    {
        WL_ASSERT(m_Brush == NULL);
        m_Brush = ::CreateHatchBrush(Hatch, Color);
        return true && m_Brush;
    }

    inline bool CBrushRoot::CreateIndirect(const LOGBRUSH * BrushInfo)
    {
        WL_ASSERT(BrushInfo);
        WL_ASSERT(m_Brush == NULL);
        m_Brush = ::CreateBrushIndirect(BrushInfo);
        return true && m_Brush;
    }

    bool CBrushRoot::Delete()
    {
        bool Result = true && ::DeleteObject(m_Brush);
        if (Result) m_Brush = NULL;
        return Result;
    }

    inline int CBrushRoot::getInfo(LOGBRUSH * LogBrush) const
    {
        WL_ASSERT(m_Brush != NULL);
        return ::GetObject(m_Brush, sizeof(LOGBRUSH), LogBrush);
    }
}

#endif //!WL_BRUSH_DETAIL_HPP