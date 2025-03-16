/*===========================================================================
 *
 * File:    EsmSubWEAT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBWEAT_H
#define __ESMSUBWEAT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

typedef struct {
	byte Clear;
	byte Cloudy;
	byte Foggy;
	byte Overcast;
	byte Rain;
	byte Thunder;
	byte Ash;
	byte Blight;
} weatherdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubWEAT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubWEAT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubWEAT();
	//virtual ~CEsmSubWEAT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubWEAT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(weatherdata_t));
		m_RecordSize = sizeof(weatherdata_t);
		memset(m_pData, 0, sizeof(weatherdata_t));
	}

	/* Get class members */
	weatherdata_t *GetWeatherData (void) {
		return ((weatherdata_t *) m_pData);
	}

	byte GetClear (void) {
		return (GetWeatherData()->Clear);
	}

	byte GetCloudy (void) {
		return (GetWeatherData()->Cloudy);
	}

	byte GetFoggy (void) {
		return (GetWeatherData()->Foggy);
	}

	byte GetOvercast (void) {
		return (GetWeatherData()->Overcast);
	}

	byte GetRain (void) {
		return (GetWeatherData()->Rain);
	}

	byte GetThunder (void) {
		return (GetWeatherData()->Thunder);
	}

	byte GetAsh (void) {
		return (GetWeatherData()->Ash);
	}

	byte GetBlight (void) {
		return (GetWeatherData()->Blight);
	}

	/* Set class members */
	void SetClear (const byte Value) {
		GetWeatherData()->Clear = Value;
	}

	void SetCloudy (const byte Value) {
		GetWeatherData()->Cloudy = Value;
	}

	void SetFoggy (const byte Value) {
		GetWeatherData()->Foggy = Value;
	}

	void SetOvercast (const byte Value) {
		GetWeatherData()->Overcast = Value;
	}

	void SetRain (const byte Value) {
		GetWeatherData()->Rain = Value;
	}

	void SetThunder (const byte Value) {
		GetWeatherData()->Thunder = Value;
	}

	void SetAsh (const byte Value) {
		GetWeatherData()->Ash = Value;
	}

	void SetBlight (const byte Value) {
		GetWeatherData()->Blight = Value;
	}

};

/*===========================================================================
 *      End of Class CEsmSubWEAT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubWEAT.H
 *=========================================================================*/

