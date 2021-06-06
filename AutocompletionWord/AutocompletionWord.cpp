#include "TrieDictionary.h"
#include <string>



int main()
{
	setlocale(LC_ALL,"ru");
	TrieNode* trieWord = new TrieNode();
	insert(trieWord, "cat");
	insert(trieWord, "catch");
	insert(trieWord, "cater");
	insert(trieWord, "cathode");
	insert(trieWord, "call");
	insert(trieWord, "cult");
	insert(trieWord, "can");
	insert(trieWord, "hello");
	insert(trieWord, "cache");
	insert(trieWord, "rut");
	insert(trieWord, "run");
	
	
	std::string wordVariants;
	wordVariants.clear();
	std::string firstVersionWord;
	std::string secondVersionWord;
	std::string thirdVersionWord;
	std::string inputWord;
	std::string fullText;
	std::string tempWord;
	std::string send;
	while (std::cin)
	{
		
		//(std::cin >> inputWord).get();// если не будет работать cin раскоментить эту строку
		getline(std::cin, inputWord);
		//std::cin.ignore(32767, '\n');
		if (inputWord == " ")
		{
			tempWord += inputWord;
			fullText += tempWord;
			std::cout << fullText;
			tempWord.clear();
			continue;
		}
		tempWord += inputWord;
		
		wordSubstitution(trieWord, wordVariants, tempWord);
		if (wordVariants=="")
		{
			std::cout << fullText << tempWord;
			continue;
		}
		char buf[50];
		int indexVersion = 0;
		int numberVersion = 0;

		/*std::cout << "Select the appropriate word by pressing 1, 2 or 3. If there is no such word, press 0\n";
		int сhoice;
		std::cin >> сhoice;
		std::cin.ignore(32767, '\n');
		for (size_t i = 0, ib =0; i < wordVariants.length(); ++i)
		{ 
			if (сhoice == 1)
			{
				buf[ib] = wordVariants[i];
			}
			if (wordVariants[i] == ' ')
			{
				--сhoice;
			}
		}*/
		for (size_t i = 0; i < wordVariants.length(); ++i)
		{
			if (numberVersion == 0)
			{
				buf[indexVersion] = wordVariants[i];
				indexVersion++;
				if (wordVariants[i] == ' ')
				{
					buf[indexVersion] = '\0';
					firstVersionWord += std::string(buf);
					numberVersion++;
					indexVersion = 0;
				}
				continue;
			}
			else if (numberVersion == 1)
			{
				buf[indexVersion] = wordVariants[i];
				indexVersion++;
				if (wordVariants[i] == ' ')
				{
					buf[indexVersion] = '\0';
					secondVersionWord += std::string(buf);
					numberVersion++;
					indexVersion = 0;
				}
				continue;
			}
			else if (numberVersion == 2)
			{
				buf[indexVersion] = wordVariants[i];
				indexVersion++;
				if (wordVariants[i] == ' ')
				{
					buf[indexVersion] = '\0';
					thirdVersionWord += std::string(buf);
					numberVersion++;
					indexVersion = 0;
				}
				continue;
			}

		}

		
		std::cout << "1 " << firstVersionWord << std::endl;

		std::cout << "2 " << secondVersionWord << std::endl;
		std::cout << "3 " << thirdVersionWord << std::endl;

		std::cout << "Select the appropriate word by pressing 1, 2 or 3. If there is no such word, press 0\n";
		char сhoice;
		std::cin >> сhoice;
				std::cin.ignore(32767, '\n');
		switch (сhoice)
		{
		case '1':
		{
			if (firstVersionWord != "")
				fullText += tempWord;
			else
			fullText += firstVersionWord;
			std::cout << fullText;
			wordVariants.clear();
			tempWord.clear();
			firstVersionWord.clear();
			secondVersionWord.clear();
			thirdVersionWord.clear();
			break;
		}
		case '2':
		{
			if (secondVersionWord != "")
			{
				fullText += secondVersionWord;
				tempWord.clear();
				std::cout << fullText;
			}
			else
			{
				std::cout << fullText << tempWord;
			}
			std::cout << fullText;
			wordVariants.clear();
			
			firstVersionWord.clear();
			secondVersionWord.clear();
			thirdVersionWord.clear();
			break;
		}
		case '3':
		{
			
				
				if (thirdVersionWord != "")
			{
				fullText += thirdVersionWord;
				tempWord.clear();
				std::cout << fullText;
			}
				else {
					std::cout << fullText<< tempWord;
				}
			wordVariants.clear();
			firstVersionWord.clear();
			secondVersionWord.clear();
			thirdVersionWord.clear();
			break;
		}
		default:
		{
			wordVariants.clear();
			firstVersionWord.clear();
			secondVersionWord.clear();
			thirdVersionWord.clear();
			std::cout << fullText<<tempWord;
		break;
		}
		}
	}
	return 0;
}

// Консольный ч