// Lowell Crook, Grant Daly, Matthew Larrimore, Billy McAllister
// CSC 322-101
// File System Project

#include "Header.h"


using namespace std;


fstream drive;

#define validAlias 3
#define invalidAlias 2
#define leftoverAlias 3
#define noleftoverAlias 2
#define headerSZ 70


#pragma region *************************************************** Main ****************************************************************************

int main() 
{
	file();
	
	CSC322FILE * testFile = CSC322_fopen("test", "wb");
	char testArray[] = "testicular data awwwwwwwwwwwww yeaaaaaaaaaaaaaa thats right ";
	cout << CSC322_fwrite(testArray, sizeof(testArray) - 1, testFile);
	//char * temptemptemp = (char*)malloc((testFile->getLength()+1) * sizeof(char));
	//CSC322_fread(temptemptemp, testFile->getLength(), testFile);
	 
	//cout << "temptemptemp: ";
	//cout << (char*)temptemptemp << endl;
	
	CSC322_fclose(testFile);
	drive.close(); 
	wait();
}
#pragma endregion


#pragma region *************************************************** CSC322FILE Class ****************************************************************

//************************************ Constructors **************************************
CSC322FILE::CSC322FILE(short validNPT, const char* fileNamePtrNPT)
{
	setValid(validNPT);
	setFileName(fileNamePtrNPT);
	setRead(false);
	setWrite(false);
	setAppend(false);
	setPlus(false);
	setBinary(false);
}

CSC322FILE::CSC322FILE(const char* fileNamePtrNPT)
{
	setFileName(fileNamePtrNPT);
	setRead(false);
	setWrite(false);
	setAppend(false);
	setPlus(false);
	setBinary(false);
}

CSC322FILE::CSC322FILE(const char* fileNamePtrNPT, bool read, bool write, bool append, bool plus, bool binary)
{
	setFileName(fileNamePtrNPT);
	setRead(read);
	setWrite(write);
	setAppend(append);
	setPlus(plus);
	setBinary(binary);
}

CSC322FILE::CSC322FILE()
{
	setValid(validAlias);
	setLength(0);
	setLeftovers(noleftoverAlias);
	setFileName("");
}

CSC322FILE::~CSC322FILE(){}

//************************************ Setters **************************************
void CSC322FILE::setLength(short lengthINPT)
{
	length = lengthINPT;
}

bool CSC322FILE::setLeftovers(short leftOverNPT)
{
	leftovers = leftOverNPT;
	return true;
}

bool CSC322FILE::setValid(short ValidNPT)
{
	valid = ValidNPT;
	return true;
}

bool CSC322FILE::setFileName(const char fileNameINPT[])
{
	const char * fileNamePTR = fileNameINPT;
	int arrayCounter = 0;
	
	for (fileNamePTR; *fileNamePTR != '\0'; fileNamePTR++)
	{
		fileName[arrayCounter] = *fileNamePTR;
		if (arrayCounter == 63)
		{
			fileName[64] = '\0';
			return true;
		}
		arrayCounter++;
	}
	fileName[arrayCounter] = '\0';
	return true;
}

bool CSC322FILE::setOrigin(int originNPT)
{
	origin = originNPT;
	return true;
}

void CSC322FILE::setData(char * newData)
{
	data = newData;
}

bool CSC322FILE::setOffSet(long offSetNPT)
{
	offSet = offSetNPT;
	return true;
}

bool CSC322FILE::setBinary(bool binaryBool)
{
	binary = binaryBool;
	return true;
}

bool CSC322FILE::setWrite(bool writeBool)
{
	write = writeBool;
	return true;
}

bool CSC322FILE::setRead(bool readBool)
{
	read = readBool;
	return true;
}

bool CSC322FILE::setAppend(bool appendBool)
{
	append = appendBool;
	return true;
}

bool CSC322FILE::setPlus(bool plusBool)
{
	plus = plusBool;
	return true;
}

