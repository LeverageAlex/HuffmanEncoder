#include <iostream>
#include <fstream>
#include "Huffman.h"


int main() {
    std::ifstream file("text.txt");
    if(!file.is_open()) {
        throw std::runtime_error("Could not open File");
    }

    //Read text
    std::string text;
    while(file) {
        char c;
        file.get(c);
        text += c;
    }
    //Debug Output
    //std::cout << text << std::endl;

    std::map charProbs = countCharacters(text);
    std::cout << "Truth table:" << std::endl;
    for(auto [c, count] : charProbs) {
        std::cout << c << ": " << count << std::endl;
    }

    std::deque<NodePtr> nodes = createVector(charProbs);

    NodePtr root = doHuffman(nodes);

    std::map<char, std::string> huffTable = createHuffmanTable(root);


    std::string encodedText;
    for (auto c: text) {
        encodedText += huffTable.at(c);
    }

    std::cout << "Encoded Text: " << encodedText << std::endl;

    std::string decodedOutput = huffmanToText(encodedText, root);

    std::cout << "Decoded Text:\n" << decodedOutput << std::endl;


    return 0;
}


