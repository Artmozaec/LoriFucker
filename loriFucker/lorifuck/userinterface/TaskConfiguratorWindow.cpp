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

	//Текст
	framesAmountText = new LabelText(TEXT_ALL_FRAMES);
	omitsAmountText = new LabelText(TEXT_ALL_OMITS);
	
	//Колличество фрагментов и пропусков
	framesAmountText->setCaption(IntToStr(inTask->getFramesManager()->getFramesAmount()));
	omitsAmountText->setCaption(IntToStr(inTask->getFramesManager()->getFramesOmit()));
	
	//Комбинированные списки выбора пропорции
	horizontalFramesComboBox = new ComboBox(COMBO_HORIZONTAL_FRAMES);
	verticalFramesComboBox = new ComboBox(COMBO_VERTICAL_FRAMES);
	
	//Инициализируем списки возможными вариациями
	intValuesToComboBox(inTask->getImageProportion()->getAllVariations(), horizontalFramesComboBox);
	intValuesToComboBox(inTask->getImageProportion()->getAllVariations(), verticalFramesComboBox);
	
	//Устанавливаем выбор на текущих размерах пропорции
	horizontalFramesComboBox->selectString(IntToStr(inTask->getHorizontalFrames()));
	verticalFramesComboBox->selectString(IntToStr(inTask->getVerticalFrames()));
	
	//Инициализируем обработчики выбора списка пропорций
	//(Синхронное изменение двух списков)
	horizontalFramesComboBox->setOnChangeSelectionHandler(horizontalFramesComboBoxHandler);
	verticalFramesComboBox->setOnChangeSelectionHandler(verticalFramesComboBoxHandler);

	DialogBox(
		hndl,
		MAKEINTRESOURCE(IDD_TASK_CONFIGURATOR), //Шаблон
		ownewHandle, //Дескриптор родительского окна
		taskConfiguratorWindowDlgProc//Адрес процедуры обработки
	);
}


void TaskConfiguratorWindow::intValuesToComboBox(std::vector<int> intValues, ComboBox *comboBox){
	std::vector<int>::iterator ch;
	for (ch=intValues.begin(); ch<intValues.end(); ch++){
		comboBox->addString(IntToStr(*ch));
	}
}


//Обработчики выбора пропорций изображения
void TaskConfiguratorWindow::horizontalFramesComboBoxHandler(ComboBox *callComboBox, std::string str){
	
	//Узнаем какая должна быть противоположная сторона
	int secondSide = taskConfiguratorWindow->task->getImageProportion()->getSecondSideFrames(StrToInt(str));
	
	//Меняем значение противоположного комбобокса
	taskConfiguratorWindow->verticalFramesComboBox->selectString(IntToStr(secondSide));
	
	//Внесены изменения
	taskConfiguratorWindow->chastityDestroy();

	//Обновляем прямоугольник пропорции
	taskConfiguratorWindow->updateRectangleProportions();
}

void TaskConfiguratorWindow::verticalFramesComboBoxHandler(ComboBox *callComboBox, std::string str){
	
	//Узнаем какая должна быть противоположная сторона
	int secondSide = taskConfiguratorWindow->task->getImageProportion()->getSecondSideFrames(StrToInt(str));
	
	//Меняем значение противоположного комбобокса
	taskConfiguratorWindow->horizontalFramesComboBox->selectString(IntToStr(secondSide));
	
	//Внесены изменения
	taskConfiguratorWindow->chastityDestroy();

	//Обновляем прямоугольник пропорции
	taskConfiguratorWindow->updateRectangleProportions();
}


void TaskConfiguratorWindow::onClickSaveChangesButton(Button *callButton){
	//Сохранение всех элементов окна обратно, в Task
	taskConfiguratorWindow->task->setHorizontalFrames(
		StrToInt(taskConfiguratorWindow->horizontalFramesComboBox->getCurrentSelected())
	);
	taskConfiguratorWindow->task->setVerticalFrames(
		StrToInt(taskConfiguratorWindow->verticalFramesComboBox->getCurrentSelected())
	);

	//Восстановить девственность
	taskConfiguratorWindow->saveChangesButton->disable();
}


void TaskConfiguratorWindow::onClickCancelButton(Button *callButton){
	EndDialog(taskConfiguratorWindow->windowHandle, 0);
}

//Внесены изменения
void TaskConfiguratorWindow::chastityDestroy(){
	//Активна кнопка сохранить, в её обработчике процедура сохранения
	saveChangesButton->enable();
}

void TaskConfiguratorWindow::updateRectangleProportions(){
		rectangleProportions->setRectangleProportions(
			StrToInt(taskConfiguratorWindow->horizontalFramesComboBox->getCurrentSelected()),
			StrToInt(taskConfiguratorWindow->verticalFramesComboBox->getCurrentSelected())
		);
}

BOOL CALLBACK taskConfiguratorWindowDlgProc(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	

	
	if ((messageCode == WM_COMMAND)&&(LOWORD(wParam) == 2)){//Код нажатия на кнопку (крестик) заголовка окна!
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
	
	//Инициализация указателя на окно диалога
	if (messageCode == WM_INITDIALOG){ 
		taskConfiguratorWindow->windowHandle = windowHandle;
		
		//Создание прямоугольника пропорций
		taskConfiguratorWindow->rectangleProportions = new RectangleProportions(198, 120, 150, 90, windowHandle);
		
		//Устанавливаем пропорции
		taskConfiguratorWindow->updateRectangleProportions();
	}
	
	return false;
}


