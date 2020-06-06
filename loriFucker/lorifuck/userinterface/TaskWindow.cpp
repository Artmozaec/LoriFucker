#include "TaskWindow.h"
#include "..\..\resource.h"
#include "taskselector\TaskSelector.h"
#include "..\mytypes\StringList.h"
TaskWindow *taskWindow;

BOOL CALLBACK taskWindowDlgProc(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);


TaskWindow::TaskWindow(ProgramDirection *inProgramDirection){
	taskWindow = this;
	//thisHandle = NULL;
	//thisHandle = GetDlgItem(NULL, IDD_START_FORM);
	programDirection = inProgramDirection;
	
	HINSTANCE hndl = GetModuleHandle(NULL);

	//---------------Лист задач-----------------------------
	taskListBox = new ListBox(TASK_LIST);
	taskListBox->setOnDblItemClick(onDblClickTaskListBox);

	//---------------Инициализация кнопок--------------------
	//Добавить задание
	addTaskButton = new Button(IDC_ADD_TASK_BUTTON);
	addTaskButton->setEnableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_ADD_TASK_ACTIVE)));
	addTaskButton->setDisableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_ADD_TASK_PASSIVE)));
	addTaskButton->setOnClickHandler(onClickAddTaskButton);



	upTaskButton = new Button(IDC_UP_TASK_BUTTON);
	upTaskButton->setEnableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_UP_TASK_ACTIVE)));
	upTaskButton->setDisableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_UP_TASK_PASSIVE)));
	upTaskButton->setOnClickHandler(onClickUpTaskButton);
	
	
	downTaskButton = new Button(IDC_DOWN_TASK_BUTTON);
	downTaskButton->setEnableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_DOWN_TASK_ACTIVE)));
	downTaskButton->setDisableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_DOWN_TASK_PASSIVE)));
	downTaskButton->setOnClickHandler(onClickDownTaskButton);


	//Кнопка удаления
	deleteTaskButton = new Button(IDC_DELETE_TASK_BUTTON);
	deleteTaskButton->setEnableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_DELETE_TASK_ACTIVE)));
	deleteTaskButton->setDisableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_DELETE_TASK_PASSIVE)));
	deleteTaskButton->setOnClickHandler(onClickRemoveTaskButton);


	startButton = new Button(IDC_START_BUTTON);
	startButton->setEnableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_START_ACTIVE)));
	startButton->setDisableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_START_PASSIVE)));
	startButton->setOnClickHandler(onClickStartButton);


	pauseButton = new Button(IDC_PAUSE_BUTTON);
	pauseButton->setEnableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_PAUSE_ACTIVE)));
	pauseButton->setDisableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_PAUSE_PASSIVE)));
	pauseButton->setOnClickHandler(onClickPauseTaskButton);


	stopButton = new Button(IDC_STOP_BUTTON);
	stopButton->setEnableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_STOP_ACTIVE)));
	stopButton->setDisableImage(LoadBitmap(hndl, MAKEINTRESOURCE(IDB_STOP_PASSIVE)));
	stopButton->setOnClickHandler(onClickStopTaskButton);
	stopButton->disable();

	//Индикаторы прогресса
	taskProgressBar = new ProgressBar(5, 330, 20, 230);

	//Устанавливаем начальные состояния кнопок
	stopConfiguration();
}

TaskConfiguratorWindow::~TaskConfiguratorWindow(){

}


//Показать окно
void TaskWindow::showWindow(){
	HINSTANCE hndl = GetModuleHandle(NULL);

	DialogBox(
		hndl,
		MAKEINTRESOURCE(IDD_START_FORM), //Шаблон
		NULL, //Дескриптор родительского окна
		taskWindowDlgProc//Адрес процедуры обработки
	);	
}

void TaskWindow::onClickAddTaskButton(Button *callButton){
	TaskSelector *taskSelector = new TaskSelector();

	if (!taskSelector->showSelector()){
		//Если ничего не выбрали, выходим
		delete(taskSelector);
		return;
	}
	
	//Достаем выбранный путь
	std::string patch = taskSelector->getPatch();
		
	//Создаём новую задачу
	if (!taskWindow->programDirection->addTask(patch)){
		//Если добавление не удалось значит такой путь задачи уже был
		MessageBox(NULL, "Такая задача уже есть!", "повтор задачи", MB_ICONERROR);
	}

	//Обновляем список
	taskWindow->updateListContent();

	//Устанавливаем выделение на свежедобавленном пункте
	taskWindow->taskListBox->select(patch);

	//Обновляем состояние кнопок
	taskWindow->stopConfiguration();

	delete(taskSelector);
}


void TaskWindow::onClickStartButton(Button *callButton){
	taskWindow->programDirection->startWorkTasks();
	taskWindow->workConfiguration();
}

