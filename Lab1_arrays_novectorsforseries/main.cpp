#include "fileWork.h"
#include <string>
int main()
{	
	const string fileName = "base.txt";
	srand(time(NULL));
	bool flag = true;
	unsigned long long a;
	while (flag)
	{
		cout << "Press 1 to create a new file, 2 to sort, 3 to open certain file, 0 to exit: ";
		cin >> a;
		string str;
		switch (a)
		{
		case 1:
			cout << " 1gb == 1024mb"
			   << "\n32gb == 32768mb"
				"\nEnter the size of file in mb: ";
			cin >> a;
			if(a >= 32768/2)
				createFile(fileName, a* (131072/2) , 2);
			else
				createFile(fileName, a * 131072);
			cout << "File " << fileName << " is created successfully!\n\n";
			break;
		case 2:
			cout << "Enter the number of files of one type in range [2, 10]: ";
			cin >> a;
			if (a < 2 || a > 10)
				cout << "Invalid value. Try [2, 10].\n\n";
			else
				str = sortFile(a, fileName);
			cout << "The file is successfully sorted. Results are in file " << str << "1.txt.\n\n";
			break;
		case 3:
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the name of file: ";
			getline(cin, str);
			cout << "Enter the number of displayed numbers: ";
			cin >> a;
			cout << "File " << str << ": \n";
			readFile(str, a);
			cout << endl;
			break;
		case 0:
			flag = false;
			break;
		default:
			break;
		}
	}
	return 0;
}