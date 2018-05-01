/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 2
* @compiler VC
*
*/

#include "stdafx.h"

std::ifstream file;
std::string lineInput, line;
size_t n, k;
Queue<std::string> commands;

const size_t floorPerSecond = 5;
const size_t firstFloor = 1;
const size_t beginTime = 0;

size_t commandTime1 = 0;
size_t commandFloor1 = 0;
size_t timeToArrive1 = 0;
std::string currentDirection1 = "";

size_t commandTime2 = 0;
size_t commandFloor2 = 0;
size_t timeToArrive2 = 0;
std::string currentDirection2 = "";

//stack for the requests that are not going to be evaluated when they came, but afterwards
Stack<std::string> temporary;

size_t currentTime = 0;
size_t currentFloor = 0;
std::string currentDirection = "";

//reads the requests from file
void ReadFile(std::string lineInput)
{
	file.open(lineInput);

	if (file.fail())
	{
		std::cout << "Invalid input file !!!" << std::endl;
		std::exit(1);
	}
	size_t i = 0;
	while (std::getline(file, line))
	{
		if (i == 0)
		{
			std::string so;
			std::stringstream in(line);
			size_t j = 0;
			while (in >> so)
			{
				if (j == 0) n = stoi(so);
				else k = stoi(so);
				j++;
			}
			i++;
		}
		else
		{
			commands.Enqueue(line);
		}
	}
	file.close();
}

//combines every output line
std::string Result(size_t currentFloor, size_t currentTime, std::string currentDirection)
{
	std::string data;
	data.append(std::to_string(currentTime));
	data.append(" ");
	data.append(std::to_string(currentFloor));
	data.append(" ");
	data.append(currentDirection);

	return data;
}

