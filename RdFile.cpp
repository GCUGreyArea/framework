#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "RdFile.h"


RdFile::RdFile() :
    Base("RdFile"),
    mPath(nullptr),
    mFilePointer(nullptr),     
    mBuffer(nullptr),
    mReadSize(DEF_REABLOCK),        
    mLastReadSz(0),      
    mFileSize(0),        
    mReadTotal(0) {}

RdFile::RdFile(const char * path) :
    Base("RdFile"),
    mPath(path),
    mFilePointer(nullptr),     
    mBuffer(nullptr),
    mReadSize(DEF_REABLOCK),        
    mLastReadSz(0),      
    mFileSize(0),        
    mReadTotal(0) {}

RdFile::RdFile(std::string & path) :
    Base("RdFile"),
    mPath(path),
    mFilePointer(nullptr),     
    mBuffer(nullptr),
    mReadSize(DEF_REABLOCK),        
    mLastReadSz(0),      
    mFileSize(0),        
    mReadTotal(0) {}

RdFile::RdFile(const char * path, size_t readBlockSize) :
    Base("RdFile"),
    mPath(path),
    mFilePointer(nullptr),     
    mBuffer(nullptr),
    mReadSize(readBlockSize),        
    mLastReadSz(0),      
    mFileSize(0),        
    mReadTotal(0) {}

RdFile::RdFile(std::string & path, size_t readBlockSize) :
    Base("RdFile"),
    mPath(path),
    mFilePointer(nullptr),     
    mBuffer(nullptr),
    mReadSize(readBlockSize),        
    mLastReadSz(0),      
    mFileSize(0),        
    mReadTotal(0) {}

RdFile::RdFile(RdFile & fl) : 
    Base("RdFile"),
    mPath(fl.mPath),
    mFilePointer(nullptr),
    mReadSize(fl.mReadSize) {
        if(fl.mFilePointer) {
        // open the file and allocate everything
        openFile();

        // Set up the curruent pointer
        long pos = ftell(fl.mFilePointer);
        if(pos != -1) {
            fseek(mFilePointer, SEEK_SET, pos);
        }

        // Setup the last read
        mLastReadSz = fl.mLastReadSz;
        mFileSize   = fl.mFileSize;
        mReadTotal  = fl.mReadTotal;

        strncpy((char*)mBuffer,(const char*)fl.mBuffer,sizeof(unsigned char)*fl.mLastReadSz);
        mBuffer[mLastReadSz] = '\0';
    }
}


RdFile::~RdFile() {
    if(mFilePointer != nullptr) {
        fclose(mFilePointer);
        mFilePointer = nullptr;
    }

    if(mBuffer != nullptr) {
        delete [] mBuffer;
        mBuffer = nullptr;
    }

    mPath = "";
    mReadSize = 0;
    mFileSize = 0;
    mReadTotal = 0;
}

bool RdFile::openFile() {

    // First, test we have valid parrameters
    if(mPath == "") {
        fprintf(stderr,"ERROR: File path cannot be null\n");
        return false;
    }
    else if(access(mPath.c_str(), F_OK ) != 0) {
        fprintf(stderr,"ERROR: Cannot access file [%s]\n", mPath.c_str());
        return false;
    }

    // Open the file handle
    mFilePointer = fopen (mPath.c_str(), "r");
    if(mFilePointer == nullptr) {
        fprintf(stderr, "ERROR: Failed to open [file %s]\n", mPath.c_str());
        return false;
    }

    // Get the size of the file now incase wee need to allocate the total file size to the buufer
    fseek(mFilePointer, 0, SEEK_END);
    mFileSize = ftell(mFilePointer);
    // Reset the file handle to point to the start of the file
    fseek(mFilePointer, 0, SEEK_SET);


    // Now do the read size for the buffer
    if(mReadSize == FILE_READ_MAX) {
        mReadSize = mFileSize;
    }


    // Alocate one read block
    mBuffer = new unsigned char[mReadSize];
    if(mBuffer == nullptr) {
        return false;
    }

    return true;
}

/**
 * @brief Get the Nex File Buffer object
 *
 * @param fl The handle to the open file
 * @return const char* The buffer read to buffSize
 */
const unsigned char * RdFile::getNexFileBuffer() {
    if(mFilePointer == nullptr) {
        fprintf(stderr,"ERROR: File object is uninitialised, call openFile() before using!\n");
        return nullptr;
    }

    size_t readSz = 0;
    if(mReadSize <= (mFileSize - mReadTotal)) {
        readSz = mReadSize;
    }
    else {
        readSz = mFileSize - mReadTotal;
    }

    if(readSz == 0) return nullptr;

    int act = fread(mBuffer, readSz, 1, mFilePointer);
    if(act == 1) {
        mReadTotal += readSz;
        mLastReadSz = readSz;
        mBuffer[mLastReadSz] = '\0';
        return (const unsigned char*) mBuffer;
    }

    fprintf(stderr,"ERROR: Nothing read\n");
    return nullptr;
}

size_t RdFile::getLastReadSize() {
    if(mFilePointer != nullptr) {
        return mLastReadSz;
    }

    fprintf(stderr,"ERROR: file structure is uninitialized\n");
    return -1;
}


size_t RdFile::getBuffReadSize() {
    if(mFilePointer != nullptr) {
        return mReadSize;
    }

    fprintf(stderr,"ERROR: file structure is uninitialized\n");
    return -1;
}

RdFile & RdFile::operator=(RdFile & fl) {
    mPath     = fl.mPath;
    mReadSize = fl.mReadSize;
    
    // if the bufffer has been asigned then the file has been opened.
    if(fl.mFilePointer) {
        // open the file and allocate everything
        openFile();

        // Set up the curruent pointer
        long pos = ftell(fl.mFilePointer);
        if(pos != -1) {
            fseek(mFilePointer, SEEK_SET, pos);
        }

        // Setup the last read
        mLastReadSz = fl.mLastReadSz;
        mFileSize   = fl.mFileSize;
        mReadTotal  = fl.mReadTotal;

        strncpy((char*)mBuffer,(const char*)fl.mBuffer,sizeof(unsigned char)*fl.mLastReadSz);
        mBuffer[mLastReadSz] = '\0';
    }

    return *this;
}