void TaskWindow::onClickPauseTaskButton(Button *callButton){
	taskWindow->programDirection->pause();
	taskWindow->pauseButton->disable();
	taskWindow->startButton->enable();
}

void TaskWindow::onClickStopTaskButton(Button *callButton){
	taskWindow->programDirection->stop();
	taskWindow->stopConfiguration();
}

void TaskWindow::onClickUpTaskButton(Button *callButton){
	//Узнаём текущий выделенный пункт списка
	std::string selectedStr = taskWindow->taskListBox->getCurrentSelected();
	
	//Поднимаем это задание на 1 вверх
	taskWindow->programDirection->taskMoveUp(selectedStr);

	//Обновляем список
	taskWindow->updateListContent();

	//Восстановить выделение
	taskWindow->taskListBox->select(selectedStr);
}

void TaskWindow::onClickDownTaskButton(Button *callButton){
	//Узнаём текущий выделенный пункт списка
	std::string selectedStr = taskWindow->taskListBox->getCurrentSelected();
	
	//на 1 вниз
	taskWindow->programDirection->taskMoveDown(selectedStr);

	//Обновляем список
	taskWindow->updateListContent();

	//Восстановить выделение
	taskWindow->taskListBox->select(selectedStr);
}

void TaskWindow::onClickRemoveTaskButton(Button *callButton){
	//Извлекаем текущуий выделенный элемент
	std::string selectedStr = taskWindow->taskListBox->getCurrentSelected();
	

	taskWindow->programDirection->deleteTask(selectedStr);
	taskWindow->updateListContent();

	//Обновляем состояние кнопок
	taskWindow->stopConfiguration();

	//Выделить первый элемент списка
	taskWindow->taskListBox->select(0);

}

//Обработчик даблклика на listBox
void TaskWindow::onDblClickTaskListBox(ListBox *callListBox, std::string itemStr){
	//MessageBox(NULL, itemStr.c_str(), "Ы", MB_OK);
	TaskManager *taskManager = taskWindow->programDirection->getTaskManager();
	Task *task = taskManager->getTask(itemStr);
	TaskConfiguratorWindow taskConfWindow(task, taskWindow->thisHandle);
}


BOOL CALLBACK taskWindowDlgProc(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	
	//Инициализация указателя на окно диалога
	if (messageCode == WM_INITDIALOG) taskWindow->thisHandle = windowHandle;
	
	
	if ((messageCode == WM_COMMAND)&&(LOWORD(wParam) == 2)){//Код нажатия на кнопку (крестик) заголовка окна!
		//Закрытие окна
		EndDialog(windowHandle, 0);
		return true;
	}
	//Лист задач
	if (taskWindow->taskListBox->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;

	//Кнопки
	if (taskWindow->addTaskButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskWindow->deleteTaskButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskWindow->upTaskButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskWindow->downTaskButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskWindow->startButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskWindow->pauseButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskWindow->stopButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	
	if (taskWindow->taskProgressBar->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	return false;
}

//Изменить состояние индикатора прогресса всех заданий
void TaskWindow::setSatusTaskProgressBar(int percent){
	taskProgressBar->setProgressPercent(percent);
}

void TaskWindow::updateListContent(){
	TaskManager *taskManager = programDirection->getTaskManager();
	StringList *stringList = new StringList();

	//Создаём список задач
	for (int ch=0; ch<taskManager->length(); ch++){
		Task *task = taskManager->getTask(ch);
		stringList->addString(task->getPatch());
	}

	//stringList->debugShowContent();
	taskListBox->changeAllItems(stringList);
}


//Начальная конфигурация
void TaskWindow::stopConfiguration(){
	//Узнаём текущее колличество задач
	addTaskButton->enable();

	TaskManager *taskManager = programDirection->getTaskManager();
	//Если задач нет, многие кнопки не должны быть активны
	if (taskManager->length()==0){
		deleteTaskButton->disable();
		upTaskButton->disable();
		downTaskButton->disable();
		startButton->disable();
		pauseButton->disable();
		stopButton->disable();
	} else {
		deleteTaskButton->enable();
		upTaskButton->enable();
		downTaskButton->enable();
		startButton->enable();
		pauseButton->disable();
		stopButton->disable();
	}

	//Состояние процесса в 0
	setSatusTaskProgressBar(0);
}

//Задачи выполняются
void TaskWindow::workConfiguration(){
	addTaskButton->disable();
	deleteTaskButton->disable();
	upTaskButton->disable();
	downTaskButton->disable();
	startButton->disable();
	pauseButton->enable();
	stopButton->enable();
}

//Пауза
void TaskWindow::pauseConfiguration(){
}