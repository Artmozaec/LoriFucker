#include "TaskSelector.h"

TaskSelector *taskSelector;

TaskSelector::TaskSelector(){
	taskSelector = this;
	selectedPatch = new std::string();
	lastPatch = LastPatch::getInstance();
}

int __stdcall BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
	switch (uMsg) {
		case BFFM_INITIALIZED: {
			// ѕри инициализации диалога
			// посылаем сообщение установки каталога
			if(lpData!=NULL)
				SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)taskSelector->lastPatch->getLastPatch().c_str());
			} break;
		case BFFM_SELCHANGED : {
			} break;
	}
	return 0;
}


bool TaskSelector::showSelector(){
	char buf[256];

	BROWSEINFO bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot=NULL;
	bi.pszDisplayName=buf;
	bi.lpszTitle="ƒиректори€ дл€ трахани€";
	bi.ulFlags=NULL;
	bi.lpfn=BrowseCallbackProc; //ƒополнительный обработчик, который реализует установку начальной директории

	ITEMIDLIST *itls;
	
	
	if(( itls = SHBrowseForFolder(&bi)) != NULL){
		SHGetPathFromIDList(itls,buf);
		//selectedPatch(buf);
		selectedPatch->append(buf, 256);
		lastPatch->setLastPatch(*selectedPatch);
		return true;
	}

	return false;
}

std::string TaskSelector::getPatch(){
	return *selectedPatch;
}