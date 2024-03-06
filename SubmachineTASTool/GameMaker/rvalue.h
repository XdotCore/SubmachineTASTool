#pragma once

#include "cinstance.fwd.h"
#include "rvalue.fwd.h"

namespace GM {

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

    struct RefString {
        const char* m_thing;
        int m_refCount;
        int m_size;
    };

    struct RValue {
        union RValueUnion {
            __int32 v32;
            __int64 v64;
            double val;
            void* ptr;
            CInstance* obj;
            RefString* pRefStr;
            char* str;
        } value;
        unsigned __int32 flags;
        ValueType kind;
    };

}
