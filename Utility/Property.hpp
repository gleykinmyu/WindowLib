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
        typedef void     (ParentType::*SETTER)(const DataType);

    public:
        void Init(ParentType* Parent, GETTER Getter, SETTER Setter)
        {
            m_Owner = Parent;
            m_Getter = Getter;
            m_Setter = Setter;
        }

        //=================================OPERATORS==========================================

        void operator = (const DataType Data) const
        {
            (m_Owner->*m_Setter)(Data);
        }

        operator DataType ()
        {
            return (m_Owner->*m_Getter)();
        }

        //====================================================================================
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
            m_Owner = Parent;
            m_Getter = Getter;
        }

        //=================================OPERATORS===========================================
        operator DataType()
        {
            return (m_Owner->*m_Getter)();
        }

        //=====================================================================================
    private:
        ParentType* m_Owner;
        GETTER      m_Getter;

    };

    //===================================WRITE-ONLY========================================
    template<class DataType, class ParentType>
    class CProperty<WO, DataType, ParentType>
    {
        typedef void    (ParentType::*SETTER)(const DataType);

    public:
        void Init(ParentType* Parent, SETTER Setter)
        {
            m_Owner = Parent;
            m_Setter = Setter;
        }

        //=================================OPERATORS===========================================
        void operator = (DataType Data)
        {
            (m_Owner->*m_Setter)(Data);
        }

        //=====================================================================================
    private:
        ParentType* m_Owner;
        SETTER     m_Setter;
    };
}

#endif //CPROPERTY_HPP