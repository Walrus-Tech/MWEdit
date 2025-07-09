/*===========================================================================
 *
 * File:    Configfile.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, January 09, 2003
 *
 * Description
 *
 * 2 July 2003
 *  - Modified FindGroup() method to check for a 0-length group name.
 *
 *=========================================================================*/

/* Include Files */
#include "stdafx.h"
#include "cfgfile.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("CfgFile.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigEntry Method - bool Write (File);
 *
 * Output the entry to the current position in the file.  Returns false on
 * any error.
 *
 *=========================================================================*/
bool CConfigEntry::Write(CGenFile &File) {
	bool Result;
	/* Output the entry name and value */
	Result = File.Printf("%s = %s\n", m_Variable, m_Value);
	return Result;
}

/*===========================================================================
 *      End of Class Method CConfigEntry::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigGroup Method - void Destroy (void);
 *
 *=========================================================================*/
void CConfigGroup::Destroy() {
	CConfigEntry *pEntry;
	int Index;

	/* Unallocate all groups */
	for (Index = 0; Index < m_Entries.GetSize(); Index++) {
		pEntry = (CConfigEntry *)m_Entries.GetAt(Index);
		DestroyPointer(pEntry);
	}

	/* Clear the array */
	m_Entries.RemoveAll();
	m_Name.Empty();
}

/*===========================================================================
 *      End of Class Method CConfigGroup::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigGroup Method - CConfigEntry* AddEntry (pVar, pValue);
 *
 * Adds a new entry to the group.  Assumes that input strings are whitespace
 * trimmed already.  Does not check for duplicates.  Returns the new entry
 * pointer or NULL.
 *
 *=========================================================================*/
CConfigEntry *CConfigGroup::AddEntry(const TCHAR *pVar, const TCHAR *pValue) {
	DEFINE_FUNCTION("CConfigGroup::AddEntry()");
	CConfigEntry *pEntry;
	/* Allocate the new object */
	CreatePointer(pEntry, CConfigEntry);
	pEntry->SetVariable(pVar);

	if (pValue != NULL) {
		pEntry->SetValue(pValue);
	} else {
		pEntry->SetValue("");
	}

	m_Entries.Add(pEntry);
	return pEntry;
}

/*===========================================================================
 *      End of Class Method CConfigGroup::AddEntry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigGroup Method - CConfigEntry* FindEntry (pVariable);
 *
 * Returns the entry with the given variable name, or NULL.
 *
 *=========================================================================*/
CConfigEntry *CConfigGroup::FindEntry(const TCHAR *pVariable) {
	DEFINE_FUNCTION("CConfigGroup::FindEntry()");
	CConfigEntry *pEntry;
	int Result;
	int Index;
	/* Ensure valid input */
	ASSERT(pVariable != NULL);

	/* Search all defined entries */
	for (Index = 0; Index < m_Entries.GetSize(); Index++) {
		pEntry = (CConfigEntry *)m_Entries.GetAt(Index);
		Result = stricmp(pVariable, pEntry->GetVariable());

		if (Result == 0) {
			return pEntry;
		}
	}

	return NULL;
}

/*===========================================================================
 *      End of Class Method CConfigGroup::FindEntry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigGroup Method - CConfigEntry* GetEntry (pVariable);
 *
 * Finds an existing entry or creates it if it does not exist.
 *
 *=========================================================================*/
CConfigEntry *CConfigGroup::GetEntry(const TCHAR *pVariable) {
	DEFINE_FUNCTION("CConfigGroup::GetEntry()");
	CConfigEntry *pEntry;
	/* Find an existing variable */
	pEntry = FindEntry(pVariable);

	if (pEntry != NULL) {
		return pEntry;
	}

	/* Create a new variable entry */
	pEntry = AddEntry(pVariable, NULL);
	ASSERT(pEntry != NULL);
	return pEntry;
}

