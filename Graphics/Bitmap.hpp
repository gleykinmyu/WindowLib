#ifndef WL_BITMAP_HPP
#define WL_BITMAP_HPP

#include <WinLib/Graphics/Detail/BitmapRoot.hpp>
#include <WinLib/Utility.hpp>

namespace Graphics 
{
    class CBitmap : public GraphicsDetail::CBitmapRoot
    {
    public:
        CBitmap();

        bool LoadFromFile(LPCTSTR FileName, int Width = 0, int Height = 0);

        Utility::CProperty<Utility::RO, int, CBitmap> Width;
        Utility::CProperty<Utility::RO, int, CBitmap> Height;

    private:
        int     getWidth() const;
        int     getHeight() const;
    };
}

#endif //!WL_BITMAP_HPP