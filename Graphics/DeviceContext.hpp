#ifndef WL_DEVICE_CONTEXT_HPP
#define WL_DEVICE_CONTEXT_HPP

#include <Windows.h>
#include <WinLib/Utility.hpp>

namespace Graphics
{
    class CRECT : public RECT
    {
    public:
        CRECT(int Left, int Top, int Right, int Bottom)
        {
            left = Left;
            top = Top;
            right = Right;
            bottom = Bottom;
        }
    };

    enum EStockPens
    {
        spWhite = WHITE_PEN,
        spBlack = BLACK_PEN,
        spNull  = NULL_PEN,
        spDC    = DC_PEN
    };

    enum EStockBrushes
    {
        sbWhite     = WHITE_BRUSH,
        sbLightGray = LTGRAY_BRUSH,
        sbGray      = GRAY_BRUSH,
        sbDarkGray  = DKGRAY_BRUSH,
        sbBlack     = BLACK_BRUSH,
        sbNull      = NULL_BRUSH,
        sbDC        = DC_BRUSH
    };

    enum EStockFonts
    {
        sfOEMFixed      = OEM_FIXED_FONT,
        sfANSIFixed     = ANSI_FIXED_FONT,
        sfANSIVar       = ANSI_VAR_FONT,
        sfSystem        = SYSTEM_FONT,
        sfDeviceDefault = DEVICE_DEFAULT_FONT,
        sfSystemFixed   = SYSTEM_FIXED_FONT,
        sfDefualtGUI    = DEFAULT_GUI_FONT
    };

    enum ERasterOperationCodes
    {
        ropBlackness      = BLACKNESS,
        ropCaptureBlt     = CAPTUREBLT,
        ropDstInvert      = DSTINVERT,
        ropMergeCopy      = MERGECOPY,
        ropMergePaint     = MERGEPAINT,
        ropNoMirrorBitmap = NOMIRRORBITMAP,
        ropNotSrcCopy     = NOTSRCCOPY,
        ropNotSrcErase    = NOTSRCERASE,
        ropPatCopy        = PATCOPY,
        ropPatInvert      = PATINVERT,
        ropPatPaint       = PATPAINT,
        ropSrcAnd         = SRCAND,
        ropSrcCopy        = SRCCOPY,
        ropSrcErase       = SRCERASE,
        ropSrcInvert      = SRCINVERT,
        ropSrcPaint       = SRCPAINT,
        ropWhiteness      = WHITENESS
    };

    class CDeviceContext;

    bool BitBlockTransfer(HDC DestDC, int DestLeft, int DestTop, int Width, int Height,
        HDC SrcDC, int SrcLeft, int SrcTop, ERasterOperationCodes RastOp);

    bool BitBlockTransfer(HDC DestDC, const POINT* DestPoint, const SIZE* Size,
        HDC SrcDC, const POINT* SrcPoint, ERasterOperationCodes RastOp);

    bool BitBlockTransfer(HDC DestDC, const POINT & DestPoint, const SIZE & Size,
        HDC SrcDC, const POINT & SrcPoint, ERasterOperationCodes RastOp);


    class CDeviceContext
    {
    private:
        HDC m_DC = NULL;

    public:
        ~CDeviceContext();

        inline operator HDC();

        inline void Attach(HDC NewDC);
        inline HDC Detach();

        inline bool Create(LPCTSTR DriverName, LPCTSTR DeviceName, const DEVMODE* InitData);
        inline bool CreateCompatible(HDC DC);
        bool Delete();
        
        inline bool isNull();

        inline HPEN    getPen   () const;
        inline HBRUSH  getBrush () const;
        inline HFONT   getFont  () const;
        inline HBITMAP getBitmap() const;
        inline HRGN    getRgn   () const;

        HPEN    selectPen   (HPEN    Pen);
        HBRUSH  selectBrush (HBRUSH  Brush);
        HFONT   selectFont  (HFONT   Font);
        HBITMAP selectBitmap(HBITMAP Bitmap);
        HRGN    selectRgn   (HRGN    Rgn);

        HPEN    selectStockPen  (EStockPens    Pen);
        HBRUSH  selectStockBrush(EStockBrushes Brush);
        HFONT   selectStockFont (EStockFonts   Font);

        inline COLORREF getPixel(int Left, int Top);
        inline bool     setPixel(int Left, int Top, COLORREF Color);

        inline int getDeviceCaps(int Index);

        //=======================================Line-Output Functions=============================
        
