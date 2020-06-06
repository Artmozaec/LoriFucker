#ifndef TaskSelectorH
#define TaskSelectorH

#include <stdio.h>
#include <Shlobj.h>
#include <string>
#include "lastpatch\LastPatch.h"

//using namespace std;

class TaskSelector{
	public:
		TaskSelector();
		bool showSelector();
		std::string getPatch();
		LastPatch *lastPatch;
	private:
		
		//Путь выбранный пользователем
		std::string *selectedPatch;
};

#endif