/*===========================================================================
 *      End of Class Method CConfigGroup::GetEntry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CConfigGroup Method - const GetValue (pVariable);
 *
 * Returns the value of the first variable, or NULL if it does not exist.
 *
 *=========================================================================*/
const TCHAR *CConfigGroup::GetValue(const TCHAR *pVariable) {
	CConfigEntry *pEntry = FindEntry(pVariable);

	if (pEntry == NULL) {
		return NULL;
	}

	return pEntry->GetValue();
}

/*===========================================================================
 *      End of Class Method TCHAR* CConfigGroup::GetValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigGroup Method - bool SetValue (pVariable, pValue);
 *
 * Modifies an existing variable value or creates it if it does not exist.
 *
 *=========================================================================*/
bool CConfigGroup::SetValue(const TCHAR *pVariable, const TCHAR *pValue) {
	CConfigEntry *pEntry;
	/* Find or create the entry */
	pEntry = GetEntry(pVariable);
	pEntry->SetValue(pValue);
	return true;
}

/*===========================================================================
 *      End of Class Method CConfigGroup::SetValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigGroup Method - bool Write (File);
 *
 * Output the group to the current position in the file.  Returns false on
 * any error.
 *
 *=========================================================================*/
bool CConfigGroup::Write(CGenFile &File) {
	CConfigEntry *pEntry;
	int Index;
	bool Result;

	/* Output the group name if not empty */
	if (m_Name.GetLength() > 2) {
		Result = File.Printf("%s\n", m_Name);

		if (!Result) {
			return false;
		}
	}

	/* Output all entries in group */
	for (Index = 0; Index < m_Entries.GetSize(); Index++) {
		pEntry = (CConfigEntry *)m_Entries.GetAt(Index);
		Result = pEntry->Write(File);
	}

	return true;
}

/*===========================================================================
 *      End of Class Method CConfigGroup::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Constructor
 *
 *=========================================================================*/
CConfigFile::CConfigFile() : m_Groups(2) {
	//DEFINE_FUNCTION("CConfigFile::CConfigFile()");
}

/*===========================================================================
 *      End of Class CConfigFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - void Destroy (void);
 *
 *=========================================================================*/
void CConfigFile::Destroy() {
	DEFINE_FUNCTION("CConfigFile::Destroy()");
	CConfigGroup *pGroup;
	int Index;

	/* Unallocate all groups */
	for (Index = 0; Index < m_Groups.GetSize(); Index++) {
		pGroup = (CConfigGroup *)m_Groups.GetAt(Index);
		DestroyPointer(pGroup);
	}

	/* Clear the array */
	m_Groups.RemoveAll();
	/* Call the base class method */
	CGenFile::Destroy();
}

/*===========================================================================
 *      End of Class Method CConfigFile::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - CConfigGroup* AddGroup (pName);
 *
 * Adds a new group to the array, returns the new array object or NULL.
 * Adds the [] brackets to the group name if not already included.
 *
 *=========================================================================*/
CConfigGroup *CConfigFile::AddGroup(const TCHAR *pName) {
	DEFINE_FUNCTION("CConfigFile::AddGroup()");
	CConfigGroup *pGroup;
	TCHAR Buffer[CONFIG_LINE_LENGTH + 1];
	/* Create the group */
	CreatePointer(pGroup, CConfigGroup);

	if (*pName == (TCHAR)'[') {
		pGroup->SetName(pName);
	} else {
		snprintf(Buffer, CONFIG_LINE_LENGTH, "[%s]", pName);
		pGroup->SetName(Buffer);
	}

	m_Groups.Add(pGroup);
	return pGroup;
}

/*===========================================================================
 *      End of Class Method CConfigFile::AddGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - const TCHAR* CreateArrayString (pVariable, ID);
 *
 * Protected class method which creates a variable-array string of the
 * format:
 *          'Variable[ID]'
 *          'Variable[ID1][ID2]'
 *          'Variable[ID1].ID2'
 *
 * Uses a static character buffer.
 *
 *=========================================================================*/
