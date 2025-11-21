/*===========================================================================
 *
 * File:    dl_map.H
 * Author:  Dave Humphrey (uesp@sympatico.ca)
 * Created On:  May 6, 2006
 *
 * Defines a hash-map template class.
 *
 *=========================================================================*/
#ifndef __DLMAP_H
#define __DLMAP_H

#include <cctype>

#include "Common/dl_base.h"
#include "Common/dl_str.h"


/* Default size of the hash map tables */
#define DLMAP_DEFAULTSIZE 1009

/* Used to iterate through records */
typedef void *MAPPOSITION;

inline bool CompareKeys(dword Key1, dword Key2) {
	return Key1 == Key2;
}

inline bool CompareKeys(const char *Key1, const char *Key2) {
	return StringCompare(Key1, Key2, false) == 0;
}

inline dword HashKey(dword Key) {
	return Key >> 4;
}


inline dword HashKey(const char *Key) {
	dword nHash = 0;

	while (*Key) {
		nHash = (nHash << 5) + nHash + std::tolower(*Key);
		++Key;
	}

	return nHash;
}

/*===========================================================================
 *
 * Begin Class TGenMap Definition
 *
 * Template class from which specific hash-map implementations will be
 * created from.
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
class TGenMap {

	/* Private structure used as a linked list for each unique hash value */
	struct CGenMapAssoc {
		CGenMapAssoc *pNext;
		dword HashValue;
		TKey Key;
		TValue Value;
	};

  protected:
	CGenMapAssoc **m_ppHashTable; /* Array of hash records */
	dword m_RecordCount;
	dword m_HashTableSize;
	bool m_DeleteValues;


	/* Helper find method */
	virtual CGenMapAssoc *GetAssocNode(TKeyArg Key, dword &Hash);

	/* Create a new node */
	virtual CGenMapAssoc *NewAssocNode();


  public:
	/* Class Constructors/Destructors */
	TGenMap();
	virtual ~TGenMap() {
		Destroy();
	}

	virtual void Destroy();

	/* Delete a specified key */
	virtual void Delete(TKeyArg Key);

	/* Iterate through records in the map */
	virtual TValue GetFirstRecord(MAPPOSITION &Position);
	virtual TValue GetNextRecord(MAPPOSITION &Position);

	/* Iterate through records in the map */
	virtual TValue GetFirstRecordKey(TKeyArg Key, MAPPOSITION &Position);
	virtual TValue GetNextRecordKey(TKeyArg Key, MAPPOSITION &Position);

	/* Get class members */
	virtual dword GetNumRecords() {
		return m_RecordCount;
	}

	/* Initialize the hash table to a specific size */
	virtual void InitHashTable(const dword Size);

	/* Find an existing value by its key */
	virtual bool Lookup(TKeyArg Key, TValue &Record);

	/* Delete all hash table entries */
	virtual void RemoveAll();

	/* Set a value */
	virtual void SetAt(TKeyArg Key, TValue &Record);
};


/*===========================================================================
 *
 * Begin Class TGenMap Definition
 *
 * Template class from which specific hash-map implementations will be
 * created from.
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
class TGenRefMap : public TGenMap<TKey, TValue, TKeyArg> {
  public:

	TGenRefMap() {
		/* m_DeleteValues = false;*/
	}
};


#endif  // __DLMAP_H
