#ifndef LastPatchH
#define LastPatchH

#include "..\..\..\mytypes\Utils.h"
#include <string>
#include "stdio.h"
#include <windows.h>


class LastPatch{
	public:
		static LastPatch* getInstance();

		//void changeSettingsFolder(std::string patch);

		std::string getLastPatch();

		void setLastPatch(std::string patch);
	private:
		LastPatch();
		
		static LastPatch* instance;

		std::string settingsFolderPatch;

		std::string lastPatch;

		std::string fileName;

		void writeLastPatch(std::string str);

		std::string readLastPatch();
};

#endif