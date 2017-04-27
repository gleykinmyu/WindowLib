#ifndef WL_SAFE_BIT_MASKS_H
#define WL_SAFE_BIT_MASKS_H

#define DECLARE_BIT_MASK_SAFE_CLASS(ClassName, MaskType, ConstsEnumType)                                           \
    typedef                                                                                                        \
    class CBitMaskSafeT_##MaskType##_##ConstsEnumType                                                              \
    {                                                                                                              \
    private:                                                                                                       \
        MaskType Value = 0;                                                                                        \
        inline CBitMaskSafeT_##MaskType##_##ConstsEnumType(MaskType Mask) : Value(Mask) {}                         \
                                                                                                                   \
    public:                                                                                                        \
        inline CBitMaskSafeT_##MaskType##_##ConstsEnumType(ConstsEnumType Flag) : Value(Flag) {}                   \
        inline CBitMaskSafeT_##MaskType##_##ConstsEnumType(const CBitMaskSafeT_##MaskType##_##ConstsEnumType & Mask) : Value(Mask.Value) {}\
                                                                                                                   \
        inline operator MaskType() const                                                                           \
        {                                                                                                          \
            return Value;                                                                                          \
        }                                                                                                          \
																												   \
        inline const CBitMaskSafeT_##MaskType##_##ConstsEnumType operator| (ConstsEnumType Flag)                   \
        {                                                                                                          \
			return CBitMaskSafeT_##MaskType##_##ConstsEnumType(Value | Flag);                                      \
        }                                                                                                          \
																												   \
		inline const CBitMaskSafeT_##MaskType##_##ConstsEnumType & operator|= (ConstsEnumType Flag)                \
		{                                                                                                          \
			Value |= Flag;    																			           \
			return *this;                                                                                          \
		}                                                                                                          \
																												   \
		inline const CBitMaskSafeT_##MaskType##_##ConstsEnumType & operator|= (const CBitMaskSafeT_##MaskType##_##ConstsEnumType & Mask)\
		{                                                                                                          \
			Value |= Mask.Value;    																			   \
			return *this;                                                                                          \
		}                                                                                                          \
                                                                                                                   \
		inline const CBitMaskSafeT_##MaskType##_##ConstsEnumType operator| (const CBitMaskSafeT_##MaskType##_##ConstsEnumType & Mask)\
		{                                                                                                          \
			return CBitMaskSafeT_##MaskType##_##ConstsEnumType(Value | Mask.Value);                                \
		}                                                                                                          \
                                                                                                                   \
		inline const CBitMaskSafeT_##MaskType##_##ConstsEnumType & SetValue(MaskType Value)                        \
		{                                                                                                          \
			Value = Value;    																			           \
            return *this;                                                                                          \
		}                                                                                                          \
                                                                                                                   \
		inline const CBitMaskSafeT_##MaskType##_##ConstsEnumType & AddValue(MaskType Value)                        \
		{                                                                                                          \
			Value |= Value;    																			           \
			return *this;                                                                                          \
		}                                                                                                          \
                                                                                                                   \
        friend CBitMaskSafeT_##MaskType##_##ConstsEnumType operator| (ConstsEnumType, ConstsEnumType);             \
    } ClassName;                                                                                                   \
                                                                                                                   \
    inline CBitMaskSafeT_##MaskType##_##ConstsEnumType operator| (ConstsEnumType Flag1, ConstsEnumType Flag2)      \
    {                                                                                                              \
        MaskType Mask = (MaskType)Flag1 | (MaskType)Flag2;                                                         \
        return CBitMaskSafeT_##MaskType##_##ConstsEnumType(Mask);                                                  \
    }

#endif //!WL_SAFE_BIT_MASKS_H