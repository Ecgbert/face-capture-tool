#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <fstream>  
#include <iostream> 
#include <stdio.h>
#include <string>

using namespace std;
using namespace cv;
void detectAndDisplay(Mat frame);

String face_cascade_name = "C:/Users/John/Documents/Visual Studio 2013/Projects/test/test/haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;
string filename;
string extension;
int main(int argc, const char *argv[])
{
	
	
	fstream file_list("name.txt", std::ios::out);
	file_list.close();
	//fstream file_list;
	
	system("dir /a /b >> name.txt");

	if (!face_cascade.load(face_cascade_name))
	{
		printf("--(!)Error loading\n"); return -1;
	}
	file_list.open("name.txt", std::ios::in);
	//while (getline(file_list, filename))
	
	while (!file_list.eof())
	{
		getline(file_list, filename);
		cout << filename << endl;
		//int location = filename.find(".");
		if (filename.find(".", 0) != string::npos)
		{
			extension = filename.substr(filename.find("."));
			if (0 == extension.compare(".jpg") || 0 == extension.compare(".png") || 0 == extension.compare(".JPG") || 0 == extension.compare(".PNG"))
			{
				//filename = "C:\\Users\\John\\Documents\\Visual Studio 2013\\Projects\\test\\x64\\Release\\" + filename;
				Mat frame = imread(filename);
				detectAndDisplay(frame);
			}
		}
		//system("pause");	
	}
	file_list.close();
	return 0;
}

void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat faceROI, crop, res, gray;
	//-- Detect faces
	cvtColor(frame, gray, COLOR_RGB2GRAY);
	equalizeHist(gray, gray);
	face_cascade.detectMultiScale(gray, faces, 1.2, 5, CV_HAAR_DO_CANNY_PRUNING, Size(20, 100));
	cv::Rect roi_b;
	cv::Rect roi_c;
	size_t ic = 0; // ic is index of current element
	int ac = 0; // ac is area of current element

	size_t ib = 0; // ib is index of biggest element
	int ab = 0; // ab is area of biggest element

	for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
	{
		roi_c.x = faces[ic].x;
		roi_c.y = faces[ic].y;
		roi_c.width = (faces[ic].width);
		roi_c.height = (faces[ic].height);

		ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

		roi_b.x = faces[ib].x;
		roi_b.y = faces[ib].y;
		roi_b.width = (faces[ib].width);
		roi_b.height = (faces[ib].height);

		ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

		if (ac > ab)
		{
			ib = ic;
			roi_b.x = faces[ib].x;
			roi_b.y = faces[ib].y;
			roi_b.width = (faces[ib].width);
			roi_b.height = (faces[ib].height);
		}
		crop = frame(roi_b);
		resize(crop, res, Size(256, 256), 0, 0, INTER_LINEAR); // This will be needed later while saving images
		//char image_name[128];
		//sprintf(image_name, "resize_crop_%s", filename.c_str());
		stringstream ssfn;
		string _name = "crop_";
		ssfn << _name << filename;
		string image_name = ssfn.str();
		imwrite(image_name, res);
		cout << image_name << "已處理" << endl;
	}
}
