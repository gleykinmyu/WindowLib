#ifndef CPROPERTY_HPP
#define CPROPERTY_HPP

namespace Utility
{
    enum MemoryAccess { RW, RO, WO };

    template<MemoryAccess Access, class DataType, class ParentType> class CProperty;

    //===================================READ-WRITE========================================
    template<class DataType, class ParentType>
    class CProperty<RW, DataType, ParentType>
    {
        typedef DataType(ParentType::*GETTER)() const;
        typedef void    (ParentType::*SETTER)(const DataType &);

    public:
        void Init(ParentType* Parent, GETTER Getter, SETTER Setter)
        {
            m_Owner  = Parent;
            m_Getter = Getter;
            m_Setter = Setter;
        }

        inline void operator = (const DataType & Data)
        {
            (m_Owner->*m_Setter)(Data);
        }

		inline void set(const DataType & Data)
		{
			(m_Owner->*m_Setter)(Data);
		}

        inline operator DataType () const
        {
            return (m_Owner->*m_Getter)();
        }

    
    private:
        ParentType* m_Owner;
        GETTER     m_Getter;
        SETTER     m_Setter;
    };

    //===================================READ-ONLY========================================
    template<class DataType, class ParentType>
    class CProperty<RO, DataType, ParentType>
    {
        typedef DataType(ParentType::*GETTER)() const;

    public:
        void Init(ParentType* Parent, GETTER Getter)
        {
            m_Owner  = Parent;
            m_Getter = Getter;
        }

        inline operator DataType() const
        {
            return (m_Owner->*m_Getter)();
        }

    private:
        ParentType* m_Owner;
        GETTER      m_Getter;

    };

    //===================================WRITE-ONLY========================================
    template<class DataType, class ParentType>
    class CProperty<WO, DataType, ParentType>
    {
        typedef void    (ParentType::*SETTER)(const DataType &);

    public:
        void Init(ParentType* Parent, SETTER Setter)
        {
            m_Owner  = Parent;
            m_Setter = Setter;
        }

        inline void operator = (const DataType & Data)
        {
            (m_Owner->*m_Setter)(Data);
        }
	
	private:
        ParentType * m_Owner;
        SETTER       m_Setter;
    };


	//================================BOOL=================================================

	//===================================READ-WRITE========================================
	template<class ParentType>
	class CProperty<RW, bool, ParentType>
	{
		typedef bool(ParentType::*GETTER)() const;
		typedef void    (ParentType::*SETTER)(bool);

	public:
		void Init(ParentType* Parent, GETTER Getter, SETTER Setter)
		{
			m_Owner = Parent;
			m_Getter = Getter;
			m_Setter = Setter;
		}

		inline void operator = (bool Data) const
		{
			(m_Owner->*m_Setter)(Data);
		}

		inline operator bool ()
		{
			return (m_Owner->*m_Getter)();
		}


	private:
		ParentType* m_Owner;
		GETTER     m_Getter;
		SETTER     m_Setter;
	};

	//===================================READ-ONLY========================================
	template<class ParentType>
	class CProperty<RO, bool, ParentType>
	{
		typedef bool(ParentType::*GETTER)() const;

	public:
		void Init(ParentType* Parent, GETTER Getter)
		{
			m_Owner = Parent;
			m_Getter = Getter;
		}

		inline operator bool()
		{
			return (m_Owner->*m_Getter)();
		}

	private:
		ParentType* m_Owner;
		GETTER      m_Getter;

	};

	//===================================WRITE-ONLY========================================
	template<class ParentType>
	class CProperty<WO, bool, ParentType>
	{
		typedef void    (ParentType::*SETTER)(bool);

	public:
		void Init(ParentType* Parent, SETTER Setter)
		{
			m_Owner = Parent;
			m_Setter = Setter;
		}

		inline void operator = (bool Data)
		{
			(m_Owner->*m_Setter)(Data);
		}

	private:
		ParentType * m_Owner;
		SETTER       m_Setter;
	};


	//================================INTEGER WITH OPERATORS===============================

	//===================================READ-WRITE========================================
	template<class ParentType>
	class CProperty<RW, int, ParentType>
	{
		typedef int  (ParentType::*GETTER)() const;
		typedef void (ParentType::*SETTER)(int);

	public:
		void Init(ParentType * Parent, GETTER Getter, SETTER Setter, SETTER MixSetter)
		{
			m_Owner     = Parent;
			m_Getter    = Getter;
			m_Setter    = Setter;
			m_MixSetter = MixSetter;
		}

		void inline operator = (int Data)
		{
			(m_Owner->*m_Setter)(Data);
		}

		void inline operator += (int Data)
		{
			(m_Owner->*m_MixSetter)(Data);
		}

		void inline operator -= (int Data)
		{
			(m_Owner->*m_MixSetter)(-1*Data);
		}

		void inline operator ++ ()
		{
			(m_Owner->*m_MixSetter)(1);
		}

		void inline operator -- ()
		{
			(m_Owner->*m_MixSetter)(-1);
		}

		inline operator int() const
		{
			return (m_Owner->*m_Getter)();
		}

	private:
		ParentType* m_Owner;
		GETTER      m_Getter;
		SETTER      m_Setter;
		SETTER      m_MixSetter;
	};
}
#endif //CPROPERTY_HPP