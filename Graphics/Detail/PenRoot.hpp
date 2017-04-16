#ifndef WL_PEN_ROOT_HPP
#define WL_PEN_ROOT_HPP

#include <Windows.h> 

namespace GraphicsDetail
{
    class CPenRoot
    {
    private:
        HPEN m_Pen = NULL;

    public:
        ~CPenRoot();

        inline HPEN getHandle() const;

        inline void Attach(HPEN NewPen);
        inline HPEN Detach();

        inline bool Create(int Style, int Width, COLORREF Color);

        inline bool CreateIndirect(LOGPEN* LogPen);
        inline bool Delete();

        inline int getInfo(LOGPEN* LogPen) const;
    };

    inline CPenRoot::~CPenRoot()
    {
        WL_ASSERT(m_Pen == NULL);
    }

    inline HPEN CPenRoot::getHandle() const
    {
        return m_Pen;
    }

    inline void CPenRoot::Attach(HPEN NewPen)
    {
        WL_ASSERT(m_Pen == NULL);
        WL_ASSERT(NewPen != NULL);
        m_Pen = NewPen;
    }

    inline HPEN CPenRoot::Detach()
    {
        HPEN RetPen = m_Pen;
        m_Pen = NULL;
        return RetPen;
    }

    inline bool CPenRoot::Create(int Style, int Width, COLORREF Color)
    {
        WL_ASSERT(Width >= 0);
        m_Pen = ::CreatePen(Style, Width, Color);
        return m_Pen != NULL;
    }

    inline bool CPenRoot::CreateIndirect(LOGPEN * LogPen)
    {
        WL_ASSERT(LogPen != NULL);
        m_Pen = ::CreatePenIndirect(LogPen);
        return m_Pen != NULL;
    }

    inline bool CPenRoot::Delete()
    {
        WL_ASSERT(m_Pen != NULL);
        bool Result = true && ::DeleteObject(m_Pen);
        if (Result) m_Pen = NULL;
        return Result;
    }

    inline int CPenRoot::getInfo(LOGPEN * LogPen) const
    {
        WL_ASSERT(m_Pen != NULL);
        WL_ASSERT(LogPen != NULL);
        return ::GetObject(m_Pen, sizeof(LOGPEN), LogPen);
    }
}

#endif // !WL_PEN_ROOT_HPP