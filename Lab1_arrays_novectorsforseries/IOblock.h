#pragma once
#include <fstream>
#include <algorithm>
using namespace std;
class IOblock
{
	unsigned long long* a;
	int size;
	int iterator;
public:
	IOblock(int num = 4 * 1048576);	//32mb

	bool readBlock(ifstream& file);

	bool getNum(unsigned long long* num);

	bool getNumOrReadBlock(unsigned long long* num, ifstream& file);

	bool addNum(unsigned long long num);

	void writeBlock(ofstream& file);

	void addNumOrWriteBlock(unsigned long long num, ofstream& file);

	void clear();

	/*
	void sortBlock()
	{
		sort(&(a[0]), &(a[iterator + 1]));
	}*/

	~IOblock();
};
