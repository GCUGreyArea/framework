/**
 * @file RdFile.h
 * @author Barry Robinson (barry.w.robinson@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-10-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __RD_FILE__
#define __RD_FILE__

#include "Base.h"

class RdFile : private Base {
    
public:
    RdFile();
    RdFile(const char * path);
    RdFile(std::string & path);
    RdFile(const char * path, size_t readBlockSize);
    RdFile(std::string & path, size_t readBlockSize);
    RdFile(RdFile & fl);
    ~RdFile();

    bool openFile();
    const unsigned char * getNexFileBuffer();
    const unsigned char * getCurrentFileBuffer() {return mBuffer;}
    size_t getLastReadSize();
    size_t getBuffReadSize();
    RdFile & operator=(RdFile & fl);

protected:
    constexpr const static size_t DEF_REABLOCK = 1024;
    constexpr const static size_t FILE_READ_MAX = -1;

private:
    std::string mPath;       //!< Path to file 
    FILE * mFilePointer;     //!< Pointer to the file handle
    unsigned char * mBuffer; //!< Buffer for file reads
    size_t mReadSize;        //!< Size of buffer for file reads and max read size
    size_t mLastReadSz;      //!< Last read size and content of buffer size
    size_t mFileSize;        //!< Actual file size in bytes
    size_t mReadTotal;       //!< Total number of bytes read from the file
};

#endif//__RD_FILE__