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

		//Пропорции изображения
		ComboBox *horizontalFramesComboBox;
		ComboBox *verticalFramesComboBox;
		
		//Тект
		LabelText *framesAmountText; //Колличество фрагметов
		LabelText *omitsAmountText; // Колличество пропусков

		//Кнопки
		Button *saveChangesButton;
		Button *cancelButton;
		
		//Окно пути
		EditBox *patchEditBox;

		TaskConfiguratorWindow();
		~TaskConfiguratorWindow();

		//Обработчики нажатия кнопок
		static void onClickSaveChangesButton(Button *callButton);
		static void onClickCancelButton(Button *callButton);

		//Обработчики выбора пропорций изображения
		static void horizontalFramesComboBoxHandler(ComboBox *callComboBox, std::string str);
		static void verticalFramesComboBoxHandler(ComboBox *callComboBox, std::string str);

		//Дескриптор этого окна
		HWND windowHandle;

		//Внесены изменения
		void chastityDestroy();

		//Изменение размера прямоугольника пропрций
		void updateRectangleProportions();
	private:
		//Ссылка на текущую отображаемую задачу
		Task *task;
		//Показывает вектор занчений int в комбинированном списке
		void intValuesToComboBox(std::vector<int> intValues, ComboBox *comboBox);
};

#endif