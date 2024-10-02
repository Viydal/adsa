#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class hashTable {
protected:
  std::vector<std::tuple<std::string, std::string>> table;

public:
  hashTable() {
    for (int i = 0; i < 26; i++) {
      table.push_back(std::make_tuple("NULL", "never used"));
    }
  }

  int searchKey(std::string key) {
    int hashKey = hashFunction(key);

    int counter = 0;
    while (counter < 26) {
      if (std::get<1>(table[hashKey]) == "never used") {
        return hashKey;
      } else {
        hashKey++;
        if (hashKey > 25) {
          hashKey = 0;
        }
        counter++;
      }
    }

    return -1;
  }

  void insertValue(std::string key) {
    std::tuple<std::string, std::string> newTuple = std::make_tuple(key, "occupied");

    int pos = searchKey(key);

    if (pos == -1) {
      std::cout << "NOT ENOUGH SPACE." << std::endl;
      return;
    } else {
      table[pos] = newTuple;
    }
  }

  void deleteValue(std::string key) {
    int hashKey = hashFunction(key);

    int counter = 0;
    while (counter < 26) {
      if (std::get<1>(table[hashKey]) == "never used") {
        return;
      } else {
        if (std::get<0>(table[hashKey]) == key) {
          std::get<1>(table[hashKey]) = "tombstone";
          return;
        }
        hashKey++;
        if (hashKey > 25) {
          hashKey = 0;
        }
        counter++;
      }
    }
  }

  int hashFunction(std::string key) {
    int hashKey = key[key.length() - 1] - 'a';
    return hashKey;
  }

  void printTable() {
    for (size_t i = 0; i < table.size(); i++) {
      std::string key = std::get<0>(table[i]);
      std::string status = std::get<1>(table[i]);

      if (status == "occupied") {
        std::cout << key << " ";
      }
    }
  }
};

int main() {
  hashTable hash;

  std::string input;
  std::getline(std::cin, input);

  std::stringstream ss(input);

  std::string currentInstruction;
  while (ss >> currentInstruction) {
    if (currentInstruction[0] == 'A') {
      hash.insertValue(
          currentInstruction.substr(1, currentInstruction.length() - 1));
    } else if (currentInstruction[0] == 'D') {
      hash.deleteValue(
          currentInstruction.substr(1, currentInstruction.length() - 1));
    }
  }

  hash.printTable();
}