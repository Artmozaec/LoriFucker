#ifndef TaskManagerH
#define TaskManagerH


#include "Task.h"
#include <vector>

class TaskManager{
	public:
		TaskManager();
		~TaskManager();
		
		//���������� ������� �� ������ 
		Task *getTask(int);
		
		//���������� ������� �� ������ ����
		Task *getTask(std::string);
		
		//����������� �������
		int length();

		//�������� �������
		bool addTask(Task *task);

		//������� �������
		void deleteTask(std::string taskName);
		
		//����������� ������ �����
		void taskMoveUp(std::string taskPatch);
		
		//����������� ������ ����
		void taskMoveDown(std::string taskPatch);
	private:
		std::vector<Task *> *taskContainer;

		int findTask(std::string taskName);

};

#endif