#include "LastPatch.h"

LastPatch* LastPatch::instance = NULL;

//� �� ���� ��� ��� �� �..��, �� ��� ������ ��������� ������ "error c2129 static function"
//�� ����� ������� extractFileDir, ���� ��� ���������� � h �����!!!!
#include "..\..\..\mytypes\Utils.cpp"

LastPatch::LastPatch(){
	//����� ���� � ����������
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