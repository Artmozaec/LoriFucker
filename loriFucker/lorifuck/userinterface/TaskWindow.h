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
		
		//�������� ����
		void showWindow();		
		
		//������
		Button *addTaskButton;
		Button *deleteTaskButton;
		Button *upTaskButton;
		Button *downTaskButton;
		Button *startButton;
		Button *pauseButton;
		Button *stopButton;		
		
		//���� �������
		ListBox *taskListBox;
		
		//��������� ��������� ���� �����
		ProgressBar *taskProgressBar;

		//����������� ������� ������
		static void onClickAddTaskButton(Button *callButton);
		static void onClickStartButton(Button *callButton);
		static void onClickRemoveTaskButton(Button *callButton);
		static void onClickUpTaskButton(Button *callButton);
		static void onClickDownTaskButton(Button *callButton);
		static void onClickPauseTaskButton(Button *callButton);
		static void onClickStopTaskButton(Button *callButton);

		//���������� ��������� �� listBox
		static void onDblClickTaskListBox(ListBox *callListBox, std::string itemStr);
		
		//���������� ����� ����
		HWND thisHandle;

		//�������� ��������� ���������� ��������� ���� �������
		void setSatusTaskProgressBar(int percent);
		
		ProgramDirection *programDirection;
		
		
		//������������ ������ ��� ������ �������� � ������ ���������
		//��������� ������������
		void stopConfiguration();
		//������ �����������
		void workConfiguration();
		//�����
		void pauseConfiguration();

	private:
		//���������� ����������� ������ �����
		void updateListContent();
};

#endif