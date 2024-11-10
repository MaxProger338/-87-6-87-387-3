#include <iostream>
#include <string>
using namespace std;

template<typename T>
class DoubleLinkedList
{
    private:
        class Node
        {
        public:
            T value;
            Node* next;
            Node* prev;

            Node(T value) : value{ value }, next{ nullptr }, prev{ nullptr } {}
        };

        Node* _first;
        Node* _last;

    public:
        DoubleLinkedList() : _first{ nullptr }, _last{ nullptr } {}

        ~DoubleLinkedList()
        {
            if (!IsEmpty())
            {
                Node* current = _first->next;

                while (current != nullptr)
                {
                    delete current->prev;
                    current = current->next;
                }
                delete _last;

                _first = nullptr;
                _last = nullptr;
            }
        }

        bool IsEmpty() const
        {
            return _first == nullptr;
        }

        DoubleLinkedList& PushBack(T value)
        {
            Node* node = new Node(value);

            if (IsEmpty())
            {
                _first = node;
                _last = node;
                return *this;
            }

            _last->next = node;
            node->prev = _last;
            _last = node;

            return *this;
        }

        DoubleLinkedList& DeleteBack()
        {
            if (IsEmpty())
            {
                return *this;
            }

            Node* current = _last->prev;

            delete _last;
            current->next = nullptr;
            _last = current;

            return *this;
        }
};

template<class K, class V>
class BinaryTree
{
    private:
        class Node
        {
            public:
                K key;
                V value;

                Node* parent;
                Node* left;
                Node* right;

                int count;

                Node(K key, V value) : key{ key }, value{ value }, count{ count },
                                       parent { nullptr }, left{ nullptr }, 
                                       right{ nullptr } {}

                Node& print(short indent, string name)
                {
                    for (int i = 0; i < indent; i++)
                    {
                        if (i == indent - 1)
                            cout << name;

                        cout << '\t';
                    }
                    cout << key << " : " << value << endl;

                    return *this;
                }
        };

        Node* _root;

        BinaryTree& printNode(Node* node, int indent, string name = "") 
        {
            node->print(indent, name);
            if (node->left)
                printNode(node->left, indent + 1, "left");

            if (node->right)
                printNode(node->right, indent + 1, "right");

            return *this;
        }

        BinaryTree& deleteOnCascade(Node* node)
        {
            if (node->left)
                deleteOnCascade(node->left);
            if (node->right)
                deleteOnCascade(node->right);

            delete node;
            return *this;
        }



    public:
        BinaryTree() : _root{ nullptr } {}

        ~BinaryTree()
        {
            deleteOnCascade(_root);
        }

        bool isEmpty() const
       {
           return _root == nullptr;
       }

        int getSize()
        {
            if (isEmpty())
                return 0;

            return getCascadeSize(_root);
        }

        int getCascadeSize(Node* node) const
        {
            return 1 + node->left ? getCascadeSize(node->left) : 0 +
                       node->right ? getCascadeSize(node->right) : 0;
        }

        BinaryTree& clear()
       {
           deleteOnCascade(_root);

           return *this;
       }

        string translate(string word)
        {
            Node* current = _root;

            while (current != nullptr)
            {
                if (word == current->key)
                    return current->value;

                else if (word > current->key)
                    current = current->right;

                else
                    current = current->left;
            }

            return nullptr;
        }
        

        /*BinaryTree& DeleteElement(T element)
        {
            if (isEmpty())
                return *this;

            Node* current = _root;
            while (current != nullptr)
            {
                if (element == current->value)
                    break;

                if (element > current->value)
                    current = current->right;
                else
                    current = current->left;
            }
            if (current == nullptr)
                return *this;

            Node* maxInLeft = current->left;
            while (maxInLeft->right != nullptr)
            {
                maxInLeft = maxInLeft->right;
            }

            current->value = maxInLeft->value;

            maxInLeft->parent->right = maxInLeft->left;
            delete maxInLeft;

            return *this;
        }*/

        BinaryTree& push(K key, V value)
        {
            Node* parent  = nullptr;
            Node* current = _root;
            while (current)
            {
                parent = current;

                if (key == current->key)
                    return *this;

                else if (key > current->key)
                    current = current->right;

                else
                    current = current->left;
            }

            Node* node = new Node(key, value);

            if (isEmpty())
                _root = node;
            
            else if (key > parent->key)
                parent->right = node;

            else
                parent->left = node;

            return *this;
        }

        BinaryTree& print()
        {
            printNode(_root, 0);
            return *this;
        }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    BinaryTree<string, string> tree;

    //tree.push("apple", "яблоко");
    //tree.push("hello", "привет");
    //tree.push("blue", "голубой");
    //tree.push("green", "зелёный");
    //tree.push("red", "красный");
    tree.push("red", "красный");
    tree.push("orange", "оранжевый");
    tree.push("yellow", "жёлтый");
    tree.push("green", "зелёный");
    tree.push("blue", "голубой");
    tree.push("red blue", "синий");
    tree.push("purple", "фиолетовый");
    tree.push("white", "белый");
    tree.push("black", "чёрный");

    tree.print();

    //tree.Push(10);
    //tree.Push(13);
    //tree.Push(5);
    //tree.Push(8);
    //tree.Push(3);
    //tree.Push(4);
    //tree.Push(2);
    //tree.Push(6);
    //tree.Push(9);
    //tree.Push(7);

    //tree.Print();
    //cout << tree << endl;

    //cout << endl;
    //cout << "===========================" << endl;
    //cout << endl;

    //tree.DeleteElement(10);

    //tree.Print();

    return 0;
}
