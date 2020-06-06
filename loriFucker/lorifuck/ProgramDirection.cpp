#include "ProgramDirection.h"
#include "mytypes\BitmapContainer.h"
#include "mytypes\Color.h"
#include "mytypes\Utils.h"

ProgramDirection *programDirection;

//������������ ��������� ���������� �����
DWORD WINAPI trackStatusThread(LPVOID lp){
	programDirection->trackWorkStatus();
	return 0;
}

//������������ ��������� ���������� �����
void ProgramDirection::trackWorkStatus(){
	int stateValue = 0;
	
	//��� ������ ������� ������������� ��������� 100% ���� ����� ��������
	while (stateValue < 100){
		//�������� ��������� ������������� ���� ����� � ���������
		stateValue = taskWorker->getTaskStatus();
		
		//� ����������
		taskWindow->setSatusTaskProgressBar(stateValue);

		//���������� ������ �����
		if (programState == STOP) break;

		//� ���� 2 �������
		Sleep(100);
	}

	//������ ���������, ������������� ������������ STOP
	taskWindow->stopConfiguration();

	programState = STOP;
}

ProgramDirection::ProgramDirection(){
	programDirection = this;
	
	//������ �������� �����
	taskManager = new TaskManager();

	//���������� ������� ������ ������������� �������
	taskWindow = new TaskWindow(this);

	//������ ������� ��� ����� ������� ����������
	pauseEventHandle = CreateEvent(
		NULL,
		TRUE,
		TRUE,
		"pause_lori_fucker"
	);

	programState = STOP;

	taskWindow->showWindow();
}



TaskManager *ProgramDirection::getTaskManager(){
	return taskManager;
}

//�������� ������
bool ProgramDirection::addTask(std::string taskPatch){
	//������ ����� ������
	Task *task = new Task(taskPatch);

	//��������� � ��������
	return taskManager->addTask(task);
}

//������� ������
void ProgramDirection::deleteTask(std::string taskPatch){
	taskManager->deleteTask(taskPatch);
}

//����������� ������ �����
void ProgramDirection::taskMoveUp(std::string taskPatch){
	taskManager->taskMoveUp(taskPatch);
}
		
//����������� ������ ����
void ProgramDirection::taskMoveDown(std::string taskPatch){
	taskManager->taskMoveDown(taskPatch);
}

void ProgramDirection::pause(){
	ResetEvent(pauseEventHandle);
}

void ProgramDirection::stop(){
	//�������� ��������
	programState = STOP;//� ������� ������������ ��������
	taskWorker->stopWorking();
	//���� ���� �����, ����������� ������
	SetEvent(pauseEventHandle);
}

void ProgramDirection::startWorkTasks(){
	if (programState == PLAY){
		SetEvent(pauseEventHandle);
		return;
	}
	programState = PLAY;

	//������ ����� ������������� �������� ������
	statusThread = CreateThread(NULL, 0, trackStatusThread, 0, 0, NULL);

	//����������� �����
	taskWorker = new TaskWorker(taskManager);
}