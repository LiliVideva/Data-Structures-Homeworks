/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 4
* @compiler VC
*
*/

#include "stdafx.h"
#include"tree.h"

BinarySearchTree<long,std::string> balance;

void ReadBinaryFile(std::string lineInput)
{
	std::ifstream file;
	long keyFile, size;
	std::streampos begin, end;
	//variables we use to read from the file
	char *f1="", *f2="",*f3="";
	long bytes = 0;

	file.open(lineInput, std::ios::binary | std::ios::in);

	if (file.fail())
	{
		std::cout << "Invalid input file !!!" << std::endl;
		std::exit(1);
	}
	else
	{
		begin = file.tellg();
		//we put the pointer at the beginning of the file
		file.seekg(0, std::ios::end);
		end = file.tellg();
		//while there is still information in the file
		while (bytes < (end - begin)) {
			file.seekg(bytes, std::ios::beg);
			file.read(f1, 4);
			keyFile = std::stoi(f1);
			file.read(f2, 4);
			//the size of the data we need
			size = std::stoi(f2);
			file.read(f3, size);
			bytes += (8 + size);
			balance.add(keyFile, f3);
		}
	}
	file.close();
}

int main(size_t argc, char* argv[])
{
	std::string lineInput;
	lineInput=argv[1];
	//we open the file to take the information
	ReadBinaryFile(lineInput);

	long key=0;
	std::string data="";
	bool result = false;
	std::string command, com;
	int count = 0;

	while (getline(std::cin,command))
	{
		std::string take="";
		std::stringstream so(command);
		
		while (so >> take)
		{
			if (count == 0)
			{
				com = take;

			}
			if (count == 1)
			{
				key = stoi(take);
			}
			if (count == 2)
			{
				data = take;
			}
			if(com == "removeall" && count==1) count = 3;
			else if(count<=2) 	count++;
		}
			if (count == 3)
			{
				if (com == "add")
				{
					balance.add(key, data);
				}
				if (com == "remove")
				{
					result = balance.remove(key, data);
					if (result) std::cout << "true" << std::endl;
					else std::cout << "false" <<std::endl;
				}
				if (com == "removeall")
				{
					std::cout << balance.removeall(key) << std::endl;
				}
				if (com == "search")
				{
					result = balance.search(key, data);
					if (result) std::cout << "true" << std::endl;
					else std::cout << "false" << std::endl;
				}
				else
				{
					std::cout << "Wrong command! Try again!" << std::endl;
				}
				data = "";
				count = 0;
			}
	}
    return 0;
}

