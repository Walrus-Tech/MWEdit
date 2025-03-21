/*===========================================================================
 *
 * File:    EsmClothing.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMCLOTHING_H
#define __ESMCLOTHING_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem3.h"
#include "EsmSubCTDT.h"
#include "EsmSubByte.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Number of body part definitions allowed in a clothing record */
#define MWESM_CLOTH_MAXBODYPARTS 7

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmClothing Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmClothing : public CEsmItem3 {
	DECLARE_SUBRECCREATE();


	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubCTDT *m_pClothData;   /* Reference to subrecords */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmClothing();
	//virtual ~CEsmClothing() { Destroy(); }
	virtual void Destroy (void);

	/* Compare two fields of the record */
	virtual int CompareFields (const int FieldID, CEsmRecord* pRecord);

	/* Return a new record object */
	static CEsmRecord *Create (void);

	/* Create a new, empty, record */
	virtual void CreateNew (CEsmFile* pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString (const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType (void) {
		return _T("Clothing");
	}

	/* Get class members */
	clothdata_t *GetClothData (void) {
		return (m_pClothData == NULL ? NULL : m_pClothData->GetClothData() );
	}

	const TCHAR *GetClothType (void);
	virtual float GetWeight (void) {
		return (m_pClothData == NULL ? 0 : m_pClothData->GetWeight());
	}

	virtual long GetValue (void) {
		return (m_pClothData == NULL ? 0 : m_pClothData->GetValue());
	}

	virtual long GetEnchantPts (void) {
		return (m_pClothData == NULL ? 0 : m_pClothData->GetEnchantPts());
	}

	int GetClothTypeID (void) {
		return (m_pClothData == NULL ? 0 : m_pClothData->GetClothType());
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	void SetClothType (const int Type) {
		if (m_pClothData) {
			m_pClothData->SetClothType(Type);
		}
	}

	void SetWeight (const float Weight) {
		if (m_pClothData) {
			m_pClothData->SetWeight(Weight);
		}
	}

	virtual void SetEnchantPts (const long Value) {
		if (m_pClothData) {
			m_pClothData->SetEnchantPts((ushort) Value);
		}
	}

	virtual void SetValue (const long Value) {
		if (m_pClothData) {
			m_pClothData->SetValue((ushort) Value);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue (const int FieldID, const TCHAR* pString);

};

/*===========================================================================
 *      End of Class CEsmClothing Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Convert an armor type to a string */
const TCHAR *GetESMClothType (const int ArmorType);
int GetESMClothType (const TCHAR* pString);
bool GetESMClothType (int &OutIndex, const TCHAR* pString);

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
