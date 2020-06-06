#include "ImageProportion.h"

ImageProportion::ImageProportion(int amountFrames){
	imageAmountFrames = amountFrames;
	generateProportins(amountFrames);	
}

void ImageProportion::generateProportins(int amountFrames){
	int rest;
	for(int ch=2; ch<amountFrames; ch++){
		rest = amountFrames%ch;
		if (rest == 0){
			proportions.push_back(ch);
		}
	}
}

//���� ��� ���������
std::vector<int> ImageProportion::getAllVariations(){
	return proportions;
}

//���� ������� ��������
int ImageProportion::getMedian(){
	if (proportions.size() == 0) return 0;
	int pos = proportions.size()/2;
	return proportions.at(pos);
}

//���� ������ ��������������� �������
int ImageProportion::getSecondSideFrames(int firstSideFrames){
	std::vector<int>::iterator it;
	
	for(it = proportions.begin(); it<proportions.end(); it++){
		if ((*it*firstSideFrames) == imageAmountFrames){
			return *it;
		}
	}
	return 0;
}
