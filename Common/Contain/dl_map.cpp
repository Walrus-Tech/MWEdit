#include "Common/Contain/dl_map.h"

#include <cstddef>
#include <cstring>

#include "Common/dl_base.h"
#include "Common/dl_mem.h"

/*===========================================================================
 *
 * Class TGenMap Constructor
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg> TGenMap<TKey, TValue, TKeyArg>::TGenMap() {
	m_ppHashTable = NULL;
	m_RecordCount = 0;
	m_HashTableSize = DLMAP_DEFAULTSIZE;
	m_DeleteValues = true;
}


/*===========================================================================
 *
 * Class TGenMap Method - void Destroy (void);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
inline void TGenMap<TKey, TValue, TKeyArg>::Destroy() {
	RemoveAll();
}


/*===========================================================================
 *
 * Class TGenMap Method - void Delete (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
void TGenMap<TKey, TValue, TKeyArg>::Delete(TKeyArg Key) {
	CGenMapAssoc *pAssoc;
	CGenMapAssoc *pLastAssoc = NULL;
	dword Hash;
	/* Ignore if no table defined */
	Hash = HashKey(Key) % m_HashTableSize;

	if (m_ppHashTable == NULL) {
		return;
	}

	for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {
		if (CompareKeys(pAssoc->Key, Key)) {
			if (pLastAssoc != NULL) {
				pLastAssoc->pNext = pAssoc->pNext;
			} else {
				m_ppHashTable[Hash] = pAssoc->pNext;
			}

			if (m_DeleteValues) {
				DestroyPointer(pAssoc->Value);
			}

			DestroyPointer(pAssoc);
			return;
		}

		pLastAssoc = pAssoc;
	}
}


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetAssocNode (Key, Hash);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
typename TGenMap<TKey, TValue, TKeyArg>::CGenMapAssoc
*TGenMap<TKey, TValue, TKeyArg>::GetAssocNode(TKeyArg Key, dword &Hash) {
	CGenMapAssoc *pAssoc;
	/* Ignore if no table defined */
	Hash = HashKey(Key) % m_HashTableSize;

	if (m_ppHashTable == NULL) {
		return NULL;
	}

	for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {
		if (CompareKeys(pAssoc->Key, Key)) {
			return pAssoc;
		}
	}

	return NULL;
}


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetFirstRecord (Position);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TValue TGenMap<TKey, TValue, TKeyArg>::GetFirstRecord(MAPPOSITION &Position) {
	CGenMapAssoc *pAssoc;
	dword Index;
	Position = (MAPPOSITION)NULL;

	if (m_ppHashTable == NULL) {
		return NULL;
	}

	for (Index = 0; Index < m_HashTableSize; ++Index) {
		pAssoc = m_ppHashTable[Index];

		if (pAssoc != NULL) {
			Position = (MAPPOSITION)pAssoc;
			return pAssoc->Value;
		}
	}

	/* Nothing to return */
	return NULL;
}


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetNextRecord (Key, Hash);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TValue TGenMap<TKey, TValue, TKeyArg>::GetNextRecord(MAPPOSITION &Position) {
	CGenMapAssoc *pAssoc;
	dword Index;
	pAssoc = (CGenMapAssoc *)Position;

	if (m_ppHashTable == NULL) {
		return NULL;
	}

	if (pAssoc == NULL) {
		return NULL;
	}

	pAssoc = pAssoc->pNext;

	if (pAssoc != NULL) {
		Position = (MAPPOSITION)pAssoc;
		return pAssoc->Value;
	}

	for (Index = pAssoc->HashValue + 1; Index < m_HashTableSize; ++Index) {
		pAssoc = m_ppHashTable[Index];

		if (pAssoc != NULL) {
			Position = (MAPPOSITION)pAssoc;
			return pAssoc->Value;
		}
	}

	/* Nothing to return */
	Position = (MAPPOSITION)NULL;
	return NULL;
}


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetFirstRecordKey (Key, Position);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TValue TGenMap<TKey, TValue, TKeyArg>::GetFirstRecordKey(TKeyArg Key, MAPPOSITION &Position) {
	CGenMapAssoc *pAssoc;
	dword Hash;
	Position = (MAPPOSITION)NULL;

	if (m_ppHashTable == NULL) {
		return NULL;
	}

	Hash = HashKey(Key) % m_HashTableSize;
	pAssoc = m_ppHashTable[Hash];

	while (pAssoc) {
		Position = (MAPPOSITION)pAssoc;

		if (CompareKeys(pAssoc->Key, Key)) {
			return pAssoc->Value;
		}

		pAssoc = pAssoc->pNext;
	}

	/* No match */
	Position = NULL;
	return NULL;
}


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetNextRecordKey (Key, Hash);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TValue TGenMap<TKey, TValue, TKeyArg>::GetNextRecordKey(TKeyArg Key, MAPPOSITION &Position) {
	CGenMapAssoc *pAssoc;
	pAssoc = (CGenMapAssoc *)Position;

	if (m_ppHashTable == NULL) {
		return NULL;
	}

	if (pAssoc == NULL) {
		return NULL;
	}

	pAssoc = pAssoc->pNext;

	while (pAssoc) {
		Position = (MAPPOSITION)pAssoc;

		if (CompareKeys(pAssoc->Key, Key)) {
			return pAssoc->Value;
		}

		pAssoc = pAssoc->pNext;
	}

	/* Nothing to return */
	Position = NULL;
	return NULL;
}


