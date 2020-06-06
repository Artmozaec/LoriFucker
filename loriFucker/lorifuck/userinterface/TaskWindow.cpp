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

	//---------------���� �����-----------------------------
	taskListBox = new ListBox(TASK_LIST);
	taskListBox->setOnDblItemClick(onDblClickTaskListBox);

	//---------------������������� ������--------------------
	//�������� �������
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


	//������ ��������
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

	//���������� ���������
	taskProgressBar = new ProgressBar(5, 330, 20, 230);

	//������������� ��������� ��������� ������
	stopConfiguration();
}

TaskConfiguratorWindow::~TaskConfiguratorWindow(){

}


//�������� ����
void TaskWindow::showWindow(){
	HINSTANCE hndl = GetModuleHandle(NULL);

	DialogBox(
		hndl,
		MAKEINTRESOURCE(IDD_START_FORM), //������
		NULL, //���������� ������������� ����
		taskWindowDlgProc//����� ��������� ���������
	);	
}

void TaskWindow::onClickAddTaskButton(Button *callButton){
	TaskSelector *taskSelector = new TaskSelector();

	if (!taskSelector->showSelector()){
		//���� ������ �� �������, �������
		delete(taskSelector);
		return;
	}
	
	//������� ��������� ����
	std::string patch = taskSelector->getPatch();
		
	//������ ����� ������
	if (!taskWindow->programDirection->addTask(patch)){
		//���� ���������� �� ������� ������ ����� ���� ������ ��� ���
		MessageBox(NULL, "����� ������ ��� ����!", "������ ������", MB_ICONERROR);
	}

	//��������� ������
	taskWindow->updateListContent();

	//������������� ��������� �� ���������������� ������
	taskWindow->taskListBox->select(patch);

	//��������� ��������� ������
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
	//����� ������� ���������� ����� ������
	std::string selectedStr = taskWindow->taskListBox->getCurrentSelected();
	
	//��������� ��� ������� �� 1 �����
	taskWindow->programDirection->taskMoveUp(selectedStr);

	//��������� ������
	taskWindow->updateListContent();

	//������������ ���������
	taskWindow->taskListBox->select(selectedStr);
}

void TaskWindow::onClickDownTaskButton(Button *callButton){
	//����� ������� ���������� ����� ������
	std::string selectedStr = taskWindow->taskListBox->getCurrentSelected();
	
	//�� 1 ����
	taskWindow->programDirection->taskMoveDown(selectedStr);

	//��������� ������
	taskWindow->updateListContent();

	//������������ ���������
	taskWindow->taskListBox->select(selectedStr);
}

void TaskWindow::onClickRemoveTaskButton(Button *callButton){
	//��������� �������� ���������� �������
	std::string selectedStr = taskWindow->taskListBox->getCurrentSelected();
	

	taskWindow->programDirection->deleteTask(selectedStr);
	taskWindow->updateListContent();

	//��������� ��������� ������
	taskWindow->stopConfiguration();

	//�������� ������ ������� ������
	taskWindow->taskListBox->select(0);

}

//���������� ��������� �� listBox
void TaskWindow::onDblClickTaskListBox(ListBox *callListBox, std::string itemStr){
	//MessageBox(NULL, itemStr.c_str(), "�", MB_OK);
	TaskManager *taskManager = taskWindow->programDirection->getTaskManager();
	Task *task = taskManager->getTask(itemStr);
	TaskConfiguratorWindow taskConfWindow(task, taskWindow->thisHandle);
}


BOOL CALLBACK taskWindowDlgProc(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	
	//������������� ��������� �� ���� �������
	if (messageCode == WM_INITDIALOG) taskWindow->thisHandle = windowHandle;
	
	
	if ((messageCode == WM_COMMAND)&&(LOWORD(wParam) == 2)){//��� ������� �� ������ (�������) ��������� ����!
		//�������� ����
		EndDialog(windowHandle, 0);
		return true;
	}
	//���� �����
	if (taskWindow->taskListBox->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;

	//������
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

//�������� ��������� ���������� ��������� ���� �������
void TaskWindow::setSatusTaskProgressBar(int percent){
	taskProgressBar->setProgressPercent(percent);
}

void TaskWindow::updateListContent(){
	TaskManager *taskManager = programDirection->getTaskManager();
	StringList *stringList = new StringList();

	//������ ������ �����
	for (int ch=0; ch<taskManager->length(); ch++){
		Task *task = taskManager->getTask(ch);
		stringList->addString(task->getPatch());
	}

	//stringList->debugShowContent();
	taskListBox->changeAllItems(stringList);
}


//��������� ������������
void TaskWindow::stopConfiguration(){
	//����� ������� ����������� �����
	addTaskButton->enable();

	TaskManager *taskManager = programDirection->getTaskManager();
	//���� ����� ���, ������ ������ �� ������ ���� �������
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

	//��������� �������� � 0
	setSatusTaskProgressBar(0);
}

//������ �����������
void TaskWindow::workConfiguration(){
	addTaskButton->disable();
	deleteTaskButton->disable();
	upTaskButton->disable();
	downTaskButton->disable();
	startButton->disable();
	pauseButton->enable();
	stopButton->enable();
}

//�����
void TaskWindow::pauseConfiguration(){
}