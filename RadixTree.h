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
    RadixTree() { root = new Node(false, true); }
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
        Node(bool end, bool leaf) : isEnd(end), isLeaf(leaf) {
            for (int i = 0; i < 128; i++) //128 max unique characters
                edges[i] = new Edge();
        }
        Node(ValueType value, bool leaf) : isEnd(true), value(value), isLeaf(leaf) {
            for (int i = 0; i < 128; i++) //128 max unique characters
                edges[i] = new Edge();
        }
        ~Node() {
            for (int i = 0; i < 128; i++) {
                if (edges[i] != nullptr)
                    delete edges[i];
            }
        }
        void newEdge(std::string label, const ValueType& value, bool leaf) {
            if (label.length() <= 0)
                return;
            int index = label.at(0) - 'a';
            edges[index] = new Edge(label, value, leaf);
        }
        bool isEnd; //is the node the end of the word?
        bool isLeaf; //is the node at the bottom of its branch?
        ValueType value; //holds value if node is leaf
        Edge* edges[128]; //array of pointers to edges
    };
    struct Edge {
        Edge() {
            nextNode = nullptr;
            label = "";
        };
        Edge(std::string label) : label(label) { //edge connectors (not actual words)
            nextNode = new Node(false, false);
        }
        Edge(std::string label, ValueType value, bool leaf) : label(label) {
            nextNode = new Node(value, leaf);
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
    
    bool inserted = false;
    char curChar = key.at(0);
    int index = curChar - 'a';
    Edge* curEdge = n->edges[index];
    std::string edgeLabel = curEdge->label;
    
    //base case: edge with same starting letter does not exist
    if (edgeLabel == "") {
        n->newEdge(key, value, true);
        return;
    }
    
    //base case: duplicate key, update value to new value
    if (edgeLabel == key) {
        curEdge->nextNode->value = value;
        return;
    }
    
    //inserting at bottom of tree
    if (curEdge->nextNode->isLeaf) {
        //case: edge matches beginning of key
        if (edgeLabel.length() < key.length() && edgeLabel == key.substr(0, edgeLabel.length())) {
            insertNode(key.substr(edgeLabel.length()), value, curEdge->nextNode);
            inserted = true;
        }
        
        //case:: key matches beginning of edge
        if (edgeLabel.length() > key.length() && key == edgeLabel.substr(0, key.length())) {
            std::string edgeEnd = edgeLabel.substr(key.length());
            ValueType edgeValue = curEdge->nextNode->value;
            curEdge->label = key;
            curEdge->nextNode->value = value;
            insertNode(edgeEnd, edgeValue, curEdge->nextNode);
            inserted = true;
        }
        
        //case: edge partially matches beginning of key
        if (!inserted) {
            std::string match;
            int splitIndex = splitEdge(edgeLabel, key, match);
            std::string edgeEnd = edgeLabel.substr(splitIndex);
            ValueType edgeValue = curEdge->nextNode->value;
            curEdge->label = match;
            curEdge->nextNode->isEnd = false;
            curEdge->nextNode->newEdge(edgeEnd, edgeValue, true);
            insertNode(key.substr(splitIndex), value, curEdge->nextNode);
        }
    }
    
    //inserting at middle of tree
    else {
        //case: edge matches beginning of key
        
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
            //if (node->edges[i]->nextNode->isEnd)
                std::cout << node->edges[i]->label << " : " << node->edges[i]->nextNode->value << std::endl;
            //else
           //     std::cout << node->edges[i]->label << std::endl;
            printPreorder(node->edges[i]->nextNode);
        }
    }
}


#endif /* RadixTree_h */
