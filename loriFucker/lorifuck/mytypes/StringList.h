#ifndef StringListH
#define StringListH

#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "iostream"

class StringList{
	public:
		StringList();
		~StringList();
		void addString(std::string);
		std::string getString(int);

		void debugShowContent();

		//Меняет последовательность элементов содержимого на противоположную
		void invert();

		int length();

		//Поиск строки str
		int findString(std::string str);
	private:
		//Несет в себе список string
		std::vector<std::string> *stringContainer;
};

#endif