//************************************ Getters ************************************
char* CSC322FILE::getFileName()
{
	return fileNamePtr;
}

char* CSC322FILE::getDataPointer()
{
	return data;
}

short CSC322FILE::getValid()
{
	return valid;
}

short CSC322FILE::getLeftovers() 
{
	return leftovers;
}

short CSC322FILE::getLength()
{
	return length; 
}

int CSC322FILE::getOrigin()
{
	return origin;
}

char *  CSC322FILE::getData()
{
	return data;
}

long CSC322FILE::getOffSet()
{
	return offSet; 
}

bool CSC322FILE::getBinary()
{
	return binary;
}

bool CSC322FILE::getWrite()
{
	return write;
}

bool CSC322FILE::getRead()
{
	return read;
}

bool CSC322FILE::getAppend()
{
	return append;
}

bool CSC322FILE::getPlus()
{
	return plus;
}

//************************************ Our Functions *************************************
void CSC322FILE::prettyPrint()
{
	cout << "**********************************************" << endl;
	cout << "Valid flag:  " << getValid() << endl;
	cout << "File length: " << getLength() << endl;
	cout << "Leftovers:   " << getLeftovers() << endl;
	cout << "File name:   " << getFileName() << endl;
	cout << "Origin:      " << getOrigin() << endl;
	cout << "**********************************************" << endl;
}

#pragma endregion


#pragma region *************************************************** Part 3 Functions ****************************************************************

//************************************ Required Functions **************************************
CSC322FILE* CSC322_fopen(const char *filename, const char *mode)
{
	if (debug_part3) cout << "CSC322_fopen(): " << endl;
	bool read = false;
	bool write = false;
	bool binary = false;
	bool append = false;
	bool plus = false;
	for (mode; *mode != '\0'; mode++)
	{
		if (*mode == 'w')
		{
			write = true;
		}
		else if (*mode == 'r')
		{
			read = true;
		}
		else if (*mode == 'a')
		{
			append = true;
		}
		else if (*mode == 'b')
		{
			binary = true;
		}
		else if (*mode == '+')
		{
			plus = true; 
		}
	}
	if (read && binary)
	{
		// Opens for reading if the file does not exist it fails. 
		if (debug_part3) cout << "Got to Read && Binary: " << endl;
		CSC322FILE* temp = findFile(filename);
		if (temp == nullptr)
		{
			cerr << "file not found" << endl;
			delete temp; 
			return nullptr;
		}
		else
		{
			temp->setBinary(binary);
			temp->setRead(read);
			CSC322_fseek(temp, 0, temp->getOrigin()); 
			return temp;
		}
	}
	else if (write && binary)
	{
		if (debug_part3) cout << "Got to write && binary: " << endl;
		CSC322FILE* tempFile = findFile(filename);
		if (tempFile == nullptr)
		{
			return new CSC322FILE(filename, read, write, append, plus, binary);
		}
		CSC322_fseek(tempFile, 0, tempFile->getOrigin());
		tempFile->setBinary(binary);
		tempFile->setWrite(write);
		return tempFile;
	}
	else if (append && binary)
	{
		// Opens for writing at the end of the file. Creates the file if it doesn't exist.
		CSC322FILE* tempFile = findFile(filename);
		if (tempFile == nullptr)
		{
			return new CSC322FILE(filename, read, write, append, plus, binary);
		}
		const int tempLength = tempFile->getLength();
		CSC322_fseek(tempFile, tempFile->getLength(), tempFile->getOrigin());
		tempFile->setBinary(binary);
		tempFile->setAppend(append);
		return tempFile;
	}
}

int CSC322_fclose(CSC322FILE *stream)
{
	delete(stream);
	return 0;
}

