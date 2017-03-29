#pragma once 
namespace wl
{
	class CModule
	{
	public:
		CModule() { }
		HINSTANCE Instance = GetModuleHandle(0);
	};
	CModule m_Application;
	CModule* Module = &m_Application;
}




