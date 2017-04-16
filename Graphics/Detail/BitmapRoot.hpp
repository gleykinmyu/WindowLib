#ifndef WL_BITMAP_ROOT_HPP
#define WL_BITMAP_ROOT_HPP

#include <Winlib/Utility.hpp>
#include <WinLib/Graphics/DeviceContext.hpp>
#include <Windows.h>

namespace GraphicsDetail 
{
    class CBitmapRoot
    {
    private:
        HBITMAP m_Bitmap = NULL;

    public:
        ~CBitmapRoot();

        inline operator HBITMAP();

        inline HBITMAP Detach();
        inline void Attach(HBITMAP NewBitmap);

        inline bool Load(HINSTANCE Instance, LPCTSTR BitmapName);
        inline bool Load(HINSTANCE Instance, LPCTSTR ImageName, int Width, int Height, UINT Load);
		
        inline bool Create(int Width, int Height, UINT Planes, UINT BitsPerPixel, const void* Bits);
        inline bool CreateIndirect(BITMAP* Bitmap);
        inline bool CreateCompatible(HDC DC, int Width, int Height);
        inline bool Delete();

        inline int  getInfo(BITMAP* Info) const;
        inline bool getDimension(SIZE* Size) const;
        inline bool setDimension(int Width, int Height, SIZE* Size = NULL);

        /*
        // DIB support
        bool CreateDIB(CDeviceContext* DC, CONST BITMAPINFOHEADER* lpbmih, DWORD dwInit, CONST VOID* lpbInit, CONST BITMAPINFO* lpbmi, UINT uColorUse)
        {
            WL_ASSERT(m_Bitmap == NULL);
            WL_ASSERT(DC);
            m_Bitmap = ::CreateDIBitmap(DC->GetHandle(), lpbmih, dwInit, lpbInit, lpbmi, uColorUse);
            return m_Bitmap != NULL;
        }
#endif // !_WIN32_WCE

        bool CreateDIBSection(CDeviceContext* DC, const BITMAPINFO* lpbmi, UINT uColorUse, void* ppvBits[], HANDLE hSection, DWORD dwOffset)
        {
            WL_ASSERT(m_Bitmap == NULL);
            WL_ASSERT(DC);
            m_Bitmap = ::CreateDIBSection(DC->GetHandle(), lpbmi, uColorUse, ppvBits, hSection, dwOffset);
            return m_Bitmap != NULL;
        }

#ifndef _WIN32_WCE
        int GetDIBits(CDeviceContext* DC, UINT uStartScan, UINT cScanLines, void* lpvBits, BITMAPINFO* lpbmi, UINT uColorUse) const
        {
            WL_ASSERT(m_Bitmap != NULL);
            WL_ASSERT(DC);
            return ::GetDIBits(DC->GetHandle(), m_Bitmap, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
        }

        int SetDIBits(CDeviceContext* DC, UINT uStartScan, UINT cScanLines, const void* lpvBits, const BITMAPINFO* lpbmi, UINT uColorUse)
        {
            WL_ASSERT(m_Bitmap != NULL);
            WL_ASSERT(DC);
            return ::SetDIBits(DC->GetHandle(), m_Bitmap, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
        }
#endif // !_WIN32_WCE*/
    };

    inline CBitmapRoot::~CBitmapRoot()
    {
        WL_ASSERT(m_Bitmap == NULL);
    }

    inline CBitmapRoot::operator HBITMAP()
    {
        return m_Bitmap;
    }

    inline HBITMAP CBitmapRoot::Detach()
    {
        HBITMAP RetBitmap = m_Bitmap;
        m_Bitmap = NULL;
        return RetBitmap;
    }

    inline void CBitmapRoot::Attach(HBITMAP NewBitmap)
    {
        WL_ASSERT(m_Bitmap == NULL);
        WL_ASSERT(NewBitmap != NULL);
        m_Bitmap = NewBitmap;
    }

    inline bool CBitmapRoot::Load(HINSTANCE Instance, LPCTSTR BitmapName)
    {
        WL_ASSERT(m_Bitmap == NULL);
        m_Bitmap = ::LoadBitmap(Instance, BitmapName);
        return m_Bitmap != NULL;
    }

    inline bool CBitmapRoot::Load(HINSTANCE Instance, LPCTSTR ImageName, int Width, int Height, UINT Load)
    {
        WL_ASSERT(m_Bitmap == NULL);
        m_Bitmap = (HBITMAP)::LoadImageA(Instance, ImageName, IMAGE_BITMAP, Width, Height, Load);
        return m_Bitmap != NULL;
    }

    inline bool CBitmapRoot::Create(int Width, int Height, UINT Planes, UINT BitsPerPixel, const void * Bits)
    {
        WL_ASSERT(m_Bitmap == NULL);
        m_Bitmap = ::CreateBitmap(Width, Height, Planes, BitsPerPixel, Bits);
        return m_Bitmap != NULL;
    }

    inline bool CBitmapRoot::CreateIndirect(BITMAP * Bitmap)
    {
        WL_ASSERT(m_Bitmap == NULL);
        WL_ASSERT(Bitmap != NULL);
        m_Bitmap = ::CreateBitmapIndirect(Bitmap);
        return m_Bitmap != NULL;
    }

    inline bool CBitmapRoot::CreateCompatible(HDC DC, int Width, int Height)
    {
        WL_ASSERT(m_Bitmap == NULL);
        WL_ASSERT(DC);
        m_Bitmap = ::CreateCompatibleBitmap(DC, Width, Height);
        return m_Bitmap != NULL;
    }

    inline bool CBitmapRoot::Delete()
    {
        bool Result = true && ::DeleteObject(m_Bitmap);
        if (Result) m_Bitmap = NULL;
        return Result;
    }

    inline int CBitmapRoot::getInfo(BITMAP * Info) const
    {
        WL_ASSERT(m_Bitmap != NULL);
        WL_ASSERT(Info);
        return ::GetObject(m_Bitmap, sizeof(BITMAP), Info);
    }

    inline bool CBitmapRoot::getDimension(SIZE * Size) const
    {
        WL_ASSERT(m_Bitmap != NULL);
        WL_ASSERT(Size != NULL);
        return true && ::GetBitmapDimensionEx(m_Bitmap, Size);
    }

    inline bool CBitmapRoot::setDimension(int Width, int Height, SIZE * Size)
    {
        WL_ASSERT(m_Bitmap != NULL);
        return true && ::SetBitmapDimensionEx(m_Bitmap, Width, Height, Size);
    }
}

#endif