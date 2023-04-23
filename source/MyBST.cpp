#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

struct Node {
    int number;
    Node *parent = nullptr;
    Node *leftChild = nullptr;
    Node *rightChild = nullptr;
};

class MyBST {
private:
    Node *root = nullptr;

public:

    /**
     * Dodanie
     * @param n
     */
    void add(int n) {
        Node *newNode = new Node;
        newNode->number = n;

        if (this->root == nullptr) {
            this->root = newNode;
            return;
        }

        this->addBelowNode(newNode, this->root);
    }

    void addBelowNode(Node *newNode, Node *parent) {
        if (newNode->number > parent->number) {
            // dodajemu po prawej
            if (parent->rightChild == nullptr) {
                parent->rightChild = newNode;
                newNode->parent = parent;
            } else {
                this->addBelowNode(newNode, parent->rightChild);
            }
        } else {
            // dodajemy po lewej
            if (parent->leftChild == nullptr) {
                parent->leftChild = newNode;
                newNode->parent = parent;
            } else {
                this->addBelowNode(newNode, parent->leftChild);
            }
        }
    }

    /**
     * metoda usuwająca element z drzewa
     * @param n
     * @param node
     * @return
     */
    int remove(int n, Node *node = nullptr) {
        if (node == nullptr) {
            node = this->root;
        }

        // usuwanie tego konkretnego elementu
        if (node->number == n) {
            // korzen
            if (node->parent == nullptr) {
                // nie ma dzieci
                if (node->leftChild == nullptr && node->rightChild == nullptr) {
                    delete node;
                    this->root = nullptr;
                }
                    // ma oboje dzieci
                else if (node->leftChild != nullptr && node->rightChild != nullptr) {
                    Node *next = node->rightChild;
                    while (next->leftChild != nullptr) {
                        next = next->leftChild;
                    }
                    node->number = next->number;
                    this->remove(next->number, next);
                }
                    // ma tylko lewe dziecko
                else if (node->leftChild != nullptr && node->rightChild == nullptr) {
                    Node *tmp = node->leftChild;
                    delete node;
                    tmp->parent = nullptr;
                    this->root = tmp;
                }
                    // ma tylko prawe dziecko
                else {
                    Node *tmp = node->rightChild;
                    delete node;
                    tmp->parent = nullptr;
                    this->root = tmp;
                }
            }
                // nie korzen
            else {
                // nie ma dzieci
                if (node->leftChild == nullptr && node->rightChild == nullptr) {
                    // usuwany jest lewym dzieckiem
                    if (node->parent->leftChild != nullptr && node->parent->leftChild->number == node->number) {
                        node->parent->leftChild = nullptr;
                    }
                        // usuwany jest prawym dzieckiem
                    else {
                        node->parent->rightChild = nullptr;
                    }
                    delete node;
                }
                    // ma oboje dzieci
                else if (node->leftChild != nullptr && node->rightChild != nullptr) {
                    Node *next = node->rightChild;
                    while (next->leftChild != nullptr) {
                        next = next->leftChild;
                    }
                    node->number = next->number;
                    this->remove(next->number, next);
                }
                    // ma tylko lewe dziecko
                else if (node->leftChild != nullptr && node->rightChild == nullptr) {
                    // usuwany jest lewym dzieckiem
                    if (node->parent->leftChild != nullptr && node->parent->leftChild->number == node->number) {
                        node->parent->leftChild = node->leftChild;
                    }
                        // usuwany jest prawym dzieckiem
                    else {
                        node->parent->rightChild = node->leftChild;
                    }
                    delete node;
                }
                    // ma tylko prawe dziecko
                else {
                    // usuwany jest lewym dzieckiem
                    if (node->parent->leftChild != nullptr && node->parent->leftChild->number == node->number) {
                        node->parent->leftChild = node->rightChild;
                    }
                        // usuwany jest prawym dzieckiem
                    else {
                        node->parent->rightChild = node->rightChild;
                    }
                    delete node;
                }
            }
            return 1;
        }

        if (node->leftChild != nullptr && this->remove(n, node->leftChild) != -1) {
            return 1;
        }
        if (node->rightChild != nullptr && this->remove(n, node->rightChild) != -1) {
            return 1;
        }

        return -1;
    }

    int search(int n, Node *node = nullptr) {
        if (node == nullptr) {
            node = this->root;
        }

        if (node->number == n) {
            return 1;
        }

        if (node->leftChild != nullptr && this->search(n, node->leftChild) != -1) {
            return 1;
        }
        if (node->rightChild != nullptr && this->search(n, node->rightChild) != -1) {
            return 1;
        }

        return -1;
    }

    void destroy() {
        removeNodes(this->root);
        this->root = nullptr;
    }

    void removeNodes(Node *node) {
        if (node == nullptr) {
            return;
        }
        this->removeNodes(node->leftChild);
        this->removeNodes(node->rightChild);
        delete (node);
    }

    void restart() {
        this->destroy();
    }

    void printBST() {
        print("", this->root, false, true);
    }

    // wyświetlanie drzewa, źródło: stackoverflow.com
    void print(const string &prefix, Node *parent, bool isLeft, bool isRoot) {
        if (parent == nullptr)
            return;

        if (isRoot) {
            cout << "─────";
        } else {
            cout << prefix <<
                 (isLeft ? "L├────" : "R└───");
        }
        cout << parent->number << endl;

        print(prefix + (isLeft ? " │   " : "    "),
              parent->leftChild, true, false);
        print(prefix + (isLeft ? " │   " : "    "),
              parent->rightChild, false, false);
    }

    MyBST() {
        this->root = nullptr;
    };

    MyBST(int *data, int length) {
        if (length == 0) {
            this->root = nullptr;
        }
        for (int i = 0; i < length; i++) {
            this->add(data[i]);
        }
    };
};