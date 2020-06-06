#include "TaskConfiguratorWindow.h"

TaskConfiguratorWindow *taskConfiguratorWindow;

BOOL CALLBACK taskConfiguratorWindowDlgProc(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);

TaskConfiguratorWindow::TaskConfiguratorWindow(Task *inTask, HWND ownewHandle){
	taskConfiguratorWindow = this;
	
	HINSTANCE hndl = GetModuleHandle(NULL);
	
	task = inTask;
	
	saveChangesButton = new Button(SAVE_BUTTON);
	saveChangesButton->setOnClickHandler(onClickSaveChangesButton);
	saveChangesButton->disable();

	cancelButton = new Button(CANCEL_BUTTON);
	cancelButton->setOnClickHandler(onClickCancelButton);

	patchEditBox = new EditBox(PATCH_EDIT_BOX);
	patchEditBox->setText(inTask->getPatch());

	//�����
	framesAmountText = new LabelText(TEXT_ALL_FRAMES);
	omitsAmountText = new LabelText(TEXT_ALL_OMITS);
	
	//����������� ���������� � ���������
	framesAmountText->setCaption(IntToStr(inTask->getFramesManager()->getFramesAmount()));
	omitsAmountText->setCaption(IntToStr(inTask->getFramesManager()->getFramesOmit()));
	
	//��������������� ������ ������ ���������
	horizontalFramesComboBox = new ComboBox(COMBO_HORIZONTAL_FRAMES);
	verticalFramesComboBox = new ComboBox(COMBO_VERTICAL_FRAMES);
	
	//�������������� ������ ���������� ����������
	intValuesToComboBox(inTask->getImageProportion()->getAllVariations(), horizontalFramesComboBox);
	intValuesToComboBox(inTask->getImageProportion()->getAllVariations(), verticalFramesComboBox);
	
	//������������� ����� �� ������� �������� ���������
	horizontalFramesComboBox->selectString(IntToStr(inTask->getHorizontalFrames()));
	verticalFramesComboBox->selectString(IntToStr(inTask->getVerticalFrames()));
	
	//�������������� ����������� ������ ������ ���������
	//(���������� ��������� ���� �������)
	horizontalFramesComboBox->setOnChangeSelectionHandler(horizontalFramesComboBoxHandler);
	verticalFramesComboBox->setOnChangeSelectionHandler(verticalFramesComboBoxHandler);

	DialogBox(
		hndl,
		MAKEINTRESOURCE(IDD_TASK_CONFIGURATOR), //������
		ownewHandle, //���������� ������������� ����
		taskConfiguratorWindowDlgProc//����� ��������� ���������
	);
}


void TaskConfiguratorWindow::intValuesToComboBox(std::vector<int> intValues, ComboBox *comboBox){
	std::vector<int>::iterator ch;
	for (ch=intValues.begin(); ch<intValues.end(); ch++){
		comboBox->addString(IntToStr(*ch));
	}
}


//����������� ������ ��������� �����������
void TaskConfiguratorWindow::horizontalFramesComboBoxHandler(ComboBox *callComboBox, std::string str){
	
	//������ ����� ������ ���� ��������������� �������
	int secondSide = taskConfiguratorWindow->task->getImageProportion()->getSecondSideFrames(StrToInt(str));
	
	//������ �������� ���������������� ����������
	taskConfiguratorWindow->verticalFramesComboBox->selectString(IntToStr(secondSide));
	
	//������� ���������
	taskConfiguratorWindow->chastityDestroy();

	//��������� ������������� ���������
	taskConfiguratorWindow->updateRectangleProportions();
}

void TaskConfiguratorWindow::verticalFramesComboBoxHandler(ComboBox *callComboBox, std::string str){
	
	//������ ����� ������ ���� ��������������� �������
	int secondSide = taskConfiguratorWindow->task->getImageProportion()->getSecondSideFrames(StrToInt(str));
	
	//������ �������� ���������������� ����������
	taskConfiguratorWindow->horizontalFramesComboBox->selectString(IntToStr(secondSide));
	
	//������� ���������
	taskConfiguratorWindow->chastityDestroy();

	//��������� ������������� ���������
	taskConfiguratorWindow->updateRectangleProportions();
}


void TaskConfiguratorWindow::onClickSaveChangesButton(Button *callButton){
	//���������� ���� ��������� ���� �������, � Task
	taskConfiguratorWindow->task->setHorizontalFrames(
		StrToInt(taskConfiguratorWindow->horizontalFramesComboBox->getCurrentSelected())
	);
	taskConfiguratorWindow->task->setVerticalFrames(
		StrToInt(taskConfiguratorWindow->verticalFramesComboBox->getCurrentSelected())
	);

	//������������ �������������
	taskConfiguratorWindow->saveChangesButton->disable();
}


void TaskConfiguratorWindow::onClickCancelButton(Button *callButton){
	EndDialog(taskConfiguratorWindow->windowHandle, 0);
}

//������� ���������
void TaskConfiguratorWindow::chastityDestroy(){
	//������� ������ ���������, � � ����������� ��������� ����������
	saveChangesButton->enable();
}

void TaskConfiguratorWindow::updateRectangleProportions(){
		rectangleProportions->setRectangleProportions(
			StrToInt(taskConfiguratorWindow->horizontalFramesComboBox->getCurrentSelected()),
			StrToInt(taskConfiguratorWindow->verticalFramesComboBox->getCurrentSelected())
		);
}

BOOL CALLBACK taskConfiguratorWindowDlgProc(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	

	
	if ((messageCode == WM_COMMAND)&&(LOWORD(wParam) == 2)){//��� ������� �� ������ (�������) ��������� ����!
		taskConfiguratorWindow->onClickCancelButton(NULL);
		return true;
	}	
	
	if (taskConfiguratorWindow->patchEditBox->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskConfiguratorWindow->saveChangesButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskConfiguratorWindow->cancelButton->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskConfiguratorWindow->framesAmountText->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskConfiguratorWindow->omitsAmountText->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskConfiguratorWindow->horizontalFramesComboBox->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	if (taskConfiguratorWindow->verticalFramesComboBox->messageIntercept(windowHandle, messageCode, wParam, lParam)) return true;
	
	//������������� ��������� �� ���� �������
	if (messageCode == WM_INITDIALOG){ 
		taskConfiguratorWindow->windowHandle = windowHandle;
		
		//�������� �������������� ���������
		taskConfiguratorWindow->rectangleProportions = new RectangleProportions(198, 120, 150, 90, windowHandle);
		
		//������������� ���������
		taskConfiguratorWindow->updateRectangleProportions();
	}
	
	return false;
}


