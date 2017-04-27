#ifndef WL_WINDOW_LIBRARY_HPP
#define WL_WINDOW_LIBRARY_HPP

#include <Windows.h>
#include <WinLib/Utility.hpp>

namespace Window
{
	class CWindowHandle;
}

namespace Detail
{
	struct CWindowNode
	{
		HWND                    m_Handle = NULL;
		Window::CWindowHandle * m_This = NULL;
		CWindowNode           * m_Next = NULL;
	};

	class CWindowTable
	{
	public:
		CWindowTable(CWindowNode * Array[], size_t Size);

		bool AddWindow(HWND Handle, Window::CWindowHandle * This);
		bool DeleteWindow(HWND Handle);
		inline Window::CWindowHandle * getWindowThis(HWND Handle);

		void Dump(FILE * Stream);

		~CWindowTable();

	private:
		size_t m_Size;
		CWindowNode * wm_FindWindowNode(HWND Handle);
		inline unsigned wm_Hash(HWND Handle);

		CWindowNode * * m_WindowTable;
	};

	inline unsigned CWindowTable::wm_Hash(HWND Handle)
	{
		unsigned Hash = (unsigned)Handle ^ 0xCFCFCFCF;
		return Hash % m_Size;
	}

	inline Window::CWindowHandle * CWindowTable::getWindowThis(HWND Handle)
	{
		CWindowNode * Node = wm_FindWindowNode(Handle);
		if (Node == NULL) return NULL;
		return Node->m_This;
	}

	inline CWindowTable::CWindowTable(CWindowNode * Array[], size_t Size)
	{
		WL_ASSERT(Array != NULL);
		WL_ASSERT(Size);
		m_WindowTable = Array;
		m_Size = Size;
	}

	bool CWindowTable::AddWindow(HWND Handle, Window::CWindowHandle * This)
	{
		if (wm_FindWindowNode(Handle) == NULL)
		{
			CWindowNode * Node = new CWindowNode;
			Node->m_Next = m_WindowTable[wm_Hash(Handle)];
			m_WindowTable[wm_Hash(Handle)] = Node;

			Node->m_Handle = Handle;
			Node->m_This = This;
			return true;
		}
		return false;
	}

	bool CWindowTable::DeleteWindow(HWND Handle)
	{
		CWindowNode * Node = m_WindowTable[wm_Hash(Handle)];
		if (Node == NULL) return true;
		if (Node->m_Handle == Handle)
		{
			m_WindowTable[wm_Hash(Handle)] = Node->m_Next;
			delete Node;
			return true;
		}

		CWindowNode * PrevNode = m_WindowTable[wm_Hash(Handle)];
		CWindowNode * CurNode = PrevNode->m_Next;
		for (; CurNode != NULL; PrevNode = CurNode, CurNode = CurNode->m_Next)
		{
			if (CurNode->m_Handle == Handle)
			{
				PrevNode->m_Next = CurNode->m_Next;
				delete CurNode;
				return true;
			}
		}
		return false;
	}

	CWindowNode * CWindowTable::wm_FindWindowNode(HWND Handle)
	{
		for (CWindowNode * Node = m_WindowTable[wm_Hash(Handle)]; Node != NULL; Node = Node->m_Next)
		{
			if (Node->m_Handle == Handle)
				return Node;
		}
		return NULL;
	}

	void CWindowTable::Dump(FILE * Stream)
	{
		WL_ASSERT(Stream != NULL);
		if (Stream == NULL) return;
		for (unsigned Cnt = 0; Cnt < m_Size; Cnt++)
		{
			fprintf(Stream, "[%u]", Cnt);
			for (CWindowNode * Node = m_WindowTable[Cnt];
				Node != NULL;
				Node = Node->m_Next)
			{
				fprintf(Stream, "=");
			}
			fprintf(Stream, "\n");
		}
		fclose(Stream);
	}

	inline CWindowTable::~CWindowTable()
	{
		for (unsigned Cnt = 0; Cnt < m_Size; Cnt++)
		{
			CWindowNode * Node = m_WindowTable[Cnt];
			while (Node != NULL)
			{
				CWindowNode * NextNode = Node->m_Next;
				delete Node;
				Node = NextNode;
			}
		}
	}

	class CModule
	{
	public:
		CModule();
		HINSTANCE Instance = GetModuleHandle(0);
		CWindowTable WindowTable;
	
	private:
		static const size_t m_WindowTableSize = 101; // <- only SIMPLY number
		CWindowNode * m_WindowTable[m_WindowTableSize] = {};
	};

	CModule::CModule() : WindowTable(m_WindowTable, m_WindowTableSize)
	{

	}

	static CModule m_Module;
}

namespace wl
{
	Detail::CModule* Module = &Detail::m_Module;
}

#endif //!WL_WINDOW_LIBRARY_HPP