int CSC322_fread(void *buffer, size_t nBytes, CSC322FILE *stream)
{
	if (debug_part3) cout << "CSC322_fread()" << endl;
	int bytesRead = 0;

	// check for file mode
	if (!stream->getRead() && !stream->getPlus())
	{
		if (debug_part3) cout << "CSC322_fread() FAILED: file not open in read mode" << endl;
		return -1;
	}

	// check for out of bounds
	if ((CSC322_ftell(stream) + nBytes) > stream->getLength())
	{
		if (debug_part3) cout << "CSC322_fread() FAILED: ftell was too close to end of file" << endl;
		return -1;
	}

	char * dataRead = (char*)malloc(nBytes + 1);

	for (int i = 0; i < nBytes; i += 2)
	{
		char * temp = readWord(CSC322_ftell(stream) + stream->getOrigin());
		dataRead[i] = temp[0];
		dataRead[i + 1] = temp[1];
		CSC322_fseek(stream, CSC322_ftell(stream) + 2, stream->getOrigin());
		bytesRead += 2;
	}
	dataRead[nBytes] = '\0';
	memcpy(buffer, dataRead, nBytes + 1);
	return bytesRead;
}

int CSC322_fwrite(void *buffer, size_t nBytes, CSC322FILE *stream)
{
	if (!stream->getWrite() && !stream->getPlus() && !stream->getAppend())
		return -1;
	
	CSC322FILE * tempFile = findFile(stream->getFileName());
	
	bool fileFound = true;
	if (tempFile == nullptr)
		fileFound = false;
	CSC322_fseek(stream, 0, stream->getOrigin());
	char * oldData = (char*)malloc((stream->getLength() + 1));
	if (stream->getAppend() && fileFound)
	{
		bool tempRead = stream->getRead();
		stream->setRead(true);
		CSC322_fread(oldData, stream->getLength(), stream);
		cout << (char*)oldData << endl;
		stream->setData(oldData);
		stream->setRead(tempRead);
	}
	else
	{
		oldData = nullptr;
	}

	int tempOldLength = stream->getLength();
	stream->setLength(tempOldLength + nBytes);
	
	
	int tempOff = findFreeLocation();

	char temp[headerSZ];
	short valid = validAlias;
	char* validChar = (char*)&valid;
	short length = stream->getLength();
	char* lengthChar = (char*)&length;
	short leftover = noleftoverAlias + (length % 2);
	char* leftoverChar = (char*)&leftover;
	char*  nameChar = (*stream).getFileName();
	if (nameChar == nullptr)
		return -1;


	int count = 0;
	for (validChar; *validChar != '\0'; validChar++)
	{
		temp[count++] = *validChar;
	}
	for (lengthChar; *lengthChar != '\0'; lengthChar++)
	{
		temp[count++] = *lengthChar;
	}
	for (leftoverChar; *leftoverChar != '\0'; leftoverChar++)
	{
		temp[count++] = *leftoverChar;
	}
	for (nameChar; *nameChar != '\0'; nameChar++)
	{
		temp[count++] = *nameChar;
	}
	for (count; count < sizeof(temp); count++)
	{
		temp[count] = (char)255;
	}
	if (debug_part3 && false)
	{
		for (int i = 0; i < sizeof(temp); i++)
		{
			cout << temp[i] << endl;
		}
	}

	// Write header
	writeCharPt(temp, sizeof(temp), tempOff);

	// Adjust pointer
	stream->setOrigin(tempOff + headerSZ);
	CSC322_fseek(stream, 0, stream->getOrigin());
	
	int dataSize = 0;
	if (stream->getAppend() && fileFound)
	{
		cout << "got to append write old data" << endl;
		dataSize += writeCharPt(oldData, tempOldLength, stream->getOrigin());
	}
	// Write new data
	dataSize += writeCharPt((char*)buffer, nBytes, dataSize + stream->getOrigin());
	
	if (fileFound) CSC322_remove(stream->getFileName());

	if (stream->getAppend() && fileFound)
	{
		if (dataSize != length)
		{
			cerr << "The data was not the right size (append mode)" << endl;
			return -1;
		}
	}
	else
	{
		if (dataSize != length)
		{
			cerr << "The data was not the right size" << endl;
			return -1;
		}
	}
	return dataSize;
}

