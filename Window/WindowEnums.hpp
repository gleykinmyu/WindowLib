#ifndef WL_WINDOW_ENUMS_HPP
#define WL_WINDOW_ENUMS_HPP

#include <Windows.h>
#include <WinLib/Utility.hpp>

namespace Window
{
	typedef enum class  ws : unsigned
	{
		None  = 0,
		Popup = WS_POPUP,

		ClipChildren = WS_CLIPCHILDREN,
		Child        = WS_CHILD,

		Minimize = WS_MINIMIZE,
		Maximize = WS_MAXIMIZE,

		Visible  = WS_VISIBLE,
		Disabled = WS_DISABLED,

		Caption = WS_CAPTION,
		Border  = WS_BORDER,

		VScroll = WS_VSCROLL,
		Scroll  = WS_HSCROLL,

		OverlappedWindow = WS_OVERLAPPEDWINDOW
	} EWndStyles;

	typedef enum class wes : unsigned
	{
		None = 0,
		Transparent = WS_EX_TRANSPARENT,
		Layered     = WS_EX_LAYERED
	} EWndExStyles;

	typedef DWORD WNDSTYLE;
	typedef DWORD WNDEXSTYLE;

	template<typename MaskType, typename EnumType>
	class CWndStyleT
	{
	private:
		MaskType m_Value;
		inline CWndStyleT(MaskType Mask) : m_Value(Mask) {}

	public:

		inline CWndStyleT() : m_Value(0) {}
		inline CWndStyleT(EnumType Flag) : m_Value((unsigned)Flag) {}
		inline CWndStyleT(const CWndStyleT & Style) : m_Value(Style.m_Value) {}

		inline operator MaskType() const
		{
			return m_Value;
		}

        inline const CWndStyleT & operator| (EnumType Flag) const
        {
			return CWndStyleT(m_Value | (unsigned)Flag);
        }

		inline const CWndStyleT operator| (const CWndStyleT & Mask) const
		{
			return CWndStyle(m_Value | Mask.m_Value);
		}

		inline const CWndStyleT & operator|= (const CWndStyleT & Mask)
		{
			m_Value |= Mask.m_Value;
			return *this;
		}
                                                                                                                   
		inline const CWndStyleT & setValue(MaskType Value)
		{
			m_Value = Value;
			return *this;
		}

		inline const CWndStyleT & addValue(MaskType Value)
		{
			m_Value |= Value;
			return *this;
		}
	};

	template<typename MaskType, typename EnumType, class OwnerType>
	class CWndStylePropertyT
	{
		typedef CWndStyleT<MaskType, EnumType> WndStyleClass;
		typedef void     (OwnerType::*SETTER)(MaskType);
		typedef MaskType (OwnerType::*GETTER)() const;

	private:
		OwnerType * m_Owner;
		SETTER      m_Setter;
		SETTER      m_MixSetter;
		GETTER      m_Getter;

	public:
		void Init(OwnerType * Owner, GETTER Getter, SETTER Setter, SETTER MixSetter)
		{
			WL_ASSERT(Owner);
			WL_ASSERT(Getter);
			WL_ASSERT(Setter);
			WL_ASSERT(OP_OR_EQ);
			m_Owner = Owner;
			m_Setter = Setter;
			m_Getter = Getter;
			m_MixSetter = MixSetter;
		}

		inline operator MaskType() const
		{
			return (m_Owner->*m_Getter)();
		}

		inline operator WndStyleClass()
		{
			return WndStyleT().setValue((m_Owner->*m_Getter)());
		}

		inline void operator=(const WndStyleClass & Mask)
		{
			(m_Owner->*m_Setter)(Mask);
		}

		inline void operator|= (const WndStyleClass & Mask)
		{
			(m_Owner->*m_MixSetter)(Mask);
		}

		inline void setValue(MaskType Mask)
		{
			(m_Owner->*m_Setter)(Mask);
		}

		inline void addValue(MaskType Mask)
		{
			(m_Owner->*m_MixSetter)(Mask);
		}
	};

	typedef CWndStyleT<WNDSTYLE,   EWndStyles>   CWndStyle; 
	typedef CWndStyleT<WNDEXSTYLE, EWndExStyles> CWndExStyle;

	inline CWndStyle operator| (EWndStyles Flag1, EWndStyles Flag2)
	{
		return CWndStyle().setValue((unsigned)Flag1 | (unsigned)Flag2);
	}

	inline CWndExStyle operator| (EWndExStyles Flag1, EWndExStyles Flag2)
	{
		return CWndExStyle().setValue((unsigned)Flag1 | (unsigned)Flag2);
	}
}

#endif //!WL_WINDOW_ENUMS_HPP