#ifndef FramesManagerH
#define FramesManagerH

#include <string>
#include <windows.h>
#include <stdio.h>
#include "..\mytypes\Utils.cpp"
#include "..\mytypes\BitmapContainer.h"

class  FramesManager{
	public:
		FramesManager(std::string inPatch);

		//���������� ������������ ����� ���������
		int getFramesAmount();

		//���������� ����� ����������� ��������� ���������� � ������
		int getFramesOmit();

		//���������� ����������� ��������� ���������
		BitmapContainer* getFrame(int frameNumber);

		//��� ������ ������� ���������-(��) ������ ������
		int getFrameSideSize();
	private:
		std::string taskPatch;
		
		//����� ����������� ������� � ������
		int taskFrames;

		//����� ����������� ��������� � ������
		int taskOmit;

		

		//��������� ����� ����� �� �����
		std::string fileNameBeginPart;

		//�������� ����� ����� �����
		std::string fileNameEndPart;

		//������������ ����������� ������� � ���������
		void countFramesAndOmit();

		//�������� ������� ����� �� �����
		bool IsFileExist(std::string patch);

		//������ ������ ���� � ��������� frameNumber
		std::string generatePatch(int frameNumber);

		////////////////////////������ ���������////////////////
		//������ ������ ��������� ������
		int frameSideSize;

		//��������� ������ ���������
		int generateFrameSideSize();
};

#endif