/*===========================================================================
 *
 * Class TGenMap Method - void InitHashTable (Size);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
void TGenMap<TKey, TValue, TKeyArg>::InitHashTable(const dword Size) {
	DEFINE_FUNCTION("TGenMap::InitHashTable()");
	/* Clear the current table if any */
	DestroyArrayPointer(m_ppHashTable);
	/* Allocate the new hash table */
	m_HashTableSize = Size;
	m_ppHashTable = new CGenMapAssoc *[m_HashTableSize];
	ValidateNewPointer(m_ppHashTable);
	m_RecordCount = 0;
	std::memset(m_ppHashTable, 0, sizeof(CGenMapAssoc *) * m_HashTableSize);
}


/*===========================================================================
 *
 * Class TGenMap Method - bool Lookup (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
bool TGenMap<TKey, TValue, TKeyArg>::Lookup(TKeyArg Key, TValue &Record) {
	CGenMapAssoc *pAssoc;
	dword Hash;
	pAssoc = GetAssocNode(Key, Hash);

	if (pAssoc == NULL) {
		Record = NULL;
		return false;
	}

	Record = pAssoc->Value;
	return true;
}


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* NewAssocNode (void);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
typename TGenMap<TKey, TValue, TKeyArg>::CGenMapAssoc
*TGenMap<TKey, TValue, TKeyArg>::NewAssocNode() {
	DEFINE_FUNCTION("TGenMap::NewAssocNode()");
	TGenMap::CGenMapAssoc *pAssoc;
	CreatePointer(pAssoc, CGenMapAssoc);
	return pAssoc;
}


/*===========================================================================
 *
 * Class TGenMap Method - void RemoveAll (void);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
void TGenMap<TKey, TValue, TKeyArg>::RemoveAll() {
	DEFINE_FUNCTION("TGenMap::RemoveAll()");
	CGenMapAssoc *pAssoc;
	CGenMapAssoc *pAssoc1;
	dword Index;

	/* Delete all records in the table */
	if (m_ppHashTable != NULL) {
		for (Index = 0; Index < m_HashTableSize; ++Index) {
			for (pAssoc = m_ppHashTable[Index]; pAssoc != NULL; ) {
				pAssoc1 = pAssoc->pNext;

				if (m_DeleteValues) {
					DestroyPointer(pAssoc->Value);
				}

				DestroyPointer(pAssoc);
				pAssoc = pAssoc1;
			}
		}

		DestroyArrayPointer(m_ppHashTable);
		m_ppHashTable = NULL;
	}

	m_RecordCount = 0;
}


/*===========================================================================
 *
 * Class TGenMap Method - void SetAt (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
void TGenMap<TKey, TValue, TKeyArg>::SetAt(TKeyArg Key, TValue &Record) {
	CGenMapAssoc *pAssoc;
	dword Hash;
	/* Find an existing node */
	pAssoc = GetAssocNode(Key, Hash);

	if (pAssoc == NULL) {
		if (m_ppHashTable == NULL) {
			InitHashTable(m_HashTableSize);
		}

		pAssoc = NewAssocNode();
		pAssoc->HashValue = Hash;
		pAssoc->Key = Key;
		pAssoc->pNext = m_ppHashTable[Hash];
		m_ppHashTable[Hash] = pAssoc;
		++m_RecordCount;
	}

	pAssoc->Value = Record;
}
