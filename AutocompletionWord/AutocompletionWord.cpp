#include "TrieDictionary.h"
#include <string>



int main()
{
	// заполняем словарь
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
	
	
	std::string wordVariants;// переменная для всех вариантов слов для автоподстановки
	wordVariants.clear();    // очистим её 
	std::string VersionWord;  // вариант выбранного слова из предложенных автоподстановкой
	std::string inputWord;    // вводимое слово
	std::string fullText;     // всё что ввёл пользователь
	std::string tempWord;     // пееменная для хранения необработанных слов 
	//std::string send;
	bool space=true;           // проверка наличия пробелов
		while (std::cin)  // программа будет работать пока пользователь не закроет терминал(чата нет и письмо отправлять не надо)
	{
		
		//(std::cin >> inputWord).get();// если не будет работать cin раскоментить эту строку
		getline(std::cin, inputWord);
		//std::cin.ignore(32767, '\n');
		for (size_t i = 0,ib=0; i < inputWord.length(); ++i)// заполняем введённым текстом 
		{
			
			fullText.push_back(inputWord[i]);
			tempWord.push_back(inputWord[i]);
			
			if (inputWord[i] == ' ')  // если пользователь закончил вводить слово
			{
				tempWord.clear();    // убираем его из необработанных слов
			}
			
		}					
		wordSubstitution(trieWord, wordVariants, tempWord); // незаконченное слово отправляем на поиск сло для автоподстановки
		if (wordVariants.empty())  // если в словаре вариантов нет
		{
			tempWord.clear(); 
			std::cout << fullText;
			continue;
		}
		wordVariants.erase(wordVariants.length() - 1); // убираем пробел 
				int choice= 1;                      // нумерация вариантов
		std::cout << std::endl<<choice<< " ";
		for (size_t i = 0; i < wordVariants.length(); ++i)  // выводим варианты на экран
		{
			if (wordVariants[i] == ' ')
			{
				choice++;
				std::cout << std::endl << choice;
			}
			std::cout << wordVariants[i];
		}
		std::cout << "\nSelect the appropriate word by pressing 1, 2 or 3. If there is no such word, press 0\n";  // предлагаем выбрать вариант
		
		std::cin >> choice;
		std::cin.ignore(32767, '\n');
		for (size_t i = 0; i < wordVariants.length(); ++i)  //  выбранное слово заносим в VersionWord
		{ 
			if (choice == 1)
			{
				VersionWord.push_back( wordVariants[i]);
				
			}
			if (wordVariants[i] == ' ')
			{
				--choice;
			}
			if (choice < 1)
			{
				
				break;
			}
					}

			if (!VersionWord.empty())  // если пользователь выбрал какой либо вариант
		{
			fullText.erase(fullText.length()-tempWord.length());
			fullText += VersionWord;
			tempWord.clear();
			std::cout << fullText;
		}
		else                                 // если не выбрал 
			std::cout << fullText;
		
		wordVariants.clear();
		VersionWord.clear();
		
		

	}
	return 0;
}

