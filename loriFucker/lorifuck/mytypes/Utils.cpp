#include "Utils.h"

static std::string extractFileDir(std::string patch){
	std::string key("\\");
	int pos = patch.rfind(key);
	return std::string(patch, 0, pos);
}

static std::string IntToStr(int digit){
	char digitBuf[5];
	itoa(digit, digitBuf, 10);
	std::string str(digitBuf);
	return str;
}


static int StrToInt(std::string str){
	int result = atoi(str.c_str());
	return result;
}


