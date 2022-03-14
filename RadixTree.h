//
//  RadixTree.h
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#ifndef RadixTree_h
#define RadixTree_h

#include <stdio.h>
#include <string>
#include <iostream>
struct Node;
struct Edge;

template <typename ValueType>
class RadixTree {
public:
    RadixTree() { root = new Node(false); }
    ~RadixTree() { delete root; }
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
    void print() {
        printPreorder(root);
    }
private:
    //nodes and edges to connect tree
    struct Edge;
    struct Node {
        Node(bool leaf) : isLeaf(leaf) { //node with no value is not a leaf
            for (int i = 0; i < 128; i++) //128 max unique characters
                edges[i] = new Edge();
        }
        Node(ValueType value) : isLeaf(true), value(value) {
            for (int i = 0; i < 128; i++) //128 max unique characters
                edges[i] = new Edge();
        }
        ~Node() {
            for (int i = 0; i < 128; i++) {
                if (edges[i] != nullptr)
                    delete edges[i];
            }
        }
        void newEdge(std::string label, const ValueType& value) {
            if (label.length() <= 0)
                return;
            int index = label.at(0) - 'a';
            edges[index] = new Edge(label, value);
        }
        bool isLeaf; //is the node the end of the word?
        ValueType value; //holds value if node is leaf
        Edge* edges[128]; //array of pointers to edges
    };
    struct Edge {
        Edge() {
            nextNode = nullptr;
            label = "";
        };
        Edge(std::string label) : label(label) {
            nextNode = new Node(true);
        }
        Edge(std::string label, ValueType value) : label(label) {
            nextNode = new Node(value);
        }
        ~Edge() {
            delete nextNode;
        }
        std::string label; //label of edge
        Node* nextNode; //ptr to next node
    };
    
    //helper functions
    void insertNode(std::string key, const ValueType& value, Node* n);
    int splitEdge(std::string edge, std::string key, std::string& match);
    void printPreorder(Node* node);
    
    //member variables
    Node* root; //ptr to root node
};


//radixtree member function definitions
template <typename ValueType>
inline void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
    insertNode(key, value, root);
}

template <typename ValueType>
inline void RadixTree<ValueType>::insertNode(std::string key, const ValueType& value, Node *n)
{
    if (key.length() <= 0)
        return;
    
    //base case: edge with same starting letter does not exist
    char curChar = key.at(0);
    int index = curChar - 'a';
    Edge* curEdge = n->edges[index];
    std::string edgeLabel = curEdge->label;
    if (edgeLabel == "") {
        n->newEdge(key, value);
        return;
    }
    
    //base case: duplicate key, update value to new value
    if (edgeLabel == key) {
        curEdge->nextNode->value = value;
        return;
    }
    
    //case: edge matches beginning of key
    if (edgeLabel.length() < key.length() && edgeLabel == key.substr(0, edgeLabel.length()))
        insertNode(key.substr(edgeLabel.length()), value, curEdge->nextNode);
    
    //case:: key matches beginning of edge
    if (edgeLabel.length() > key.length() && key == edgeLabel.substr(0, key.length())) {
        std::string edgeEnd = edgeLabel.substr(key.length());
        ValueType edgeValue = curEdge->nextNode->value;
        curEdge->label = key;
        curEdge->nextNode->value = value;
        insertNode(edgeEnd, edgeValue, curEdge->nextNode);
    }
    
    //case: edge partially matches beginning of key
    else {
        std::string match;
        int splitIndex = splitEdge(edgeLabel, key, match);std::string edgeEnd = edgeLabel.substr(splitIndex);
        ValueType edgeValue = curEdge->nextNode->value;
        curEdge->label = match;
        curEdge->nextNode->isLeaf = false;
        curEdge->nextNode->newEdge(edgeEnd, edgeValue);
        insertNode(key.substr(splitIndex), value, curEdge->nextNode);
    }
    
}

template <typename ValueType>
inline int RadixTree<ValueType>::splitEdge(std::string edge, std::string key, std::string& match)
{
    int count = 0;
    for (int i = 0; i < edge.length() && i < key.length(); i++) {
            if (edge[i] == key[i])
                count++;
    }
    match = edge.substr(0, count);
    return count;
}

template <typename ValueType>
inline void RadixTree<ValueType>::printPreorder(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    for (int i = 0; i < 128; ++i)
    {
        if (node->edges[i] != nullptr && node->edges[i]->label != "") {
            if (node->edges[i]->nextNode->isLeaf)
                std::cout << node->edges[i]->label << " : " << node->edges[i]->nextNode->value << std::endl;
            else
                std::cout << node->edges[i]->label << std::endl;
            printPreorder(node->edges[i]->nextNode);
        }
    }
}


#endif /* RadixTree_h */
