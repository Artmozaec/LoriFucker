#ifndef TaskConfiguratorWindowH
#define TaskConfiguratorWindowH

#include <windows.h>
#include "components\Button.h"
#include "components\EditBox.h"
#include "components\LabelText.h"
#include "components\ComboBox.h"
#include "components\RectangleProportions.h"
#include "..\tasksmanager\Task.h"
#include "..\framesmanager\FramesManager.h"
//#include "..\mytypes\Utils.cpp"
#include "..\..\resource.h"
#include <string>

class TaskConfiguratorWindow{
	public:
		TaskConfiguratorWindow(Task *inTask,  HWND ownewHandle);
		
		RectangleProportions *rectangleProportions;	

		//��������� �����������
		ComboBox *horizontalFramesComboBox;
		ComboBox *verticalFramesComboBox;
		
		//����
		LabelText *framesAmountText; //����������� ���������
		LabelText *omitsAmountText; // ����������� ���������

		//������
		Button *saveChangesButton;
		Button *cancelButton;
		
		//���� ����
		EditBox *patchEditBox;

		TaskConfiguratorWindow();
		~TaskConfiguratorWindow();

		//����������� ������� ������
		static void onClickSaveChangesButton(Button *callButton);
		static void onClickCancelButton(Button *callButton);

		//����������� ������ ��������� �����������
		static void horizontalFramesComboBoxHandler(ComboBox *callComboBox, std::string str);
		static void verticalFramesComboBoxHandler(ComboBox *callComboBox, std::string str);

		//���������� ����� ����
		HWND windowHandle;

		//������� ���������
		void chastityDestroy();

		//��������� ������� �������������� ��������
		void updateRectangleProportions();
	private:
		//������ �� ������� ������������ ������
		Task *task;
		//���������� ������ �������� int � ��������������� ������
		void intValuesToComboBox(std::vector<int> intValues, ComboBox *comboBox);
};

#endif