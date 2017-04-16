#ifndef WL_DEVICE_CONTEXT_SAFE_T_HPP
#define WL_DEVICE_CONTEXT_SAFE_T_HPP

#include <Windows.h>
#include <WinLib/Utility.hpp>
#include <WinLib/Graphics/DeviceContextHelpers.hpp>

namespace GraphicsDetail
{
    template<class AncestorT>
    class CDeviceContextSafeT : public AncestorT
    {
    private:
        HBRUSH  m_OwnBrush = NULL;
        HPEN    m_OwnPen = NULL;
        HFONT   m_OwnFont = NULL;

    public:
        inline bool selectPen(HPEN Pen);
        inline bool selectBrush(HBRUSH Brush);
        inline bool selectFont(HFONT Font);

        CDeviceContextSafeT(HWND Owner);
        ~CDeviceContextSafeT();
    };

    template<class AncestorT>
    inline bool CDeviceContextSafeT<AncestorT>::selectPen(HPEN Pen)
    {
        return AncestorT::selectPen(Pen) != NULL;
    }

    template<class AncestorT>
    inline bool CDeviceContextSafeT<AncestorT>::selectBrush(HBRUSH Brush)
    {
        return AncestorT::selectBrush(Brush) != NULL;
    }

    template<class AncestorT>
    inline bool CDeviceContextSafeT<AncestorT>::selectFont(HFONT Font)
    {
        return AncestorT::selectFont(Font) != NULL;
    }

    template<class AncestorT>
    CDeviceContextSafeT<AncestorT>::CDeviceContextSafeT(HWND Owner) : AncestorT(Owner)
    {
        bool Result = ((m_OwnBrush = AncestorT::getBrush()) != NULL) &&
            ((m_OwnFont = AncestorT::getFont()) != NULL) &&
            ((m_OwnPen = AncestorT::getPen()) != NULL);
        if (Result == false)
        {
            m_OwnBrush = NULL, m_OwnFont = NULL, m_OwnPen = NULL;
            WL_TRACE("We cannot save current objects.");
        }
    }

    template<class AncestorT>
    CDeviceContextSafeT<AncestorT>::~CDeviceContextSafeT()
    {
        bool Result = false;

        if (m_OwnBrush && m_OwnFont && m_OwnPen)
            Result = (AncestorT::selectBrush(m_OwnBrush) != NULL) &&
            (AncestorT::selectFont(m_OwnFont) != NULL) &&
            (AncestorT::selectPen(m_OwnPen) != NULL);
        else
        {
            WL_TRACE("We cannot return DC own object. Memory leak possible.");
            Result = (AncestorT::selectStockBrush(Graphics::sbNull) != NULL) &&
                (AncestorT::selectStockFont(Graphics::sfSystem) != NULL) &&
                (AncestorT::selectStockPen(Graphics::spNull) != NULL);
            if (Result == false)
            {
                WL_TRACE("We cannot do anything (");
                WL_ASSERT(0);
            }
        }
    }
}

#endif //!WL_DEVICE_CONTEXT_SAFE_T_HPP