        inline bool getPos(POINT* Point) const;
        inline bool MoveTo(int X, int Y, POINT* RetPoint = NULL);
        inline bool MoveTo(POINT* Point,  POINT* RetPoint = NULL);

        inline bool LineTo(int x, int y);
        inline bool LineTo(POINT* Point);

        //----------------------------------------------Arc----------------------------------------

        inline bool Arc(int LeftRect, int TopRect, int RightRect, int BottomRect, int XStartArc, int YStartArc, int XEndArc, int YEndArc);
        inline bool Arc(const RECT* Rect, const POINT* Start, const POINT* End);
        inline bool ArcTo(int LeftRect, int TopRect, int RightRect, int BottomRect, int XStartArc, int YStartArc, int XEndArc, int YEndArc);
        inline bool ArcTo(const RECT* Rect, const POINT* Start, const POINT* End);

        //------------------------------------------Angle arc--------------------------------------

        inline bool AngleArc(int x, int y, int Radius, float StartAngle, float SweepAngle);
        inline int  getArcDirection() const;
        inline int  SetArcDirection(int ArcDirection);

        //--------------------------------------PolyLine-------------------------------------------
       
        inline bool Polyline    (const POINT Points[],                           int Count);
        inline bool PolyDraw    (const POINT Points[], const BYTE Types[],       int Count);
        inline bool PolylineTo  (const POINT Points[],                           int Count);
        inline bool PolyPolyline(const POINT Points[], const DWORD PolyPoints[], int Count);

        //-----------------------------------------------------------------------------------------

        inline bool PolyBezier  (const POINT Points[], int Count);
        inline bool PolyBezierTo(const POINT Points[], int Count);

        //=========================================Simple Drawing Functions========================
        
        inline bool FillRect  (const RECT* Rect, HBRUSH Brush);
        inline bool FillRect  (const RECT& Rect, HBRUSH Brush);

        inline bool FrameRect (const RECT* Rect, HBRUSH Brush);
        inline bool InvertRect(const RECT* Rect);

        //==========================================Ellipse Functions================================================


        inline bool Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
        inline bool Chord(const RECT* Rect, const POINT* Start, const POINT* End);

        //------------------------------------------------------------------------------------------------------------------

        inline bool Ellipse(int Left, int Top, int Right, int Bottom);
        inline bool Ellipse(const RECT* Rect);
        inline bool Circle(int cLeft, int cTop, int Radius);

        //------------------------------------------------------------------------------------------------------------------

        inline bool Pie(int LeftRect, int TopRect, int RightRect, int BottomRect, int XRadial1, int YRadial1, int XRadial2, int YRadial2);
        inline bool Pie(const RECT* Rect, const POINT* Start, const POINT* End);

        //=================================================Polygone Functions================================================

        inline bool Polygon(const POINT Points[], int Count);

        //=================================================Rectangle Functions================================================

        inline bool Rectangle(int Left, int Top, int Right, int Bottom);
        inline bool RoundRect(int Left, int Top, int Right, int Bottom, int Width, int Height);
        inline bool RoundRect(int Left, int Top, int Right, int Bottom, int Radius);

        inline bool Rectangle(const RECT* Rect);
        inline bool RoundRect(const RECT* Rect, int Width, int Height);
        inline bool RoundRect(const RECT* Rect, int Radius);

        //====================================================Text Functions===================================================

        inline bool TextOut(int Left, int Top, LPCTSTR String, int Length);
    };
    
    bool BitBlockTransfer(HDC DestDC, int DestLeft, int DestTop, int Width, int Height,
        HDC SrcDC, int SrcLeft, int SrcTop, ERasterOperationCodes RastOp)
    {
        WL_ASSERT(SrcDC != NULL);
        WL_ASSERT(DestDC != NULL);
        return true && ::BitBlt(DestDC, DestLeft, DestTop, Width, Height, SrcDC, SrcLeft, SrcTop, RastOp);
    }

    bool BitBlockTransfer(HDC DestDC, const POINT * DestPoint, const SIZE * Size,
        HDC SrcDC, const POINT * SrcPoint, ERasterOperationCodes RastOp)
    {
        WL_ASSERT(SrcDC != NULL);
        WL_ASSERT(DestDC != NULL);
        WL_ASSERT(DestPoint != NULL);
        WL_ASSERT(SrcPoint != NULL);
        WL_ASSERT(Size != NULL);
        return true && ::BitBlt(DestDC, DestPoint->x, DestPoint->y, Size->cx, Size->cy, SrcDC, SrcPoint->x, SrcPoint->y, RastOp);
    }

