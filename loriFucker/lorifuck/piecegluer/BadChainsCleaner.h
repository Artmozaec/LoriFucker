#ifndef BadLinksCleanerH
#define BadLinksCleanerH
#include <windows.h>
#include "Area.h"

class BadChainsCleaner{
public:
	static BadChainsCleaner* getInstance();

	void clearBadChains(Area *area);
private:
	BadChainsCleaner();
	static BadChainsCleaner* instance;

	//������� �� ������� beginArea ���� ����������� � �������� currentArea � ����������� �����������
	Area* findCrossChain(Area* crossFindedArea, Area* beginArea);

	//��������� ��� ����� � ������� ����� ������� c area
	void destroyChain(Area* downArea);

	//������� ������������� ��� ���� �����������?
	bool isCrossedChain(Area *firstChain, Area *secondChain);

	//���� ��������� ������� ������� �������� �� 4 ������� �����
	Area *findNextChain(Area *beginArea);

	//�������� ������� (��������� ��� ���������������)
	int getQualityChain(Area *chain);

	//���������� true ���� ������ firstArea ������������� ����� secondArea
	bool isTrueSequence(Area *firstArea, Area *secondArea);

	//��������� ������ �������
	void clearBadChain(Area *firstArea, Area *secondArea);

	//������ ������ �������
	int getWeightChain(Area *chain);

	//���� ���������� ����� ���������� ��������� ������ ��� �����
	bool chainLengthLinksIsBad(Area *chain);

};

#endif