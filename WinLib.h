#pragma once
#include <Windows.h>
#include <assert.h>
#include "Property.h"
#include "WLDefines.h"
#include "Module.h"
#include "Window.h"
#include "WindowEvent.h"
#include "WindowDecl.h"
#include "WindowRoot.h"
#include "Desktop.h"

namespace wl
{
	/*	//CBaseWindowP: P - Property - Add to CWindow properties
	class CBaseWindowP : public CWindowCreating
	{
	public:
		typedef CProperty<RW, int, CBaseWindowP> rwINT;
		typedef CProperty<RO, HWND, CBaseWindowP> roHWND;
		typedef CProperty<RW, LONG_PTR, CBaseWindowP> rwLONG_PTR;
		typedef CProperty<RW, WCHAR, CBaseWindowP> rwWCHAR;
		//=========================================================================================================================================
		rwINT pTop;
		rwINT pLeft;
		rwINT pHeight;
		rwINT pWidth;

		roHWND     pHandle;
		rwWCHAR    pClassName;
		rwLONG_PTR pStyle;
		rwLONG_PTR pExStyle;
		//=========================================================================================================================================
		CBaseWindowP(ClsInfo& ClsInfo) : CWindowCreating(ClsInfo, NULL)
		{
			pHandle.Init(this, &CBaseWindowP::GetHandle);
			pStyle.Init(this, &CBaseWindowP::GetWndStyle, &CBaseWindowP::SetWndStyle);
			pExStyle.Init(this, &CBaseWindowP::GetWndExStyle, &CBaseWindowP::SetWndExStyle);
			pTop.Init(this, &CBaseWindowP::GetWndTop, &CBaseWindowP::SetWndTop);
			pLeft.Init(this, &CBaseWindowP::GetWndLeft, &CBaseWindowP::SetWndLeft);
			pHeight.Init(this, &CBaseWindowP::GetWndHeight, &CBaseWindowP::SetWndHeight);
			pWidth.Init(this, &CBaseWindowP::GetWndWidth, &CBaseWindowP::SetWndWidth);
		}
		//============GETTERS======================================================================================================================
	private:
		void SetWndTop(const int Top)
		{
			SetWndPos(NULL, GetWndLeft(), Top, 0, 0, SWP_NOSIZE);
		}
		void SetWndLeft(const int Left)
		{
			SetWndPos(NULL, Left, GetWndTop(), 0, 0, SWP_NOSIZE);
		}
		int GetWndTop() const
		{
			RECT Rect = {};
			GetWndRect(&Rect);
			return Rect.top;
		}
		int GetWndLeft() const
		{
			RECT Rect = {};
			GetWndRect(&Rect);
			return Rect.left;
		}
		//===========SETTERS======================================================================================================================
		void SetWndWidth(const int Width)
		{
			SetWndPos(NULL, 0, 0, Width, GetWndHeight(), SWP_NOMOVE);
		}
		void SetWndHeight(const int Height)
		{
			SetWndPos(NULL, 0, 0, GetWndWidth(), Height, SWP_NOMOVE);
		}
		int GetWndWidth() const
		{
			RECT Rect = {};
			GetWndRect(&Rect);
			return Rect.right - Rect.left;
		}
		int GetWndHeight() const
		{
			RECT Rect = {};
			GetWndRect(&Rect);
			return Rect.bottom - Rect.top;
		}
	};
	*/
	//=========================================================================================================================================






	class CMessageLoop
	{
	public:
		void Run()
		{
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0) != 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	};

}
