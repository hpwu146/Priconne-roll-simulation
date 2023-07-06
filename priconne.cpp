#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <iomanip>
#include <vector>

int main (int argc, char* argv[]) {
	
	std::vector<int> v;
	double rolls;

	if (argc < 2) {
		std::cerr << "Require to enter the number of rolls.\n";
		return 0;
	} else {
		rolls = atoi(argv[1]);
	}


	//Gacha rates
	double pickup_rate = 0.007;
	double threestar_rate = 0.03;
	double twostar_rate = 0.18;
	double onestar_rate = 0.79;
	double pity_rate = 200;
	
	//Gacha count
	double pickup_char_count = 0;
	double threestar_count = 0;
	double twostar_count = 0;
	double onestar_count = 0;
	double pity_count = 0;
	
	std::random_device rd;
	//std::default_random_engine generator(time(0));
	std::mt19937 generator(time(0));
	std::uniform_real_distribution<double> distribution(0,1.0);
	
	for (int i = 0; i < rolls; i++) {
		double n = distribution(generator);
		if (pity_count == pity_rate || n <= pickup_rate) {
			v.push_back(pity_count);
			pity_count = 0;
			pickup_char_count++;
			threestar_count++;
		} else if (n <= threestar_rate) {
			pity_count++;
			threestar_count++;
		} else if (n <= twostar_rate + threestar_rate) {
			pity_count++;
			twostar_count++; 
		} else if (n <= onestar_rate + twostar_rate + threestar_rate){
			pity_count++;
			onestar_count++;
		}
	}
	
	int average_rolls = 0;
	int total = 0;
	int reached_pity = 0;	
	
	for (int i : v) {
		total += i;
		if (i == 200) {
			reached_pity++;
		}
	}
	if (v.size() > 0) {
		average_rolls = total/v.size();
	}	
	
	std::cout << "Pickup rate = " << pickup_char_count/rolls << std::endl;
	std::cout << "Three stars rate = " << threestar_count/rolls << std::endl;
	std::cout << "Two stars rate = " << twostar_count/rolls << std::endl;
	std::cout << "One star rate = " << onestar_count/rolls << std::endl;
	std::cout << "Total rolls = " << total << std::endl;
	std::cout << "average rolls = " << average_rolls << std::endl;
	std::cout << "reached pity = " << reached_pity << std::endl;
	
	return 0;
}
