#include "FileIO.h"
#include <fstream>



FileIO::FileIO()
{
	Status = false;
}


FileIO::~FileIO()
{
	if (m_buffer != NULL)delete m_buffer;
}

bool FileIO::ReadFile(const char * fname)
{
	//Functions Variables
	std::ifstream FILE(fname, std::ifstream::binary);
	
	if (!FILE.is_open())
		return true;
	else
		Status = true;


	//GetTheSize
	FILE.seekg(0,FILE.end);
    m_FileSize = FILE.tellg();
	FILE.seekg(0,FILE.beg);

	m_buffer = new char[m_FileSize];
	for(int i =0;i<m_FileSize;i++)
	m_buffer[i] = FILE.get();
	FILE.close();
	return false;
}


 int FileIO::getFsize()
 {
	 return m_FileSize;
 }

 char * FileIO::getFbuffer()
 {
	 return m_buffer;
 }

 bool FileIO::isOpen()
 {
	 return false;
 }

 const char FileIO::operator[](std::size_t Index)
 {
	 return m_buffer[Index];
 }
