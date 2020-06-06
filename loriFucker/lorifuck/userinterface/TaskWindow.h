#ifndef TaskWindowH
#define TaskWindowH

#include <windows.h>
#include "..\ProgramDirection.h"
#include "components\Button.h"
#include "components\ListBox.h"
#include "components\ProgressBar.h"
#include "..\tasksmanager\TaskManager.h"
#include "TaskConfiguratorWindow.h"
#include <string>


class ProgramDirection;
class TaskWindow{
	public:
		TaskWindow(ProgramDirection *inProgramDirection);
		
		//Показать окно
		void showWindow();		
		
		//Кнопки
		Button *addTaskButton;
		Button *deleteTaskButton;
		Button *upTaskButton;
		Button *downTaskButton;
		Button *startButton;
		Button *pauseButton;
		Button *stopButton;		
		
		//Лист заданий
		ListBox *taskListBox;
		
		//Индикатор прогресса всех задач
		ProgressBar *taskProgressBar;

		//Обработчики нажатия кнопок
		static void onClickAddTaskButton(Button *callButton);
		static void onClickStartButton(Button *callButton);
		static void onClickRemoveTaskButton(Button *callButton);
		static void onClickUpTaskButton(Button *callButton);
		static void onClickDownTaskButton(Button *callButton);
		static void onClickPauseTaskButton(Button *callButton);
		static void onClickStopTaskButton(Button *callButton);

		//Обработчик даблклика на listBox
		static void onDblClickTaskListBox(ListBox *callListBox, std::string itemStr);
		
		//Дескриптор этого окна
		HWND thisHandle;

		//Изменить состояние индикатора прогресса всех заданий
		void setSatusTaskProgressBar(int percent);
		
		ProgramDirection *programDirection;
		
		
		//Конфигурация кнопок для разных ситуаций в работе программы
		//Начальная конфигурация
		void stopConfiguration();
		//Задачи выполняются
		void workConfiguration();
		//Пауза
		void pauseConfiguration();

	private:
		//Обновление содержимого списка задач
		void updateListContent();
};

#endif