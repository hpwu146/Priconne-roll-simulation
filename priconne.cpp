#include <iostream>
#include <random>
#include <vector>

int main (int argc, char* argv[]) 
{
	
	std::vector<int> v;
	double rolls;

	/*Check for arguments*/
	if (argc < 2) {
		std::cerr << "Require to enter the number of rolls.\n";
		return 0;
	} else {
		rolls = atoi(argv[1]);
	}

	/*Priconne Gacha rates*/
	double pickup_rate = 0.007; //0.7%
	double threestar_rate = 0.03; //3%
	double twostar_rate = 0.18; //18%
	double onestar_rate = 0.79; //79%
	double pity_rate = 200; //Ceiling 200 rolls
	
	/*Counters*/
	double pickup_char_count = 0;
	double threestar_count = 0;
	double twostar_count = 0;
	double onestar_count = 0;
	double pity_count = 0;
	
	/*Random device generator*/
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> distribution(0,1.0);
	
	/*Main loop for simulating rolls*/
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
	
	/*Variables for calculating how many pity was reached and average rolls taken to get a pickup character*/
	int average_rolls = 0;
	int total = 0;
	int reached_pity = 0;	
	
	/*Check how many times we reached pity when pickup character was acquired*/
	for (int i : v) {
		total += i;
		if (i == 200) {
			reached_pity++;
		}
	}
	if (v.size() > 0) {
		average_rolls = total/v.size();
	}	
	
	/*Print out the results*/
	std::cout << "Pickup rate = " << pickup_char_count/rolls << std::endl;
	std::cout << "Three stars rate = " << threestar_count/rolls << std::endl;
	std::cout << "Two stars rate = " << twostar_count/rolls << std::endl;
	std::cout << "One star rate = " << onestar_count/rolls << std::endl;
	std::cout << "Total rolls = " << total << std::endl;
	std::cout << "average rolls = " << average_rolls << std::endl;
	std::cout << "reached pity = " << reached_pity << std::endl;
	
	return 0;
}
