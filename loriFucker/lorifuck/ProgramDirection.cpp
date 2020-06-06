#include "ProgramDirection.h"
#include "mytypes\BitmapContainer.h"
#include "mytypes\Color.h"
#include "mytypes\Utils.h"

ProgramDirection *programDirection;

//Отслеживание прогресса выполнения задач
DWORD WINAPI trackStatusThread(LPVOID lp){
	programDirection->trackWorkStatus();
	return 0;
}

//Отслеживание прогресса выполнения задач
void ProgramDirection::trackWorkStatus(){
	int stateValue = 0;
	
	//Как только уровень завершенности достигнет 100% тред будет завершён
	while (stateValue < 100){
		//Получаем состояние выполненности всех задач в процентах
		stateValue = taskWorker->getTaskStatus();
		
		//И отображаем
		taskWindow->setSatusTaskProgressBar(stateValue);

		//Прерывание потока извне
		if (programState == STOP) break;

		//И спим 2 секунды
		Sleep(100);
	}

	//Задачи завершены, устанавливаем конфигурацию STOP
	taskWindow->stopConfiguration();

	programState = STOP;
}

ProgramDirection::ProgramDirection(){
	programDirection = this;
	
	//Создаём менеджер задач
	taskManager = new TaskManager();

	//Показываем главный диалог конфигуратора заданий
	taskWindow = new TaskWindow(this);

	//создаём событие для паузы потоков выполнения
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

//Добавить задачу
bool ProgramDirection::addTask(std::string taskPatch){
	//Создаём новую задачу
	Task *task = new Task(taskPatch);

	//Добавляем в менеджер
	return taskManager->addTask(task);
}

//Удалить задачу
void ProgramDirection::deleteTask(std::string taskPatch){
	taskManager->deleteTask(taskPatch);
}

//Переместить задачу вверх
void ProgramDirection::taskMoveUp(std::string taskPatch){
	taskManager->taskMoveUp(taskPatch);
}
		
//Переместить задачу вниз
void ProgramDirection::taskMoveDown(std::string taskPatch){
	taskManager->taskMoveDown(taskPatch);
}

void ProgramDirection::pause(){
	ResetEvent(pauseEventHandle);
}

void ProgramDirection::stop(){
	//Обрываем процессы
	programState = STOP;//И процесс отслеживания прервётся
	taskWorker->stopWorking();
	//Если была пауза, освобождаем объект
	SetEvent(pauseEventHandle);
}

void ProgramDirection::startWorkTasks(){
	if (programState == PLAY){
		SetEvent(pauseEventHandle);
		return;
	}
	programState = PLAY;

	//Создаём поток отслеживающий прогресс работы
	statusThread = CreateThread(NULL, 0, trackStatusThread, 0, 0, NULL);

	//Исполнитель задач
	taskWorker = new TaskWorker(taskManager);
}