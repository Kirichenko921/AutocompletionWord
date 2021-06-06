#include "TrieDictionary.h"

// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префиксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, std::string key)
{
    TrieNode* node = root;

    for (size_t i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфавите через смещение относитьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false 
bool search(struct TrieNode* root, std::string key)
{
    struct TrieNode* node = root;

    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// Вохвращает true если root имеет лист, иначе false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
TrieNode* remove(TrieNode* root, std::string key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // возвращаем новый корень
    return root;
}
void hasPrefix(TrieNode* nodeCurrent, int& countEnds)
{
    if (nodeCurrent->isEndOfWord) // если слово кончилось добавить в счетчик
        countEnds++;
    for (size_t i = 0; i < ALPHABET_SIZE; i++) // идем по дереву и считаем еще концы слов
    {
        if (nodeCurrent->children[i])
        {
            hasPrefix(nodeCurrent->children[i], countEnds);
        }
    }
}
                                                                                                                                                                                                                        
void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{
    
    
        if (!root)
            return;
        int count = 0;
         hasPrefix(root, count);
        if (count == 1)
        {
            buf[ind] = '\0'; // закончить строку
            res += std::string(buf) + " "; // добавить в результат и пробел после
            return; // возврат из рекурсии
        }
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if (root->children[i])
            {
                char currentChar = i + 'a';
                buf[ind] = currentChar;
                findMinPrefixes(root->children[i], buf, ind + 1, res);
            }
        }
}
//----------------------------------------------------------------------------------------

void wordSubstitution(TrieNode* root,std::string& result, std::string currentWord ) // функция поиска слов для подстановки
{
    if (!root) // если дерево пустое
        return;
    if (currentWord.empty())// если несчем сравнивать
        return;
    char buf[50]; // буфер в которой будем ложить символы подходящие для автоподстановки
    size_t indexChar = 0;  // индекс для буфера
       int counterWords = 0; // счётчик слов которые будут предложены для авттоподстановки
       bool charPresence = true; // проверка наличия символов дерева совпадающих с введённым
    while (indexChar < currentWord.length()) // ищем совпадения введённой строки с наличием в дереве
    {
        if (!charPresence) // если символы нет хот бы одного совпадения 
            return;
            charPresence = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i) // ищем совпадение в узле
        {
            if (root->children[i]) // если есть символ в узле
            {
                if (currentWord[indexChar] == i + 'a') // и если он совпадает с текущим символом  введённой строки 
                {
                    buf[indexChar] = i + 'a';  //  в буфер добавляем символ
                    indexChar++;               // увеличиваем индекс
                    root = root->children[i];  // переходим в дочерний узел
                    charPresence = true;        // соообщаем что символ нашли
                    i = ALPHABET_SIZE;
                 if (root->isEndOfWord && indexChar == currentWord.length()) //  если последний символ введённого слова совпадает с концом слова в словаре
                {
                    buf[indexChar] = '\0'; // закончить строку
                    result += std::string(buf) + " "; // добавить слово в результат 
                    counterWords++;                   // увеличить счётчик слов
                  
                }
                    else if (indexChar == currentWord.length()) // если просто закончилось введённое слово 
                    {
                     buf[indexChar] = '\0'; // закончить строку                  
                        result += std::string(buf); // добавить слово в результат 
                          
                    }
                                       
                }
            }
        }
    }
   if (counterWords==0)  // если слов для автоподставления небыло найдено
    result.clear();      // очищаем результат
    charPresence = false; // т.к isEndOfWord может быть true, переменная исполнит роль флага окончания строки
    wordSubstitutionInner(root, buf, indexChar, result, counterWords, charPresence);// запускаем алгоритм поиска слов
}
void wordSubstitutionInner(TrieNode* root, char buf[], int indexChar, std::string& result,int &counterWords,bool endWord)// внутрення функция поиска слов для подстановки
{
    if (endWord)  // если дошли до конца слова
    {
        buf[indexChar] = '\0'; // закончить строку
        result += std::string(buf)+" "; // добавить к результату
        counterWords++;                //  увеличить счётчик
    }
   
    for (int i = 0; i < ALPHABET_SIZE; ++i)// ищем  продолжение слова
    {
        if (counterWords >= 3) // если слов уже три
            return;
        if (root->children[i]) // если есть следующий символ
        {
           buf[indexChar] = i + 'a';
           endWord = root->children[i]->isEndOfWord;
           wordSubstitutionInner(root->children[i], buf, indexChar + 1, result, counterWords, endWord);
        }
    }
}