    bool BitBlockTransfer(HDC DestDC, const POINT & DestPoint, const SIZE & Size,
        HDC SrcDC, const POINT & SrcPoint, ERasterOperationCodes RastOp)
    {
        return true && ::BitBlt(DestDC, DestPoint.x, DestPoint.y, Size.cx, Size.cy, SrcDC, SrcPoint.x, SrcPoint.y, RastOp);
    }

    inline CDeviceContext::~CDeviceContext()
    {
        WL_ASSERT(m_DC == NULL);
    }

    inline CDeviceContext::operator HDC()
    {
        return m_DC;
    }

    inline void CDeviceContext::Attach(HDC NewDC)
    {
        WL_ASSERT(m_DC == NULL);
        WL_ASSERT(NewDC != NULL);
        m_DC = NewDC;
    }

    inline HDC CDeviceContext::Detach()
    {
        HDC RetDC = m_DC;
        m_DC = NULL;
        return RetDC;
    }

    inline bool CDeviceContext::Create(LPCTSTR DriverName, LPCTSTR DeviceName, const DEVMODE * InitData)
    {
        WL_ASSERT(m_DC == NULL);
        m_DC = ::CreateDC(DriverName, DeviceName, NULL, InitData);
        return m_DC != 0;
    }

    inline bool CDeviceContext::CreateCompatible(HDC DC)
    {
        WL_ASSERT(m_DC == NULL);
        WL_ASSERT(DC != NULL);
        m_DC = ::CreateCompatibleDC(DC);
        return m_DC != 0;
    }

    bool CDeviceContext::Delete()
    {
        if (m_DC == NULL) 
            return false;
        if (::DeleteDC(m_DC))
        {
            m_DC = NULL;
            return true;
        }
        return false;
    }

    inline bool CDeviceContext::isNull()
    {
        return m_DC == NULL;
    }

    inline HPEN CDeviceContext::getPen() const
    {
        WL_ASSERT(m_DC != NULL);
        return (HPEN)::GetCurrentObject(m_DC, OBJ_PEN);
    }

    inline HBRUSH CDeviceContext::getBrush() const
    {
        WL_ASSERT(m_DC != NULL);
        return (HBRUSH)::GetCurrentObject(m_DC, OBJ_BRUSH);
    }

    inline HFONT CDeviceContext::getFont() const
    {
        WL_ASSERT(m_DC != NULL);
        return (HFONT)::GetCurrentObject(m_DC, OBJ_FONT);
    }

    inline HBITMAP CDeviceContext::getBitmap() const
    {
        WL_ASSERT(m_DC != NULL);
        return (HBITMAP)::GetCurrentObject(m_DC, OBJ_BITMAP);
    }

    inline HRGN CDeviceContext::getRgn() const
    {
        WL_ASSERT(m_DC != NULL);
        return (HRGN)::GetCurrentObject(m_DC, OBJ_REGION);
    }

    HPEN CDeviceContext::selectPen(HPEN Pen)
    {
        WL_ASSERT(m_DC != NULL);
        WL_ASSERT(Pen == NULL || ::GetObjectType(Pen) == OBJ_PEN || ::GetObjectType(Pen) == OBJ_EXTPEN);
        WL_ASSERT(Pen != NULL);
        return (HPEN)::SelectObject(m_DC, Pen);
    }

    HBRUSH CDeviceContext::selectBrush(HBRUSH Brush)
    {
        WL_ASSERT(m_DC != NULL);
        WL_ASSERT(Brush == NULL || ::GetObjectType(Brush) == OBJ_BRUSH);
        WL_ASSERT(Brush != NULL);
        return (HBRUSH)::SelectObject(m_DC, Brush);
    }

    HFONT CDeviceContext::selectFont(HFONT Font)
    {
        WL_ASSERT(m_DC != NULL);
        WL_ASSERT(Font == NULL || ::GetObjectType(Font) == OBJ_FONT);
        WL_ASSERT(Font != NULL);
        return (HFONT)::SelectObject(m_DC, Font);
    }

    HBITMAP CDeviceContext::selectBitmap(HBITMAP Bitmap)
    {
        WL_ASSERT(m_DC != NULL);
        WL_ASSERT(Bitmap == NULL || ::GetObjectType(Bitmap) == OBJ_BITMAP);
        WL_ASSERT(Bitmap != NULL);
        return (HBITMAP)::SelectObject(m_DC, Bitmap);
    }

