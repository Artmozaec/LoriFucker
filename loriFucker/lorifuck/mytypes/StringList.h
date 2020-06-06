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

		//������ ������������������ ��������� ����������� �� ���������������
		void invert();

		int length();

		//����� ������ str
		int findString(std::string str);
	private:
		//����� � ���� ������ string
		std::vector<std::string> *stringContainer;
};

#endif