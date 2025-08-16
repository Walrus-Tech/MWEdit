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


#include "EsmSubBase.h"


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
 *
 * Begin Class CEsmSubWEAT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubWEAT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubWEAT();
	//virtual ~CEsmSubWEAT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubWEAT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(weatherdata_t));
		m_RecordSize = sizeof(weatherdata_t);
		memset(m_pData, 0, sizeof(weatherdata_t));
	}

	/* Get class members */
	weatherdata_t *GetWeatherData() {
		return (weatherdata_t *)m_pData;
	}

	byte GetClear() {
		return GetWeatherData()->Clear;
	}

	byte GetCloudy() {
		return GetWeatherData()->Cloudy;
	}

	byte GetFoggy() {
		return GetWeatherData()->Foggy;
	}

	byte GetOvercast() {
		return GetWeatherData()->Overcast;
	}

	byte GetRain() {
		return GetWeatherData()->Rain;
	}

	byte GetThunder() {
		return GetWeatherData()->Thunder;
	}

	byte GetAsh() {
		return GetWeatherData()->Ash;
	}

	byte GetBlight() {
		return GetWeatherData()->Blight;
	}

	/* Set class members */
	void SetClear(const byte Value) {
		GetWeatherData()->Clear = Value;
	}

	void SetCloudy(const byte Value) {
		GetWeatherData()->Cloudy = Value;
	}

	void SetFoggy(const byte Value) {
		GetWeatherData()->Foggy = Value;
	}

	void SetOvercast(const byte Value) {
		GetWeatherData()->Overcast = Value;
	}

	void SetRain(const byte Value) {
		GetWeatherData()->Rain = Value;
	}

	void SetThunder(const byte Value) {
		GetWeatherData()->Thunder = Value;
	}

	void SetAsh(const byte Value) {
		GetWeatherData()->Ash = Value;
	}

	void SetBlight(const byte Value) {
		GetWeatherData()->Blight = Value;
	}
};


#endif
