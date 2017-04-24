#ifndef WL_OBJETCS_ENUM_HPP
#define WL_OBJETCS_ENUM_HPP

#include <Windows.h>

namespace Graphics
{
	enum EStockPens
	{
		spWhite = WHITE_PEN,
		spBlack = BLACK_PEN,
		spNull = NULL_PEN,
		spDC = DC_PEN
	};

	enum EStockBrushes
	{
		sbWhite = WHITE_BRUSH,
		sbLightGray = LTGRAY_BRUSH,
		sbGray = GRAY_BRUSH,
		sbDarkGray = DKGRAY_BRUSH,
		sbBlack = BLACK_BRUSH,
		sbNull = NULL_BRUSH,
		sbDC = DC_BRUSH
	};

	enum EStockFonts
	{
		sfOEMFixed = OEM_FIXED_FONT,
		sfANSIFixed = ANSI_FIXED_FONT,
		sfANSIVar = ANSI_VAR_FONT,
		sfSystem = SYSTEM_FONT,
		sfDeviceDefault = DEVICE_DEFAULT_FONT,
		sfSystemFixed = SYSTEM_FIXED_FONT,
		sfDefualtGUI = DEFAULT_GUI_FONT
	};

	enum ERasterOperationCodes
	{
		ropBlackness = BLACKNESS,
		ropCaptureBlt = CAPTUREBLT,
		ropDstInvert = DSTINVERT,
		ropMergeCopy = MERGECOPY,
		ropMergePaint = MERGEPAINT,
		ropNoMirrorBitmap = NOMIRRORBITMAP,
		ropNotSrcCopy = NOTSRCCOPY,
		ropNotSrcErase = NOTSRCERASE,
		ropPatCopy = PATCOPY,
		ropPatInvert = PATINVERT,
		ropPatPaint = PATPAINT,
		ropSrcAnd = SRCAND,
		ropSrcCopy = SRCCOPY,
		ropSrcErase = SRCERASE,
		ropSrcInvert = SRCINVERT,
		ropSrcPaint = SRCPAINT,
		ropWhiteness = WHITENESS
	};
	
	enum EPenStyle
	{
		psSolid     = PS_SOLID,      /*__________*/
		psDash      = PS_DASH,       /* -------  */
		psDot       = PS_DOT,        /* .......  */
		psDashDot   = PS_DASHDOT,    /* _._._._  */
		psDasDotDot = PS_DASHDOTDOT, /* _.._.._  */
		psNull      = PS_NULL
	};

	enum EBrushStyle
	{
		bsHollow,
		bsSolid,
		bsHorizontal,
		bsVertical,
		bsFDiagonal,
		bsBDiagonal,
		bsCross,
		bsDiagCross
	};
}

#endif