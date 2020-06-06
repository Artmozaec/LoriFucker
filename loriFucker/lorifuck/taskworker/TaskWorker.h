#ifndef TaskWorkerH
#define TaskWorkerH

#include "..\tasksmanager\TaskManager.h"
#include "..\tasksmanager\Task.h"
#include "..\mytypes\BitmapContainer.h"
#include "logocleaner\LogoCleaner.h"

class TaskWorker{
	public:
		TaskWorker(TaskManager *inTaskManager);
		
		//Остановить выполнение всех задач
		void stopWorking();

		//Обработка всех задач
		void workAllTask();

		int getTaskStatus();

	private:
		TaskManager *taskManager;

		HANDLE taskThread;

		bool play;

		//Указатель на событие паузы, для приостанавливания потоков сборки
		HANDLE pauseEventHandle;

		//Обработка одной задачи
		void workTask(Task *task);

		LogoCleaner *logoCleaner;

		/////////////////////////СЧЁТЧИКИ ПРОГРЕССА////////////////////
		//Подсчёт колличества фрагментов во всех задачах
		int calculateAllFramesInTasks(TaskManager* taskManager);

		//Колличество фрагментов во всех задачах
		int allTaskFrames;

		//Глобальный счётчик обработанных фрагментов
		int globalFramesCounter;

};

#endif