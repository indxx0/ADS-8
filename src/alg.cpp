// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include  "bst.h"

bool isLatinLetter(int ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char toLowerCase(int ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return static_cast<char>(ch + ('a' - 'A'));
    }
    return static_cast<char>(ch);
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string word = "";
    int ch;

    while ((ch = file.get()) != EOF) {
        if (isLatinLetter(ch)) {
            word += toLowerCase(ch);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word = "";
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words;
    
    tree.getElements(words);

    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    });

    std::ofstream outFile("result/freq.txt");

    for (const auto& pair : words) {
        std::cout << pair.first << ": " << pair.second << "\n";
        if (outFile) {
            outFile << pair.first << " " << pair.second << "\n";
        }
    }
    
    if (outFile) outFile.close();
}
