#pragma once

#include <cstdint>
#include <zstring.h>

// BT - STEAM
class CallsignTagInfo
{
private:
	
    ZString FixupCallsignTag(ZString callsignTag);
	void LoadFromRegistry();
	void SaveToRegistry();
	void UpdateStringValues(ZString selectedToken);

public:
	ZString m_callsignTag;
	ZString m_callsignToken;
    uint64_t m_steamGroupID;
	int		m_index;
	bool	m_isOfficer;

	CallsignTagInfo();
    CallsignTagInfo(ZString callsignTag, uint64_t steamGroupID, int index, bool isOfficer);

	ZString GetAvailableTokens();
	
    void SetSteamGroupID(uint64_t steamGroupID, ZString callsignTag);
	void SetToken(ZString token);

	ZString Render(ZString callsign);


	inline bool operator == (const CallsignTagInfo& compare) const { return m_steamGroupID == compare.m_steamGroupID; }
	inline  bool operator > (const CallsignTagInfo& compare) const { return m_steamGroupID > compare.m_steamGroupID; }

};