//prioritize the requests
Queue<std::string> EvaluateRequests(Queue<std::string> commands)
{
	Queue<std::string> solution;
	while (!commands.IsEmpty())
	{
		if (commands.GetSize() == k)
		{
			currentTime = beginTime;
			currentFloor = firstFloor;
		}
		//gets the first element of the queue and separates the string
		std::string line1 = commands.Dequeue();

		std::string command1, direction1;
		size_t floorDifference1;

		std::string so1;
		std::stringstream in(line1);
		size_t count1 = 0;
		while (in >> so1)
		{
			if (count1 == 0)
			{
				command1 = so1;
			}
			else if (count1 == 1)
			{
				if (command1 == "call") direction1 = so1;
				else commandFloor1 = stoi(so1);
			}
			else if (count1 == 2)
			{
				if (command1 == "call") commandFloor1 = stoi(so1);
				else commandTime1 = stoi(so1);
			}
			else if (count1 == 3)
			{
				commandTime1 = stoi(so1);
			}
			count1++;
		}
		//if this is the first input element the calculations of the time start from the time of this request
		if (currentTime == 0) currentTime = commandTime1;
		//checks the direction in which the elevator is going to move
		if (commandFloor1 > currentFloor)
		{
			floorDifference1 = commandFloor1 - currentFloor;
			currentDirection1 = "up";
		}
		else if (commandFloor1 < currentFloor)
		{
			floorDifference1 = currentFloor - commandFloor1;
		}
		else
		{
			floorDifference1 = 0;
			if (commandFloor1 == 1) currentDirection1 = "down";
			else if (commandFloor1 == n) currentDirection1 = "up";
		}
		//calculates the time when the elevator is going to arrive
		timeToArrive1 = currentTime + (floorDifference1*floorPerSecond);

		//counts one cycle through the queue
		size_t sizeBeforeCheck = commands.GetSize();
		//checks if there are requests to this floor which are comming before the elevatore is going to arrive to the floor
		while (sizeBeforeCheck > 0)
		{
			//gets the element and separates the string
			std::string lineCheck = commands.Dequeue();
			sizeBeforeCheck--;

			std::string commandCheck, directionCheck;
			size_t floorDifferenceCheck;
			std::string soCheck;
			std::stringstream in(lineCheck);
			size_t countCheck = 0;
			while (in >> soCheck)
			{
				if (countCheck == 0)
				{
					commandCheck = soCheck;
				}
				else if (countCheck == 1)
				{
					if (commandCheck == "call") directionCheck = soCheck;
					else commandFloor2 = stoi(soCheck);
				}
				else if (countCheck == 2)
				{
					if (commandCheck == "call") commandFloor2 = stoi(soCheck);
					else commandTime2 = stoi(soCheck);
				}
				else if (countCheck == 3)
				{
					commandTime2 = stoi(soCheck);
				}
				countCheck++;
			}
			//checks the direction in which the elevator is going to move
			if (commandFloor2 > currentFloor)
			{
				floorDifferenceCheck = commandFloor2 - currentFloor;
				currentDirection2 = "up";
			}
			else if (commandFloor2 < currentFloor)
			{
				floorDifferenceCheck = currentFloor - commandFloor2;
				currentDirection2 = "down";
			}
			else
			{
				floorDifferenceCheck = 0;
			}
			//calculates the time when the elevator is going to arrive
			timeToArrive2 = currentTime + (floorDifferenceCheck*floorPerSecond);
			//if the command comes before the elevator is going to arrive,we skip it
			if (commandFloor1 == commandFloor2 && commandTime2 < timeToArrive1)
			{
				continue;
			}
			//else we put it back in the queue
			else commands.Enqueue(lineCheck);
		}

		//counts one cycle through the queue
		size_t saveSize = commands.GetSize();
		//checks if there is a command that should be evaluated before the current one
		while (saveSize > 0)
		{
			//gets the element and separates the string
			std::string line2 = commands.Dequeue();
			saveSize--;

			std::string command2, direction2;
			size_t floorDifference2;
			std::string so2;
			std::stringstream in(line2);
			size_t count2 = 0;
			while (in >> so2)
			{
				if (count2 == 0)
				{
					command2 = so2;
				}
				else if (count2 == 1)
				{
					if (command2 == "call") direction2 = so2;
					else commandFloor2 = stoi(so2);
				}
				else if (count2 == 2)
				{
					if (command2 == "call") commandFloor2 = stoi(so2);
					else commandTime2 = stoi(so2);
				}
				else if (count2 == 3)
				{
					commandTime2 = stoi(so2);
				}
				count2++;
			}
			//if the floor from which the elevator starts at the moment is the same as the one in this request, the time is updated
			if (currentFloor == commandFloor2) currentTime = commandTime2;
			//checks the direction in which the elevator is going to move
			if (commandFloor2 > currentFloor)
			{
				floorDifference2 = commandFloor2 - currentFloor;
				currentDirection2 = "up";
			}
			else if (commandFloor2 < currentFloor)
			{
				floorDifference2 = currentFloor - commandFloor2;
				currentDirection2 = "down";
			}
			else
			{
				floorDifference2 = 0;
			}
			//calculates the time when the elevator is going to arrive
			timeToArrive2 = currentTime + (floorDifference2*floorPerSecond);
			//the floor is the same and the stack is empty,the current data is updated with the values of the second request
			if (commandFloor1 == commandFloor2 && temporary.GetSize() == 0)
			{
				std::string res = Result(commandFloor1, timeToArrive1, currentDirection1);
				solution.Enqueue(res);
				commandTime1 = commandTime2;
				timeToArrive1 = commandTime2;
				currentTime = commandTime2;
				currentFloor = commandFloor2;
				continue;

			}
			//if the second request is in the same direction - "up"
			if (currentDirection1 == currentDirection2 && currentDirection1 == "up")
			{
				//if the request came before the expected time for this floor and the floor os between the current one and the target one
				//we put the first request in the stack and the data of the second one becomes the new current data
				if (currentFloor< commandFloor2 && commandFloor2 < commandFloor1 && commandTime2 <= timeToArrive2)
				{
					std::string res = Result(commandFloor1, timeToArrive1, currentDirection1);
					temporary.Push(res);
					commandTime1 = commandTime2;
					commandFloor1 = commandFloor2;
					timeToArrive1 = timeToArrive2;
					currentTime = commandTime1;
					currentFloor = commandFloor1;
					continue;

				}
				//if the request time is after the expected one or the floor is not between the current and targeted one,
				//then we put the request back in the queue
				else if ((currentFloor < commandFloor2 && commandFloor2<commandFloor1  && commandTime2>timeToArrive2) || (currentFloor> commandFloor2 || commandFloor2 > commandFloor1))
				{
					commands.Enqueue(line2);
				}
			}
			//if the second request is in the same direction - "down"
			else if (currentDirection1 == currentDirection2 && currentDirection1 == "down")
			{
				//if the request came before the expected time for this floor and the floor os between the current one and the target one
				//we put the first request in the stack and the data of the second one becomes the new current data
				if (currentFloor > commandFloor2 && commandFloor2 > commandFloor1 && commandTime2 <= timeToArrive2)
				{
					std::string res = Result(commandFloor1, timeToArrive1, currentDirection1);
					temporary.Push(res);
					commandTime1 = commandTime2;
					commandFloor1 = commandFloor2;
					timeToArrive1 = timeToArrive2;
					currentTime = commandTime2;
					currentFloor = commandFloor2;
					continue;

				}
				//if the request time is after the expected one or the floor is not between the current and targeted one,
				//then we put the request back in the queue
				else if ((currentFloor > commandFloor2 && commandFloor2>commandFloor1  && commandTime2>timeToArrive2) || (currentFloor< commandFloor2 || commandFloor2 < commandFloor1))
				{
					commands.Enqueue(line2);
				}
			}
			//otherweise we put the request back in the queue
			else
			{
				commands.Enqueue(line2);
			}
		}
		//calculates the output line and puts it in the new queue
		std::string res = Result(commandFloor1, timeToArrive1, currentDirection1);
		solution.Enqueue(res);
		//if there are elements in the stack,we pop them and put them in the queue with the solution
		if (temporary.GetSize() > 0)
		{
			while (!temporary.IsEmpty())
			{
				std::string temp;
				temporary.Pop(temp);
				//if we reach the last element we used its data to update the current time nad floor
				if (temporary.GetSize() == 0)
				{
					size_t time;
					size_t floor;
					std::string dir;
					std::string so;
					std::stringstream in(temp);
					size_t l = 0;
					while (in >> so)
					{
						if (l == 0)
						{
							time = stoi(so);
						}
						else if (l == 1)
						{
							floor = stoi(so);
						}
						else
						{
							dir = so;
						}
						l++;
					}
					currentFloor = floor;
					currentTime = time;
				}
				solution.Enqueue(temp);
			}
		}
		//if the stack is empty,we use the data from the first request to update the current time and floor
		else
		{
			currentFloor = commandFloor1;
			currentTime = timeToArrive1;
		}
	}
	return solution;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " SOURCE DESTINATION " << std::endl;
		return 1;
	}
	lineInput = argv[1];

	ReadFile(lineInput);
	Queue<std::string> res = EvaluateRequests(commands);
	//prints the result
	while (!res.IsEmpty())
	{
		std::cout << res.Dequeue() << std::endl;
	}
	return 0;
}