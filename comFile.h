#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define W  1		//write only
#define ADD 2		//addition write

#pragma once
class comFile
{
public:
	comFile();
	~comFile();

	void write_txt(vector<string> info, string out_file, int Mode=1);
	void read_txt(vector<string>& info, string in_file);
};