const TCHAR *CConfigFile::CreateArrayString(const TCHAR *pVariable, const int ID) {
	static TCHAR Buffer[CONFIG_LINE_LENGTH + 1];
	snprintf(Buffer, CONFIG_LINE_LENGTH, "%s[%d]", pVariable, ID);
	return Buffer;
}

const TCHAR *CConfigFile::CreateArrayString(const TCHAR *pVariable,
                                            const int ID1, const int ID2) {
	static TCHAR Buffer[CONFIG_LINE_LENGTH + 1];
	snprintf(Buffer, CONFIG_LINE_LENGTH, "%s[%d,%d]", pVariable, ID1, ID2);
	return Buffer;
}

const TCHAR *CConfigFile::CreateArrayString(const TCHAR *pVariable,
                                            const int ID1,
                                            const TCHAR *pID2) {
	static TCHAR Buffer[CONFIG_LINE_LENGTH + 1];
	snprintf(Buffer, CONFIG_LINE_LENGTH, "%s[%d].%s", pVariable, ID1, pID2);
	return Buffer;
}

/*===========================================================================
 *      End of Class Method CConfigFile::CreateArrayString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - CConfigGroup* FindGroup (pName);
 *
 * Gets the group with the given name, or NULL if it does not exist.  The
 * input group name can have the [] brackets or not.
 *
 *=========================================================================*/
CConfigGroup *CConfigFile::FindGroup(const TCHAR *pName) {
	DEFINE_FUNCTION("CConfigFile::FindGroup()");
	CConfigGroup *pGroup;
	int Result;
	int NameLength;
	int Index;
	/* Ensure valid input */
	ASSERT(pName != NULL);
	NameLength = strlen(pName);

	/* Search all defined groups */
	for (Index = 0; Index < m_Groups.GetSize(); Index++) {
		pGroup = (CConfigGroup *)m_Groups.GetAt(Index);

		if (*pName == '[') {
			Result = stricmp(pName, pGroup->GetName());
		} else if (NameLength == 0 && (pGroup->GetName())[1] == ']') {
			Result = 0;
		} else {
			Result = strnicmp(pName, (pGroup->GetName()) + 1, NameLength);
		}

		if (Result == 0) {
			return pGroup;
		}
	}

	/* No match found */
	return NULL;
}

/*===========================================================================
 *      End of Class Method CConfigFile::FindGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - CConfigGroup* GetGroup (pName);
 *
 * Finds an existing group or creates it if it does not exist.
 *
 *=========================================================================*/
CConfigGroup *CConfigFile::GetGroup(const TCHAR *pName) {
	DEFINE_FUNCTION("CConfigFile::GetGroup()");
	CConfigGroup *pGroup;
	/* Find an existing group */
	pGroup = FindGroup(pName);

	if (pGroup != NULL) {
		return pGroup;
	}

	/* Create it if is does not exist */
	pGroup = AddGroup(pName);
	ASSERT(pGroup != NULL);
	return pGroup;
}

/*===========================================================================
 *      End of Class Method CConfigFile::GetGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - ... GetArray... (pGroup, pVariable, ID, Default);
 *
 * Attempt to return the given array variable as a numeric value. The default
 * value is returned if the variable does not exist.  The array format  is
 * assumed to be
 *          pVariable[ID] = Value
 *
 *=========================================================================*/
const TCHAR *CConfigFile::GetArrayValue(const TCHAR *pGroup,
                                        const TCHAR *pVariable,
                                        const int ID) {
	return GetValue(pGroup, CreateArrayString(pVariable, ID));
}

const TCHAR *CConfigFile::GetArrayValue(const TCHAR *pGroup,
                                        const TCHAR *pVariable,
                                        const int ID1,
                                        const TCHAR *pID2) {
	return GetValue(pGroup, CreateArrayString(pVariable, ID1, pID2));
}

bool CConfigFile::GetArrayBool(const TCHAR *pGroup,
                               const TCHAR *pVariable,
                               const int ID,
                               const bool Default) {
	return GetBool(pGroup, CreateArrayString(pVariable, ID), Default);
}

