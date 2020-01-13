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
#include <boost/filesystem.hpp>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>
#include <set>
#include "tracker.hpp"

using namespace cv;
using namespace std;
namespace bf = boost::filesystem;

int main(int argc, char **argv)
{
	int startframe, endframe;
	string filepath, bgsfolder, maskfilename, outputtype, resfilename;	
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

	if(argc==2)
	{
		filepath= argv[1];
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


	bf::path path(filepath);
	bf::path parent = path.parent_path();
	bf::current_path(parent);
	// cout<<path.filename()<<endl;
	string newpathstr = path.filename().string() + "_converted";
	bf::path newpath(newpathstr);
	if(!bf::exists(newpathstr)){
		bf::create_directory(newpath);
	}

	bf::directory_iterator endIter;
	for (bf::directory_iterator iter(path); iter != endIter; iter++) {
	  if (bf::is_directory(*iter)) {
	  	bf::path output_path(newpath/iter->path().filename());
	    bf::create_directory(output_path);
	    set<string> videos;
		for (bf::directory_iterator iter_2(*iter); iter_2 != endIter; iter_2++) {
		  if (!bf::is_directory(*iter_2)) {
		  	string s = iter_2->path().filename().string();
		  	videos.insert(s.substr(0, s.rfind('_')));
		  }
		}
		for(set<string>::iterator itr=videos.begin(); itr != videos.end() ; itr++){
			MKCFTracker trackeur(startframe, endframe, Merge_threshold, UnmatchedDuration, minTrackLength);
			trackeur.readUADetrac((*iter/ *itr).string()+".txt");
			trackeur.saveToXML(string("./")+(output_path/ *itr).string());
		}

	  }

	}


	MKCFTracker trackeur(startframe, endframe, Merge_threshold, UnmatchedDuration, minTrackLength);

	// trackeur.readUADetrac(filename);

	// trackeur.saveToXML(resfilename.c_str());
	

	return 1;

}//main
