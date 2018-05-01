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

#pragma once
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')


class Trie
{
public:
	class TrieNode
	{
	public:
		TrieNode *heir[26];
		bool isLeaf;
		bool isLonger;
		long value;
		TrieNode(bool, bool, long, TrieNode* = NULL);
	};

	Trie();

	void Insert(const char*, long);
	double Search(const char*);
	TrieNode* Initialization();

private:
	TrieNode* root;
};

Trie::TrieNode::TrieNode(bool isLeaf, bool isLonger, long value, TrieNode* heir)
{
	this->isLeaf = isLeaf;
	this->isLonger = isLonger;
	this->value = value;
	for (size_t i = 0; i < 26; i++)
	{
		this->heir[i] = heir;
	}
}

Trie::Trie()
{
	root = Initialization();
}

Trie::TrieNode* Trie::Initialization()
{
	TrieNode *node = NULL;
	node = (TrieNode *)malloc(sizeof(TrieNode));
	if (node)
	{
		node->isLeaf = false;
		node->isLonger = false;
		for (size_t i = 0; i < 26; i++)
			node->heir[i] = NULL;
	}
	return node;
}

void Trie::Insert(const char* phrase, long value)
{
	size_t length = strlen(phrase);
	size_t index;
	bool alreadyExistingWord = false;

	TrieNode *temp = root;

	for (size_t i = 0; i < length; i++)
	{
		index = CHAR_TO_INDEX(phrase[i]);

		if (temp->heir[index] && i == length - 1) alreadyExistingWord = true;

		if (!temp->heir[index]) temp->heir[index] = Initialization();

		if (temp->isLeaf) temp->isLonger = true;

		temp = temp->heir[index];
	}

	if (alreadyExistingWord) temp->isLonger = true;

	temp->isLeaf = true;
	temp->value = value;
}

double Trie::Search(const char* phrase)
{
	size_t length = strlen(phrase);
	size_t index;
	TrieNode *temp = root;

	for (size_t i = 0; i < length; i++)
	{
		if (phrase[i] >= 'a' && phrase[i] <= 'z')
		{
			index = CHAR_TO_INDEX(phrase[i]);

			if (!temp->heir[index] && i<length - 1) return 0.1;

			temp = temp->heir[index];
		}
	}

	if (temp != NULL && temp->isLeaf && temp->isLonger == false)
	{
		return temp->value;
	}

	return 0.2;
}
