#ifndef FramesManagerH
#define FramesManagerH

#include <string>
#include <windows.h>
#include <stdio.h>
#include "..\mytypes\Utils.cpp"
#include "..\mytypes\BitmapContainer.h"

class  FramesManager{
	public:
		FramesManager(std::string inPatch);

		//возвращает максимальный номер фрагмента
		int getFramesAmount();

		//возвращает общее колличество пропусков фрагментов в задаче
		int getFramesOmit();

		//Возвращает изображение заданного фрагмента
		BitmapContainer* getFrame(int frameNumber);

		//Даёт размер стороны фрагмента-(ов) данной задачи
		int getFrameSideSize();
	private:
		std::string taskPatch;
		
		//Общее колличество фреймов в задаче
		int taskFrames;

		//Общее колличество пропусков в задаче
		int taskOmit;

		

		//Начальная часть имени до цифры
		std::string fileNameBeginPart;

		//Конечная часть после цифры
		std::string fileNameEndPart;

		//Подсчитывает колличество фреймов и пропусков
		void countFramesAndOmit();

		//Проверка наличия файла на диске
		bool IsFileExist(std::string patch);

		//Создаёт полный путь к фрагменту frameNumber
		std::string generatePatch(int frameNumber);

		////////////////////////РАЗМЕР ФРАГМЕНТА////////////////
		//Размер сторны фрагмента задачи
		int frameSideSize;

		//вычисляем размер фрвгмента
		int generateFrameSideSize();
};

#endif