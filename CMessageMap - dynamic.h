#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <map>
#include <utility>

template<typename WindowType, typename KeyType, typename CallBackType>
class CBaseMessageMap
{
public:
#define Handler(FuncName) LRESULT FuncName (LPARAM LParam, WPARAM WParam)
//==============================================================================================================================
	template<typename ChildWindowType>
	bool m_AddMessage(KeyType Message, ChildWindowType* Window, LRESULT(ChildWindowType::*FuncPtr)(LPARAM, WPARAM))
	{   //Cheking for inheritance of WindowType
		if ((FuncPtr == NULL) || (dynamic_cast<WindowType*>(Window) == NULL)) return false;
		//Typecasting
		CallBackType CallFunc = reinterpret_cast<CallBackType>(FuncPtr);
		m_MessageMap.insert(std::pair<KeyType, CallBackType>(Message, CallFunc));
		return true;
	}

#define AddMessage(Message,       FuncPtr) \
      m_AddMessage(Message, this, FuncPtr)
//==============================================================================================================================
	CallBackType FindMessage(KeyType Message)
	{
		std::map<KeyType, CallBackType>::iterator MesMapIt = m_MessageMap.find(Message);
		if (MesMapIt == m_MessageMap.end()) return NULL;
		else return MesMapIt->second;
	}
//==============================================================================================================================
private:
	std::map  <KeyType, CallBackType> m_MessageMap;
};