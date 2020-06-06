#ifndef ImageProportionH
#define ImageProportionH

#include <vector>
#include <algorithm>

class ImageProportion{
	public:
		ImageProportion(int amountFrames);
		
		//Дать размер противоположной стороны
		int getSecondSideFrames(int firstSideFrames);

		//Дать все пропорции
		std::vector<int> getAllVariations();
		
		//Дать среднее занчение
		int getMedian();
	private:
		//Заполняет 
		void generateProportins(int amountFrames);

		//Все возможные размеры сторон изображения
		std::vector<int> proportions;
		
		//Общее колличество фрагментов
		int imageAmountFrames;
};

#endif