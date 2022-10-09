#pragma once
#include <climits>

class seriesRead
{
	unsigned long long prev, curr;
	bool isSeries, isEndOfFile;
public:
	seriesRead();

	bool getIsSeries();

	void setIsSeries(bool);

	void setIsEndOfFile(bool);

	bool getIsEndOfFile();

	bool addNumDetermineSeries(unsigned long long);

	unsigned long long getCurr();

	void clear();
};