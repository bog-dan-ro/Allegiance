#pragma once
#ifndef NO_STEAM

#include <tvector.h>
#include <steam_api.h>
#include "CallsignTagInfo.h"

// BT - STEAM

class SteamClans
{
private:
	TVector<CallsignTagInfo, DefaultEquals, DefaultCompare>	m_availableCallsignTags; 
	bool m_officerDataReceived = false;

	void OnClanOfficerListResponse(ClanOfficerListResponse_t *pCallback, bool bIOFailure);
    CCallResult< SteamClans, ClanOfficerListResponse_t > m_SteamCallResultClanOfficerListResponse;

public:
	SteamClans();

	TVector<CallsignTagInfo, DefaultEquals, DefaultCompare> * GetAvailableCallsignTags();
};

#endif
