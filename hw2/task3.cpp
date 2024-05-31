/*

Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне 0..232 -1

Требования:
B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.

*/
#include <iostream>
#include <vector>
#include <queue>

template <class T>
class BTree {
public:
    BTree( int _t ) : root( nullptr ), t( _t ) {}
    ~BTree() {delete root; }

    void Insert( const T& key );
    void Print(void (*visit)(const std::vector<T>& keys)) const;
private:
    struct Node {
        bool IsLeaf;
        std::vector<T> Keys;
        std::vector<Node*> Children;

        Node( bool isLeaf ) : IsLeaf(isLeaf) {}
        ~Node() { for( Node* child : Children ) { delete child; } }
    };
    Node* root;
    int t;

    bool isNodeFull( Node* node ){ return node->Keys.size() == 2 * t - 1; }
    void splitChild( Node* node, int pos );
    void insertNonFull( Node* node, const T& key );
};

template <class T>
void BTree<T>::Insert(const T &key) {
    if (root == nullptr) {
        root = new Node( true );
    }

    if( isNodeFull( root ) ) {
        Node* newRoot = new Node( false );
        newRoot->Children.push_back( root );
        root = newRoot;
        splitChild( root, 0 );
    }

    insertNonFull( root, key );
}

template<class T>
void BTree<T>::insertNonFull(BTree::Node *node, const T &key) {
    if( node->IsLeaf ) {
        node->Keys.resize( node->Keys.size() + 1 );
        int pos = node->Keys.size() - 2;
        while( pos >= 0 && key < node->Keys[pos] ) {
            node->Keys[pos + 1] = node->Keys[pos];
            --pos;
        }
        node->Keys[pos + 1] = key;
    } else {
        int pos = node->Keys.size() - 1;
        while( pos >= 0 && key < node->Keys[pos] ) {
            --pos;
        }
        if( isNodeFull( node->Children[pos + 1] ) ) {
            splitChild(node, pos + 1);
            if (key > node->Keys[pos + 1]) {
                ++pos;
            }
        }
        insertNonFull(node->Children[pos + 1], key );
    }
}

template<class T>
void BTree<T>::splitChild(BTree::Node* node, int pos) { // pos = 3
    node->Keys.resize(node->Keys.size() + 1);
    node->Children.resize(node->Children.size() + 1);
    Node* oldChild = node->Children[pos];
    Node* newChild = new Node( oldChild->IsLeaf );
    newChild->Keys.resize( t - 1 );
    for (int i = 0; i < t - 1; ++i) {
        newChild->Keys[i] = oldChild->Keys[i + t];
    }
    if(!newChild->IsLeaf) {
        newChild->Children.resize(t);
        for (int i = 0; i < t; ++i) {
            newChild->Children[i] = oldChild->Children[i + t];
        }
        oldChild->Children.resize(t);
    }
    for (int i = node->Children.size() - 2.; i >= pos; --i) {
        node->Children[i + 1] = node->Children[i];
    }
    node->Children[pos + 1] = newChild;
    for (int i = node->Keys.size() - 2; i >= pos; --i) {
        node->Keys[i + 1] = node->Keys[i];
    }
    node->Keys[pos] = oldChild->Keys[t - 1];
    oldChild->Keys.resize(t - 1);
}

template<class T>
void BTree<T>::Print(void (*visit)(const std::vector<T>& keys)) const {
    if (root == nullptr) {
        return;
    }
    std::queue<Node*> queue;
    std::vector<T> layer;
    queue.push(root);
    while(!queue.empty()) {
        queue.push(nullptr);
        while(queue.front() != nullptr) {
            Node* node = queue.front();
            queue.pop();
            for (int i = 0; i < node->Keys.size(); ++i) {
                layer.push_back(node->Keys[i]);
            }
            for (int i = 0; i < node->Children.size(); ++i) {
                queue.push(node->Children[i]);
            }
        }
        queue.pop();
        visit(layer);
        layer.clear();

    }
}

int main() {
    int t;
    std::cin >> t;
    BTree<int> tree(t);
    while(std::cin >> t)
    {
        tree.Insert(t);
    }
    tree.Print([]( const std::vector<int>& keys ) { for( int key : keys ) { std::cout << key << " "; } std::cout << std::endl; } );
    return 0;
}