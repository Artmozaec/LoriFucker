#include "TaskWorker.h"
#include "..\mytypes\Utils.h"

TaskWorker *taskWorker;

DWORD WINAPI threadTaskWork(LPVOID lp){
	taskWorker->workAllTask();
	return 0;
}

TaskWorker::TaskWorker(TaskManager *inTaskManager){
	taskManager = inTaskManager;

	logoCleaner = new LogoCleaner();

	taskWorker = this;

	play = true;

	//������������ ����� ����������� ���������� �����
	allTaskFrames = calculateAllFramesInTasks(taskManager);

	//���������� ������� � 0
	globalFramesCounter = 0;

	//�������� ������� �����
	pauseEventHandle = OpenEvent(SYNCHRONIZE, FALSE, "pause_lori_fucker");

	//������ ����� ���������� �����
	taskThread = CreateThread(NULL, 0, threadTaskWork, 0, 0, NULL);
}

int TaskWorker::calculateAllFramesInTasks(TaskManager* taskManager){
	Task *task;
	int result = 0;
	for (int taskCh=0; taskCh<taskManager->length(); taskCh++){
		task = taskManager->getTask(taskCh);
		result += task->getFramesManager()->getFramesAmount();
	}
	return result;
}

//��������� ���� �����
void TaskWorker::workAllTask(){
	for (int taskCh=0; taskCh<taskManager->length(); taskCh++){
		//������������ ������� ������
		workTask(taskManager->getTask(taskCh));
	}
}



//��������� ����� ������
void TaskWorker::workTask(Task *task){
	FramesManager *framesManager = task->getFramesManager();
	
	//������ ������� ���������
	int fragmentSize = framesManager->getFrameSideSize();
	
	//������ �������������� ����������� 
	//���� ����� ����������� ���������
	BitmapContainer *resultBitmap = new BitmapContainer(
		task->getHorizontalResultSize(),
		task->getVerticalResultSize()
	);

	BitmapContainer *fragment = NULL;
	int framePosHor = 0;
	int framePosVert = 0;
	for (int frameCh=0; frameCh<framesManager->getFramesAmount(); frameCh++){
		//��������� ��������� ��������
		fragment = framesManager->getFrame(frameCh);
		//fragment->getPixel(1,1);
		//���������, ���-�� �����, ���� ���� ��������
		WaitForSingleObject(pauseEventHandle, INFINITE);

		//��������� �� ����-��..
		if (!play) return;

		//��������� ��� ���� �����
		if ((fragment->getShirina()<fragmentSize) || 
			(fragment->getVisota()<fragmentSize)){

			fragment->crop(fragmentSize, fragmentSize, TOP_LEFT);
		}
		//������������ �����
		logoCleaner->clearLogo(fragment);
		
		//fragment->saveImage(std::string("C:\\chiphr.tif"));
		
		////////////////�������////////////
		#ifdef _MyDEBUG
			frameCh=framesManager->getFramesAmount();
			globalFramesCounter = frameCh;
		#endif

		//��������� ������������ ����� � ������������� �����������
		//MessageBox(NULL, IntToStr(frameCh).c_str(), "�", MB_OK);
		resultBitmap->addFragment(fragment, framePosHor*fragmentSize, framePosVert*fragmentSize);
		
		//����������
		delete(fragment);

		framePosHor++;
		if (framePosHor>task->getHorizontalFrames()-1){
			framePosHor = 0;
			framePosVert++;
		}
		//����������� ���������� �������
		globalFramesCounter++;
	}

	//��������� ���������
	std::string patch;
	patch += task->getPatch().c_str();
	patch += "\\assembly.jpg";
	//MessageBox(NULL, patch.c_str(), "�", MB_OK);
	resultBitmap->saveImage(patch);
}

int TaskWorker::getTaskStatus(){
	return (globalFramesCounter*100)/allTaskFrames;
}



//���������� ���������� ���� �����
void TaskWorker::stopWorking(){
	play = false;
}
