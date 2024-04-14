#include "vector.h"
#include "list.h"
#include "deque.h"
#include "hashtable.h"
using namespace myStd;
void testVector(){
   // 创建一个 Vector 对象
    vector<int> myVector;

    int N;
    std::cin >> N;
    // 读走回车
    getchar();

    std::string line;
    for (int i = 0; i < N; i++)
    {
        // 读取整行
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "push")
        {
            int value;
            iss >> value;
            myVector.push_back(value);
        }
        else if (command == "print")
        {
            if (myVector.size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            myVector.printElements();
        }
        else if (command == "size")
        {
            std::cout << myVector.size() << std::endl;
        }
        else if (command == "get")
        {
            int index;
            iss >> index;
            std::cout << myVector[index] << std::endl;
        }
        else if (command == "insert")
        {
            int index, value;
            iss >> index >> value;
            myVector.insert(index, value);
        }
        else if (command == "pop")
        {
            myVector.pop_back();
        }
        else if (command == "iterator")
        {
            if (myVector.size() == 0)
            {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (auto it = myVector.begin(); it != myVector.end(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "foreach")
        {
            if (myVector.size() == 0)
            {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto &element : myVector)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "clear")
        {
            myVector.clear();
        }
    }
}

void testList(){
     list<int> myList;
    
    int N;
    std::cin >> N;
    // 读走回车
    getchar();
    std::string line;
    // 接收命令
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_back") {
            iss >> value;
            myList.push_back(value);
        }

        if (command == "push_front") {
            iss >> value;
            myList.push_front(value);
        }

        if (command == "pop_back") {
            myList.pop_back();
        }

        if (command == "pop_front") {
            myList.pop_front();
        }

        if (command == "remove") {
            iss >> value;
            myList.remove(value);
        }

        if (command == "clear") {
            myList.clear();
        }

        if (command == "size") {
            std::cout << myList.size() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << myList[value] << std::endl;
        }

        if (command == "print") {
            if (myList.size() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                myList.printElements();
            }
        }
    }
    return;
}

void testDeque(){
    deque<int> myDeque;

    int N;
    std::cin >> N;
    // 读走回车
    getchar();
    std::string line;
    // 接收命令
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_back") {
            iss >> value;
            myDeque.push_back(value);
        }

        if (command == "push_front") {
            iss >> value;
            myDeque.push_front(value);
        }

        if (command == "pop_back") {
            if (myDeque.size() == 0) {
                continue;
            }
            myDeque.pop_back();
        }

        if (command == "pop_front") {
            if (myDeque.size() == 0) {
                continue;
            }
            myDeque.pop_front();
        }

        if (command == "clear") {
            myDeque.clear();
        }

        if (command == "size") {
            std::cout << myDeque.size() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << myDeque[value] << std::endl;
        }

        if (command == "print") {
            if (myDeque.size() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                myDeque.printElements();
            }
        }
    }
    return;
}

void testHashTable(){
    HashTable<int, int> hashTable;

    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        
        int key;
        int value;

        if (command == "insert") {
            iss >> key >> value;
            hashTable.insert(key, value);
        }

        if (command == "erase") {
            if (hashTable.size() == 0) {
                continue;
            }
            iss >> key;
            hashTable.erase(key);
        }

        if (command == "find") {
            if (hashTable.size() == 0) {
                std::cout << "not exist" << std::endl;
                continue;
            }
            iss >> key;
            int* res = hashTable.find(key);
            if (res != nullptr) {
                std::cout << *res << std::endl;
            } else {
                std::cout << "not exist" << std::endl;
            }
        }

        if (command == "print") {
            if (hashTable.size() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                hashTable.print();
            }
        }

        if (command == "size") {
            std::cout << hashTable.size() << std::endl;
        }
    }
}

int main()
{
    // testVector();
    // testList();
    // testDeque();
    testHashTable();
    return 0;
}