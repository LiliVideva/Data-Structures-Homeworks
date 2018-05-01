/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 1
* @compiler VC
*
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "stack.h"

std::ifstream file;
std::string expressionFile, operationsFile, operationsLine, line;
Stack<std::string> expressionLine, reversedPostfix;

//Reads the symbols and operations from the second file and puts them into a string
void ReadTheFileWithTheOperations(std::string operationsFile)
{
	file.open(operationsFile);
	
	if (file.fail())
	{
		std::cout << "Invalid operations file !!!" << std::endl;
		std::exit(1);
	}

	while (std::getline(file, line))
	{
		std::string so;
		std::stringstream in(line);
		while (in >> so)
		{
			if (so != "0" && so != "1")
				operationsLine += so + " ";
		}
	}
	file.close();
}

//Reads the file with the expression, checks it for errors and puts it into a stack
void ReadTheFileWithTheExpression(std::string expressionFile)
{
	file.open(expressionFile);

	if (file.fail())
	{
		std::cout << "Invalid expression file !!!" << std::endl;
		std::exit(1);
	}

	while (std::getline(file, line))
	{
		for (size_t i = 0; i < line.size() - 1; i++)
		{
			if ((line[i] == '-') && (line[i + 1] == ' '))
			{
				std::cerr << "Error.Operator in expression on line " << i << std::endl;
				return;
			}
		}
		if (line[line.size() - 1] == '-')
		{
			std::cerr << "Error.Operator in expression on line " << line.size() - 1 << std::endl;
			return;
		}
		std::string so;
		std::stringstream in(line);
		while (in >> so)
		{
			int num = 0;
			std::stringstream checkNum(so);
			if ((so[0] >= 'a' && so[0] <= 'z') || !(checkNum >> num).fail())
				expressionLine.Push(so);
			else
			{
				std::cerr << "Error.Invalid expression" << std::endl;
				return;
			}
		}
	}
	file.close();
}

//Converts the input prefix expression to postfix
std::string PrefixToPostfix(Stack<std::string> expressionLine, std::string operationsLine)
{
	Stack<std::string>temporary;
	std::string line, result;
	while (!expressionLine.IsEmpty())
	{
		expressionLine.Pop(line);
		int num = 0;
		std::istringstream in(line);
		if (!(in >> num).fail()) temporary.Push(line);
		else
		{
			for (size_t i = 0; i < operationsLine.size(); i++)
			{
				if (line[0] == operationsLine[i])
				{
					std::string operand1, operand2;
					temporary.Pop(operand1);
					temporary.Pop(operand2);
					std::string concatenation = operand1 + " " + operand2 + " " + line;
					temporary.Push(concatenation);
				}
			}
		}

	}
	temporary.Pop(result);
	return result;
}

//Reverses the postfix expression and puts it into a stack of strings
Stack<std::string> ReverseAndSplitPostfixString(std::string convertion)
{
	Stack<std::string> postfix;
	std::string so;
	std::stringstream in(convertion);
	while (in >> so) postfix.Push(so);

	while (postfix.GetSize())
	{
		std::string reversedString;
		postfix.Pop(reversedString);
		reversedPostfix.Push(reversedString);
	}
	return reversedPostfix;
}

//Calculates the result of the converted into postfix expression
double CalculatePostfix(Stack<std::string> postfix, std::string operationsLine)
{
	
	Stack<double> result;
	double answer;
	while(!postfix.IsEmpty())
	{
		postfix.Pop(line);
		int num = 0;
		std::istringstream in(line);
		if (!(in >> num).fail()) result.Push(stod(line));
		else
		{
			if (result.GetSize() < 2) std::cout << "Incorrect data" << std::endl;
			for (size_t i = 0; i < operationsLine.size() - 2; i++)
			{
				if (line[0] == operationsLine[i])
				{
					double operand1, operand2,evaluate;
					result.Pop(operand1);
					result.Pop(operand2);
					if (operationsLine[i + 2] == '+')
					{
						evaluate = operand2 + operand1;
						result.Push(evaluate);
					}
					else if (operationsLine[i + 2] == '-')
					{
						evaluate = operand2 - operand1;
						result.Push(evaluate);
					}
					else if (operationsLine[i + 2] == '*')
					{
						evaluate = operand2 * operand1;
						result.Push(evaluate);
					}
					else if (operationsLine[i + 2] == '/')
					{
						try {
							evaluate = operand2 / operand1;
							result.Push(evaluate);
						}
						catch (std::exception ex)
						{
							std::cout << ex.what() << "Divide by zero exception!" << std::endl;
						}
					}
				}
			}
		}
	}
	if(result.GetSize()==1) result.Pop(answer);
	else std::cout << "Incorrect data" << std::endl;
	return answer;
}
int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " SOURCE DESTINATION " << std::endl;
		return 1;
	}

	expressionFile = argv[1];
	operationsFile = argv[2];

	ReadTheFileWithTheOperations(operationsFile);
	ReadTheFileWithTheExpression(expressionFile);

	//std::cout << operationsLine << std::endl;

	std::string convertion = PrefixToPostfix(expressionLine, operationsLine);
	std::cout << convertion << std::endl;

	reversedPostfix = ReverseAndSplitPostfixString(convertion);

	double result = CalculatePostfix(reversedPostfix, operationsLine);
	std::cout << std::setprecision(5) << std::fixed << result << std::endl;

    return 0;
}