#ifndef WL_BITMAP_CPP
#define WL_BITMAP_CPP

#include <WinLib/Graphics/Bitmap.hpp>

namespace Graphics 
{
    CBitmap::CBitmap()
    {
        Width. Init(this, &CBitmap::getWidth);
        Height.Init(this, &CBitmap::getHeight);
    }

	CBitmap::~CBitmap()
	{
		WL_ASSERT(isNull() == true);
	}

    bool CBitmap::LoadFromFile(LPCTSTR FileName, int Width, int Height)
    {
        return Load(NULL, FileName, Width, Height, LR_LOADFROMFILE);
    }

    int CBitmap::getWidth() const
    {
        BITMAP BitmapInfo = {};
        getInfo(&BitmapInfo);
        return BitmapInfo.bmWidth;
    }

    int CBitmap::getHeight() const
    {
        BITMAP BitmapInfo = {};
        getInfo(&BitmapInfo);
        return BitmapInfo.bmHeight;
    }
}

#endif //!WL_BITMAP_CPP