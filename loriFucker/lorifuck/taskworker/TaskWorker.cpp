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

	//Подсчитываем общее колличество фрагментов задач
	allTaskFrames = calculateAllFramesInTasks(taskManager);

	//Глобальный счётчик в 0
	globalFramesCounter = 0;

	//Получаем события паузы
	pauseEventHandle = OpenEvent(SYNCHRONIZE, FALSE, "pause_lori_fucker");

	//Создаём поток выполнения задач
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

//Обработка всех задач
void TaskWorker::workAllTask(){
	for (int taskCh=0; taskCh<taskManager->length(); taskCh++){
		//Обрабатываем текущую задачу
		workTask(taskManager->getTask(taskCh));
	}
}



//Обработка одной задачи
void TaskWorker::workTask(Task *task){
	FramesManager *framesManager = task->getFramesManager();
	
	//Размер стороны фрагмента
	int fragmentSize = framesManager->getFrameSideSize();
	
	//Создаём результирующее изображение 
	//куда будут вставляться фрагменты
	BitmapContainer *resultBitmap = new BitmapContainer(
		task->getHorizontalResultSize(),
		task->getVerticalResultSize()
	);

	BitmapContainer *fragment = NULL;
	int framePosHor = 0;
	int framePosVert = 0;
	for (int frameCh=0; frameCh<framesManager->getFramesAmount(); frameCh++){
		//Загружаем очередной фрагмент
		fragment = framesManager->getFrame(frameCh);
		//fragment->getPixel(1,1);
		//Проверяем, нет-ли паузы, если есть засыпаем
		WaitForSingleObject(pauseEventHandle, INFINITE);

		//Проверяем не стоп-ли..
		if (!play) return;

		//Расширяем его если нужно
		if ((fragment->getShirina()<fragmentSize) || 
			(fragment->getVisota()<fragmentSize)){

			fragment->crop(fragmentSize, fragmentSize, TOP_LEFT);
		}
		//Обрабатываем фрейм
		logoCleaner->clearLogo(fragment);
		
		//fragment->saveImage(std::string("C:\\chiphr.tif"));
		
		////////////////отЛАДКА////////////
		#ifdef _MyDEBUG
			frameCh=framesManager->getFramesAmount();
			globalFramesCounter = frameCh;
		#endif

		//Добавляем обработанный фрейм в результрующее изображение
		//MessageBox(NULL, IntToStr(frameCh).c_str(), "Ы", MB_OK);
		resultBitmap->addFragment(fragment, framePosHor*fragmentSize, framePosVert*fragmentSize);
		
		//Уничтожаем
		delete(fragment);

		framePosHor++;
		if (framePosHor>task->getHorizontalFrames()-1){
			framePosHor = 0;
			framePosVert++;
		}
		//Увеличиваем глобальный счетчик
		globalFramesCounter++;
	}

	//Сохраняем результат
	std::string patch;
	patch += task->getPatch().c_str();
	patch += "\\assembly.jpg";
	//MessageBox(NULL, patch.c_str(), "Ы", MB_OK);
	resultBitmap->saveImage(patch);
}

int TaskWorker::getTaskStatus(){
	return (globalFramesCounter*100)/allTaskFrames;
}



//Остановить выполнение всех задач
void TaskWorker::stopWorking(){
	play = false;
}