    HRGN CDeviceContext::selectRgn(HRGN Rgn)
    {
        WL_ASSERT(m_DC != NULL);
        WL_ASSERT(Rgn == NULL || ::GetObjectType(Rgn) == OBJ_REGION);
        WL_ASSERT(Rgn != NULL);
        return (HRGN)::SelectObject(m_DC, Rgn);
    }

    HPEN CDeviceContext::selectStockPen(EStockPens Pen)
    {
        WL_ASSERT(m_DC != NULL);
        return selectPen((HPEN)::GetStockObject(Pen));
    }

    HBRUSH CDeviceContext::selectStockBrush(EStockBrushes Brush)
    {
        WL_ASSERT(m_DC != NULL);
        return selectBrush((HBRUSH)::GetStockObject(Brush));
    }

    HFONT CDeviceContext::selectStockFont(EStockFonts Font)
    {
         return selectFont((HFONT)::GetStockObject(Font));
    }

    inline COLORREF CDeviceContext::getPixel(int Left, int Top)
    {
        return ::GetPixel(m_DC, Left, Top);
    }

    inline bool CDeviceContext::setPixel(int Left, int Top, COLORREF Color)
    {
        return true && ::SetPixelV(m_DC, Left, Top, Color);
    }

    inline int CDeviceContext::getDeviceCaps(int Index)
    {
        WL_ASSERT(m_DC != NULL);
        return ::GetDeviceCaps(m_DC, Index);
    }

