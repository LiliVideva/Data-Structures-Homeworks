/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 6.2
* @compiler VC
*
*/

#include"stdafx.h"
#include"SearchTree.h"

std::string  line;
SearchTree tree;

//function for reading from file and inserting the information from it in a tree 
void ReadFromFile(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (file.fail())
	{
		std::cout << "Couldn't open the file !!!" << std::endl;
		std::exit(1);
	}
	//getting the lines, separated by new line
	while (std::getline(file, line))
	{
		std::string l;
		std::stringstream in(line);
		size_t data;
		//getting the data, separated by tab
		while (getline(in, l, '\t'))
		{
			std::stringstream so(l);
			so >> data;
			tree.add(data);
		}
	}
	file.close();
}

//function for writing the data from the tree into the same file
void WriteInFile(std::string fileName)
{
	std::ofstream file;
	file.open(fileName);

	if (file.fail())
	{
		std::cout << "Couldn't open the file !!!" << std::endl;
		std::exit(1);
	}

	tree.print(file);
	file.close();
}

int main(size_t argc, char* argv[])
{
	//checking the number of arguments
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " SOURCE DESTINATION " << std::endl;
		return 1;
	}
	//getting the elements from the file, set as a first argument
	std::string lineInput = argv[1];
	ReadFromFile(lineInput);
	//checking how many subtrees with the number of elements as the second argument and writing them in the same file
	size_t number;
	std::cin >> number;
	std::cout << tree.checkElements(number) << std::endl;
	WriteInFile(lineInput);
	return 0;
}