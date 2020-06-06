#ifndef ImageProportionH
#define ImageProportionH

#include <vector>
#include <algorithm>

class ImageProportion{
	public:
		ImageProportion(int amountFrames);
		
		//���� ������ ��������������� �������
		int getSecondSideFrames(int firstSideFrames);

		//���� ��� ���������
		std::vector<int> getAllVariations();
		
		//���� ������� ��������
		int getMedian();
	private:
		//��������� 
		void generateProportins(int amountFrames);

		//��� ��������� ������� ������ �����������
		std::vector<int> proportions;
		
		//����� ����������� ����������
		int imageAmountFrames;
};

#endif