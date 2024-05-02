/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

 */
#include<iostream>
#include <vector>
#include<stack>

template<class T, class Compare>
class BinaryTree {
public:
    BinaryTree(const Compare& _cmp) : root(nullptr), cmp(_cmp) {}
    ~BinaryTree();

    void Add(const T& key);
    bool Has(const T& key) const;

    void Dfs(void (*visit)(const T& key)) const;
private:
    struct Node {
        T Key;
        Node* Left;
        Node* Right;
        Node(const T& key) : Key(key), Left(nullptr), Right(nullptr) {}
    };
    Node* root;
    Compare cmp;
};

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree() {
    Node* node = root;
    std::stack<Node*> stack;
    do {
        while (node != nullptr) {
            if (node->Right != nullptr) {
                stack.push(node->Right);
            }
            stack.push(node);
            node = node->Left;
        }
        if (!stack.empty()) {
            node = stack.top();
            if (node->Right == stack.top()) {
                stack.pop();
                stack.push(node);
                node = node->Right;
            } else {
                delete node;
                node = nullptr;
            }
            stack.pop();
        }
    } while (!stack.empty());
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T &key) {
    if (root == nullptr) {
        root = new Node(key);
        return;
    }
    Node* node = root;
    Node* pre = nullptr;
    while (node != nullptr) {
        pre = node;
        if (cmp(key, node->Key)) {
            if (node->Left == nullptr) {
                node->Left = new Node(key);
                return;
            }
            node = node->Left;
        } else {
            if (node->Right == nullptr) {
                node->Right = new Node(key);
                return;
            }
            node = node->Right;
        }
    }
}

template<class T, class Compare>
bool BinaryTree<T, Compare>::Has(const T &key) const {
    Node* node = root;
    while (node != nullptr && node->Key != key) {
        if (cmp(key, node->Key)) {
            node = node->Left;
        } else {
            node = node->Right;
        }
    }

    if (node == nullptr) {
        return false;
    }
    return true;
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Dfs(void (*visit)(const T&)) const {
    Node* node = root;
    std::stack<Node*> stack;
    while( node != nullptr || !stack.empty()) {
        while (node != nullptr) {
            stack.push(node);
            node = node->Left;
        }
        Node* temp = stack.top();
        visit(stack.top()->Key);
        node = stack.top()->Right;
        stack.pop();
    }
};

struct IntCmp {
    bool operator()( int l, int r ) { return l < r; }
};

int main() {
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree( cmp );
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        tree.Add(val);
    }
    tree.Dfs([]( const int& key ) { std::cout << key << " "; } );
    return 0;
}
