#ifndef WL_SAFE_BIT_MASKS_H
#define WL_SAFE_BIT_MASKS_H

#define DECLARE_BIT_MASK_SAFE_CLASS(ClassName, MaskType, ConstsEnumType)                                    \
    typedef                                                                                                 \
    class CBitMaskSafeT_##MaskType##_##ConstsEnumType                                                       \
    {                                                                                                       \
    private:                                                                                                \
        MaskType Value = 0;                                                                                 \
        CBitMaskSafeT_##MaskType##_##ConstsEnumType(MaskType Mask) : Value(Mask) {}                         \
        CBitMaskSafeT_##MaskType##_##ConstsEnumType(const CBitMaskSafeT_##MaskType##_##ConstsEnumType &) {} \
                                                                                                            \
    public:                                                                                                 \
        CBitMaskSafeT_##MaskType##_##ConstsEnumType(ConstsEnumType Flag) : Value(Flag) {}                   \
        CBitMaskSafeT_##MaskType##_##ConstsEnumType & operator| (ConstsEnumType Flag)                       \
        {                                                                                                   \
            Value |= (MaskType)Flag;                                                                        \
            return *this;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        operator MaskType() const                                                                           \
        {                                                                                                   \
            return Value;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        friend CBitMaskSafeT_##MaskType##_##ConstsEnumType operator| (ConstsEnumType, ConstsEnumType);      \
    } ClassName;                                                                                            \
                                                                                                            \
    CBitMaskSafeT_##MaskType##_##ConstsEnumType operator| (ConstsEnumType Flag1, ConstsEnumType Flag2)      \
    {                                                                                                       \
        MaskType Mask = (MaskType)Flag1 | (MaskType)Flag2;                                                  \
        return CBitMaskSafeT_##MaskType##_##ConstsEnumType(Mask);                                           \
    }                                  

#endif //!WL_SAFE_BIT_MASKS_H