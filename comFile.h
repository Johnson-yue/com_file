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

class BoxExtractor {
public:
	Rect extract(Mat img);
	Rect extract(const std::string& windowName, Mat img, bool showCrossair = true);

	struct handlerT{
		bool isDrawing;
		Rect box;
		Mat image;

		// initializer list
		handlerT() : isDrawing(false) {};
	}params;

private:
	static void mouseHandler(int event, int x, int y, int flags, void *param);
	void opencv_mouse_callback(int event, int x, int y, int, void *param);
};

