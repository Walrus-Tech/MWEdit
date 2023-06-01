/*===========================================================================
 *
 * File:	dl_map.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	May 6, 2006
 *
 * Defines a hash-map template class.
 *
 *=========================================================================*/
#ifndef __DLMAP_H
#define __DLMAP_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dl_err.h"
  #include "dl_str.h"
  #include <ctype.h>
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Default size of the hash map tables */
  #define DLMAP_DEFAULTSIZE 1009

	/* Used to iterate through records */
  typedef void* MAPPOSITION;

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/



 /*===========================================================================
  *
  * Begin Predefined CompareKeys Functions
  *
  *=========================================================================*/
  inline bool CompareKeys(dword Key1, dword Key2) {
      return (Key1 == Key2);
  }

  inline bool CompareKeys(const char* Key1, const char* Key2) {
      return (StringCompare(Key1, Key2, false) == 0);
  }
  /*===========================================================================
   *		End of Predefined CompareKeys Functions
   *=========================================================================*/


   /*===========================================================================
    *
    * Begin Predefined HashKey Functions
    *
    *=========================================================================*/
  inline dword HashKey(dword Key) {
      return (Key >> 4);
  }


  inline dword HashKey(const char* Key) {
      dword nHash = 0;

      while (*Key) {
          nHash = (nHash << 5) + nHash + tolower(*Key);
          ++Key;
      }

      return nHash;
  }
  /*===========================================================================
   *		End of Predefined HashKey Functions
   *=========================================================================*/

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
	CGenMapAssoc* pNext;
	dword	      HashValue;
	TKey	      Key;
	TValue        Value;
   };

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CGenMapAssoc** m_ppHashTable;		/* Array of hash records */
  dword		 m_RecordCount;
  dword		 m_HashTableSize;
  bool		 m_DeleteValues;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper find method */
  virtual CGenMapAssoc* GetAssocNode (TKeyArg Key, dword& Hash);

	/* Create a new node */
  virtual CGenMapAssoc* NewAssocNode (void);

	
  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  TGenMap();
  virtual ~TGenMap() { Destroy(); }
  virtual void Destroy (void);

	/* Delete a specified key */
  virtual void Delete (TKeyArg Key);

	/* Iterate through records in the map */
  virtual TValue GetFirstRecord (MAPPOSITION& Position);
  virtual TValue GetNextRecord  (MAPPOSITION& Position);

	/* Iterate through records in the map */
  virtual TValue GetFirstRecordKey (TKeyArg Key, MAPPOSITION& Position);
  virtual TValue GetNextRecordKey  (TKeyArg Key, MAPPOSITION& Position);

	/* Get class members */
  virtual dword GetNumRecords (void) { return (m_RecordCount); }

	/* Initialize the hash table to a specific size */
  virtual void InitHashTable (const dword Size);

	/* Find an existing value by its key */
  virtual bool Lookup (TKeyArg Key, TValue& Record);

	/* Delete all hash table entries */
  virtual void RemoveAll (void);

	/* Set a value */
  virtual void SetAt (TKeyArg Key, TValue& Record);

 };
/*===========================================================================
 *		End of Class TGenMap Definition
 *=========================================================================*/


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

  TGenRefMap() {/* m_DeleteValues = false;*/ }
};
/*===========================================================================
 *		End of Class TGenMap Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Constructor
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TGenMap<TKey, TValue, TKeyArg>::TGenMap () {
  m_ppHashTable   = NULL;
  m_RecordCount   = 0;
  m_HashTableSize = DLMAP_DEFAULTSIZE;
  m_DeleteValues  = true;
}
/*===========================================================================
 *		End of Class TGenMap Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - void Destroy (void);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
inline void TGenMap<TKey, TValue, TKeyArg>::Destroy (void) {
  RemoveAll();
 }
/*===========================================================================
 *		End of Class Method TGenMap::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - void Delete (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
void TGenMap<TKey, TValue, TKeyArg>::Delete (TKeyArg Key) {
  CGenMapAssoc* pAssoc;
  CGenMapAssoc* pLastAssoc = NULL;
  dword         Hash;

	/* Ignore if no table defined */
  Hash = HashKey(Key) % m_HashTableSize;
  if (m_ppHashTable == NULL) return;
  
  for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {

    if (CompareKeys(pAssoc->Key, Key)) {

      if (pLastAssoc != NULL) 
        pLastAssoc->pNext = pAssoc->pNext;
      else
        m_ppHashTable[Hash] = pAssoc->pNext;

      if (m_DeleteValues) { DestroyPointer(pAssoc->Value); }
      DestroyPointer(pAssoc);
      return;
     }

    pLastAssoc = pAssoc;
   }

 }
