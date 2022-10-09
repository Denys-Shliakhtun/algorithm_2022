#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "seriesRead.h"
#include "IOblock.h"
#include <iostream>
#include <fstream>

using namespace std;

void createFile(string, unsigned long long, int = 1);
void readFile(string, int);
string sortFile(int, string);

template <typename T>
void openArrFile(string str, int num, T** fileArray)
{
	for (int i = 0; i < num; i++)
	{
		char* a = new char;
		_itoa(i + 1, a, 10);
		fileArray[i] = new T(str + string(a) + ".txt", ios::binary);
	}
}

template <typename T>
void closeArrFile(T fileArray, int num)
{
	for (int i = 0; i < num; i++)	
		fileArray[i]->close();	
}
