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

void BoxExtractor::mouseHandler(int event, int x, int y, int flags, void *param){
	BoxExtractor *self = static_cast<BoxExtractor*>(param);
	self->opencv_mouse_callback(event, x, y, flags, param);
}

void BoxExtractor::opencv_mouse_callback(int event, int x, int y, int, void *param){
	handlerT * data = (handlerT*)param;
	switch (event){
		// update the selected bounding box
	case EVENT_MOUSEMOVE:
		if (data->isDrawing){
			data->box.width = x - data->box.x;
			data->box.height = y - data->box.y;
		}
		break;

		// start to select the bounding box
	case EVENT_LBUTTONDOWN:
		data->isDrawing = true;
		data->box = cvRect(x, y, 0, 0);
		break;

		// cleaning up the selected bounding box
	case EVENT_LBUTTONUP:
		data->isDrawing = false;
		if (data->box.width < 0){
			data->box.x += data->box.width;
			data->box.width *= -1;
		}
		if (data->box.height < 0){
			data->box.y += data->box.height;
			data->box.height *= -1;
		}
		break;
	}
}

Rect BoxExtractor::extract(Mat img){
	return extract("Bounding Box Extractor", img);
}

Rect BoxExtractor::extract(const std::string& windowName, Mat img, bool showCrossair){

	int key = 0;

	// show the image and give feedback to user
	imshow(windowName, img);
	printf("Select an object to track and then press SPACE/BACKSPACE/ENTER button!\n");

	// copy the data, rectangle should be drawn in the fresh image
	params.image = img.clone();

	// select the object
	setMouseCallback(windowName, mouseHandler, (void *)&params);

	// end selection process on SPACE (32) BACKSPACE (27) or ENTER (13)
	while (!(key == 32 || key == 27 || key == 13)){
		// draw the selected object
		rectangle(
			params.image,
			params.box,
			Scalar(255, 0, 0), 2, 1
			);

		// draw cross air in the middle of bounding box
		if (showCrossair){
			// horizontal line
			line(
				params.image,
				Point((int)params.box.x, (int)(params.box.y + params.box.height / 2)),
				Point((int)(params.box.x + params.box.width), (int)(params.box.y + params.box.height / 2)),
				Scalar(255, 0, 0), 2, 1
				);

			// vertical line
			line(
				params.image,
				Point((int)(params.box.x + params.box.width / 2), (int)params.box.y),
				Point((int)(params.box.x + params.box.width / 2), (int)(params.box.y + params.box.height)),
				Scalar(255, 0, 0), 2, 1
				);
		}

		// show the image bouding box
		imshow(windowName, params.image);

		// reset the image
		params.image = img.clone();

		//get keyboard event
		key = waitKey(1);
	}


	return params.box;
}
