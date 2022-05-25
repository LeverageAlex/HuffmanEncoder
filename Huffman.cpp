//
// Created by alexanderfink on 25.05.22.
//

#include "Huffman.h"


std::map<char, int> countCharacters(std::string text) {
    std::map<char, int> probs;

    for (char character : text) {
        if(probs.contains(character)) {
            probs.at(character) += 1;
        }
        else {
            probs.emplace(character, 1);
        }
    }



    return probs;
}

std::deque<NodePtr> createVector(charTable chars) {
    std::deque<NodePtr> deque;
    for (auto [c, count] : chars) {
        auto node = std::make_shared<Node>(c, count);

        deque.push_back(node);
    }

    return deque;
}

NodePtr doHuffman(std::deque<NodePtr> nodes) {


    while(nodes.size() > 1) {
        std::sort(nodes.begin(), nodes.end(), [](const NodePtr &a, const NodePtr &b) { return a->getProb() < b->getProb(); });

        NodePtr firstNode = nodes.front();
        nodes.pop_front();
        NodePtr secondNode = nodes.front();
        nodes.pop_front();

        NodePtr newNode = std::make_shared<Node>(firstNode->getProb() + secondNode->getProb(), firstNode, secondNode);
        nodes.push_back(newNode);
    }
    return nodes.front();
}

static void goToLeafes(NodePtr currentNode, std::map<char, std::string> &map, std::string code) {
    if(currentNode != nullptr) {
        if (currentNode->isLeaf()) {
            map.emplace(currentNode->getChar(), code);
        } else {
            goToLeafes(currentNode->getLeft(), map, code + "0");
            goToLeafes(currentNode->getRight(), map, code + "1");

        }
    }
}

std::map<char, std::string> createHuffmanTable(NodePtr root) {
    std::map<char, std::string> huffTable;
    goToLeafes(root, huffTable, "");


    return huffTable;
}

std::string huffmanToText(std::string chiffrat, NodePtr root) {
    std::string encodedText;

    NodePtr currentNode = root;
    for (char c : chiffrat) {
        if(currentNode->isLeaf()) {
            encodedText += currentNode->getChar();
            currentNode = root;
        }
            if(c == '0') {
                currentNode = currentNode->getLeft();
            } else if(c == '1') {
                currentNode = currentNode->getRight();
            }


    }



    return encodedText;
}


char Node::getChar() const {
    return this->c.value();
}

double Node::getProb() const {
    return this->prob;
}

void Node::setChar(char l) {
    this->c = l;
}

void Node::setProb(double prob) {
    this->prob = prob;
}

Node::Node(char l, double probl):c(l),prob(probl) {
}

Node::Node(double probl, NodePtr left, NodePtr right):prob(probl), left(left), right(right) {
}

Node::Node(double probl):prob(probl) {

}

bool Node::isLeaf() const {
    return c.has_value();
}

NodePtr Node::getLeft() {
    return left;
}
NodePtr Node::getRight() {
    return right;
}



