#include "vector.h"
#include "list.h"
#include "deque.h"
#include "hashtable.h"
#include "rbtree.h"
#include "set.h"
#include "unordered_set.h"
#include "multiset.h"
#include "map.h"
#include "unordered_map.h"
#include "multimap.h"
#include "stack.h"
#include "queue.h"
#include "priority_queue.h"
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
                std::cout << "elem not exist" << std::endl;
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

void testRBTree(){
    RBTree<int, int> rbTree;

    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; i++)
    {
      std::getline(std::cin, line);
      std::istringstream iss(line);
      std::string command;
      iss >> command;

      int key;
      int value;

      if (command == "insert")
      {
          iss >> key >> value;
          rbTree.insert(key, value);
      }

      if (command == "size")
      {
          std::cout << rbTree.size() << std::endl;
      }

      if (command == "at")
      {
          iss >> key;
          int *res = rbTree.at(key);
          if (res == nullptr)
          {
              std::cout << "not exist" << std::endl;
          }
          else
          {
              std::cout << *res << std::endl;
          }
      }

      if (command == "remove")
      {
          iss >> key;
          rbTree.remove(key);
      }

      if (command == "print")
      {
          if (rbTree.empty())
          {
              std::cout << "empty" << std::endl;
          }
          else
          {
              rbTree.print();
          }
      }
    }
    return;
}

void testSet(){
  set<int> mySet;

  // 插入元素
  mySet.insert(10);
  mySet.insert(20);
  mySet.insert(30);

  // 打印集合大小
  std::cout << "当前集合的大小: " << mySet.size() << std::endl;

  // 检查集合是否包含特定元素
  int keyToCheck = 20;
  std::cout << "集合是否包含元素" << keyToCheck << ": "
            << (mySet.contains(keyToCheck) ? "是" : "否") << std::endl;

  // 删除元素
  int keyToDelete = 20;
  mySet.erase(keyToDelete);
  std::cout << "删除元素" << keyToDelete
            << "后，当前集合的大小: " << mySet.size() << std::endl;

  // 再次检查集合是否包含已删除的元素
  std::cout << "删除元素" << keyToDelete << "后，集合是否包含元素"
            << keyToDelete << ": " << (mySet.contains(keyToCheck) ? "是" : "否")
            << std::endl;

  // 检查集合是否为空
  std::cout << "集合是否为空: " << (mySet.empty() ? "是" : "否") << std::endl;

  return;
}

void testUnorderedSet(){
  unordered_set<int> intSet;

  // 插入一些数字
  intSet.insert(1);
  intSet.insert(2);
  intSet.insert(3);

  // 检查集合是否为空
  std::cout << "集合是否为空? " << (intSet.empty() ? "是" : "否") << std::endl;

  // 检查集合的大小
  std::cout << "集合的大小: " << intSet.size() << std::endl;

  // 查找一个元素
  std::cout << "2 是否在集合中? " << (intSet.find(2) ? "是" : "否")
            << std::endl;

  // 删除一个元素
  intSet.erase(2);
  std::cout << "删除 2 后，2 是否还在集合中? " << (intSet.find(2) ? "是" : "否")
            << std::endl;

  // 清空集合
  intSet.clear();
  std::cout << "清空后集合是否为空? " << (intSet.empty() ? "是" : "否")
            << std::endl;

  // 创建一个字符串类型的 Unordered_set 集合
  unordered_set<std::string> stringSet;

  // 插入一些字符串
  stringSet.insert("apple");
  stringSet.insert("banana");
  stringSet.insert("cherry");

  // 查找一个字符串
  std::cout << "'banana' 是否在集合中? "
            << (stringSet.find("banana") ? "是" : "否") << std::endl;

  // 删除一个字符串
  stringSet.erase("banana");
  std::cout << "删除 'banana' 后，'banana' 是否还在集合中? "
            << (stringSet.find("banana") ? "是" : "否") << std::endl;

  return;
}

void testMultiSet(){
  multiset<int> mySet; // Create an Unordered_set for integers

  // Insert some elements
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);

  // Check if elements are in the set
  std::cout << "Does the set contain 1? " << (mySet.count(1) > 0 ? "Yes" : "No")
            << std::endl;
  std::cout << "Does the set contain 4? " << (mySet.count(4) > 0 ? "Yes" : "No")
            << std::endl;

  // Print the size of the set
  std::cout << "The set size is: " << mySet.size() << std::endl;

  // Remove an element
  mySet.erase(2);
  std::cout << "After erasing 2, does the set contain 2? "
            << (mySet.count(2) > 0 ? "Yes" : "No") << std::endl;
  std::cout << "The set size is now: " << mySet.size() << std::endl;

  // Clear the set
  mySet.clear();
  std::cout << "After clearing, is the set empty? "
            << (mySet.empty() ? "Yes" : "No") << std::endl;

  return;
}

