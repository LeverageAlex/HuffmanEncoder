//
// Created by alexanderfink on 25.05.22.
//

#ifndef HUFFMAN_WORKSHOP_HUFFMAN_H
#define HUFFMAN_WORKSHOP_HUFFMAN_H

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <deque>
#include <optional>

using charTable = std::map<char, int>;

charTable countCharacters(std::string text);

class Node;
using NodePtr = std::shared_ptr<Node>;


class Node{
    std::optional<char> c;
    double prob;
    NodePtr left;
    NodePtr right;

public:
    Node(double probl);
    Node(char l, double probl);
    Node(double probl, NodePtr left, NodePtr right);
    [[nodiscard]] char getChar() const;
    [[nodiscard]] double getProb() const;
    void setChar(char l);
    void setProb(double prob);
    bool isLeaf() const;
    NodePtr getLeft();
    NodePtr getRight();
};

std::deque<NodePtr> createVector(charTable chars);
NodePtr doHuffman(std::deque<NodePtr> nodes);
std::map<char, std::string> createHuffmanTable(NodePtr root);

std::string huffmanToText(std::string chiffrat, NodePtr root);


#endif //HUFFMAN_WORKSHOP_HUFFMAN_H
