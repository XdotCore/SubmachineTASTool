#pragma once

#include "chashmap.h"
#include "linkedlist.h"
#include "cevent.h"
#include "cphysicsdatagm.h"

namespace GM {

	struct CObjectGM {
		const char* m_Name;
		CObjectGM* m_ParentObject;
		CHashMap<int, CObjectGM>* m_ChildrenMap;
		CHashMap<int, CEvent>* m_EventsMap;
		CPhysicsDataGM m_PhysicsData;
		LinkedList<CInstance> m_Instances;
		LinkedList<CInstance> m_InstancesRecursive;
		unsigned __int32 m_Flags;
		__int32 m_SpriteIndex;
		__int32 m_Depth;
		__int32 m_Parent;
		__int32 m_Mask;
		__int32 m_ID;
	};

}