int CConfigFile::GetArrayInt(const TCHAR *pGroup, const TCHAR *pVariable, const int ID,
                             const int Default) {
	return GetInt(pGroup, CreateArrayString(pVariable, ID), Default);
}

int CConfigFile::GetArrayInt(const TCHAR *pGroup,
                             const TCHAR *pVariable,
                             const int ID1,
                             const int ID2,
                             const int Default) {
	return GetInt(pGroup, CreateArrayString(pVariable, ID1, ID2), Default);
}

int CConfigFile::GetArrayInt(const TCHAR *pGroup,
                             const TCHAR *pVariable,
                             const int ID1,
                             const TCHAR *pID2,
                             const int Default) {
	return GetInt(pGroup, CreateArrayString(pVariable, ID1, pID2), Default);
}

float CConfigFile::GetArrayReal(const TCHAR *pGroup,
                                const TCHAR *pVariable,
                                const int ID,
                                const float Default) {
	return GetReal(pGroup, CreateArrayString(pVariable, ID), Default);
}

float CConfigFile::GetArrayReal(const TCHAR *pGroup,
                                const TCHAR *pVariable,
                                const int ID1,
                                const TCHAR *pID2,
                                const float Default) {
	return GetReal(pGroup, CreateArrayString(pVariable, ID1, pID2), Default);
}

/*===========================================================================
 *      End of Class Method CConfigFile::GetArray...()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - bool GetBool (pGroup, pVariable, Default);
 *
 * Attempt to return the given variable as a bool value. The default value
 * is returned if the variable does not exist.
 *
 *=========================================================================*/
bool CConfigFile::GetBool(const TCHAR *pGroup, const TCHAR *pVariable, const bool Default) {
	const TCHAR *pValue;
	/* Attempt to find the variable value */
	pValue = GetValue(pGroup, pVariable);

	if (pValue == NULL) {
		return Default;
	}

	/* Convert the string to a bool value */
	return StringToBoolean(pValue);
}

/*===========================================================================
 *      End of Class Method CConfigFile::GetBool()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - int GetInt (pGroup, pVariable, Default);
 *
 * Attempt to return the given variable as an integer value. The default value
 * is returned if the variable does not exist.
 *
 *=========================================================================*/
int CConfigFile::GetInt(const TCHAR *pGroup, const TCHAR *pVariable, const int Default) {
	const TCHAR *pValue;
	/* Attempt to find the variable value */
	pValue = GetValue(pGroup, pVariable);

	if (pValue == NULL) {
		return Default;
	}

	/* Convert the string to an integer value */
	return atoi(pValue);
}

/*===========================================================================
 *      End of Class Method CConfigFile::GetInt()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - float GetReal (pGroup, pVariable, Default);
 *
 * Attempt to return the given variable as a float value. The default value
 * is returned if the variable does not exist.
 *
 *=========================================================================*/
float CConfigFile::GetReal(const TCHAR *pGroup, const TCHAR *pVariable, const float Default) {
	const TCHAR *pValue;
	/* Attempt to find the variable value */
	pValue = GetValue(pGroup, pVariable);

	if (pValue == NULL) {
		return Default;
	}

	/* Convert the string to a float value */
	return (float)atof(pValue);
}

/*===========================================================================
 *      End of Class Method CConfigFile::GetReal()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CConfigFile Method - const GetValue (pVariable);
 *
 * Searches all groups and returns the first match of the given variable.
 * Returns NULL if it is not found.
 *
 *=========================================================================*/
const TCHAR *CConfigFile::GetValue(const TCHAR *pVariable) {
	DEFINE_FUNCTION("CConfigFile::GetValue()");
	CConfigGroup *pGroup;
	const TCHAR *pResult;
	int Index;
	/* Ensure valid input */
	ASSERT(pVariable != NULL);

	/* Search all defined groups */
	for (Index = 0; Index < m_Groups.GetSize(); Index++) {
		pGroup = (CConfigGroup *)m_Groups.GetAt(Index);
		pResult = pGroup->GetValue(pVariable);

		if (pResult != NULL) {
			return pResult;
		}
	}

	/* No match found */
	return NULL;
}

