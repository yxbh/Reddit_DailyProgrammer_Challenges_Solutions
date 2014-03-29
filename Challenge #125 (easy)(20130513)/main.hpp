#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

std::string filepath("B:\\project_spec.txt");
std::fstream fin;
std::stringstream file_content;
std::map<std::string, unsigned> total_word_count;

const bool CheckCmdArgv(const int p_argc, const std::string & p_path);

int main(int argc, char* argv[])
{
	if (!CheckCmdArgv(argc, filepath))
	{
		std::cerr << "Missing command arguements! Aborting..." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	(filepath.empty()) ? (fin.open(argv[1], std::ios::in)) : (fin.open(filepath, std::ios::in));
	if (!fin)
	{
		std::cerr << "Failed to open file! Aborting..." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	char buffer;
	std::string str_buf;
	unsigned num_symbols(0);
	while (!fin.eof() && fin.get(buffer)) // load from file, and count unique words
	{
		if (!isalpha(buffer))
		{
			if (str_buf.length() != 0)
			{
				std::transform(str_buf.begin(), str_buf.end(), str_buf.begin(), ::tolower);
				total_word_count[str_buf] += 1;
			}
			str_buf.clear();
		}
		else
			str_buf += buffer;

		if (!isspace(buffer) && !isalnum(buffer)) ++num_symbols;

		file_content << buffer;
	}

	// dump all unique words
	//for (auto & word_count : total_word_count) std::cout << word_count.first << std::endl;

	// calculate num letters
	unsigned num_letters(0);
	for (auto & word_count : total_word_count) num_letters += word_count.first.size() * word_count.second;

	// calculate top 3 common words
	std::map<unsigned, std::string> common_words;
	for (auto & word_count : total_word_count) common_words.insert(std::make_pair(word_count.second, word_count.first));
	//for (auto & common_word : common_words) std::cout << common_word.first << " : " << common_word.second << std::endl;

	// calculate top 3 common letters
	std::map<char, unsigned> letter_count;
	for (auto & word_count : total_word_count) for ( const char cb : word_count.first ) letter_count[cb] += word_count.second; 
	std::map<unsigned, char> common_letters;
	for (const auto char_count : letter_count) common_letters.insert(std::make_pair(char_count.second, char_count.first));

	// num word used only once
	unsigned num_singelton_word(0);
	std::vector<std::string> singelton_words;
	for (auto & word_count : total_word_count) if (word_count.second == 1) singelton_words.push_back(word_count.first);

	// print statistics
	std::cout << "Total unique words: " << total_word_count.size() << std::endl;
	std::cout << "Total number of letters: " << num_letters << std::endl;
	std::cout << "Total number of symbols: " << num_symbols << std::endl;
	std::cout << "Top 3 most common words: ";
	for (auto it = common_words.crbegin(); it != common_words.crend() && std::distance(common_words.crbegin(), it) < 3; ++it) std::cout << it->second << " ";
	std::cout << std::endl;
	std::cout << "Top 3 most common letters: ";
	for (auto it = common_letters.crbegin(); it != common_letters.crend() && std::distance(common_letters.crbegin(), it) < 3; ++it) std::cout << it->second << " ";
	std::cout << std::endl;
	std::cout << "Words only used once: ";
	for (const std::string & s_word : singelton_words) std::cout << s_word + " ";
	std::cout << std::endl;

	system("pause");
	return EXIT_SUCCESS;
} 

const bool CheckCmdArgv(const int p_argc, const std::string & p_path)
{
	if ( p_argc < 2 )
	{
		if (p_path.length() == 0)
			return false;
		else
			return true;
	}
	return true;
}
