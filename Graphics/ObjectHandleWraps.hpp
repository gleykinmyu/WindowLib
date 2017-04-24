#ifndef WL_OBJECT_HANDLE_WRAPS_HPP
#define WL_OBJECT_HANDLE_WRAPS_HPP

#include <Windows.h>
#include <WinLib/Graphics/ObjectEnums.hpp>
#include <WinLib/Graphics/StructWraps.hpp>

namespace Graphics
{
	class CPenHandle
	{
	private:
		HPEN m_Pen = NULL;

	public:
		CPenHandle();
		CPenHandle(HPEN Pen);

		inline operator HPEN();

		inline bool isNull();
		inline HPEN getHandle() const;

		inline void Attach(HPEN NewPen);
		inline HPEN Detach();

		inline bool Create(int Style, int Width, COLORREF Color);

		inline bool CreateIndirect(LOGPEN* LogPen);
		inline bool Delete();

		inline int  getInfo(LOGPEN* LogPen) const;
	};

	class CBrushHandle
	{
	private:
		HBRUSH m_Brush = NULL;

	public:
		CBrushHandle();
		CBrushHandle(HBRUSH Brush);

		inline operator HBRUSH();

		inline void Attach(HBRUSH NewBrush);
		inline HBRUSH Detach();

		inline HBRUSH getHandle() const;

		inline bool isNull();

		inline bool CreateSolid(COLORREF Color);
		inline bool CreateHatch(int Hatch, COLORREF Color);
		inline bool CreateIndirect(const LOGBRUSH* BrushInfo);
		bool Delete();

		inline int getInfo(LOGBRUSH* LogBrush) const;
	};

	class CBitmapHandle
	{
	private:
		HBITMAP m_Bitmap = NULL;

	public:
		CBitmapHandle();
		CBitmapHandle(HBITMAP Bitmap);

		inline operator HBITMAP();

		inline bool isNull();
		inline HBITMAP getHandle();

		inline HBITMAP Detach();
		inline void    Attach(HBITMAP NewBitmap);

		inline bool Load(HINSTANCE Instance, LPCTSTR BitmapName);
		inline bool Load(HINSTANCE Instance, LPCTSTR ImageName, int Width, int Height, UINT Load);

		inline bool Create(int Width, int Height, UINT Planes, UINT BitsPerPixel, const void* Bits);
		inline bool CreateIndirect(BITMAP * Bitmap);
		inline bool CreateCompatible(HDC DC, int Width, int Height);
		inline bool Delete();

		inline int  getInfo(BITMAP* Info) const;
		inline bool getDimension(SIZE* Size) const;
		inline bool setDimension(int Width, int Height, SIZE* Size = NULL);
	};

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

		inline CPenHandle    getPen   () const;
		inline CBrushHandle  getBrush () const;
		inline HFONT         getFont  () const;
		inline CBitmapHandle getBitmap() const;
		inline HRGN          getRgn   () const;

		CPenHandle    selectPen   (HPEN    Pen);
		CBrushHandle  selectBrush (HBRUSH  Brush);
		HFONT         selectFont  (HFONT   Font);
		CBitmapHandle selectBitmap(HBITMAP Bitmap);
		HRGN          selectRgn   (HRGN    Rgn);

		CPenHandle    selectStockPen(EStockPens    Pen);
		CBrushHandle  selectStockBrush(EStockBrushes Brush);
		HFONT         selectStockFont(EStockFonts   Font);

		inline COLORREF getPixel(int Left, int Top);
		inline bool     setPixel(int Left, int Top, COLORREF Color);

		inline int getDeviceCaps(int Index);

		//=======================================Line-Output Functions=============================

		inline bool getPos(POINT* Point) const;
		inline bool MoveTo(int X, int Y, POINT* RetPoint = NULL);
		inline bool MoveTo(POINT* Point, POINT* RetPoint = NULL);

		inline bool LineTo(int x, int y);
		inline bool LineTo(POINT* Point);

		//----------------------------------------------Arc----------------------------------------

		inline bool Arc(int LeftRect, int TopRect, int RightRect, int BottomRect, int XStartArc, int YStartArc, int XEndArc, int YEndArc);
		inline bool Arc(const RECT* Rect, const POINT * Start, const POINT * End);
		inline bool ArcTo(int LeftRect, int TopRect, int RightRect, int BottomRect, int XStartArc, int YStartArc, int XEndArc, int YEndArc);
		inline bool ArcTo(const RECT* Rect, const POINT* Start, const POINT* End);

