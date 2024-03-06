#pragma once

namespace GM {

	template<typename Key, typename Value>
	struct CHashMapElement {
		Value* m_Value;
		Key m_Key;
	};

	template<typename Key, typename Value>
	struct CHashMap {
		int m_CurrentSize;
		int m_UsedCount;
		int m_CurrentMask;
		int m_Grow_Threshold;
		CHashMapElement<Key, Value>* m_Elements;
	};

}
