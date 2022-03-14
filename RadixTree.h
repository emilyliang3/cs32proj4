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

template <typename ValueType>
class RadixTree {
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
private:
    //nodes and edges to connect tree
    struct Node {
        Node(bool isLeaf) : isLeaf(isLeaf)) {
            edges* = new CharEdge[127]; //128 max unique characters
        }
        ~Node() {
            delete[] edges;
        }
        bool isLeaf; //is the node the end of the word?
        Node* edges[]; //array of pointers to edges
        ValueType value; //holds value if node is leaf
    };
    struct Edge {
        Edge(string label) : label(label) {
            *nextNode = new Node(true);
        }
        string label; //label of edge
        Node* nextNode; //ptr to next node
    };
    struct CharEdge { //data structure that holds edges since not allowed to use hashmaps
        CharEdge() : edgeExist(false) { //by default no edge exists
            e = nullptr;
        }
        char c;
        bool edgeExist;
        Edge* e;
    };
    //other
    Node* root; //ptr to root node
};

RadixTree::RadixTree()
{
    root = new Node(false);
}

RadixTree::~RadixTree()
{
    delete root;
}

#endif /* RadixTree_h */