/*===========================================================================
 *      End of Class Method TCHAR* CConfigFile::GetValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CConfigFile Method - const GetValue (pGroup, pVariable);
 *
 * Searches the given group for the first occurence of the specified variable.
 * Returns NULL if it is not found.  The [] for the group can be present or
 * not.
 *
 *=========================================================================*/
const TCHAR *CConfigFile::GetValue(const TCHAR *pGroupName, const TCHAR *pVariable) {
	DEFINE_FUNCTION("CConfigFile::GetValue()");
	CConfigGroup *pGroup;
	/* Ensure valid input */
	ASSERT(pGroupName != NULL && pVariable != NULL);
	/* Attempt to find the matching group name */
	pGroup = FindGroup(pGroupName);

	if (pGroup == NULL) {
		return NULL;
	}

	/* Search the groups */
	return pGroup->GetValue(pVariable);
}

/*===========================================================================
 *      End of Class Method TCHAR* CConfigFile::GetValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - bool LoadINI (pFilename);
 *
 * Attempt to load and parse the given config file, returns false on any error.
 *
 *=========================================================================*/
bool CConfigFile::LoadINI(const TCHAR *pFilename) {
	CConfigGroup *pReadingGroup;
	bool Result;
	char Buffer[CONFIG_LINE_LENGTH + 1];
	char *pVariable;
	char *pValue;
	int iResult;
	/* Delete the current config content */
	Destroy();
	/* Attempt to open the file for input */
	Result = Open(pFilename, "rt");

	if (!Result) {
		return false;
	}

	/* Create the root level group */
	pReadingGroup = AddGroup("");

	/* Read and parse entire file */
	while (!IsEOF()) {
		/* Input one line from file */
		iResult = ReadLine(Buffer, CONFIG_LINE_LENGTH);

		if (iResult == READLINE_ERROR) {
			Close();
			return false;
		}

		/* Parse input line */
		Result = SeperateVarValue(&pVariable, &pValue, Buffer, (TCHAR)'=', NULL_CHAR);

		/* Check for start of new group */
		if (!Result && *pVariable == (TCHAR)'[') {
			pReadingGroup = AddGroup(pVariable);
		} else if (pReadingGroup != NULL && Result) { /* Else add entry to current group */
			pReadingGroup->AddEntry(pVariable, pValue);
		}
	}

	Close();
	return true;
}

/*===========================================================================
 *      End of Class Method CConfigFile::LoadINI()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - bool SaveINI (pFilename);
 *
 * Outputs the config file to the given filename, returns false on any error.
 *
 *=========================================================================*/
bool CConfigFile::SaveINI(const TCHAR *pFilename) {
	CConfigGroup *pGroup;
	bool Result;
	int Index;
	/* Attempt to open file for output */
	Result = Open(pFilename, "wt");

	if (!Result) {
		return false;
	}

	/* Output all groups in config */
	for (Index = 0; Index < m_Groups.GetSize(); Index++) {
		pGroup = (CConfigGroup *)m_Groups.GetAt(Index);
		Result = pGroup->Write(*this);

		if (!Result) {
			Close();
			return false;
		}
	}

	Close();
	return true;
}

/*===========================================================================
 *      End of Class Method CConfigFile::SaveINI()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - bool SetArray... (pGroup, pVariable, ID, Value);
 *
 * Sets or creates the given config array variable to the specific numeric value.
 * Returns false on any error.  Assumes that the array variable format is:
 *
 *          Variable[ID] = Value
 *
 *=========================================================================*/
bool CConfigFile::SetArrayValue(const TCHAR *pGroup,
                                const TCHAR *pVariable,
                                const int ID,
                                const TCHAR *pValue) {
	return SetValue(pGroup, CreateArrayString(pVariable, ID), pValue);
}

