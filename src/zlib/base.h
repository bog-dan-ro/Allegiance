//////////////////////////////////////////////////////////////////////////////
//
// Base
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _base_h_
#define _base_h_

#include <memory>

#include "tref.h"
#include "zstring.h"

////////////////////////////////////////////////////////////////////////////////
//
// Helper Functions
//
////////////////////////////////////////////////////////////////////////////////

bool IsWindows9x();

////////////////////////////////////////////////////////////////////////////////
//
// File
//
////////////////////////////////////////////////////////////////////////////////
class ZFilePrivate;
class ZFile : public IObject {
protected:
	std::unique_ptr<ZFilePrivate> d;
public:
    enum FileFlags {
        ReadOnly = 1 << 0,
        WriteOnly = 1 << 1,
        ReadWrite = ReadOnly | WriteOnly,
        Append = 1 << 2,
        Truncate = 1 << 3
    };

public:
	ZFile(); // BUILD_DX9: added for DX9 but can stay for DX7 as well

    ZFile(const PathString& strPath, FileFlags mode = ReadOnly);
    virtual ~ZFile();

    virtual bool  IsValid();
    virtual int   GetLength();
    virtual uint8_t * GetPointer(bool bWrite = false, bool bCopyOnWrite = false);
	virtual void SetPointer(uint8_t * ptr);
    virtual uint32_t Read(void* p, uint32_t length);
    uint32_t Write(void* p, uint32_t length);

    bool  Write(uint32_t value);
    bool  Write(int   value);
    bool  Write(float value);
    bool  Write(const ZString& str);
    bool  WriteString(const ZString& str);
    bool  WriteAlignedString(const ZString& str);
    bool  WritePad(int length);
//KGJV 32B - added Tell and Seek
    long  Tell();
    int   Seek(long offset, int origin);

    template<class Type>
    bool WriteStructure(const Type& value) 
    {
        return Write(&value, sizeof(Type));
    }

	// BT - STEAM
	ZString GetSha1Hash();
    static uint64_t GetMostRecentFileModificationTime(ZString &searchPath);
};

inline ZFile::FileFlags operator|(ZFile::FileFlags a, ZFile::FileFlags b)
{
    return ZFile::FileFlags(a | b);
}

class ZWriteFile : public ZFile {
public:
    ZWriteFile(const PathString& strPath);
};

#endif
