#include "LastPatch.h"

LastPatch* LastPatch::instance = NULL;

//Я не знаю что это за х..ня, но без эттого включения ошибка "error c2129 static function"
//Не видит функцию extractFileDir, хотя она определена в h файле!!!!
#include "..\..\..\mytypes\Utils.cpp"

LastPatch::LastPatch(){
	//Узнаём путь к приложению
	char patch[1000];
	GetModuleFileName(0,patch,1000);

	
	settingsFolderPatch = extractFileDir(std::string(patch));

	fileName = "\\loriFuckerLastPatch.txt";
	lastPatch = readLastPatch();
}

LastPatch* LastPatch::getInstance(){
	if (instance == NULL){
		instance = new LastPatch();
	}
	return instance;
}

void LastPatch::writeLastPatch(std::string str){
	FILE *file;
	std::string fullPatch = settingsFolderPatch+fileName;


	file = fopen(fullPatch.c_str(), "wt");
	fprintf(file, lastPatch.c_str());
	fclose(file);
}


std::string LastPatch::readLastPatch(){
	char buf[1000];
	FILE *file;
	std::string fullPatch = settingsFolderPatch+fileName;

	file = fopen(fullPatch.c_str(), "rt");
	if (file == NULL) return std::string("C:\\");
	fgets(buf, 1000, file);
	fclose(file);
	return std::string(buf);
}

std::string LastPatch::getLastPatch(){
	return lastPatch;
}

void LastPatch::setLastPatch(std::string patch){
	lastPatch = patch;
	writeLastPatch(patch);
}