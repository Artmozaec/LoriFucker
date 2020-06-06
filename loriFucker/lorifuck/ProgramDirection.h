#ifndef ProgramDirectionH
#define ProgramDirectionH


#include <windows.h>
#include <stdio.h>
#include "userinterface\TaskWindow.h"
#include "userinterface\taskselector\lastpatch\LastPatch.h"
#include "tasksmanager\TaskManager.h"
#include "taskworker\TaskWorker.h"
#include "mytypes\Utils.h"
#include <string>

enum ProgramState{
	STOP,
	PLAY,
};

class TaskWindow;
class ProgramDirection{
	public:
		ProgramDirection();

		//���������� ������ �� �������� �����
		TaskManager *getTaskManager();

		//�������� ������
		bool addTask(std::string taskPatch);

		//������� ������
		void deleteTask(std::string taskPatch);

		//����������� ������ �����
		void taskMoveUp(std::string taskPatch);
		
		//����������� ������ ����
		void taskMoveDown(std::string taskPatch);

		//������ ���������� �����
		void startWorkTasks();
		
		//
		void pause();
		void stop();

		//������������ ��������� ���������� �����
		void trackWorkStatus();
	private:
		//������ �� ����������
		//HINSTANCE *hInst;
		//��������� �� ������� �����, ��� ����������������� ������� ������
		HANDLE pauseEventHandle;

		HANDLE statusThread;
		
		//���� ������������� �������
		TaskWindow *taskWindow;

		//�������� �����
		TaskManager *taskManager;

		//������ �� ���������� �����
		TaskWorker *taskWorker;

		//��������� ���������
		ProgramState programState;
};

#endif