bool CConfigFile::SetArrayValue(const TCHAR *pGroup,
                                const TCHAR *pVariable,
                                const int ID1,
                                const TCHAR *pID2,
                                const TCHAR *pValue) {
	return SetValue(pGroup, CreateArrayString(pVariable, ID1, pID2), pValue);
}

bool CConfigFile::SetArrayBool(const TCHAR *pGroup,
                               const TCHAR *pVariable,
                               const int ID,
                               const bool Value) {
	return SetBool(pGroup, CreateArrayString(pVariable, ID), Value);
}

bool CConfigFile::SetArrayInt(const TCHAR *pGroup,
                              const TCHAR *pVariable,
                              const int ID,
                              const int Value) {
	return SetInt(pGroup, CreateArrayString(pVariable, ID), Value);
}

bool CConfigFile::SetArrayInt(const TCHAR *pGroup,
                              const TCHAR *pVariable,
                              const int ID1,
                              const int ID2,
                              const int Value) {
	return SetInt(pGroup, CreateArrayString(pVariable, ID1, ID2), Value);
}

bool CConfigFile::SetArrayInt(const TCHAR *pGroup,
                              const TCHAR *pVariable,
                              const int ID1,
                              const TCHAR *pID2,
                              const int Value) {
	return SetInt(pGroup, CreateArrayString(pVariable, ID1, pID2), Value);
}

bool CConfigFile::SetArrayReal(const TCHAR *pGroup,
                               const TCHAR *pVariable,
                               const int ID,
                               const float Value) {
	return SetReal(pGroup, CreateArrayString(pVariable, ID), Value);
}

bool CConfigFile::SetArrayReal(const TCHAR *pGroup,
                               const TCHAR *pVariable,
                               const int ID1,
                               const TCHAR *pID2,
                               const float Value) {
	return SetReal(pGroup, CreateArrayString(pVariable, ID1, pID2), Value);
}

/*===========================================================================
 *      End of Class Method CConfigFile::SetArray...()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - bool SetBool (pGroup, pVariable, Value);
 *
 * Sets or creates the given config variable to the specific boolean value.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CConfigFile::SetBool(const TCHAR *pGroup, const TCHAR *pVariable, const bool Value) {
	return SetValue(pGroup, pVariable, BooleanToString(Value));
}

/*===========================================================================
 *      End of Class Method CConfigFile::SetBool()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - bool SetInt ( pGroup, pVariable, Value);
 *
 * Sets or creates the given config variable to the specific integer value.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CConfigFile::SetInt(const TCHAR *pGroup, const TCHAR *pVariable, const int Value) {
	TCHAR Buffer[64];
	sprintf(Buffer, "%d", Value);
	return SetValue(pGroup, pVariable, Buffer);
}

/*===========================================================================
 *      End of Class Method CConfigFile::SetInt()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - bool SetReal (pGroup, pVariable, Value);
 *
 * Sets or creates the given config variable to the specific float value.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CConfigFile::SetReal(const TCHAR *pGroup, const TCHAR *pVariable, const float Value) {
	TCHAR Buffer[64];
	sprintf(Buffer, "%g", Value);
	return SetValue(pGroup, pVariable, Buffer);
}

/*===========================================================================
 *      End of Class Method CConfigFile::SetReal()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CConfigFile Method - bool SetValue (pGroupName, pVariable, pValue);
 *
 * Sets the given variable value.  Creates the variable if it does not
 * exist.  Returns false on any error.
 *
 *=========================================================================*/
bool CConfigFile::SetValue(const TCHAR *pGroupName, const TCHAR *pVariable, const TCHAR *pValue) {
	CConfigGroup *pGroup;
	/* Find the group and create if it does not exist */
	pGroup = GetGroup(pGroupName);
	/* Set the entry value */
	return pGroup->SetValue(pVariable, pValue);
}

/*===========================================================================
 *      End of Class Method CConfigFile::SetValue()
 *=========================================================================*/
