/*===========================================================================
 *
 * File:    EsmProbe.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMPROBE_H
#define __ESMPROBE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem2.h"
#include "EsmSubPBDT.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmProbe Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmProbe : public CEsmItem2 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubPBDT *m_pProbeData;   /* Reference to subrecords */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmProbe();
	//virtual ~CEsmProbe() { Destroy(); }
	virtual void Destroy (void);

	/* Compare two fields of the record */
	virtual int CompareFields (const int FieldID, CEsmRecord* pRecord);

	/* Return a new record object */
	static CEsmRecord *Create (void);

	/* Create a new, empty, record */
	virtual void CreateNew (CEsmFile* pFile);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType (void) {
		return _T("Probe");
	}

	/* Get class members */
	probedata_t *GetProbeData (void) {
		return (m_pProbeData ? m_pProbeData->GetProbeData() : NULL);
	}

	virtual float GetWeight (void) {
		return (m_pProbeData ? GetProbeData()->Weight : 0);
	}

	virtual long GetValue (void) {
		return (m_pProbeData ? GetProbeData()->Value : 0);
	}

	float GetQuality (void) {
		return (m_pProbeData ? GetProbeData()->Quality : 0);
	}

	long GetUses (void) {
		return (m_pProbeData ? GetProbeData()->Uses : 0);
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString (const int FieldID);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	virtual void SetWeight (const float Weight) {
		if (GetProbeData() != NULL) {
			GetProbeData()->Weight = Weight;
		}
	}

	virtual void SetValue (const long Value) {
		if (GetProbeData() != NULL) {
			GetProbeData()->Value = Value;
		}
	}

	void SetUses (const int Value) {
		if (GetProbeData()) {
			GetProbeData()->Uses = Value;
		}
	}

	void SetQuality (const float Value) {
		if (GetProbeData()) {
			GetProbeData()->Quality = Value;
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue (const int FieldID, const TCHAR* pString);

};

/*===========================================================================
 *      End of Class CEsmArmor Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmProbe.H
 *=========================================================================*/
