#include "StringList.h"
#include "iomanip"
#include <iostream>


StringList::StringList(){
	stringContainer = new std::vector<std::string>;
}

StringList::~StringList(){
	delete(stringContainer);
}


void StringList::addString(std::string inString){
	stringContainer->insert(stringContainer->begin(), inString);
}

std::string StringList::getString(int pos){
	return stringContainer->at(pos);
}

int StringList::length(){
	return stringContainer->size();
}

void StringList::invert(){
	std::reverse(stringContainer->begin(),stringContainer->end());
}

int StringList::findString(std::string str){
	std::vector<std::string>::iterator it;
	it = std::find(stringContainer->begin(), stringContainer->end(), str);
	return it-stringContainer->begin();
}

void StringList::debugShowContent(){
	for(int ch=0; ch<length(); ch++){
		MessageBox(NULL, getString(ch).c_str(), "Û", MB_OK);
	}
}