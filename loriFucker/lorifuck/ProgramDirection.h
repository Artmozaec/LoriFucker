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

		//Возвращает ссылку на менеджер задач
		TaskManager *getTaskManager();

		//Добавить задачу
		bool addTask(std::string taskPatch);

		//Удалить задачу
		void deleteTask(std::string taskPatch);

		//Переместить задачу вверх
		void taskMoveUp(std::string taskPatch);
		
		//Переместить задачу вниз
		void taskMoveDown(std::string taskPatch);

		//Начать выполнение задач
		void startWorkTasks();
		
		//
		void pause();
		void stop();

		//Отслеживание прогресса выполнения задач
		void trackWorkStatus();
	private:
		//Ссылка на приложение
		//HINSTANCE *hInst;
		//Указатель на событие паузы, для приостанавливания потоков сборки
		HANDLE pauseEventHandle;

		HANDLE statusThread;
		
		//Окно конфигуратора заданий
		TaskWindow *taskWindow;

		//Менеджер задач
		TaskManager *taskManager;

		//Ссылка на обработчик задач
		TaskWorker *taskWorker;

		//Состояние программы
		ProgramState programState;
};

#endif