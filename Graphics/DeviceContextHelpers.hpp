#ifndef WL_DEVICE_CONTEXT_HELPERS_HPP
#define WL_DEVICE_CONTEXT_HELPERS_HPP

#include <Windows.h>
#include <WinLib/Utility.hpp>
#include <WinLib/Graphics/DeviceContext.hpp>

namespace Graphics
{
    class CClientDCroot : public CDeviceContext
    {
    private:
        HWND m_Owner = NULL;

    public:
        CClientDCroot(HWND Owner)
        {
            WL_ASSERT(isNull() == true);
            WL_ASSERT(Owner);
            HDC DC = ::GetDC(Owner);
            if (DC != NULL)
                Attach(DC);
        }

        ~CClientDCroot()
        {
            WL_ASSERT(isNull() == false);
            ::ReleaseDC(m_Owner, Detach());
        }
    };

    class CWindowDCroot : public CDeviceContext
    {
    private:
        HWND m_Owner = NULL;

    public:
        CWindowDCroot(HWND Owner)
        {
            WL_ASSERT(isNull() == true);
            WL_ASSERT(Owner);
            HDC DC = ::GetWindowDC(Owner);
            if (DC != NULL)
                Attach(DC);
        }

        ~CWindowDCroot()
        {
            WL_ASSERT(isNull() == false);
            ::ReleaseDC(m_Owner, Detach());
        }
    };

    class CPaintDCroot : public CDeviceContext
    {
    private:
        HWND        m_Owner = NULL;

    public:
        PAINTSTRUCT PtStruct = {};

        CPaintDCroot(HWND Owner)
        {
            WL_ASSERT(isNull() == true);
            WL_ASSERT(Owner);
            HDC DC = ::BeginPaint(Owner, &PtStruct);
            if (DC != NULL)
                Attach(DC);
        }

        ~CPaintDCroot()
        {
            WL_ASSERT(isNull() == false);
            if (::EndPaint(m_Owner, &PtStruct) != false)
                Detach();
        }
    };

    class CMemoryDCroot : public CDeviceContext
    {
    public:
        CMemoryDCroot(HDC CompDC, int Width, int Height)
        {
            WL_ASSERT(isNull() == true);
            WL_ASSERT(CompDC);
            HDC DC = ::CreateCompatibleDC(CompDC);
            if (DC != NULL)
                Attach(DC);
        }

        ~CMemoryDCroot()
        {
            CDeviceContext::Delete();
        }
    };
}

#endif //!WL_DEVICE_CONTEXT_HELPERS_HPP