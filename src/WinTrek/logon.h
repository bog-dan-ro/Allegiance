#ifndef _logon_h_
#define _logon_h_

#include <zstring.h>

//////////////////////////////////////////////////////////////////////////////
//
// logon
//
//////////////////////////////////////////////////////////////////////////////

class LogonSite : public IObject {
public:
    virtual void OnLogon(const ZString& strName, const ZString& strPassword, BOOL fRememberPW) = 0;
    virtual void OnAbort() = 0;
};

enum LogonType
{
  LogonAllegianceZone,
  LogonFreeZone,
  LogonLAN,
};

class IPopup;
class Modeler;
TRef<IPopup> CreateLogonPopup(Modeler* pmodeler, LogonSite* psite, LogonType lt, 
                              LPCSTR szPrompt, LPCSTR szName, LPCSTR szPW, BOOL fRememberPW);

#endif
