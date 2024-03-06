#pragma once

#include "rvalue.fwd.h"
#include "cinstance.fwd.h"
#include "chashmap.h"
#include "cobjectgm.h"
#include "cphysicsobject.h"
#include "cskeletoninstance.h"
#include "yyrect.h"

namespace GM {

    enum EJSRetValBool : __int32 {
        EJSRVB_FALSE = 0x0,
        EJSRVB_TRUE = 0x1,
        EJSRVB_TYPE_ERROR = 0x2
    };

    enum InstanceKeywords : __int32 {
        VAR_SELF = -1,
        VAR_OTHER = -2,
        VAR_ALL = -3,
        VAR_NOONE = -4,
        VAR_GLOBAL = 5,
        VAR_BUILTIN = -6,
        VAR_LOCAL = -7,
        VAR_STACKTOP = -9,
        VAR_ARGUMENT = -15
    };

    enum YYObjectKind : __int32 {
        OBJECT_KIND_YYOBJECTBASE = 0x0,
        OBJECT_KIND_CINSTANCE = 0x1,
        OBJECT_KIND_ACCESSOR = 0x2,
        OBJECT_KIND_SCRIPTREF = 0x3,
        OBJECT_KIND_PROPERTY = 0x4,
        OBJECT_KIND_ARRAY = 0x5,
        OBJECT_KIND_WEAKREF = 0x6,
        OBJECT_KIND_CONTAINER = 0x7,
        OBJECT_KIND_SEQUENCE = 0x8,
        OBJECT_KIND_SEQUENCEINSTANCE = 0x9,
        OBJECT_KIND_SEQUENCETRACK = 0xA,
        OBJECT_KIND_SEQUENCECURVE = 0xB,
        OBJECT_KIND_SEQUENCECURVECHANNEL = 0xC,
        OBJECT_KIND_SEQUENCECURVEPOINT = 0xD,
        OBJECT_KIND_SEQUENCEKEYFRAMESTORE = 0xE,
        OBJECT_KIND_SEQUENCEKEYFRAME = 0xF,
        OBJECT_KIND_SEQUENCEKEYFRAMEDATA = 0x10,
        OBJECT_KIND_SEQUENCEEVALTREE = 0x11,
        OBJECT_KIND_SEQUENCEEVALNODE = 0x12,
        OBJECT_KIND_SEQUENCEEVENT = 0x13,
        OBJECT_KIND_NINESLICE = 0x14,
        OBJECT_KIND_FILTERHOST = 0x15,
        OBJECT_KIND_EFFECTINSTANCE = 0x16,
        OBJECT_KIND_SKELETON_SKIN = 0x17,
        OBJECT_KIND_AUDIOBUS = 0x18,
        OBJECT_KIND_AUDIOEFFECT = 0x19,
        OBJECT_KIND_MAX = 0x1A
    };

    typedef void(__cdecl* FNGetOwnProperty)(YYObjectBase* Object, RValue* Result, const char* Name);
    typedef void(__cdecl* FNDeleteProperty)(YYObjectBase* Object, RValue* Result, const char* Name, bool ThrowOnError);
    typedef EJSRetValBool(__cdecl* FNDefineOwnProperty)(YYObjectBase* Object, const char* Name, RValue* Result, bool ThrowOnError);

    struct CInstanceBase {
        void* vtable;
        RValue* m_YYVars;
    };

    struct CWeakRef;

    struct YYObjectBase : CInstanceBase {
        YYObjectBase* m_Flink;
        YYObjectBase* m_Blink;
        YYObjectBase* m_Prototype;
        const char* m_Class;
        FNGetOwnProperty m_GetOwnProperty;
        FNDeleteProperty m_DeleteProperty;
        FNDefineOwnProperty m_DefineOwnProperty;
        b* m_YYVarsMap;
        CWeakRef** m_WeakRef;
        unsigned __int32 m_WeakRefCount;
        unsigned __int32 m_VariableCount;
        unsigned __int32 m_Flags;
        unsigned __int32 m_Capacity;
        unsigned __int32 m_Visited;
        unsigned __int32 m_VisitedGC;
        __int32 m_GCGeneration;
        __int32 m_GCCreationFrame;
        __int32 m_Slot;
        YYObjectKind m_ObjectKind;
        __int32 m_RValueInitType;
        __int32 m_CurrentSlot;
    };

    struct CWeakRef : YYObjectBase {
        YYObjectBase* pWeakRef;
    };

    struct CInstance : YYObjectBase {
        __int64 m_CreateCounter;
        CObjectGM* m_Object;
        CPhysicsObject* m_PhysicsObject;
        CSkeletonInstance* m_SkeletonAnimation;

        void* m_SequenceInstance;
        unsigned __int32 m_InstanceFlags;
        __int32 m_ID;
        __int32 m_ObjectIndex;
        __int32 m_SpriteIndex;
        float m_SequencePosition;
        float m_LastSequencePosition;
        float m_SequenceDirection;
        float m_ImageIndex;
        float m_ImageSpeed;
        float m_ImageScaleX;
        float m_ImageScaleY;
        float m_ImageAngle;
        float m_ImageAlpha;
        unsigned __int32 m_ImageBlend;
        float m_X;
        float m_Y;
        float m_XStart;
        float m_YStart;
        float m_XPrevious;
        float m_YPrevious;
        float m_Direction;
        float m_Speed;
        float m_Friction;
        float m_GravityDirection;
        float m_Gravity;
        float m_HorizontalSpeed;
        float m_VerticalSpeed;
        YYRECT m_BoundingBox;
        __int32 m_Timers[12];
        __int64 m_RollbackFrameKilled;
        void* m_TimelinePath;
        CCode* m_InitCode;
        CCode* m_PrecreateCode;
        CObjectGM* m_OldObject;
        __int32 m_LayerID;
        __int32 m_MaskIndex;
        __int16 m_MouseOverCount;
        CInstance* m_Flink;
        CInstance* m_Blink;
    };

}
