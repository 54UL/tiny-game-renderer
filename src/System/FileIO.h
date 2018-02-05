#pragma once
#include <iostream>



class FileIO
{
public:

	FileIO();
	~FileIO();

	//Read functions
	bool ReadFile(const char * fname);//returns the whole file in an char array
	//WriteFuctions
	
	//misc functions
	 int getFsize();
	 char * getFbuffer();//Gets the last read of the file data 
	 
	 bool isOpen();

	 const char operator[](std::size_t Index);
private:
	bool Status;
	int    m_FileSize;
	char * m_buffer;
};

