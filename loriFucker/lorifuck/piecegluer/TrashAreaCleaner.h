#ifndef TrashAreaCleanerH
#define TrashAreaCleanerH

#include "Area.h"

class TrashAreaCleaner{
public:
	static TrashAreaCleaner* getInstance();

	//�������� ��������� �� ������
	void clearTrashAreas(Area *firstArea);
private:
	TrashAreaCleaner();
	static TrashAreaCleaner* instance;

	//��������� ������� ��������?
	bool isTrashNextArea(Area *area);

	//������������������ �������� ����������?
	bool areasIsSolid(Area *firstArea, Area *secondArea);

	//��������� ��������� �������� �� firstArea �� endArea ����� ��������
	//� ���������� ��������� �� ����������� ��������
	//Area *takeoverAreas(Area *firstArea, Area *endArea);
};

#endif