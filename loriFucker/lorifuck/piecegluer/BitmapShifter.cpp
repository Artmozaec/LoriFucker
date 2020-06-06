#include "BitmapShifter.h"

BitmapShifter* BitmapShifter::instance = NULL;

BitmapShifter *BitmapShifter::getInstance(){
	if (instance==NULL){
		instance = new BitmapShifter();
	}

	return instance;
}

BitmapShifter::BitmapShifter(){
	image = NULL;
}

//������� ������
int BitmapShifter::calculateFrequencyShifting(int shift){
	if (shift>abstractHeighImage){
		return 1;
	} else {
		return abstractHeighImage/shift;
	}
}


//��������� ��������
void BitmapShifter::calculateShiftParametrs(
		int &periodAccretion, //������ ���������� 
		int &accretion, //�����������
		int &verticalCorrectionPeriod, //������ ������������ ��������� � 1 ������
		int &horizontalCorrectionPeriod, //������ �������������� ��������� 1 ������

		int shift
		){
	if (shift>abstractHeighImage){
		verticalCorrectionPeriod = 0; //��������� ���������, � ������ �������� ��� �� ����
		periodAccretion = 0;
		
		accretion = shift/abstractHeighImage;
		
		//verticalCorrectionPeriod = (periodAccretion*shift)

	} else {
		horizontalCorrectionPeriod = 0; //��������� ���������, � ������ �������� ��� �� ����
		accretion = 1;
		//������ � ������� ����� ���������� � 1 �������
		periodAccretion = abstractHeighImage/shift;

		//����������� ������� ���������
		int lapse = abstractHeighImage - (periodAccretion*shift);

		//����������� ������ � ������� ��� ����������� ����� ����������
		//�� ���� ������ ��������
		if (lapse !=0) verticalCorrectionPeriod = abstractHeighImage/lapse;
	}
}


void BitmapShifter::shiftUpArea(int pos, int length, int shift){
	if ((shift == 0) || (length == 0)) return;
	int periodAccretion = 0; //������ ���������� 
	int accretion = 0; //�����������
	int verticalCorrectionPeriod = 0; //������ ������������ ��������� � 1 ������
	int horizontalCorrectionPeriod = 0; //������ �������������� ��������� 1 ������


	calculateShiftParametrs(
		periodAccretion,
		accretion,
		verticalCorrectionPeriod,
		horizontalCorrectionPeriod,

		abs(shift)
	);

	//������� ��������
	int currentDelta = shift;
	

	for (int 
		lineCh=0, //����� ������� �����
		accrCh=0; //������� ������� ����������
	
		lineCh<abstractHeighImage; 
		
		lineCh++, 
		accrCh++
	){
		shiftLine(pos, lineCh, length, currentDelta);
	
		if ((verticalCorrectionPeriod != 0) && (lineCh%verticalCorrectionPeriod) == 0){//������� ����� ������ ������������ ���������!
			//��� �����, �������� ������ ���������� �� 1
			if (accrCh != 0) accrCh--;
		}
		if (accrCh>=periodAccretion){
			if (shift>0){
				currentDelta -= accretion;
			} else {
				currentDelta += accretion;
			}
			accrCh=0;
		}
	}
}

void BitmapShifter::shiftDownArea(int pos, int length, int shift){
	if ((shift == 0) || (length == 0)) return;
	int periodAccretion = 0; //������ ���������� 
	int accretion = 0; //�����������
	int verticalCorrectionPeriod = 0; //������ ������������ ��������� � 1 ������
	int horizontalCorrectionPeriod = 0; //������ �������������� ��������� 1 ������


	calculateShiftParametrs(
		periodAccretion,
		accretion,
		verticalCorrectionPeriod,
		horizontalCorrectionPeriod,

		abs(shift)
	);

	//������� ��������
	int currentDelta = shift;
	

	for (int 
		lineCh=abstractHeighImage, //����� ������� �����
		accrCh=0; //������� ������� ����������
	
		lineCh>0; 
		
		lineCh--, 
		accrCh++
	){
		shiftLine(pos, lineCh, length, currentDelta);
	
		if ((verticalCorrectionPeriod != 0) && (lineCh%verticalCorrectionPeriod) == 0){//������� ����� ������ ������������ ���������!
			//��� �����, �������� ������ ���������� �� 1
			if (accrCh != 0) accrCh--;
		}
		if (accrCh>=periodAccretion){
			if (shift>0){
				currentDelta -= accretion;
			} else {
				currentDelta += accretion;
			}
			accrCh=0;
		}
	}

}

void BitmapShifter::changeImage(BitmapContainer *inImage){
	image = inImage;

	if (image->getShirina()>image->getVisota()){
		orientation = horizontal;
		abstractHeighImage = image->getVisota();
	} else {
		orientation = vertical;
		abstractHeighImage = image->getShirina();
	}
}


//������� ����� ������� length �� shift ��������
void BitmapShifter::shiftLine(int posX, int posY, int length, int shift){
	if (orientation == horizontal){
		if (shift>0){//� �����
			shiftHorLineRight(posX, posY, length, shift);
		} else {//� ����
			shiftHorLineLeft(posX, posY, length, abs(shift));
		}
	}  else if (orientation == vertical){
		if (shift>0){//� ���
			shiftVertLineDown(posY, posX, length, shift);
		} else {//� �����
			shiftVertLineUp(posY, posX, length, abs(shift));
		}
	}

}


void BitmapShifter::shiftHorLineLeft(int posX, int posY, int length, int shift){

	Color *fillColor = image->getPixel(posX+length, posY);
	//�������� ������������ �����
	BitmapContainer *movedLine = image->getArea(posX, posY, 1, length);
	//movedLine->saveImage(std::string("C:\\tt.tif"));
	//��������� � ������ �� shift �������
	image->addFragment(movedLine, posX-shift, posY);

	//��������� ����� ������ ������� �����
	image->drawHorizontalLine((posX+length)-shift, posY, shift, fillColor);
}


void BitmapShifter::shiftHorLineRight(int posX, int posY, int length, int shift){
	Color *fillColor = image->getPixel(posX, posY);

	//�������� ������������ �����
	BitmapContainer *movedLine = image->getArea(posX, posY, 1, length);
	//movedLine->saveImage(std::string("C:\\tt.tif"));
	//��������� � ������ �� shift �������
	image->addFragment(movedLine, posX+shift, posY);

	//��������� ����� ������ ������� �����
	image->drawHorizontalLine(posX, posY, shift, fillColor);
}

void BitmapShifter::shiftVertLineDown(int posX, int posY, int length, int shift){
	Color *fillColor = image->getPixel(posX, posY);

	//�������� ������������ �����
	BitmapContainer *movedLine = image->getArea(posX, posY, length, 1);
	
	//��������� � ���� �� shift �������
	image->addFragment(movedLine, posX, posY+shift);

	//��������� ����� ������ ������� �����
	image->drawVerticalLine(posX, posY, shift, fillColor);
}

void BitmapShifter::shiftVertLineUp(int posX, int posY, int length, int shift){
	Color *fillColor = image->getPixel(posX, posY+length);
	//�������� ������������ �����
	BitmapContainer *movedLine = image->getArea(posX, posY, length, 1);
	//movedLine->saveImage(std::string("C:\\tt.tif"));
	//��������� � ������ �� shift �������
	image->addFragment(movedLine, posX, posY-shift);

	//��������� ����� ������ ������� �����
	image->drawVerticalLine(posX, (posY+length)-shift, shift, fillColor);
}



