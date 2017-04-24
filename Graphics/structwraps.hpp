#ifndef WL_STRUCT_WRAPS_HPP
#define WL_STRUCT_WRAPS_HPP

#include <Windows.h>

namespace Graphics
{
	struct CRECT : public RECT
	{
	public:
		CRECT()
		{
			left   = 0;
			top    = 0;
			right  = 0;
			bottom = 0;
		}
		CRECT(int Left, int Top, int Right, int Bottom)
		{
			left   = Left;
			top    = Top;
			right  = Right;
			bottom = Bottom;
		}
	};

	struct CPOINT : public POINT
	{
		CPOINT()
		{
			x = 0;
			y = 0;
		}

		CPOINT(int X, int Y) 
		{
			x = X;
			y = Y;
		}
	};
}

#endif //!WL_STRUCT_WRAPS_HPP
