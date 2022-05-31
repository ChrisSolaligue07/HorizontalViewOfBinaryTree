#include <iostream>
#include <queue>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

ofstream tree;
string null;

struct BTnode{
    int val;
    BTnode *izq;
    BTnode *der;
    BTnode(int val){
        this->val = val;
        izq = nullptr;
        der = nullptr;
    }
};

struct Btree{
    BTnode *root;
    Btree(){
        root = nullptr;
    }
    bool find(BTnode *&tmp, BTnode *&node_ant ,int val){
        for(auto i = root; i; tmp = i){
            if(val == i->val) {
                return false;
            }
            node_ant = i;
            i = (val < i->val) ? i->izq : i = i->der;
        }
        return true;
    }
    void insert(int val){
        if(root == nullptr){
            root = new BTnode(val);
            return;
        } else {
            BTnode *node = nullptr;
            BTnode *node_ant = nullptr;
            if(find(node, node_ant, val)){
                node = new BTnode(val);
                if(val < node_ant->val){
                    node_ant->izq = node;
                    return;
                } else if (val > node_ant->val) {
                    node_ant->der = node;
                    return;
                }
                return;
            } else {
                cout << "El dato existe" << endl;
                return;
            }

        }
    }
    int height(BTnode *node){
        if(node == nullptr) {
            return 0;
        } else {
            int leftHeight = height(node->izq);
            int rightHeight = height(node->der);
            return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
        }
    }


    void printNode(BTnode *node, int i, int alt_actual, int &spacesi, int &spacesii){
        if(i == alt_actual){
            if(node != nullptr) {
                tree << setw(spacesi) << node->val;
                cout << setw(spacesi) << node->val;
            } else {
                tree << setw(spacesi) << null;
                cout << setw(spacesi) << null;
            }
            spacesi = spacesii;
            return;
        } else {
            if(node == nullptr){
                printNode(node, i + 1, alt_actual, spacesi, spacesii);
                printNode(node, i + 1, alt_actual, spacesi, spacesii);
                return;
            }
            printNode(node->izq, i + 1, alt_actual, spacesi, spacesii);
            printNode(node->der, i + 1, alt_actual, spacesi, spacesii);
        }
    }

    void print(BTnode *root){
        int alt = height(root);
        int j = -1;
        int ji = -2;
        for(int i = 0; i < alt; i++){
            int a = pow(2, alt - (j++)); // j = j + 1;
            int b = pow(2, alt - (ji++)); // ji = ji + 1;
            printNode(root, 1, i + 1, a, b);
            cout << "\n";
            tree << "\n";
        }
    }

};

int main()
{
    tree.open("treeView.txt");
    Btree Bt;
    int root = 5;
    Bt.insert(root);

    null = to_string(root);                 // Obtain an adequate space for null values
    for(int i = 0; i < null.size(); i++){
        null[i] = '.';
    }

    Bt.insert(4);
    Bt.insert(10);
    Bt.insert(200);
    Bt.insert(2000);
    Bt.insert(-2);
    Bt.insert(-10);
    Bt.insert(-600);
    cout << "Tree height: " << Bt.height(Bt.root) << "\n\n";
    tree << "Tree height: " << Bt.height(Bt.root) << "\n\n";
    Bt.print(Bt.root);

    return 0;
}