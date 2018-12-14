// Lowell Crook, Grant Daly, Matthew Larrimore, Billy McAllister
// CSC 322-101
// File System Project Part 3

#ifndef HEADER_H_
#define HEADER_H_
#include <iostream>
#include <fstream>
#include <conio.h>	
#include <cstdlib>		
#include <time.h> 
#include <string>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

//****************************** Statics ***************************************
static const int emptyWord = 65535; //just a word
static const int sectorSize = 65536;  // in bytes
int nextFreeWord; //next free word to write to.
// const bool debug_mode = false;
static const bool debug_class = false;
static const bool debug_part3 = true;
static const bool debug_part1 = false;
size_t wordSize = 2;

//****************************** CSC322FILE Class ******************************
class CSC322FILE 
{
	private:
		//********* Written on drive **********
		short valid;
		short length;
		short leftovers;
		char fileName[65];
		char* data;
		//*********Kept in memory **********
		int origin;
		long offSet;
		char* fileNamePtr = fileName; 
		bool binary;
		bool write;
		bool read;
		bool append;
		bool plus;

	public:
		//********* Constructors ***********
		CSC322FILE();
		CSC322FILE(const char* fileNamePtrNPT);
		CSC322FILE(short validNPT, const char* fileNamePtrNPT);
		CSC322FILE::CSC322FILE(const char* fileNamePtrNPT, bool read, bool write, bool append, bool plus, bool binary);
		//********* Destructor ***********
		~CSC322FILE();
		//********* Setters ***********
		bool setFileName(const char fileNameINPT[]);
		void setLength(short lengthINPT);
		bool setValid(short ValidNPT);
		bool setOrigin(int originNPT);
		bool setLeftovers(short leftoversNPT);
		void setData(char* data);
		bool setOffSet(long offSetNPT); 
		bool setBinary(bool binaryBool);
		bool setWrite(bool writeBool);
		bool setRead(bool readBool);
		bool setAppend(bool appendBool);
		bool setPlus(bool plusBool);
		//********* Getters ************
		char* getFileName();
		char* getDataPointer();
		short getValid();
		int getOrigin();
		short getLength(); 
		short getLeftovers();
		long getOffSet();
		char *  CSC322FILE::getData();
		bool getBinary();
		bool getWrite();
		bool getRead();
		bool getAppend();
		bool getPlus();
		//********* Functions **********
		void CSC322FILE::prettyPrint();
};

//****************************** Part 3 Functions ******************************
CSC322FILE* CSC322_fopen(const char *filename, const char *mode);
int CSC322_fclose(CSC322FILE *stream);
int CSC322_fread(void *buffer, size_t nBytes, CSC322FILE *stream);
int CSC322_fwrite(void *buffer, size_t nBytes, CSC322FILE *stream);

int CSC322_fseek(CSC322FILE *stream, long filePointer, int origin);
long CSC322_ftell(CSC322FILE *stream);
int CSC322_remove(const char *path);

//******************************** Our Functions *********************************
int writeCharPt(char* data, int length, int address);
//int readCharPt(char* data, int length, int address);
bool readHeader(CSC322FILE * stream, int address);
int findFreeLocation();
CSC322FILE* findFile(const char* filename);

//****************************** Part 1 Functions ******************************
void eraseAllSectors();
void eraseSector(int nSectorNr);
bool writeWord(int nAddress, char* nWord);
int readCharPt(char* data, int length, int address);
char * readWord(int nAddress);
void file();
void wait();




#endif