#pragma once

#include "rvalue.h"
#include "linkedlist.h"
#include "cinstance.h"

namespace GM {

	struct CLayer;
	struct CLayerInstanceElement;
	struct CLayerSpriteElement;

	struct CLayerEffectInfo;

	struct CLayerElementBase {
		int m_Type;
		int m_ID;
		bool m_RuntimeDataInitialized;
		const char* m_Name;
		CLayer* m_layer;
		union CLayerElementBaseFlinkUnion {
			CLayerInstanceElement* m_InstanceFlink;
			CLayerSpriteElement* m_SpriteFlink;
			CLayerElementBase* m_Flink;
		} flink;
		union CLayerElementBaseBlinkUnion {
			CLayerInstanceElement* m_InstanceBlink;
			CLayerSpriteElement* m_SpriteBlink;
			CLayerElementBase* m_Blink;
		} blink;
	};

	struct CLayerInstanceElement : CLayerElementBase {
		int m_InstanceID;
		CInstance* m_Instance;
	};

	struct CLayerSpriteElement : CLayerElementBase {
		int m_SpriteIndex;
		float m_SequencePosition;
		float m_SequenceDirection;
		float m_ImageIndex;
		float m_ImageSpeed;
		__int32 m_SpeedType;
		float m_ImageScaleX;
		float m_ImageScaleY;
		float m_ImageAngle;
		unsigned __int32 m_ImageBlend;
		float m_ImageAlpha;
		float m_X;
		float m_Y;
	};

	struct CLayer {
		__int32 m_Id;
		__int32 m_Depth;
		float m_XOffset;
		float m_YOffset;
		float m_HorizontalSpeed;
		float m_VerticalSpeed;
		bool m_Visible;
		bool m_Deleting;
		bool m_Dynamic;
		const char* m_Name;
		RValue m_BeginScript;
		RValue m_EndScript;
		bool m_EffectEnabled;
		bool m_EffectPendingEnabled;
		RValue m_Effect;
		CLayerEffectInfo* m_InitialEffectInfo;
		__int32 m_ShaderID;
		LinkedList<CLayerElementBase> m_Elements;
		CLayer* m_Flink;
		CLayer* m_Blink;
		void* m_GCProxy;
	};

}
