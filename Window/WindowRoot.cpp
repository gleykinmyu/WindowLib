#ifndef WL_WINDOW_ROOT_CPP
#define WL_WINDOW_ROOT_CPP

#include <WinLib/Window/WindowRoot.hpp>

namespace Window
{
    bool CWindowRoot::Create(CWindowHandle * Parent, WndInfo & Info)
    {
		WL_ASSERT(Parent != NULL);
		return 	CWindowImpl::Create(*Parent, getClassName(), Info, this);
    }

	bool CWindowRoot::Create(CWindowHandle & Parent, WndInfo & Info)
	{
		return 	CWindowImpl::Create(Parent, getClassName(), Info, this);
	}

	CWindowRoot::~CWindowRoot()
	{
		WL_ASSERT(isNull() == true);		
	}
}

#endif // !WL_WINDOW_ROOT_CPP