		//------------------------------------------Angle arc--------------------------------------

		inline bool AngleArc(int x, int y, int Radius, float StartAngle, float SweepAngle);
		inline int  getArcDirection() const;
		inline int  SetArcDirection(int ArcDirection);

		//--------------------------------------PolyLine-------------------------------------------

		inline bool Polyline(const POINT Points[], int Count);
		inline bool PolyDraw(const POINT Points[], const BYTE Types[], int Count);
		inline bool PolylineTo(const POINT Points[], int Count);
		inline bool PolyPolyline(const POINT Points[], const DWORD PolyPoints[], int Count);

		//-----------------------------------------------------------------------------------------

		inline bool PolyBezier(const POINT Points[], int Count);
		inline bool PolyBezierTo(const POINT Points[], int Count);

		//=========================================Simple Drawing Functions========================

		inline bool FillRect(const RECT* Rect, CBrushHandle Brush);
		inline bool FillRect(const RECT& Rect, CBrushHandle Brush);

		inline bool FrameRect(const RECT* Rect, CBrushHandle Brush);
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
		HDC SrcDC, int SrcLeft, int SrcTop, ERasterOperationCodes RastOp);

	bool BitBlockTransfer(HDC DestDC, const POINT* DestPoint, const SIZE* Size,
		HDC SrcDC, const POINT* SrcPoint, ERasterOperationCodes RastOp);

	bool BitBlockTransfer(HDC DestDC, const POINT & DestPoint, const SIZE & Size,
		HDC SrcDC, const POINT & SrcPoint, ERasterOperationCodes RastOp);
	
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

	inline CPenHandle CDeviceContext::getPen() const
	{
		WL_ASSERT(m_DC != NULL);
		return CPenHandle((HPEN)::GetCurrentObject(m_DC, OBJ_PEN));
	}

	inline CBrushHandle CDeviceContext::getBrush() const
	{
		WL_ASSERT(m_DC != NULL);
		return CBrushHandle((HBRUSH)::GetCurrentObject(m_DC, OBJ_BRUSH));
	}

	inline HFONT CDeviceContext::getFont() const
	{
		WL_ASSERT(m_DC != NULL);
		return (HFONT)::GetCurrentObject(m_DC, OBJ_FONT);
	}

	inline CBitmapHandle CDeviceContext::getBitmap() const
	{
		WL_ASSERT(m_DC != NULL);
		return CBitmapHandle((HBITMAP)::GetCurrentObject(m_DC, OBJ_BITMAP));
	}

	inline HRGN CDeviceContext::getRgn() const
	{
		WL_ASSERT(m_DC != NULL);
		return (HRGN)::GetCurrentObject(m_DC, OBJ_REGION);
	}

	CPenHandle CDeviceContext::selectPen(HPEN Pen)
	{
		WL_ASSERT(m_DC != NULL);
		WL_ASSERT(Pen == NULL || ::GetObjectType(Pen) == OBJ_PEN || ::GetObjectType(Pen) == OBJ_EXTPEN);
		WL_ASSERT(Pen != NULL);
		return CPenHandle((HPEN)::SelectObject(m_DC, Pen));
	}

	CBrushHandle CDeviceContext::selectBrush(HBRUSH Brush)
	{
		WL_ASSERT(m_DC != NULL);
		WL_ASSERT(Brush == NULL || ::GetObjectType(Brush) == OBJ_BRUSH);
		WL_ASSERT(Brush != NULL);
		return CBrushHandle((HBRUSH)::SelectObject(m_DC, Brush));
	}

	HFONT CDeviceContext::selectFont(HFONT Font)
	{
		WL_ASSERT(m_DC != NULL);
		WL_ASSERT(Font == NULL || ::GetObjectType(Font) == OBJ_FONT);
		WL_ASSERT(Font != NULL);
		return (HFONT)::SelectObject(m_DC, Font);
	}

	CBitmapHandle CDeviceContext::selectBitmap(HBITMAP Bitmap)
	{
		WL_ASSERT(m_DC != NULL);
		WL_ASSERT(Bitmap == NULL || ::GetObjectType(Bitmap) == OBJ_BITMAP);
		WL_ASSERT(Bitmap != NULL);
		return CBitmapHandle((HBITMAP)::SelectObject(m_DC, Bitmap));
	}

	HRGN CDeviceContext::selectRgn(HRGN Rgn)
	{
		WL_ASSERT(m_DC != NULL);
		WL_ASSERT(Rgn == NULL || ::GetObjectType(Rgn) == OBJ_REGION);
		WL_ASSERT(Rgn != NULL);
		return (HRGN)::SelectObject(m_DC, Rgn);
	}

	CPenHandle CDeviceContext::selectStockPen(EStockPens Pen)
	{
		WL_ASSERT(m_DC != NULL);
		return selectPen((HPEN)::GetStockObject(Pen));
	}

	CBrushHandle CDeviceContext::selectStockBrush(EStockBrushes Brush)
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

	inline bool CDeviceContext::FillRect(const RECT * Rect, CBrushHandle Brush)
	{
		WL_ASSERT(m_DC != NULL);
		return true && ::FillRect(m_DC, Rect, Brush);
	}

	inline bool CDeviceContext::FillRect(const RECT & Rect, CBrushHandle Brush)
	{
		return true && ::FillRect(m_DC, &Rect, Brush);
	}

	inline bool CDeviceContext::FrameRect(const RECT * Rect, CBrushHandle Brush)
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

	


	inline CPenHandle::CPenHandle() : m_Pen(0)
	{
	}

	inline CPenHandle::CPenHandle(HPEN Pen) : m_Pen(Pen)
	{
	}

	inline CPenHandle::operator HPEN()
	{
		return m_Pen;
	}

	inline bool CPenHandle::isNull()
	{
		return m_Pen == NULL;
	}

	inline HPEN CPenHandle::getHandle() const
	{
		return m_Pen;
	}

	inline void CPenHandle::Attach(HPEN NewPen)
	{
		WL_ASSERT(m_Pen == NULL);
		WL_ASSERT(NewPen != NULL);
		m_Pen = NewPen;
	}

	inline HPEN CPenHandle::Detach()
	{
		HPEN RetPen = m_Pen;
		m_Pen = NULL;
		return RetPen;
	}

	inline bool CPenHandle::Create(int Style, int Width, COLORREF Color)
	{
		WL_ASSERT(Width >= 0);
		m_Pen = ::CreatePen(Style, Width, Color);
		return m_Pen != NULL;
	}

	inline bool CPenHandle::CreateIndirect(LOGPEN * LogPen)
	{
		WL_ASSERT(LogPen != NULL);
		m_Pen = ::CreatePenIndirect(LogPen);
		return m_Pen != NULL;
	}

	inline bool CPenHandle::Delete()
	{
		WL_ASSERT(m_Pen != NULL);
		bool Result = true && ::DeleteObject(m_Pen);
		if (Result) m_Pen = NULL;
		return Result;
	}

	inline int CPenHandle::getInfo(LOGPEN * LogPen) const
	{
		WL_ASSERT(m_Pen != NULL);
		WL_ASSERT(LogPen != NULL);
		return ::GetObject(m_Pen, sizeof(LOGPEN), LogPen);
	}





	inline CBrushHandle::CBrushHandle() : m_Brush(0)
	{
	}

	inline CBrushHandle::CBrushHandle(HBRUSH Brush) : m_Brush(Brush)
	{
	}

	inline CBrushHandle::operator HBRUSH()
	{
		return m_Brush;
	}

	inline void CBrushHandle::Attach(HBRUSH NewBrush)
	{
		WL_ASSERT(m_Brush == NULL);
		WL_ASSERT(NewBrush != NULL);
		m_Brush = NewBrush;
	}

	inline HBRUSH CBrushHandle::Detach()
	{
		HBRUSH RetBrush = m_Brush;
		m_Brush = NULL;
		return RetBrush;
	}

	inline HBRUSH CBrushHandle::getHandle() const
	{
		return m_Brush;
	}

	inline bool CBrushHandle::isNull()
	{
		return m_Brush == NULL;
	}

	inline bool CBrushHandle::CreateSolid(COLORREF Color)
	{
		WL_ASSERT(m_Brush == NULL);
		m_Brush = ::CreateSolidBrush(Color);
		return true && m_Brush;
	}

	inline bool CBrushHandle::CreateHatch(int Hatch, COLORREF Color)
	{
		WL_ASSERT(m_Brush == NULL);
		m_Brush = ::CreateHatchBrush(Hatch, Color);
		return true && m_Brush;
	}

	inline bool CBrushHandle::CreateIndirect(const LOGBRUSH * BrushInfo)
	{
		WL_ASSERT(BrushInfo);
		WL_ASSERT(m_Brush == NULL);
		m_Brush = ::CreateBrushIndirect(BrushInfo);
		return true && m_Brush;
	}

	bool CBrushHandle::Delete()
	{
		bool Result = true && ::DeleteObject(m_Brush);
		if (Result) m_Brush = NULL;
		return Result;
	}

	inline int CBrushHandle::getInfo(LOGBRUSH * LogBrush) const
	{
		WL_ASSERT(m_Brush != NULL);
		return ::GetObject(m_Brush, sizeof(LOGBRUSH), LogBrush);
	}




	inline CBitmapHandle::CBitmapHandle() : m_Bitmap(0)
	{
	}

	inline CBitmapHandle::CBitmapHandle(HBITMAP Bitmap) : m_Bitmap(Bitmap)
	{
	}

	inline CBitmapHandle::operator HBITMAP()
	{
		return m_Bitmap;
	}

	inline bool CBitmapHandle::isNull()
	{
		return m_Bitmap == NULL;
	}

	inline HBITMAP CBitmapHandle::getHandle()
	{
		return m_Bitmap;
	}

	inline HBITMAP CBitmapHandle::Detach()
	{
		HBITMAP RetBitmap = m_Bitmap;
		m_Bitmap = NULL;
		return RetBitmap;
	}

	inline void CBitmapHandle::Attach(HBITMAP NewBitmap)
	{
		WL_ASSERT(m_Bitmap == NULL);
		WL_ASSERT(NewBitmap != NULL);
		m_Bitmap = NewBitmap;
	}

	inline bool CBitmapHandle::Load(HINSTANCE Instance, LPCTSTR BitmapName)
	{
		WL_ASSERT(m_Bitmap == NULL);
		m_Bitmap = ::LoadBitmap(Instance, BitmapName);
		return m_Bitmap != NULL;
	}

	inline bool CBitmapHandle::Load(HINSTANCE Instance, LPCTSTR ImageName, int Width, int Height, UINT Load)
	{
		WL_ASSERT(m_Bitmap == NULL);
		m_Bitmap = (HBITMAP)::LoadImageA(Instance, ImageName, IMAGE_BITMAP, Width, Height, Load);
		return m_Bitmap != NULL;
	}

	inline bool CBitmapHandle::Create(int Width, int Height, UINT Planes, UINT BitsPerPixel, const void * Bits)
	{
		WL_ASSERT(m_Bitmap == NULL);
		m_Bitmap = ::CreateBitmap(Width, Height, Planes, BitsPerPixel, Bits);
		return m_Bitmap != NULL;
	}

	inline bool CBitmapHandle::CreateIndirect(BITMAP * Bitmap)
	{
		WL_ASSERT(m_Bitmap == NULL);
		WL_ASSERT(Bitmap != NULL);
		m_Bitmap = ::CreateBitmapIndirect(Bitmap);
		return m_Bitmap != NULL;
	}

	inline bool CBitmapHandle::CreateCompatible(HDC DC, int Width, int Height)
	{
		WL_ASSERT(m_Bitmap == NULL);
		WL_ASSERT(DC);
		m_Bitmap = ::CreateCompatibleBitmap(DC, Width, Height);
		return m_Bitmap != NULL;
	}

	inline bool CBitmapHandle::Delete()
	{
		bool Result = true && ::DeleteObject(m_Bitmap);
		if (Result) m_Bitmap = NULL;
		return Result;
	}

	inline int CBitmapHandle::getInfo(BITMAP * Info) const
	{
		WL_ASSERT(m_Bitmap != NULL);
		WL_ASSERT(Info);
		return ::GetObject(m_Bitmap, sizeof(BITMAP), Info);
	}

	inline bool CBitmapHandle::getDimension(SIZE * Size) const
	{
		WL_ASSERT(m_Bitmap != NULL);
		WL_ASSERT(Size != NULL);
		return true && ::GetBitmapDimensionEx(m_Bitmap, Size);
	}

	inline bool CBitmapHandle::setDimension(int Width, int Height, SIZE * Size)
	{
		WL_ASSERT(m_Bitmap != NULL);
		return true && ::SetBitmapDimensionEx(m_Bitmap, Width, Height, Size);
	}

}

#endif //!WL_OBJECT_HANDLE_WRAPS_HPP