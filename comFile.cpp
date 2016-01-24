#include "comFile.h"


comFile::comFile()
{
}


comFile::~comFile()
{
}

void comFile::write_txt(vector<string> info, string out_file, int Mode)
{
	int num = info.size();

	if (num <= 0)
	{
		cout << "write information is empty!!!please check input " << endl;
		return;
	}

	ofstream outfile;

	switch (Mode)
	{
	case 1:outfile.open(out_file.c_str()); 
		break;
	case 2:outfile.open(out_file.c_str(), ios::app); 
		break;
	default:outfile.open(out_file.c_str());
		break;
	}

	if (!outfile.is_open())
	{
		cout << "open file :" << out_file << "has failed!!!!" << endl;
		return;
	}

	for (size_t i = 0; i < num; i++)
	{
		outfile << info[i] << "\r";
	}

	outfile.close();
	return;
}

void comFile::read_txt(vector<string>& info, string in_file)
{
	char buf[1024];

	ifstream file(in_file.c_str());

	if (!file.is_open())
	{
		cout << "open file :" << in_file << "has failed!!" << endl;
		return;
	}

	for (int i =0; file.good() && !file.eof();i++)
	{
		//memset(buf, 0, 1024);
		//file.getline(buf, 1024);      //读取的内容包含换行符
		//string message(buf);

		string message;
		file >>message ;				//读取的内容不包含换行符

		cout << "comFile::read_txt--line :" << message << endl;
		info.push_back(message);
	}

	file.close();
	return;

}