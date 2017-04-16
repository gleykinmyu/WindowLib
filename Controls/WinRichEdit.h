#pragma once
#include <Windows.h>
#include "WinControls.h"
#include <richedit.h>

class CWinRichEdit : public CWinControls
{
	LPCTSTR Initialize() { LoadLibrary(L"RICHED32.DLL"); return L"RICHEDIT"; }
public:
	CWinRichEdit() : CWinControls(Initialize(), L"WinRichEdit") {  }
};