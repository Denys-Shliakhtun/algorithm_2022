#include "fileWork.h"

void createFile(string fileName, unsigned long long count, int count2)
{
	ofstream fileOut(fileName, ios::binary);
	unsigned long long num;
	IOblock block;
	for (int j = 0; j < count2; j++)
	{
		for (int i = 0; i < count; i++)
		{
			num = rand() % 10000 + 1;
			if (!block.addNum(num))
			{
				block.writeBlock(fileOut);
				block.clear();
				block.addNum(num);
			}
		}
	}
		
	block.writeBlock(fileOut);	
	
	fileOut.close();
}

void readFile(string fileName, int count)
{
	ifstream fileIn(fileName, ios::binary);
	unsigned long long *num = new unsigned long long, prev;
	prev = ULLONG_MAX;
	IOblock block;
	bool flag = true;
	if (block.readBlock(fileIn))
	{
		for (int i = 0; i < count && flag; i++)
		{
			if (block.getNumOrReadBlock(num, fileIn))
			{
				if (*num != prev)
				{
					cout << *num << '\n';
					prev = *num;
				}
				else
					i--;
			}
			else
				flag = false;			
		}
	}	
	fileIn.close();
}

string sortFile(int num, string fileName)
{
	ofstream** fileWriteArr = new ofstream * [num]; 
	openArrFile<ofstream>("B", num, fileWriteArr);
	ifstream** fileReadArr = new ifstream * [num];
	
	ifstream fileIn(fileName, ios::binary);
	unsigned long long number, temp = 0;
	bool allFilesB_used = false;
	int i = 0;

	IOblock initialBlockRead;
	IOblock* blockRead = new IOblock[num];
	IOblock* blockWrite = new IOblock[num];

	while (initialBlockRead.getNumOrReadBlock(&number, fileIn))
	{		
		if (number >= temp)
		{
			temp = number;
		}
		else
		{
			if (i == num - 1)
				allFilesB_used = true;
			i = (i + 1) % num;
			temp = 0;			
		}
		blockWrite[i].addNumOrWriteBlock(number, *(fileWriteArr[i]));
	}
	fileIn.close();	
	for (int i = 0; i < num; i++)
		blockWrite[i].writeBlock(*(fileWriteArr[i]));
	
	closeArrFile<ofstream**>(fileWriteArr, num);
	if (!allFilesB_used)	
		num = i+1;	

	int flag = 1;
	string fileName1, fileName2;
	int counter;
	while (flag)	//changing from file B to C and vice versa
	{
		flag % 2 == 1 ? fileName1 = "B" : fileName1 = "C";
		fileName1 == "B" ? fileName2 = "C" : fileName2 = "B";
		
		openArrFile<ifstream>(fileName1, num, fileReadArr);
		openArrFile<ofstream>(fileName2, num, fileWriteArr);
		
		seriesRead* series = new seriesRead[num];
		for (int i = 0; i < num; i++)
		{
			if (blockRead[i].getNumOrReadBlock(&temp, *(fileReadArr[i])))			
				series[i].addNumDetermineSeries(temp);			
			else			
				series[i].setIsEndOfFile(true);			
		}

		counter = 0;	//number of file that is used for recording
		bool areAllFilesUsed = false;
		bool innerFlag = true;
		while (innerFlag) //every loop detecting one series from every file of 1 type and recording to another
		{
			bool areAllNumbersRecorded = false;			
			while (!areAllNumbersRecorded) //merging series into 1 file
			{
				areAllNumbersRecorded = true;
				int pos;
				unsigned long long min = ULLONG_MAX;
				for (int j = 0; j < num; j++)
				{
					if (series[j].getIsSeries() && !series[j].getIsEndOfFile())
					{
						if (series[j].getCurr() <= min)
						{
							min = series[j].getCurr();
							pos = j;
						}
						areAllNumbersRecorded = false;
					}
				}
				if (!areAllNumbersRecorded)
				{					
					blockWrite[counter].addNumOrWriteBlock(min, *(fileWriteArr[counter]));
					if (blockRead[pos].getNumOrReadBlock(&temp, *(fileReadArr[pos])))						
						series[pos].addNumDetermineSeries(temp);						
					else						
						series[pos].setIsEndOfFile(true);										
				}
			}
			counter++;
			if (counter == num)
			{
				counter = 0;
				areAllFilesUsed = true;
			}
			innerFlag = false;
			for (int j = 0; j < num; j++)
			{
				series[j].setIsSeries(true);
				if (!series[j].getIsEndOfFile())				
					innerFlag = true;				
			}			
		}		
		
		for (int i = 0; i < num; i++)
		{
			blockRead[i].clear();
			blockWrite[i].writeBlock(*(fileWriteArr[i]));
		}
		closeArrFile(fileReadArr, num);
		closeArrFile(fileWriteArr, num);

		if (!areAllFilesUsed)
			num = counter;
		flag++;
		if (num == 1)
			flag = 0;

		delete[] series;
	}
	
	delete[] blockRead;
	delete[] blockWrite;
	delete[] fileReadArr;
	delete[] fileWriteArr;
	return fileName2;
}