int CSC322_fseek(CSC322FILE *stream, long offset, int origin)
{
	if(stream->setOffSet(offset) && stream->setOrigin(origin))
		return 0;
	else
		return -1; 
}

long CSC322_ftell(CSC322FILE *stream)
{
	return stream->getOffSet();
}

int CSC322_remove(const char *path)
{
	CSC322FILE* temp = findFile(path); 
	if (temp == nullptr)
		return -1;
	char tempValid[3];
	tempValid[0] = (char)invalidAlias;
	tempValid[1] = (char)temp->getLength();
	tempValid[2] = '\0';
	writeWord(temp->getOrigin() - headerSZ, tempValid);
	return 0;
}

//************************************ Our Functions **************************************
int writeCharPt(char* data, int length, int address)
{
	char temp[3];
	temp[2] = '\0';
	int i = 0;
	for (i; i < length-2; i += 2)
	{

		temp[0] = data[i];
		temp[1] = data[i + 1];
		writeWord(address + i, temp);
	}
	if (length % 2 == 0)
	{
		temp[0] = data[i];
		temp[1] = data[i + 1];
		writeWord(address + i, temp);
		i += 2;
	}
	else if (length % 2 == 1)
	{
		temp[0] = data[i];
		temp[1] = (char)255;
		writeWord(address + i, temp);
		i += 1;
	}
	return i;
}

bool readHeader(CSC322FILE * stream, int address)
{
	if (debug_part3) cout << "readHeader()" << endl;
	char charHeader[headerSZ];
	for (int i = 0; i < sizeof(charHeader); i += 2)
	{
		char * temp = readWord(address);
		charHeader[i] = temp[0];
		charHeader[i + 1] = temp[1];
		address += 2;
		if (charHeader[0] == (char)255)
		{
			if (debug_part3) cout << "Invalid file" << endl;
			stream = nullptr;
			return false;
		}
	}
	stream->setOrigin(address);
	stream->setValid((short)charHeader[0]);
	stream->setLength((short)charHeader[1]);
	stream->setLeftovers((short)charHeader[2]);
	char fileName[65];
	 
	for (int i = 0; i < sizeof(fileName); i++)
	{
		if (charHeader[i + 3] == (char)255)
		{
			fileName[i] = '\0';
			break;
		}
		else
		{
			fileName[i] = charHeader[i + 3];
		}
	}
	
	char * tempChPtr;
	tempChPtr = fileName;
	stream->setFileName(tempChPtr);
	if (debug_part3) stream->prettyPrint();
	return true;
}

int findFreeLocation()
{
	if (debug_part3) cout << "FindFreeLocation(): " << endl;
	int tempDiskPointer = 0;
	do
	{
		CSC322FILE* tempFile = new CSC322FILE();

		if (!readHeader(tempFile, tempDiskPointer))
		{
			return tempDiskPointer;
		}
		tempDiskPointer += headerSZ;
		
		tempDiskPointer += tempFile->getLength() + (tempFile->getLeftovers() % 2);
		delete tempFile;
	} while (tempDiskPointer < 20 * sectorSize);
	return -1;
}

CSC322FILE* findFile(const char* filename)
{
	if (debug_part3) cout << "findFile(): " << endl;
	int tempDiskPointer = 0;
	do{
		CSC322FILE* tempFile = new CSC322FILE();
		if (!readHeader(tempFile, tempDiskPointer))
		{
			if (debug_part3) cout << "No more files" << endl;
			return nullptr;
		}
		if (strcmp(tempFile->getFileName(), filename) == 0)
		{
			if (tempFile->getValid() == validAlias)
			{
				if (debug_part3) cout << "File Found" << endl;
				return tempFile;
			}
		}
		tempDiskPointer += headerSZ;
		tempDiskPointer += tempFile->getLength() + (tempFile->getLength() % 2);
		delete tempFile;

	} while (tempDiskPointer < 20 * sectorSize);
	return nullptr;
}

