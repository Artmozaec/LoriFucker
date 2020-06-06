#include "Task.h"

Task::Task(std::string inPatch){
	taskPatch = inPatch;

	//Менеджер фрагментов задачи
	framesManager = new FramesManager(taskPatch);

	imageProportion = new ImageProportion(framesManager->getFramesAmount());
	
	verticalFrames = imageProportion->getMedian();
	horizontalFrames = imageProportion->getSecondSideFrames(verticalFrames);
}


Task::~Task(){
	delete(framesManager);
	delete(imageProportion);
}

std::string Task::getPatch(){
	return taskPatch;
}

FramesManager *Task::getFramesManager(){
	return framesManager;
}

ImageProportion *Task::getImageProportion(){
	return imageProportion;
}


int Task::getHorizontalFrames(){
	return horizontalFrames;
}

int Task::getVerticalFrames(){
	return verticalFrames;
}

void Task::setHorizontalFrames(int inHorizontalFrames){
	horizontalFrames = inHorizontalFrames;
}

void Task::setVerticalFrames(int inVerticalFrames){
	verticalFrames = inVerticalFrames;
}

int Task::getHorizontalResultSize(){
	int horizontalSize = (horizontalFrames-1)*framesManager->getFrameSideSize();

	//Получаем самый левый фрагмент, он может быть обрезан
	BitmapContainer *leftFrame = framesManager->getFrame(horizontalFrames-1);

	//Складываем его размер с общей шириной
	return horizontalSize+leftFrame->getShirina();
}

int Task::getVerticalResultSize(){
	int verticalSize = (verticalFrames-1)*framesManager->getFrameSideSize();
	
	//Получаем самый нижний фрагмент, он может быть обрезан
	BitmapContainer *downFrame = framesManager->getFrame((verticalFrames*horizontalFrames)-3);

	return verticalSize+downFrame->getVisota();
}