#pragma once

enum ValueType {
    Real = 0x0,
    String = 0x1,
    Array = 0x2,
    Ptr = 0x3,
    Vec3 = 0x4,
    Undefined = 0x5,
    Object = 0x6,
    Int = 0x7,
    Vec4 = 0x8,
    Vec44 = 0x9,
    Long = 0xA,
    Null = 0xC,
    Bool = 0xD,
    Iterator = 0xE,
    Ref = 0xF,
    Unset = 0xFFFFFF
};

struct RValue {
    union RValueUnion {
        int v32;
        __int64 v64;
        double val;
        void* ptr;
    } value;
    unsigned int flags;
    ValueType kind;
};
