#include "IOblock.h"

IOblock::IOblock(int num)
{
	a = new unsigned long long[num]; size = num;
	clear();
	iterator = 0;
}

bool IOblock::readBlock(ifstream& file)
{
	clear();
	if (file.read((char*)a, size * sizeof(unsigned long long)))
		return true;
	else
		return false;
}

bool IOblock::getNum(unsigned long long* num)
{
	if (iterator < size)
	{
		if (a[iterator] != ULLONG_MAX)
		{
			*num = a[iterator];
			iterator++;
			return true;
		}
	}
	return false;
}

bool IOblock::getNumOrReadBlock(unsigned long long* num, ifstream& file)
{
	if (!getNum(num))
	{
		if (readBlock(file))
			return getNum(num);
		else
			return false;
	}
	else
		return true;
}

bool IOblock::addNum(unsigned long long num)
{
	if (iterator < size)
	{
		a[iterator] = num;
		iterator++;
		return true;
	}
	return false;
}

void IOblock::writeBlock(ofstream& file)
{
	if (iterator > 0)	
		file.write((char*)a, sizeof(unsigned long long) * size);
	clear();
}

void IOblock::addNumOrWriteBlock(unsigned long long num, ofstream& file)
{
	if (!addNum(num))
	{
		writeBlock(file);
		clear();
		addNum(num);
	}
}

void IOblock::clear()
{
	for (int i = 0; i < size; i++) a[i] = ULLONG_MAX;
	iterator = 0;
}

IOblock::~IOblock()
{
	delete[size] a;
}
