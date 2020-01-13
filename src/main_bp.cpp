#include <iostream>  
#include <string> 
#include "opencv2/opencv.hpp" 
#include <opencv2/opencv.hpp> 
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>
#include "tracker.hpp"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	int startframe, endframe;
	string filename, bgsfolder, maskfilename, outputtype, resfilename;	
	Mat  frame;
	vector <Frameresult> result;
	vector<Rect2d> bboxvec; 
	clock_t start, finish;
	char bgspath[300];

	//Parameters
	int Merge_threshold = 2000;     // square     example, 20^2=400.
	int Min_blob_size = 900;
	int UnmatchedDuration = 8;
	// int minTrackLength = 12;

	int minTrackLength = 0;
	char filepath[250];

	if(argc==3)
	{
		filename= argv[1];
		resfilename = argv[2];
	}
		else
	{
		cout << "Error: not enough arguments. Usage: arg1:input filename arg2:output filename" << endl;
		return -1;
	}
	
	
	cout << "starting..." << endl;
	
	startframe=1;
	endframe=0;	
	bool okonce=false;


	MKCFTracker trackeur(startframe, endframe, Merge_threshold, UnmatchedDuration, minTrackLength);

	trackeur.readUADetrac(filename);

	trackeur.saveToXML(resfilename.c_str());
	

	return 1;

}//main
