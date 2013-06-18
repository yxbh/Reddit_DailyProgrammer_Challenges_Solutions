/**
  *	Author: YanXiang (Ben) Huang
  * Date: 18/06/2013
  * Reddit link to challenge: http://www.reddit.com/r/dailyprogrammer/comments/1givnn/061713_challenge_130_easy_roll_the_dies/
  */
#include <iostream>
#include <random>
#include <string>
#include <sstream>

struct roll
{
	unsigned int diceCount;
	unsigned int diceFaceCount;
};

const roll parser(const std::string p_cmd)
{
	std::stringstream ss(p_cmd);
	roll newRoll;
	ss >> newRoll.diceCount;
	ss.ignore() >> newRoll.diceFaceCount;
	return newRoll;
}

void print_dice(const int argc, const char* const argv[])
{
	std::default_random_engine rand;
	for(int i = 1; i < argc; ++i)
	{
		roll newRoll = parser(argv[i]);
		std::uniform_int_distribution<int> distribution(1,newRoll.diceFaceCount);
		for (int j = 0; j < static_cast<int>(newRoll.diceCount); ++j)
		{
			std::cout << distribution(rand) << " ";
		}
		std::cout << "\n";
	}
}

int main(const int argc,const char* const argv[]/**/)
{
	print_dice(argc, argv);
	return 0;
}

