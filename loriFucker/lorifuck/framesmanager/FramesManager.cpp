#include "FramesManager.h"
#include <io.h>

FramesManager::FramesManager(std::string inPatch){
	taskPatch = inPatch;
	taskOmit = 0;
	taskFrames = 0;
	fileNameEndPart = ".jpg";
	//fileNameEndPart = ".tif";
	frameSideSize = 0;
	//������ ������� ������� � ��������� ������
	countFramesAndOmit();

	//������� ������ ���������
	frameSideSize = generateFrameSideSize();

	//���� �� ������ ��������� �� �������
	if (frameSideSize == -1){
		MessageBox(NULL, "�� ������� ���������� ������ ���������!!", "������-������", MB_ICONERROR);
	}
}

bool FramesManager::IsFileExist(std::string patch)
{
   DWORD dwAttr = GetFileAttributes(patch.c_str());
   return (dwAttr != 0xFFFFFFFF) && (0 == (dwAttr & FILE_ATTRIBUTE_DIRECTORY));
}

std::string FramesManager::generatePatch(int frameNumber){
	std::string patch;
	patch += taskPatch.c_str();
	patch += '\\';
	patch += IntToStr(frameNumber);
	patch = patch + fileNameEndPart;
	return patch;
}


void FramesManager::countFramesAndOmit(){
	int omitTogether = 0; //����������� ��������� ���������� �����
	std::string curPatch;

	while(true){	
		//���������� ���
		curPatch = generatePatch(taskFrames);

		if (!IsFileExist(curPatch)){ //���� ����� ���
			if (omitTogether>5){
				//���� ����������� ��������� ������ ������ ����������� ��������
				taskOmit -= omitTogether; //���� ��������� �� ����� ���� ���, ��� �� ��������� �������
				taskFrames -= omitTogether;
				return;
			}
			taskOmit++;
			omitTogether++;
		} else {//���� ����
			omitTogether = 0;
		}
		taskFrames++;
	}
}

int FramesManager::getFramesAmount(){
	return taskFrames;
}

int FramesManager::getFramesOmit(){
	return taskOmit;
}


BitmapContainer* FramesManager::getFrame(int frameNumber){
	std::string patch = generatePatch(frameNumber);
	if (IsFileExist(patch)){
		BitmapContainer *bitmapContainer = new BitmapContainer(generatePatch(frameNumber));
		/*

		*/
		return bitmapContainer;
	} else {//���� ����� ��� ���������� ������ �������
		return new BitmapContainer(255, 255);
	}
}


int FramesManager::getFrameSideSize(){
	return frameSideSize;
}

//������� ������ ��������� �������� � ������� ���������
int FramesManager::generateFrameSideSize(){
	//BitmapContainer *bitmap = NULL;
	for(int ch=0; ch<20; ch++){
		if (IsFileExist(generatePatch(ch))){
			BitmapContainer bitmap(generatePatch(ch));
			if (bitmap.getVisota() == bitmap.getShirina()){
				return bitmap.getShirina();
			}
			
		}
	}
	return -1;
}