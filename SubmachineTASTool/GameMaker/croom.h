#pragma once

#include "ccode.h"
#include "linkedlist.h"
#include "chashmap.h"
#include "carraystructure.h"
#include "clayer.h"

namespace GM {

	struct CBackGM {
		bool visible;
		bool foreground;
		int index;
		float x;
		float y;
		bool htiled;
		bool vtiled;
		float hspeed;
		float vspeed;
		float xscale;
		float yscale;
		unsigned int blend;
		float alpha;
	};

	struct CViewGM {
		bool visible;
		float xview;
		float yview;
		float wview;
		float hview;
		int xport;
		int yport;
		int wport;
		int hport;
		float angle;
		int hborder;
		int vborder;
		int hspeed;
		int vspeed;
		int index;
		int SurfaceID;
		int cameraID;
	};

	struct CPhysicsWorld;

	struct YYRoomTiles {
		int count;
	};

	struct YYRoomInstances {
		int count;
	};

	struct RTile {
		float x;
		float y;
		int index;
		int xo;
		int yo;
		int w;
		int h;
		float depth;
		int id;
		float xscale;
		float yscale;
		unsigned int blend;
		float alpha;
		bool visible;
	};

	struct YYRoom {
		unsigned __int32 m_NameOffset;
		unsigned __int32 m_Caption;
		__int32 m_Width;
		__int32 m_Height;
		__int32 m_Speed;
		__int32 m_Persistent;
		__int32 m_Color;
		__int32 m_ShowColor;
		unsigned __int32 m_CreationCode;
		__int32 m_EnableViews;
		unsigned __int32 pBackgrounds;
		unsigned __int32 pViews;
		unsigned __int32 pInstances;
		unsigned __int32 pTiles;
		__int32 m_PhysicsWorld;
		__int32 m_PhysicsWorldTop;
		__int32 m_PhysicsWorldLeft;
		__int32 m_PhysicsWorldRight;
		__int32 m_PhysicsWorldBottom;
		float m_PhysicsGravityX;
		float m_PhysicsGravityY;
		float m_PhysicsPixelToMeters;
	};

	struct CRoom {
		__int32 m_LastTile;
		CRoom* m_InstanceHandle;
		const char* m_Caption;
		__int32 m_Speed;
		__int32 m_Width;
		__int32 m_Height;
		bool m_Persistent;
		unsigned __int32 m_Color;
		bool m_ShowColor;
		CBackGM* m_Backgrounds[8];
		bool m_EnableViews;
		bool m_ClearScreen;
		bool m_ClearDisplayBuffer;
		CViewGM* m_Views[8];
		const char* m_LegacyCode;
		CCode* m_CodeObject;
		bool m_HasPhysicsWorld;
		__int32 m_PhysicsGravityX;
		__int32 m_PhysicsGravityY;
		float m_PhysicsPixelToMeters;
		LinkedList<CInstance> m_ActiveInstances;
		LinkedList<CInstance> m_InactiveInstances;
		CInstance* m_MarkedFirst;
		CInstance* m_MarkedLast;
		__int32* m_CreationOrderList;
		__int32 m_CreationOrderListSize;
		YYRoom* m_WadRoom;
		void* m_WadBaseAddress;
		CPhysicsWorld* m_PhysicsWorld;
		__int32 m_TileCount;
		CArrayStructure<RTile> m_Tiles;
		YYRoomTiles* m_WadTiles;
		YYRoomInstances* m_WadInstances;
		const char* m_Name;
		bool m_IsDuplicate;
		LinkedList<CLayer> m_Layers;
		CHashMap<int, CLayer> m_LayerLookup;
		CHashMap<int, CLayerElementBase> m_LayerElementLookup;
		CLayerElementBase* m_LastElementLookedUp;
		CHashMap<int, CLayerInstanceElement> m_InstanceElementLookup;
		__int32* m_SequenceInstanceIDs;
		__int32 m_SequenceInstanceIdCount;
		__int32 m_SequenceInstanceIdMax;
		__int32* m_EffectLayerIDs;
		__int32 m_EffectLayerIdCount;
		__int32 m_EffectLayerIdMax;
	};

	extern CRoom** currentRoom;
}