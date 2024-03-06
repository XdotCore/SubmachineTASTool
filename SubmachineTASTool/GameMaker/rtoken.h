#pragma once

#include "rvalue.h"

namespace GM {

    struct RToken {
        int m_Kind;
        unsigned int m_Type;
        int m_Ind;
        int m_Ind2;
        RValue m_Value;
        int m_ItemNumber;
        RToken* m_Items;
        int m_Position;
    };

}
