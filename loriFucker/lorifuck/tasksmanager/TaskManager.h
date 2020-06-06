#ifndef TaskManagerH
#define TaskManagerH


#include "Task.h"
#include <vector>

class TaskManager{
	public:
		TaskManager();
		~TaskManager();
		
		//Возвращает задание по номеру 
		Task *getTask(int);
		
		//Возвращает задание по строке пути
		Task *getTask(std::string);
		
		//Колличество заданий
		int length();

		//Добавить задание
		bool addTask(Task *task);

		//Удалить задание
		void deleteTask(std::string taskName);
		
		//Переместить задачу вверх
		void taskMoveUp(std::string taskPatch);
		
		//Переместить задачу вниз
		void taskMoveDown(std::string taskPatch);
	private:
		std::vector<Task *> *taskContainer;

		int findTask(std::string taskName);

};

#endif