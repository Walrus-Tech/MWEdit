/*===========================================================================
 *
 * File:    Configfile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, January 09, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __CONFIGFILE_H
#define __CONFIGFILE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "GenFile.h"
#include "SString.h"
#include "PtrArray.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
#define CONFIG_LINE_LENGTH 256
/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CConfigEntry Definition
 *
 * One variable/value pair in the config file.
 *
 *=========================================================================*/
class CConfigEntry {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	CSString m_Variable;
	CSString m_Value;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CConfigEntry() { ; }

	virtual ~CConfigEntry() {
		Destroy();
	}

	virtual void Destroy(void) {
		m_Variable.Empty();
		m_Value.Empty();
	}

	/* Get class members */
	const TCHAR *GetVariable(void) const {
		return (m_Variable);
	}

	const TCHAR *GetValue(void) const {
		return (m_Value);
	}

	/* Set class members */
	void SetVariable(const TCHAR *pString) {
		m_Variable = pString;
	}

	void SetValue(const TCHAR *pString) {
		m_Value = pString;
	}

	/* Output entry to file */
	bool Write(CGenFile &File);

};

typedef TPtrArray<CConfigEntry> CCfgEntryArray;
/*===========================================================================
 *      End of Class CConfigEntry Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CConfigGroup Definition
 *
 * A single group of config variables in a config file.
 *
 *=========================================================================*/
class CConfigGroup {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	CSString m_Name;        /* Group name */
	CCfgEntryArray m_Entries;     /* Array of config entries */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CConfigGroup() : m_Entries(2) {;}

	virtual ~CConfigGroup() {
		Destroy();
	}

	virtual void Destroy(void);

	/* Adds a new entry to the group */
	CConfigEntry *AddEntry(const TCHAR *pVar, const TCHAR *pValue);

	/* Find the first matching entry */
	CConfigEntry *FindEntry(const TCHAR *pVariable);

	/* Find an existing entry or create it */
	CConfigEntry *GetEntry(const TCHAR *pVariable);

	/* Get class members */
	const TCHAR *GetName(void) const {
		return (m_Name);
	}

	/* Find a variable value */
	const TCHAR *GetValue(const TCHAR *pVariable);

	/* Set class members */
	void SetName(const TCHAR *pName) {
		m_Name = pName;
	}

	/* Set a variable value */
	bool SetValue(const TCHAR *pVariable, const TCHAR *pValue);

	/* Output the group to the given file */
	bool Write(CGenFile &File);

};

typedef TPtrArray<CConfigGroup> CCfgGroupArray;
/*===========================================================================
 *      End of Class CConfigGroup Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CConfigFile Definition
 *
 * Handles input/output of TCScan config files.
 *
 *=========================================================================*/
class CConfigFile : public CGenFile {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	CCfgGroupArray m_Groups;      /* Array of config groups */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper method to make a variable array string */
	const TCHAR *CreateArrayString(const TCHAR *pVariable, const int ID);
	const TCHAR *CreateArrayString(const TCHAR *pVariable, const int ID1, const int ID2);
	const TCHAR *CreateArrayString(const TCHAR *pVariable, const int ID1, const TCHAR *pID2);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CConfigFile();
	virtual ~CConfigFile() {
		Destroy();
	}

	virtual void Destroy(void);

	/* Add a group to the array */
	CConfigGroup *AddGroup(const TCHAR *pName);

	/* Get a specific group */
	CConfigGroup *FindGroup(const TCHAR *pName);

	/* Get an existing group or create it */
	CConfigGroup *GetGroup(const TCHAR *pName);

	/* Get config values */
	const TCHAR *GetValue(const TCHAR *pVariable);
	const TCHAR *GetValue(const TCHAR *pGroup, const TCHAR *pVariable);
	const TCHAR *GetArrayValue(const TCHAR *pGroup, const TCHAR *pVariable, const int ID);
	const TCHAR *GetArrayValue(const TCHAR *pGroup, const TCHAR *pVariable, const int ID1,
	                           const TCHAR *pID2);

	/* Attempt to load and parse the given config file */
	bool LoadINI(const TCHAR *pFilename);

	/* Output the config data to the given filename */
	bool SaveINI(const TCHAR *pFilename);

	/* Set a variable value */
	bool SetValue(const TCHAR *pGroupName, const TCHAR *pVariable, const TCHAR *pValue);
	bool SetArrayValue(const TCHAR *pGroupName, const TCHAR *pVariable, const int ID,
	                   const TCHAR *pValue);
	bool SetArrayValue(const TCHAR *pGroupName, const TCHAR *pVariable, const int ID1,
	                   const TCHAR *pID2, const TCHAR *pValue);

	/* Get numeric values */
	float GetArrayReal(const TCHAR *pGroup, const TCHAR *pVariable, const int ID, const float Default);
	float GetArrayReal(const TCHAR *pGroup, const TCHAR *pVariable, const int ID1, const TCHAR *pID2,
	                   const float Default);
	int GetArrayInt(const TCHAR *pGroup, const TCHAR *pVariable, const int ID, const int Default);
	int GetArrayInt(const TCHAR *pGroup, const TCHAR *pVariable, const int ID1, const int ID2,
	                const int Default);
	int GetArrayInt(const TCHAR *pGroup, const TCHAR *pVariable, const int ID1, const TCHAR *pID2,
	                const int Default);
	bool GetArrayBool(const TCHAR *pGroup, const TCHAR *pVariable, const int ID, const bool Default);
	float GetReal(const TCHAR *pGroup, const TCHAR *pVariable, const float Default);
	int GetInt(const TCHAR *pGroup, const TCHAR *pVariable, const int Default);
	bool GetBool(const TCHAR *pGroup, const TCHAR *pVariable, const bool Default);

	/* Set numeric values */
	bool SetArrayReal(const TCHAR *pGroup, const TCHAR *pVariable, const int ID, const float Value);
	bool SetArrayReal(const TCHAR *pGroup, const TCHAR *pVariable, const int ID1, const TCHAR *pID2,
	                  const float Value);
	bool SetArrayInt(const TCHAR *pGroup, const TCHAR *pVariable, const int ID, const int Value);
	bool SetArrayInt(const TCHAR *pGroup, const TCHAR *pVariable, const int ID1, const TCHAR *pID2,
	                 const int Value);
	bool SetArrayInt(const TCHAR *pGroup, const TCHAR *pVariable, const int ID1, const int ID2,
	                 const int Value);
	bool SetArrayBool(const TCHAR *pGroup, const TCHAR *pVariable, const int ID, const bool Value);
	bool SetReal(const TCHAR *pGroup, const TCHAR *pVariable, const float Value);
	bool SetInt(const TCHAR *pGroup, const TCHAR *pVariable, const int Value);
	bool SetBool(const TCHAR *pGroup, const TCHAR *pVariable, const bool Value);

};

/*===========================================================================
 *      End of Class CConfigFile Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Configfile.H
 *=========================================================================*/
