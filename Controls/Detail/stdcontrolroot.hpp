#ifndef WL_STD_CONTROL_ROOT
#define WL_STD_CONTROL_ROOT

#include <Windows.h>
#include <WinLib/Window.hpp>

namespace ControlsDetail
{
    class CStdControlRoot : public Window::CWindowRoot
    {
	public:
		inline bool Create(Window::CWindowHandle Parent, Window::WndInfo & Info);

 	private:
		virtual bool MessageProcessor(System::CMessage * Message) override
		{
			DefaultMessageProcessor(Message);
			return true;
		}
    };

	inline bool CStdControlRoot::Create(Window::CWindowHandle Parent, Window::WndInfo & Info)
	{
		return CWindowRoot::Create(Parent, Info.Style(Window::ws::Child));
	}
};

#endif //!WL_STD_CONTROL_ROOT
