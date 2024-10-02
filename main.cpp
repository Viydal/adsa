#include <iostream>
#include <string>
#include <tuple>
#include <vector>

class hashTable {
protected:
  std::vector<int> vectorStrings(26, 0);

public:
  hashTable() { vectorStrings(26, std::make_tuple("NULL", "NULL")); }

  bool searchKey(std::string key) {}

  void insertValue(std::string key) {
    int hashKey = hashFunction(key);
    while (/* condition */) {
      /* code */
    }
  }

  void deleteValue(std::string key) {}

  int hashFunction(std::string key) {
    int hashKey = key[key.length() - 1] - 'a';
    return hashKey;
  }
};

int main() {
  hashTable hash;
  std::cout << hash.hashFunction("apple") << std::endl;
}