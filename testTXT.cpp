#include "comFile.h"
#include <iostream>
#include<string>
#include<vector>

using namespace std;

int main()
{
	comFile a;

	vector<string> information;
	
	char num[512];
	string  prefix="²âÊÔµÚ",after="ÐÐ";
	string fileName = "E:\\name.txt";

	for (int i = 0; i < 10; i++)
	{
		_itoa_s(i, num, 10);
		string order(num);
		string text = prefix + order + after+"\n";

		information.push_back(text);
	}

	//a.write_txt(information, fileName);
	//cout << "write done!!" << endl;

	vector<string> reread;
	a.read_txt(reread, fileName);
	cout << "read done!!" << endl;

	return 0;

}