void testMap(){
  map<int, std::string> map;

  // 插入键值对
  map.insert(1, "Apple");
  map.insert(2, "Banana");
  map.insert(3, "Cherry");

  // 打印大小
  std::cout << "当前Map的大小: " << map.size() << std::endl;

  // 访问元素
  try {
    std::cout << "键1对应的值: " << map.at(1) << std::endl;
    std::cout << "键2对应的值: " << map.at(2) << std::endl;
  } catch (const std::out_of_range &e) {
    std::cerr << "错误: " << e.what() << std::endl;
  }

  // 检查是否包含某个键
  int keyToCheck = 3;
  std::cout << "Map是否包含键" << keyToCheck << ": "
            << (map.contains(keyToCheck) ? "是" : "否") << std::endl;

  // 使用[]运算符访问或创建元素
  std::cout << "键4对应的值（在此之前不存在，将被创建）: " << map[4]
            << std::endl;

  // 删除元素
  int keyToDelete = 2;
  std::cout << "删除键" << keyToDelete << std::endl;
  map.erase(keyToDelete);

  // 再次打印大小
  std::cout << "删除键" << keyToDelete << "后，当前Map的大小: " << map.size()
            << std::endl;

  // 使用[]运算符为元素赋值
  map[4] = "Pear";
  std::cout << "键4对应的值: " << map[4] << '\n';
  return;
}

void testUnorderedMap()
{
  unordered_map<std::string, std::string> map;

  // 插入一些键值对
  map.insert("apple", "苹果");
  map.insert("banana", "香蕉");
  map.insert("cherry", "樱桃");

  // 检查映射是否为空
  std::cout << "映射是否为空? " << (map.empty() ? "是" : "否") << std::endl;

  // 获取映射的大小
  std::cout << "映射的大小: " << map.size() << std::endl;

  // 访问元素
  std::cout << "apple 对应的中文是: " << map["apple"] << std::endl;

  // 修改元素
  map["apple"] = "红苹果";
  std::cout << "修改后 apple 对应的中文是: " << map["apple"] << std::endl;

  // 使用 [] 操作符插入新的键值对
  map["orange"] = "橙子";
  std::cout << "orange 对应的中文是: " << map["orange"] << std::endl;

  // 查找元素
  std::cout << "cherry 是否在映射中? " << (map.find("cherry") ? "是" : "否")
            << std::endl;

  // 删除元素
  map.erase("banana");
  std::cout << "删除 banana 后，banana 是否还在映射中? "
            << (map.find("banana") ? "是" : "否") << std::endl;

  // 清空映射
  map.clear();
  std::cout << "清空后映射是否为空? " << (map.empty() ? "是" : "否")
            << std::endl;

}

void testMultiMap()
{
  multimap<std::string, int> myMultiMap;

  // 插入一些键值对
  myMultiMap.insert("apple", 10);
  myMultiMap.insert("banana", 20);
  myMultiMap.insert("apple", 30); // "apple"可以有多个值

  // 获取并打印键"apple"的所有值
  auto appleValues = myMultiMap.at("apple");
  if (appleValues) {
    std::cout << "Values for 'apple':";
    for (const auto &val : *appleValues) {
      std::cout << val << ", ";
    }
    std::cout << '\n';
  }

  // 从MultiMap中移除键"banana"的所有值
  myMultiMap.remove("banana");

  // 从MultiMap中移除键"apple"的值30
  myMultiMap.remove("apple", 30);

  // 检查MultiMap是否为空
  if (!myMultiMap.empty()) {
    std::cout << "The MultiMap is not empty, it has " << myMultiMap.size()
              << " elements." << std::endl;
  }

}


void testStack(){
    stack<int> stack;

    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int element;
        if (command == "push") {
            iss >> element;
            stack.push(element);
        }
        if (command == "pop") {
            try {
                stack.pop();
            } catch(const std::runtime_error& e) {
                // 不做任何处理
                continue;
            }
        }
        if (command == "top") {
            try {
                std::cout << stack.top() << std::endl;
            } catch(const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }   
        }
        if (command == "size") {
            std::cout << stack.size() << std::endl;
        }
        if (command == "empty") {
            std::cout << (stack.empty() ? "true" : "false") << std::endl;
        }
    }
}

void testQueue()
{
   queue<int> myQueue;

    int N;
    std::cin >> N;
    getchar();
    std::string line;

    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        int element;

        if (command == "push") {
            iss >> element;
            myQueue.push(element);
        }

        if (command == "pop") {
            try {
                myQueue.pop();
            } catch(const std::runtime_error& e) {
                // 不做任何处理
                continue;
            }
        }

        if (command == "front") {
            try {
                std::cout << myQueue.front() << std::endl;
            } catch(const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }   
        }

        if (command == "back") {
            try {
                std::cout << myQueue.back() << std::endl;
            } catch(const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }   
        }

        if (command == "size") {
            std::cout << myQueue.size() << std::endl;
        }

        if (command == "empty") {
            std::cout << (myQueue.empty() ? "true" : "false") << std::endl;
        }
    }
}

void testPriorityQueue()
{
    priority_queue<int> pq1;

    pq1.push(3);
    pq1.push(1);
    pq1.push(4);
    pq1.push(1);

    std::cout << "Top element of pq1: " << pq1.top() << std::endl;

    pq1.pop();
    std::cout << "Priority queue pq1 size after pop: " << pq1.size() << std::endl;

    // 使用 std::vector 作为底层容器的示例
    std::vector<int> vec = {9, 5, 7, 2, 6};
    priority_queue<int, std::vector<int>> pq2(vec);

    std::cout << "Top element of pq2: " << pq2.top() << std::endl;

    pq2.pop();
    std::cout << "Priority queue pq2 size after pop: " << pq2.size() << std::endl;

}
int main()
{
    // testVector();
    // testList();
    // testDeque();
    // testHashTable();
    // testRBTree();
    // testSet();
    // testUnorderedSet();
    // testMultiSet();
    // testMap();
    // testUnorderedMap();
    // testMultiMap();
    // testStack();
    // testQueue();
    testPriorityQueue();
    return 0;
}