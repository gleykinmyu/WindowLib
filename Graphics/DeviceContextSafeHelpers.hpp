#ifndef WL_DEVICE_CONTEXT_SAFE_HPP
#define WL_DEVICE_CONTEXT_SAFE_HPP

#include <Windows.h>
#include <WinLib/Graphics//Detail/DeviceContextSafeHelpersT.hpp>

namespace Graphics
{
    typedef GraphicsDetail::CDeviceContextSafeT<CClientDCroot> CClientDCsafe;
    typedef GraphicsDetail::CDeviceContextSafeT<CWindowDCroot> CWindowDCsafe;
    typedef GraphicsDetail::CDeviceContextSafeT<CPaintDCroot>  CPaintDCSafe;

    class CMemoryDCsafe : public CMemoryDCroot
    {
    private:
        HBITMAP m_OwnBitmap = NULL;

    public:
        CMemoryDCsafe(HDC CompDC, int Width, int Height) : CMemoryDCroot(CompDC, Width, Height)
        {
            m_OwnBitmap = CMemoryDCroot::getBitmap();
            if (m_OwnBitmap == NULL) WL_TRACE("We coudn't save DC own Bitmap");
        }

        ~CMemoryDCsafe()
        {
            if (m_OwnBitmap != NULL)
                if (selectBitmap(m_OwnBitmap) == NULL)
                    WL_TRACE("We coudn't return DC own Bitmap");
        }
    };
}

#endif // !WL_DEVICE_CONTEXT_SAFE_HPP