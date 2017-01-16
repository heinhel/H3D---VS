#include "FileSystem.hpp"
#include <Windows.h>
#include "Utilities.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of MemoryStream
/////////////////////////////////////////////////////////////////
h3d::MemoryStream::MemoryStream() {
	m_bufferPtr = NULL;
	m_bufferSize = m_currentPos = 0;
}
h3d::MemoryStream::~MemoryStream() {
	m_bufferPtr = NULL;
	m_bufferSize = m_currentPos = 0;
}
/////////////////////////////////////////////////////////////////
void h3d::MemoryStream::open(char* buffer,unsigned long size)
{
	m_bufferPtr  = &buffer;
	m_bufferSize = size;
	m_currentPos = 0;
}
void h3d::MemoryStream::close()
{
	m_bufferPtr = NULL;
	m_bufferSize = 0;
}
/////////////////////////////////////////////////////////////////
char* h3d::MemoryStream::read(unsigned long bytes) 
{
	if (bytes + m_currentPos > m_bufferSize)
	{
		static char* tempBuffer;
		tempBuffer = new char[bytes];
		memcpy(tempBuffer, *m_bufferPtr+m_currentPos, bytes);
		return tempBuffer;
	}
	else return nullptr;
}
/////////////////////////////////////////////////////////////////
// Implementations for FileHandle
/////////////////////////////////////////////////////////////////
h3d::FileHandle::FileHandle() 
{
	
}
h3d::FileHandle::~FileHandle() 
{

}
/////////////////////////////////////////////////////////////////
bool h3d::FileHandle::open(std::string path, int param)
{
	DWORD dwShareMode;

	m_fileHandle = CreateFile((LPWSTR)path.c_str(),
							  GENERIC_READ | GENERIC_WRITE,
							  dwShareMode,
							  NULL,
							  OPEN_EXISTING,
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
	if (m_fileHandle == INVALID_HANDLE_VALUE)
	{
		Log.error("Unable to open %s",path.c_str());
		return false;
	}
}
bool h3d::FileHandle::close()
{
	CloseHandle(m_fileHandle);
}
/////////////////////////////////////////////////////////////////
unsigned long h3d::FileHandle::read(char* dst, size_t size)
{
	
}
unsigned long h3d::FileHandle::write(char* src, size_t size)
{

}
/////////////////////////////////////////////////////////////////
unsigned long h3d::FileHandle::getIterPos()
{
	
}
unsigned long h3d::FileHandle::setIterPos(unsigned long val)
{

}
/////////////////////////////////////////////////////////////////
unsigned long h3d::FileHandle::getFileSize() {
	return m_fileSizeBytes;
}
std::string   h3d::FileHandle::getFilePath() {
	return m_filePath;
}
bool          h3d::FileHandle::isOpen() {
	return m_isOpen;
}
/////////////////////////////////////////////////////////////////