/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include "split.h"
#include <iostream>

int main(int argc, char* argv[])
{
    Node* n1 = new Node{2, nullptr};
    Node* n2 = new Node{3, nullptr};
    Node* n3 = new Node{5, nullptr};
    Node* n4 = new Node{8, nullptr};
    Node* n5 = new Node{10, nullptr};
    Node* n6 = new Node{11, nullptr};

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;

    Node* in = n1;
    Node* odds = nullptr;
    Node* evens = nullptr;

    split(in, odds, evens);

    std::cout << odds->value << " " << odds->next->value << odds->next->next->value << std::endl;
    std::cout << evens->value << " " << evens->next->value << odds->next->next->value << std::endl;
}
