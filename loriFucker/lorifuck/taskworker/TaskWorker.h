#ifndef TaskWorkerH
#define TaskWorkerH

#include "..\tasksmanager\TaskManager.h"
#include "..\tasksmanager\Task.h"
#include "..\mytypes\BitmapContainer.h"
#include "logocleaner\LogoCleaner.h"

class TaskWorker{
	public:
		TaskWorker(TaskManager *inTaskManager);
		
		//���������� ���������� ���� �����
		void stopWorking();

		//��������� ���� �����
		void workAllTask();

		int getTaskStatus();

	private:
		TaskManager *taskManager;

		HANDLE taskThread;

		bool play;

		//��������� �� ������� �����, ��� ����������������� ������� ������
		HANDLE pauseEventHandle;

		//��������� ����� ������
		void workTask(Task *task);

		LogoCleaner *logoCleaner;

		/////////////////////////�ר����� ���������////////////////////
		//������� ����������� ���������� �� ���� �������
		int calculateAllFramesInTasks(TaskManager* taskManager);

		//����������� ���������� �� ���� �������
		int allTaskFrames;

		//���������� ������� ������������ ����������
		int globalFramesCounter;

};

#endif