#pragma endregion


#pragma region *************************************************** Part 1 Functions ****************************************************************
void eraseAllSectors()
{
	if (debug_part1) cout << "Erasing all sectors" << endl;

	drive.seekg(0);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 32768*2; j++)
		{
			drive << (char)255 << (char)255; //255 is the decimal equivilant for 1111 1111 or an empty byte. Write two and we get and empty word
		}
	}
}

void eraseSector(int nSectorNr)
{
	if (debug_part1) cout << "Erasing sector " << nSectorNr << endl;
	
	if (nSectorNr < 20 && nSectorNr >= 0) // the sector number has to be within the range of our drive
	{
		drive.seekg(nSectorNr * 255);
		for (int i = 0; i < 255/2; i++)
		{
			drive << (char)255 << (char)255; 
		}
	}
	else
	{
		cerr << "Invalid Sector Number" << endl;
	}
}

bool writeWord(int nAddress, char* nWord)
{
	if (debug_part1)
	{
		cout << "Writing word ";
		for (int i = 0; nWord[i] != '\0'; i++)
		{
			cout << nWord[i];
		}
		cout << " to the file" << endl;
	}
	int sizeOfnWord = 0;
	for (int i = 0; nWord[i] != '\0'; i++) // find the length of the word
		sizeOfnWord++;

	if (sizeOfnWord != 2) // Make sure that the word is the right length
	{
		cerr << "Error: Incorrect Word Size." << endl;
		return false;
	}
	else if (nAddress % 2 != 0) // Make sure the address is aligned with word boundry
	{
		cerr << "Trying to write at address off word boundary [" << nAddress << "]" << endl;
		return false;
	}
	else if (nAddress > 1310718 || nAddress < 0)
	{
		cerr << "Address Out of Bounds" << endl;
		return false;
	}
	else
	{
		char * oldWord = readWord(nAddress);			//read in the word from the file
		short oldShort = *oldWord;						//make a short that is equal to the value of the original word 
		short newShort = *nWord;						//make a short that is equal to the value of the new word
		if ((oldShort & newShort) != newShort)   //preform the bit wise AND operation that can olny be done on number values
		{
			if (debug_part1) cout << "We can't write to the file." << endl;

			return false;
		}
		else
		{
			if (debug_part1)cout << "Yes, we can write to the file... writing now" << endl;
			
			drive.seekg(nAddress);
			drive << nWord;
		}
		delete oldWord;
		return true;
	}
}

char* readWord(int nAddress)
{
	if (debug_part1) {
		cout << "Reading word at " << nAddress << endl;
	}
	if (nAddress % 2 != 0) // Make sure the address is aligned with word boundry
	{
		cerr << "Trying to read at address off word boundary [" << nAddress << "]" << endl;
	}
	else if (nAddress > 1310718 || nAddress < 0)
	{
		cerr << "Address Out of Bounds [" << nAddress << "]" << endl;
	}
	else
	{
		char* tempWord;
		drive.seekg(nAddress);
		tempWord = new char[2];
		drive.read(tempWord, 2);
		if (debug_part1)
		{
			cout << "We read ";
			for (int i = 0; i < 2; i++)
			{
				cout << tempWord[i];
			}
			cout << " from the file" << endl;
		}
		return tempWord;
	}
	return nullptr;
}

void file()
{
	if (!drive.is_open())
	{
		if (ifstream("drive.bin"))
		{
			if(debug_part1) cout << "file exists" << endl;
			drive.open("drive.bin", ios::out | ios::in | ios::binary);
		}
		else
		{
			if (debug_part1) cout << "file does not exist" << endl;
			drive.open("drive.bin", ios::out | ios::binary);
			eraseAllSectors();
			drive.close();
			drive.open("drive.bin", ios::out | ios::in | ios::binary);
		}

	}
}

void wait()
{
	cout << "Press any key to end..." << endl;
	_getch();
}
#pragma endregion

