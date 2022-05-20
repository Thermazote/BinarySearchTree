#include <iostream>
#include <vector>


class Node
{
public:
    int key;
    Node* left_node;
    Node* right_node;

    Node(int key)
    {
        this->key = key;
        this->left_node = nullptr;
        this->right_node = nullptr;
    }

    void print()
    {
        std::cout << this->key << '\t';
    }
};


class BinTree
{
private:
    Node* root;

    int global_indent = 4;
    
    void add(Node* node, int key)
    {
        if (key < node->key) {
            if (!node->left_node) {
                node->left_node = new Node(key);
            }
            else {
                add(node->left_node, key);
            }
        }
        else {
            if (!node->right_node) {
                node->right_node = new Node(key);
            }
            else {
                add(node->right_node, key);
            }
        }
    }

    struct Trunk
    {
        Trunk* prev;
        std::string str;

        Trunk(Trunk* prev, std::string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };

    void showTrunks(Trunk* p)
    {
        if (p == nullptr) {
            return;
        }

        showTrunks(p->prev);
        std::cout << p->str;
    }

    void print(Node* node, Trunk* prev, bool isLeft)
    {
        if (node == nullptr) {
            return;
        }

        std::string prev_str = "    ";
        Trunk* trunk = new Trunk(prev, prev_str);

        print(node->right_node, trunk, true);

        if (!prev) {
            trunk->str = "---";
        }
        else if (isLeft)
        {
            trunk->str = ".---";
            prev_str = "   |";
        }
        else {
            trunk->str = "`---";
            prev->str = prev_str;
        }

        showTrunks(trunk);
        std::cout << " " << node->key << std::endl;

        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        print(node->left_node, trunk, false);
    }

    void preOrderTraversal(Node* node) {
        if (node) {
            node->print();
            inOrderTraversal(node->left_node);
            inOrderTraversal(node->right_node);
        }
    }

    void inOrderTraversal(Node* node) {
        if (node) {
            inOrderTraversal(node->left_node);
            node->print();
            inOrderTraversal(node->right_node);
        }
    }

    void postOrderTraversal(Node* node) {
        if (node) {
            inOrderTraversal(node->left_node);
            inOrderTraversal(node->right_node);
            node->print();
        }
    }

public:
    BinTree(std::vector<int> *keys)
    {
        this->root = new Node((*keys)[0]);
        for (int i = 1; i < keys->size(); i++) {
            add(root, (*keys)[i]);
        }
    }

    void add(int key)
    {
        add(root, key);
    }

    void print()
    {
        print(root, nullptr, false);
    }

    void preOrderTraversal() {
        preOrderTraversal(root);
        std::cout << std::endl;
    }

    void inOrderTraversal() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }

    void postOrderTraversal() {
        postOrderTraversal(root);
        std::cout << std::endl;
    }
};


int main()
{

    int N = (std::rand() % (100 - 5 + 1)) + 5;
    std::vector<int> keys(N);
    for (int i = 0; i < N; i++) {
        keys[i] = std::rand() % (255 + 1);
    }

    std::cout << "Keys:" << std::endl;
    for (auto key : keys) {
        std::cout << key << '\t';
    }
    std::cout << std::endl << std::endl;

    std::cout << "Binary tree:" << std::endl;
    BinTree tree(&keys);
    tree.print();
    std::cout << std::endl;

    std::cout << "Pre-order traversal: " << std::endl;  //Прямой обход
    tree.preOrderTraversal();
    std::cout << std::endl;

    std::cout << "In-order traversal: " << std::endl;   // Симметричный обход
    tree.inOrderTraversal();
    std::cout << std::endl;

    std::cout << "Post-order traversal: " << std::endl; // Обратный обход
    tree.postOrderTraversal();
    std::cout << std::endl;
}
