#ifndef CPROPERTY_H
#define CPROPERTY_H


#define RWInit(getter, setter) _Init(this, getter, setter)
#define ROInit(getter)         _Init(this, getter, NULL)
#define WOInit(setter)         _Init(this, NULL, setter)

enum MemoryAccess { RW, RO, WO };

template<MemoryAccess Access, class DataType, class OwnerType>
class CProperty;

template<class DataType, class OwnerType>
class CProperty<RW, DataType, OwnerType>
{
private:
	typedef DataType(OwnerType::*GETTER)();
	typedef void    (OwnerType::*SETTER)(const DataType);

	OwnerType* m_Owner;
	GETTER     m_Getter;
	SETTER     m_Setter;
public:
	void _Init(OwnerType* Owner, GETTER Getter, SETTER Setter)
	{
		m_Owner = Owner;
		m_Getter = Getter;
		m_Setter = Setter;
	}
	
	void operator = (DataType Data)
	{
		(m_Owner->*m_Setter)(Data);
	}

	operator DataType()
	{
		return (m_Owner->*m_Getter)();
	}
};

template<class DataType, class OwnerType>
class CProperty<RO, DataType, OwnerType>
{
private:
	typedef DataType(OwnerType::*GETTER)();
	typedef void    (OwnerType::*SETTER)(const DataType);

	OwnerType* m_Owner;
	GETTER     m_Getter;
	SETTER     m_Setter;
public:
	void _Init(OwnerType* Owner, GETTER Getter, SETTER Setter)
	{
		m_Owner = Owner;
		m_Getter = Getter;
		m_Setter = Setter;
	}
	operator DataType()
	{
		return (m_Owner->*m_Getter)();
	} 
};


template<class DataType, class OwnerType>
class CProperty<WO, DataType, OwnerType>
{
private:
	typedef DataType(OwnerType::*GETTER)();
	typedef void    (OwnerType::*SETTER)(const DataType);

	OwnerType* m_Owner;
	GETTER     m_Getter;
	SETTER     m_Setter;
public:
	void _Init(OwnerType* Owner, GETTER Getter, SETTER Setter)
	{
		m_Owner = Owner;
		m_Getter = Getter;
		m_Setter = Setter;
	}

	void operator = (DataType Data)
	{
		(m_Owner->*m_Setter)(Data);
	}
};

//====================================================BASE PROPERTY TYPES==================================================================

#endif //CPROPERTY_H