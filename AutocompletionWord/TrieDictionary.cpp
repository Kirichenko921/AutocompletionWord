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

    for (int i = 0; i < key.length(); i++)
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

    for (int i = 0; i < key.length(); i++)
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
void has_prefix(TrieNode* node, int& cnt_ends)
{
    if (node->isEndOfWord) // если слово кончилось добавить в счетчик
        cnt_ends++;
    for (size_t i = 0; i < ALPHABET_SIZE; i++) // идем по дереву и считаем еще концы слов
    {
        if (node->children[i]) {
            has_prefix(node->children[i], cnt_ends);
        }
    }
}
                                                                                                                                                                                                                        
void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{
    // ваш код
    
        if (!root)
            return;
        int cnt = 0;
        has_prefix(root, cnt);
        if (cnt == 1)
        {
            buf[ind] = '\0'; // закончить строку
            res += std::string(buf) + " "; // добавить в результат и пробел после
            return; // возврат из рекурсии
        }
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if (root->children[i])
            {
                char c = i + 'a';
                buf[ind] = c;
                findMinPrefixes(root->children[i], buf, ind + 1, res);
            }
        }
}
  