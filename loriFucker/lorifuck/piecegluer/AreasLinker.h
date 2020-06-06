#ifndef AreasLinkerH
#define AreasLinkerH

#include "Area.h"

class AreasLinker{
public:
	static AreasLinker* getInstance();

	//�� ����� ���� ����� �������� ����� ��� � �������������, �� ��� �� �����, � ������ ������
	//��� ������� ���������� ������ �� ���������������

	//������ ������ - ��� ������ ������� � ������������������ ��������
	//������� ������� ������� ������� ����� ������� � ��������� �� ������� ����
	void linkAreaLinesToGrid(Area* upSideUpLine, Area* upSideDownLine, Area* downSideUpLine, Area* downSideDownLine);
private:
	AreasLinker();
	static AreasLinker* instance;

	//��������� ����������, �� ��������� �������
	void primaryLink(Area *upArea, Area *downArea);

	//��������� ���������� ��� ��������� ��������� ��������
	void secondaryLink(Area *upArea, Area *downArea);

	//������� ����� ������� � etalon �������, �� first � second ��������� �
	//Area *getMoreNear(Area *etalon, Area *first, Area *second);
	Area *getMoreNearDistanceAndColor(Area *etalon, Area *first, Area *second);
	Area *getMoreNearDistance(Area *etalon, Area *first, Area *second);
	Area *getMoreNearColor(Area *etalon, Area *first, Area *second);
	
	//����� ��������� ������� �������
	Area *searchProximate(Area *seekingArea, Area *searchSequence);

	//����� ��������� ������� ������� ������� ����� � ����
	Area *findProximateLinkedDown(Area *seekingArea, Area *searchSequence);
};

#endif
