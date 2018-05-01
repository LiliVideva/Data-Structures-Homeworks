/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 3
* @compiler VC
*
*/

#include "stdafx.h"
#include "Trie.h"

std::ifstream firstFile, nextFile;
std::string lineInput, sentenceLine, line, currentLine;
size_t longestPhraseCounter = 0;
long sum = 0;
size_t counter = 0;


Trie root;

//reads the "dictionary"
void ReadFirstFile(std::string lineInput)
{
	firstFile.open(lineInput);

	if (firstFile.fail())
	{
		std::cout << "Invalid input file !!!" << std::endl;
		std::exit(1);
	}

	std::string phrase = "";
	size_t tempCounter = 0;
	std::string so;
	//reads word by word
	while (firstFile >> so)
	{
		int num = 0;
		std::stringstream checkNum(so);
		//if we have reached a number we insert the combined word and its value in the trie
		if (!(checkNum >> num).fail())
		{
			root.Insert(const_cast<char *> (phrase.c_str()), stoi(so));
			phrase = "";
			if (tempCounter > longestPhraseCounter) longestPhraseCounter = tempCounter;
			tempCounter = 0;
		}
		//otherwise we append it to a string and count the number of words in the newly formed phrase
		else {
			phrase = phrase + so;
			tempCounter++;
		}
	}
	firstFile.close();
}

//reads all other files with texts
double ReadFile(std::string textFile)
{
	nextFile.open(textFile);

	if (nextFile.fail())
	{
		std::cout << "Invalid input file !!!" << std::endl;
		std::exit(1);
	}

	std::string phrase = "";
	size_t tempCounter = 0;
	std::string so;
	//reads text word by word
		while (nextFile >> so)
		{
			//transforms all letters to lower case
			std::transform(so.begin(), so.end(), so.begin(), ::tolower);
			char* soConvert = const_cast<char *> (so.c_str());
			//split so by characters different from letters
			char* word;
			char  delims[] = "!\"#$%&\'()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
			char *context = NULL;
			word = strtok_s(soConvert,delims,&context);
			while (word != NULL)
			{
				//searches for the word in the trie
				double wordValue = root.Search(word);
				//if the word is found and it is the longest one, we add to the sum
				if (wordValue != 0.1 && wordValue != 0.2)
				{
					sum += (long)wordValue;
				}
				//if the word is found but it is not the longest one and we have not checked for a phrase yet
				else if (wordValue == 0.2 || phrase != "")
				{
					//if the tempCounter of words in the phrase is smaller than the longest phrase in the dictionary, we add the word to the phrase
					if (tempCounter < longestPhraseCounter)
					{
						phrase = phrase + so;
						tempCounter++;
						//if this is not the first word in the phrase,we search it in the trie
						if (phrase != so) {
							double phraseValue = root.Search(word);
							//if this is the longest word,we add it to the sum,and empty the phrase and the tempCounter
							if (phraseValue != 0.1 && phraseValue != 0.2)
							{
								sum += (long)phraseValue;
								phrase = "";
								tempCounter = 0;
							}
						}
					}
					//otherwise we initialize the phrase and the tempCounter
					else
					{
						phrase = "";
						tempCounter = 0;
					}
				}
				//couns the words in the text
				counter++;
				word = strtok_s(NULL,delims,&context);
			}
		}
	nextFile.close();
	//if no words are found in the dictionary,we return the sum which is 0
	if (counter == 0) return sum;
	//otherwise we calculate the coefficient
	if (sum >= 0) return (sum / counter);
	//if the sum is negative we divide it as positive and then turn the result to negative
	double result = (-sum /counter);
	return -result;
}
int main(size_t argc, char* argv[])
{
	lineInput= argv[1];
	//for every file entered calculate its coefficient and return it as a result 
	for (size_t i = 2; i < argc; i++)
	{
	sentenceLine = argv[i];
	std::cout << sentenceLine << " " << ReadFile(sentenceLine) << std::endl;
	}
	return 0;
}