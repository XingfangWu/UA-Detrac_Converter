import xml.etree.ElementTree as ET
import cv2
import numpy as np
import sys
import os


def convertXML(path, file):
	tree = ET.parse(path + "/" + file)
	root = tree.getroot()

	Mask = 255-np.zeros((540, 960), np.uint8)

	#Building mask

	for i in range(len(root[1])):
		y = int(float(root[1][i].get('top')))
		x = int(float(root[1][i].get('left')))
		h = int(float(root[1][i].get('height')))
		w = int(float(root[1][i].get('width')))
		Mask2 = cv2.rectangle(Mask, (x, y), (x+w, y+h), (0,0,0),-1)

	#cv2.imshow('ImageWindow', Mask2)
	#cv2.waitKey()
	if len(root[1]) >0 :
		cv2.imwrite('Mask.png',Mask2)

	Track = list()
	for j in range(0,500):
		Track.append([])

	minframe = int(float(root[2].get('num')))
	maxid =0
	for j in range(2,len(root)):
		frame = int(float(root[j].get('num')))
		for i in range(len(root[j][0])):
			id = int(float(root[j][0][i].get('id')))
			y = int(float(root[j][0][i][0].get('top')))
			x = int(float(root[j][0][i][0].get('left')))
			h = int(float(root[j][0][i][0].get('height')))
			w = int(float(root[j][0][i][0].get('width')))
			Track[id].append([frame,y,x,w,h])
			if id>maxid:
				maxid=id
		
	maxframe = frame
	# print(maxid)

	if not os.path.exists(path+"/converted"):
		os.makedirs(path+"/converted")

	file1 = open(path+"/converted/"+f,'w')

	file1.write('<?xml version="1.0"?>\n')
	text = '<Video fname="Res.xml" start_frame="{}" end_frame="{}">\n'.format(minframe,maxframe)
	file1.write(text)
	for i in range(1,maxid):
		if len(Track[i]) > 0:
			text= '<Trajectory obj_id="{}" obj_type="Unknown" start_frame = "{}" end_frame = "{}">\n'.format(i,Track[i][0][0],Track[i][0][0]+len(Track[i]))
			file1.write(text)
			for bbox in Track[i]:
				text= '<Frame frame_no="{}" x="{}" y="{}" width="{}" height="{}" observation="0" annotation="0" contour_pt="0"></Frame>\n'.format(bbox[0], bbox[2],bbox[1], bbox[3], bbox[4])
				file1.write(text)
			file1.write('</Trajectory>\n')
	file1.write('</Video>\n')
	file1.close()


if len(sys.argv)!=2:
	sys.exit()

path = sys.argv[1]

files= os.listdir(path)

for f in files:
	if os.path.splitext(f)[-1]==".xml":
		convertXML(path, f)