/*===========================================================================
 *		End of Class Method TGenMap::Delete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetAssocNode (Key, Hash);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
typename TGenMap<TKey, TValue, TKeyArg>::CGenMapAssoc* TGenMap<TKey, TValue, TKeyArg>::GetAssocNode (TKeyArg Key, dword& Hash) {
  CGenMapAssoc* pAssoc;

	/* Ignore if no table defined */
  Hash = HashKey(Key) % m_HashTableSize;
  if (m_ppHashTable == NULL) return (NULL);
  
  for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {
    if (CompareKeys(pAssoc->Key, Key)) return pAssoc;
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method TGenMap::GetAssocNode()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetFirstRecord (Position);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TValue TGenMap<TKey, TValue, TKeyArg>::GetFirstRecord (MAPPOSITION& Position) {
  CGenMapAssoc* pAssoc;
  dword	       Index;

  Position = (MAPPOSITION) NULL;
  if (m_ppHashTable == NULL) return (NULL);

  for (Index = 0; Index < m_HashTableSize; ++Index) {
    pAssoc = m_ppHashTable[Index];
    
    if (pAssoc != NULL) {
      Position = (MAPPOSITION) pAssoc;
      return (pAssoc->Value);
     }
   }

	/* Nothing to return */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method TGenMap::GetFirstRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetNextRecord (Key, Hash);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TValue TGenMap<TKey, TValue, TKeyArg>::GetNextRecord (MAPPOSITION& Position) {
  CGenMapAssoc* pAssoc;
  dword	       Index;

  pAssoc = (CGenMapAssoc *) Position;
  if (m_ppHashTable == NULL) return (NULL);
  if (pAssoc        == NULL) return (NULL);

  pAssoc = pAssoc->pNext;

  if (pAssoc != NULL) {
    Position = (MAPPOSITION) pAssoc;
    return (pAssoc->Value);
   }

  for (Index = pAssoc->HashValue + 1; Index < m_HashTableSize; ++Index) {
    pAssoc = m_ppHashTable[Index]; 
    
    if (pAssoc != NULL) {
      Position = (MAPPOSITION) pAssoc;
      return (pAssoc->Value);
     }
   }

	/* Nothing to return */
  Position = (MAPPOSITION) NULL;
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method TGenMap::GetNextRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetFirstRecordKey (Key, Position);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TValue TGenMap<TKey, TValue, TKeyArg>::GetFirstRecordKey (TKeyArg Key, MAPPOSITION& Position) {
  CGenMapAssoc* pAssoc;
  dword	        Hash;

  Position = (MAPPOSITION) NULL;
  if (m_ppHashTable == NULL) return (NULL);

  Hash     = HashKey(Key) % m_HashTableSize;
  pAssoc   = m_ppHashTable[Hash];

  while (pAssoc) {
    Position = (MAPPOSITION) pAssoc;
    if (CompareKeys(pAssoc->Key, Key)) return (pAssoc->Value);
    pAssoc = pAssoc->pNext;
  }

	/* No match */
  Position = NULL;
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method TGenMap::GetFirstRecordKey()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* GetNextRecordKey (Key, Hash);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
TValue TGenMap<TKey, TValue, TKeyArg>::GetNextRecordKey (TKeyArg Key, MAPPOSITION& Position) {
  CGenMapAssoc* pAssoc;

  pAssoc = (CGenMapAssoc *) Position;
  if (m_ppHashTable == NULL) return (NULL);
  if (pAssoc        == NULL) return (NULL);

  pAssoc = pAssoc->pNext;

  while (pAssoc) {
    Position = (MAPPOSITION) pAssoc;
    if (CompareKeys(pAssoc->Key, Key)) return (pAssoc->Value);
    pAssoc = pAssoc->pNext;
  }

	/* Nothing to return */
  Position = NULL;
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method TGenMap::GetNextRecordKey()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - void InitHashTable (Size);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
void TGenMap<TKey, TValue, TKeyArg>::InitHashTable (const dword Size) {
  DEFINE_FUNCTION("TGenMap::InitHashTable()");
  
	/* Clear the current table if any */
  DestroyArrayPointer(m_ppHashTable);

	/* Allocate the new hash table */ 
  m_HashTableSize = Size;
  m_ppHashTable   = new CGenMapAssoc* [m_HashTableSize];
  ValidateNewPointer(m_ppHashTable);
  m_RecordCount   = 0;
  memset(m_ppHashTable, 0, sizeof(CGenMapAssoc*) * m_HashTableSize);
 }
/*===========================================================================
 *		End of Class Method TGenMap::InitHashTable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - bool Lookup (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
bool TGenMap<TKey, TValue, TKeyArg>::Lookup (TKeyArg Key, TValue& Record) {
  CGenMapAssoc* pAssoc;
  dword        Hash;

  pAssoc = GetAssocNode(Key, Hash);

  if (pAssoc == NULL) {
    Record = NULL;
    return (false);
   }

  Record = pAssoc->Value;
  return (true);
 }
/*===========================================================================
 *		End of Class Method TGenMap::Lookup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - CGenMapAssoc* NewAssocNode (void);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
typename TGenMap<TKey, TValue, TKeyArg>::CGenMapAssoc* TGenMap<TKey, TValue, TKeyArg>::NewAssocNode (void) {
  DEFINE_FUNCTION("TGenMap::NewAssocNode()");
  TGenMap::CGenMapAssoc* pAssoc;

  CreatePointer(pAssoc, CGenMapAssoc);
  return (pAssoc);
 }
/*===========================================================================
 *		End of Class Method TGenMap::NewAssocNode()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - void RemoveAll (void);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
void TGenMap<TKey, TValue, TKeyArg>::RemoveAll (void) {
  DEFINE_FUNCTION("TGenMap::RemoveAll()");
  CGenMapAssoc*	pAssoc;
  CGenMapAssoc*	pAssoc1;
  dword		Index;

	/* Delete all records in the table */
  if (m_ppHashTable != NULL) {
    for (Index = 0; Index < m_HashTableSize; ++Index) {
      for (pAssoc = m_ppHashTable[Index]; pAssoc != NULL; ) {
        pAssoc1 = pAssoc->pNext;

	if (m_DeleteValues) { DestroyPointer(pAssoc->Value); }
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
 *		End of Class Method TGenMap::RemoveAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TGenMap Method - void SetAt (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TValue, class TKeyArg>
void TGenMap<TKey, TValue, TKeyArg>::SetAt (TKeyArg Key, TValue& Record) {
  CGenMapAssoc* pAssoc;
  dword         Hash;

	/* Find an existing node */
  pAssoc = GetAssocNode(Key, Hash);

  if (pAssoc == NULL) {
    if (m_ppHashTable == NULL) InitHashTable(m_HashTableSize);

    pAssoc = NewAssocNode();
    pAssoc->HashValue = Hash;
    pAssoc->Key       = Key;

    pAssoc->pNext       = m_ppHashTable[Hash];
    m_ppHashTable[Hash] = pAssoc;
    ++m_RecordCount;
   }

  pAssoc->Value = Record;
 }
/*===========================================================================
 *		End of Class Method TGenMap::SetAt()
 *=========================================================================*/




#endif
/*===========================================================================
 *		End of File dl_map.H
 *=========================================================================*/
