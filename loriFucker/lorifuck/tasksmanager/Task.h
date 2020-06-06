#ifndef TaskH
#define TaskH

#include <string>
#include "..\framesmanager\FramesManager.h"
#include "..\imageproportion\ImageProportion.h"

class Task{
	public:
		Task(std::string inPatch);
		~Task();
		std::string getPatch();

		FramesManager *getFramesManager();

		ImageProportion *getImageProportion();

		int getHorizontalFrames();
		int getVerticalFrames();
		void setHorizontalFrames(int inHorizontalFrames);
		void setVerticalFrames(int inVerticalFrames);

		int getHorizontalResultSize();
		int getVerticalResultSize();

	private:
		std::string taskPatch;

		//�������� ���������� ����������� ������
		FramesManager *framesManager;
		
		//��������� �����������
		ImageProportion *imageProportion;

		//������ �� ��������� � �����������
		int verticalFrames;
		int horizontalFrames;
};

#endif