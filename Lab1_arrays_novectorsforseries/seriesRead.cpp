#include "seriesRead.h"

seriesRead::seriesRead() {
	curr = prev = 0;
	isSeries = true;
	isEndOfFile = false;
}

bool seriesRead::getIsSeries()
{
	return isSeries;
}

void seriesRead::setIsSeries(bool flag)
{
	isSeries = flag;
}

void seriesRead::setIsEndOfFile(bool flag)
{
	isEndOfFile = flag;
}

bool seriesRead::getIsEndOfFile()
{
	return isEndOfFile;
}

bool seriesRead::addNumDetermineSeries(unsigned long long num)
{
	prev = curr;
	curr = num;
	if (prev <= curr && curr != ULLONG_MAX)
		isSeries = true;
	else
		isSeries = false;
	return isSeries;
}

unsigned long long seriesRead::getCurr()
{
	return curr;
}

void seriesRead::clear()
{
	prev = 0;
	curr = 0;
	isSeries = true;
}