    inline bool CDeviceContext::getPos(POINT * Point) const
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::GetCurrentPositionEx(m_DC, Point);
    }

    inline bool CDeviceContext::MoveTo(int x, int y, POINT * RetPoint)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::MoveToEx(m_DC, x, y, RetPoint);
    }

    inline bool CDeviceContext::MoveTo(POINT* Point, POINT * RetPoint)
    {
        WL_ASSERT(m_DC != NULL);
        return MoveTo(Point->x, Point->y, RetPoint);
    }

    inline bool CDeviceContext::LineTo(int x, int y)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::LineTo(m_DC, x, y);
    }

    inline bool CDeviceContext::LineTo(POINT * Point)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::LineTo(m_DC, Point->x, Point->y);
    }

    inline bool CDeviceContext::Arc(int LeftRect, int TopRect, int RightRect, int BottomRect, 
        int XStartArc, int YStartArc, int XEndArc, int YEndArc)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Arc(m_DC, LeftRect, TopRect, RightRect, BottomRect, XStartArc, YStartArc, XEndArc, YEndArc);
    }

    inline bool CDeviceContext::Arc(const RECT * Rect, const POINT * Start, const POINT * End)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Arc(m_DC, Rect->left, Rect->top, Rect->right, Rect->bottom,
            Start->x, Start->y,
            End->x, End->y);
    }

    inline bool CDeviceContext::ArcTo(int LeftRect, int TopRect, int RightRect, int BottomRect, 
        int XStartArc, int YStartArc, int XEndArc, int YEndArc)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::ArcTo(m_DC, LeftRect, TopRect, RightRect, BottomRect, XStartArc, YStartArc, XEndArc, YEndArc);
    }

    inline bool CDeviceContext::ArcTo(const RECT * Rect, const POINT * Start, const POINT * End)
    {
        WL_ASSERT(m_DC != NULL);
        return ArcTo(Rect->left, Rect->top, Rect->right, Rect->bottom, Start->x, Start->y, End->x, End->y);
    }

    inline bool CDeviceContext::AngleArc(int x, int y, int Radius, float StartAngle, float SweepAngle)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::AngleArc(m_DC, x, y, Radius, StartAngle, SweepAngle);
    }

    inline int CDeviceContext::getArcDirection() const
    {
        WL_ASSERT(m_DC != NULL);
        return ::GetArcDirection(m_DC);
    }

    inline int CDeviceContext::SetArcDirection(int ArcDirection)
    {
        WL_ASSERT(m_DC != NULL);
        return ::SetArcDirection(m_DC, ArcDirection);
    }

    inline bool CDeviceContext::Polyline(const POINT Points[], int Count)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Polyline(m_DC, Points, Count);
    }

    inline bool CDeviceContext::PolyDraw(const POINT Points[], const BYTE Types[], int Count)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::PolyDraw(m_DC, Points, Types, Count);
    }

    inline bool CDeviceContext::PolylineTo(const POINT Points[], int Count)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::PolylineTo(m_DC, Points, Count);
    }

    inline bool CDeviceContext::PolyPolyline(const POINT Points[], const DWORD PolyPoints[], int Count)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::PolyPolyline(m_DC, Points, PolyPoints, Count);
    }

    inline bool CDeviceContext::PolyBezier(const POINT Points[], int Count)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::PolyBezier(m_DC, Points, Count);
    }

    inline bool CDeviceContext::PolyBezierTo(const POINT Points[], int Count)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::PolyBezierTo(m_DC, Points, Count);
    }

    inline bool CDeviceContext::FillRect(const RECT * Rect, HBRUSH Brush)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::FillRect(m_DC, Rect, Brush);
    }

    inline bool CDeviceContext::FillRect(const RECT & Rect, HBRUSH Brush)
    {
        return true && ::FillRect(m_DC, &Rect, Brush);
    }

    inline bool CDeviceContext::FrameRect(const RECT * Rect, HBRUSH Brush)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::FrameRect(m_DC, Rect, Brush);
    }

    inline bool CDeviceContext::InvertRect(const RECT * Rect)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::InvertRect(m_DC, Rect);
    }

    inline bool CDeviceContext::Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Chord(m_DC, x1, y1, x2, y2, x3, y3, x4, y4);
    }

    inline bool CDeviceContext::Chord(const RECT * Rect, const POINT * Start, const POINT * End)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Chord(m_DC, Rect->left, Rect->top, Rect->right, Rect->bottom, Start->x, Start->y, End->x, End->y);
    }

    inline bool CDeviceContext::Ellipse(int Left, int Top, int Right, int Bottom)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Ellipse(m_DC, Left, Top, Right, Bottom);
    }

    inline bool CDeviceContext::Ellipse(const RECT * Rect)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Ellipse(m_DC, Rect->left, Rect->top, Rect->right, Rect->bottom);
    }

    inline bool CDeviceContext::Circle(int cLeft, int cTop, int Radius)
    {
        return true && ::Ellipse(m_DC, cLeft - Radius, cTop - Radius, cLeft + Radius, cTop + Radius);
    }

    inline bool CDeviceContext::Pie(int LeftRect, int TopRect, int RightRect, int BottomRect, int XRadial1, int YRadial1, int XRadial2, int YRadial2)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Pie(m_DC, LeftRect, TopRect, RightRect, BottomRect,
            XRadial1, YRadial1, XRadial2, YRadial2);
    }

    inline bool CDeviceContext::Pie(const RECT * Rect, const POINT * Start, const POINT * End)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Pie(m_DC, Rect->left, Rect->top, Rect->right, Rect->bottom, Start->x, Start->y, End->x, End->y);
    }

    inline bool CDeviceContext::Polygon(const POINT Points[], int Count)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Polygon(m_DC, Points, Count);
    }

    inline bool CDeviceContext::Rectangle(int Left, int Top, int Right, int Bottom)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Rectangle(m_DC, Left, Top, Right, Bottom);
    }

    inline bool CDeviceContext::Rectangle(const RECT * Rect)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::Rectangle(m_DC, Rect->left, Rect->top, Rect->right, Rect->bottom);
    }

    inline bool CDeviceContext::RoundRect(int Left, int Top, int Right, int Bottom, int Width, int Height)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::RoundRect(m_DC, Left, Top, Right, Bottom, Width, Height);
    }

    inline bool CDeviceContext::RoundRect(const RECT * Rect, int Width, int Height)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::RoundRect(m_DC, Rect->left, Rect->top, Rect->right, Rect->bottom, Width, Height);
    }

    inline bool CDeviceContext::RoundRect(int Left, int Top, int Right, int Bottom, int Radius)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::RoundRect(m_DC, Left, Top, Right, Bottom, Radius, Radius);
    }

    inline bool CDeviceContext::RoundRect(const RECT * Rect, int Radius)
    {
        WL_ASSERT(m_DC != NULL);
        return true && ::RoundRect(m_DC, Rect->left, Rect->top, Rect->right, Rect->bottom, Radius, Radius);
    }

    inline bool CDeviceContext::TextOut(int Left, int Top, LPCTSTR String, int Length)
    {
        WL_ASSERT(m_DC != NULL);
        WL_ASSERT_STRLEN(Length >= 0);
        return true && ::TextOut(m_DC, Left, Top, String, Length);
    }
}
#endif //!WL_DEVICE_CONTEXT_HPP