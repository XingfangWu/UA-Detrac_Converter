#include "tracker.hpp"

MKCFTracker::MKCFTracker(int start, int end, int merge, int unmatched, int minTrackLength)
{
	ids =0; 	
	startframe = start, minTrackLengthth = minTrackLength, mergeth = merge; unmatchedDurationth=unmatched;
	endframe = end;
}

void MKCFTracker::saveLastActiveTracks()
{
	for (int i = 0; i < activeTracks.size(); i++)
	{
		Result.push_back(activeTracks[i]);
	}
	activeTracks.clear();	
}

MKCFTracker::~MKCFTracker()
{
}

bool MKCFTracker::saveToXML(string filename)
{
	saveLastActiveTracks();
	ofstream outdata;

	string filename1 = filename+".xml";
	// string str2=".";
	// filename1.replace(filename1.find(str2),str2.length()+3,".xml");

	outdata.open(filename1, ios::out);	
	outdata << "<?xml version="<< char(34) << "1.0"<< char(34) << "?>"<< endl;
	outdata << "<Video fname="<< char(34)<< filename1<< char(34) << " start_frame=" << char(34) << startframe << char(34) << " end_frame=" << char(34) << endframe << char(34)<<">" << endl;

	for(int i=0;i<Result.size();i++)
	{
		if(Result[i].bboxes.size()>minTrackLengthth) // Tracks longer than N
		{
			outdata << "	<Trajectory obj_id=" << char(34) << Result[i].label << char(34) << " obj_type=" << char(34) << "Unknown" << char(34) << " start_frame = " << char(34) << Result[i].startframe << char(34) << " end_frame = " << char(34) << Result[i].startframe + Result[i].bboxes.size() - 1 << char(34) << ">" << endl;
			for (int j = 0; j < Result[i].bboxes.size(); j++) {
					if(Result[i].bboxes[j].x<0) Result[i].bboxes[j].x=0;
					if(Result[i].bboxes[j].y<0) Result[i].bboxes[j].y=0;
					outdata << "		<Frame frame_no=" << char(34) << Result[i].startframe+j
						<< char(34) << " x=" << char(34) << Result[i].bboxes[j].x
						<< char(34) << " y=" << char(34) << Result[i].bboxes[j].y 
						<< char(34) << " width=" << char(34) << Result[i].bboxes[j].width
						<< char(34) << " height=" << char(34) << Result[i].bboxes[j].height
						<< char(34) << " observation=" << char(34) << 0 << char(34) << " annotation=" << char(34)
						<< 0 << char(34) << " contour_pt=" << char(34) << 0 << char(34) << "></Frame>" << endl;
			}//for
			outdata << "	</Trajectory>" << endl;
		}

	}//for
	outdata << "</Video>";
	outdata.close();
	return true;
}

bool MKCFTracker::readUADetrac(string filename)
{
	string filename1 = filename;
	string str2=".";
	filename1.replace(filename1.rfind(str2),str2.length()+3,"_LX.txt");
	string filename2 = filename;
	filename2.replace(filename2.rfind(str2),str2.length()+3,"_LY.txt");
	string filename3 = filename;
	filename3.replace(filename3.rfind(str2),str2.length()+3,"_W.txt");
	string filename4 = filename;
	filename4.replace(filename4.rfind(str2),str2.length()+3,"_H.txt");

	ifstream indata1, indata2, indata3, indata4;

	indata1.open(filename1, ios::in);
	indata2.open(filename2, ios::in);
	indata3.open(filename3, ios::in);
	indata4.open(filename4, ios::in);


	string line1, line2, line3, line4;

	int i = 0;
	int nbobj = 0;
	// Read all the other lines
	while (std::getline(indata1, line1))
	{

		if(i++==0){
			nbobj = count(line1.begin(), line1.end(), ',')+1;
			cout << "Number of objects:" << nbobj << endl;
			Result.resize(nbobj);
			for (int j=0; j<nbobj; j++) 
			{
				Result[j].label = j+1;
			}
		}

		getline(indata2, line2);
		getline(indata3, line3);
		getline(indata4, line4);

		stringstream ss1(line1);
		stringstream ss2(line2);
		stringstream ss3(line3);
		stringstream ss4(line4);

    	for (int j=0; j<nbobj; j++) 
		{
			Rect2d bbox;
			ss1 >> bbox.x;
			ss2 >> bbox.y;
			ss3 >> bbox.width;
			ss4 >> bbox.height;
			if(bbox.x != 0 && bbox.width !=0 && bbox.height !=0 && Result[j].startframe == -1)
				Result[j].startframe = i;
		
			if(bbox.x != 0 && bbox.width !=0 && bbox.height !=0)
				Result[j].bboxes.push_back(bbox);		
		    
        	if (ss1.peek() == ',')
			{
            	ss1.ignore();
				ss2.ignore();
				ss3.ignore();
				ss4.ignore();
			}	
    	}
	}
	return true;
}

