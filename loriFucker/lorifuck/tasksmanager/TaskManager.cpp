#include "TaskManager.h"

TaskManager::TaskManager(){
	taskContainer = new std::vector<Task *>;
}

TaskManager::~TaskManager(){
	delete(taskContainer);
}

int TaskManager::length(){
	return taskContainer->size();
}

//���������� ������� �� ������ 
Task *TaskManager::getTask(int taskNum){
	return taskContainer->at(taskNum);
}

//������� �� �����
Task *TaskManager::getTask(std::string str){
	int pos = findTask(str);
	if (pos == -1) return NULL;
	return getTask(pos);
}


//�������� �������
bool TaskManager::addTask(Task *task){
	//��������� ������������ ������
	if (findTask(task->getPatch()) != -1) return false;

	taskContainer->push_back(task);
	return true;
}

int TaskManager::findTask(std::string taskName){
	for(int ch=0; ch<taskContainer->size(); ch++){
		Task *task = taskContainer->at(ch);
		std::string patch = task->getPatch();
		if (patch == taskName) return ch;
	}
	return -1;
}

//������� �������
void TaskManager::deleteTask(std::string taskName){
	//������� ������� ������
	int pos = findTask(taskName);
	if (pos == -1) return;
	taskContainer->erase(taskContainer->begin()+pos);
}



//����������� ������ �����
void TaskManager::taskMoveUp(std::string taskName){
	//������� ������� ������
	int pos = findTask(taskName);
	
	//���� ������ �� ����� �����
	if (pos == 0) return;

	Task *task = taskContainer->at(pos);
	taskContainer->erase(taskContainer->begin()+pos);
	taskContainer->insert(taskContainer->begin()+pos-1, task);
}
		
//����������� ������ ����
void TaskManager::taskMoveDown(std::string taskName){
	//������� ������� ������
	int pos = findTask(taskName);
	
	//���� ������ � ����� ����
	if (pos == taskContainer->size()-1) return;

	Task *task = taskContainer->at(pos);
	taskContainer->erase(taskContainer->begin()+pos);
	taskContainer->insert(taskContainer->begin()+pos+1, task);
}

