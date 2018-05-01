/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 5
* @compiler VC
*
*/

#include "stdafx.h"
#include"SearchTree.h"

SearchTree firstFile;

//function for reading from the binary files
void ReadBinaryFile(std::string fileName, size_t n)
{
	std::ifstream file;
	std::streampos begin, end;
	int64_t bytes = 0, data;
	char* line = "";
	//open binary file for reading
	file.open(fileName, std::ios::in | std::ios::binary);
	if (file.fail())
	{
		std::cout << "Invalid input file: " << (char*)&fileName << std::endl;
		std::exit(1);
	}
	//set the two pointers at the beginning and at the end of the file
	begin = file.tellg();
	file.seekg(0, std::ios::end);
	end = file.tellg();
	file.seekg(0, std::ios::beg);
	//while there is still information in the file, the number  is got from every 8 bytes
	while (bytes<(end - begin)) {
		file.seekg(bytes, std::ios::cur);
		file.read(line, 8);
		data = std::atoi(line);
		//if it is the first file, the tree is bild
		if (n == 1)
		{
			firstFile.add(data);
		}
		//otherwise the number is searched in the tree
		else firstFile.search(data);
		bytes += 8;
	}
	file.close();
}

//function for creating a result file with the intersection of elements
void CreateResultFile(std::string fileName, size_t n)
{
	std::ofstream file;
	std::string outputFile = "\\result.bin";
	std::string result = fileName + outputFile;
	//create output binary file 
	file.open(result, std::ios::binary | std::ios::app | std::ios::out);
	if (file.fail())
	{
		std::cout << "Invalid input file: " << (char*)&fileName << std::endl;
		std::exit(1);
	}
	//all elements that are common for all files are added in the file
	firstFile.print(file, n);
	file.close();
}

int main(size_t argc, char* argv[])
{
	//checking the number of arguments
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " SOURCE DESTINATION " << std::endl;
		return 1;
	}
	//the first argument is the number of files
	size_t n;
	n = std::atoi(argv[1]);
	//reading the files, creating the tree and searching for the next elements in it
	for (size_t i = 2; i < argc; i++)
	{
		ReadBinaryFile(argv[i], i - 1);
	}
	//getting the path of the source file and creating the result file there
	std::string argv_str(argv[0]);
	std::string base = argv_str.substr(0, argv_str.find_last_of("\\"));
	CreateResultFile(base, n);

	return 0;
}

