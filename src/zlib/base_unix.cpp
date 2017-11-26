#include "base.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "zassert.h"

////////////////////////////////////////////////////////////////////////////////
//
// Helper Functions
//
////////////////////////////////////////////////////////////////////////////////

bool IsWindows9x()
{
    return false;
}

class ZFilePrivate
{
public:
	~ZFilePrivate()
	{
        if (m_fileHandle != -1)
            close(m_fileHandle);
	}
public:
    int m_fileHandle = -1;
	PathString m_pathString; // BT - STEAM
    void* m_p = nullptr;
    bool m_mapped = false;
};

////////////////////////////////////////////////////////////////////////////////
//
// ZFile
//
////////////////////////////////////////////////////////////////////////////////

// BUILD_DX9: added for DX9 but can stay for DX7 as well
ZFile::ZFile( ) :
	d(new ZFilePrivate)
{
}


ZFile::ZFile(const PathString& strPath, FileFlags mode) :
	d(new ZFilePrivate)
{
#warning FIXME !!!
    int how = 0;
    if (mode & ReadWrite)
        how = O_RDWR;
    d->m_pathString = strPath;
    d->m_fileHandle = open(strPath, how);
}

ZFile::~ZFile()
{
    if (d->m_p && d->m_mapped) {
        int res = munmap(d->m_p, GetLength());
        ZAssert(res == 0);
    }
}

bool ZFile::IsValid()
{
     return d->m_fileHandle != -1;
}

uint32_t ZFile::Read(void* p, uint32_t length)
{
    return read(d->m_fileHandle, p, length);
}

uint32_t ZFile::Write(void* p, uint32_t length)
{
    uint32_t cbActual = write(d->m_fileHandle, p, length);

    ZAssert(cbActual == length);

    return cbActual;
}

bool ZFile::Write(const ZString& str)
{
    return (Write((void*)(PCC)str, str.GetLength()) != 0);
}

bool  ZFile::WriteString(const ZString& str)
{
    return (Write((void*)(PCC)str, str.GetLength() + 1) != 0);
}

bool  ZFile::WriteAlignedString(const ZString& str)
{
    int length = str.GetLength() + 1;

    if (Write((void*)(PCC)str, str.GetLength() + 1) != 0) {
        return WritePad(length);
    }

    return false;
}

bool ZFile::WritePad(int length)
{
    static uint8_t zeros[] = { 0, 0, 0 };
    int pad = 4 - (length & 3);

    if (pad != 4) {
        return (Write(zeros, pad) != 0);
    }

    return true;
}

bool ZFile::Write(uint32_t value)
{
    return (Write(&value, 4) != 0);
}

bool ZFile::Write(int value)
{
    return (Write(&value, 4) != 0);
}

bool ZFile::Write(float value)
{
    return (Write(&value, 4) != 0);
}

int ZFile::GetLength()
{
    auto current = lseek(d->m_fileHandle, 0, SEEK_CUR);
    auto size = lseek(d->m_fileHandle, 0, SEEK_END);
    lseek(d->m_fileHandle, current, SEEK_SET);
    return size;
}

uint8_t* ZFile::GetPointer(bool bWrite, bool bCopyOnWrite)
{
    ZAssert(!bWrite || !bCopyOnWrite);

    if (d->m_p == nullptr) {
         d->m_mapped = true;
         d->m_p = mmap(nullptr, GetLength(), PROT_READ | bWrite ? PROT_WRITE : 0, MAP_PRIVATE, d->m_fileHandle, 0);
    }

    return (uint8_t*)d->m_p;
}

void ZFile::SetPointer(uint8_t * ptr)
{
	d->m_p = ptr;
}

ZWriteFile::ZWriteFile(const PathString& strPath) :
    ZFile(strPath, ReadWrite | Truncate)
{
}

// KGJV 32B - added Tell and Seek
long   ZFile::Tell()
{
    return lseek(d->m_fileHandle, 0, SEEK_CUR);
}
int   ZFile::Seek(long offset, int origin)
{
    return lseek(d->m_fileHandle, offset, origin);
}

// BT - Steam
// https://social.msdn.microsoft.com/Forums/vstudio/en-US/c43c3b36-c698-45da-89f4-ecd0e825c059/implementing-sha1-hash-using-windows-cryptography-api-and-c?forum=vcgeneral
ZString ZFile::GetSha1Hash()
{
    return {};
}

// BT - STEAM
// https://stackoverflow.com/questions/27217063/how-to-read-filename-of-the-last-modified-file-in-a-directory
uint64_t ZFile::GetMostRecentFileModificationTime(ZString &searchPath)
{
    return 0;
}
