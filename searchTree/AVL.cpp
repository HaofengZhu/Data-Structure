#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

template <typename T>
class AVL
{
private:
    struct Node
    {
        T val;
        Node *left;
        Node *right;
        int height;
        Node(T v) : val(v), left(NULL), right(NULL), height(1) {}
    };

public:
    AVL() : root(NULL) {}
    ~AVL() { clear(); }

    void insert(T val)
    {
        insert(root, val);
    }

    void del(T val)
    {
        del(root, val);
    }
    bool find(T val)
    {
        return false;
    }

    void clear()
    {
        clear(root);
    }

    string PerOrder()
    {
        stringstream ss;
        queue<Node *> q;
        q.push(root);
        Node *tmp;
        ss << "<";
        while (!q.empty())
        {
            tmp = q.front();
            q.pop();
            if (tmp == NULL)
            {
                ss << "NULL";
            }
            else
            {
                ss << tmp->val;
                q.push(tmp->left);
                q.push(tmp->right);
            }
            ss << ",";
        }
        ss << ">";
        return ss.str();
    }

private:
    Node *root;

    void clear(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        else
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    int height(Node *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        int leftHeight = 0, rightHeight = 0;
        if (node->left != NULL)
        {
            leftHeight = node->left->height;
        }
        if (node->right != NULL)
        {
            rightHeight = node->right->height;
        }
        return max(leftHeight, rightHeight) + 1;
    }
    int treeBalanceFator(Node *node)
    {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return leftHeight - rightHeight;
    }

    Node *rightRotation(Node *node1)
    {
        if (node1 == NULL || node1->left == NULL)
        {
            return NULL;
        }

        Node *node2 = node1->left;
        node1->left = node2->right;
        node2->right = node1;

        //???????????????,node2??????node1???height
        node1->height = height(node1);
        node2->height = height(node2);

        return node2;
    }

    Node *leftRotation(Node *node1)
    {
        if (node1 == NULL || node1->right == NULL)
        {
            return NULL;
        }
        Node *node2 = node1->right;
        node1->right = node2->left;
        node2->left = node1;

        //???????????????,node2??????node1???height
        node1->height = height(node1);
        node2->height = height(node2);

        return node2;
    }

    void treeReBalance(Node *&node)
    {
        int fator = treeBalanceFator(node);
        if (fator > 1)
        {
            if (treeBalanceFator(node->left) > 0)
            {
                // LL???
                node = rightRotation(node);
            }
            else
            {
                // LR???
                node->left = leftRotation(node->left);
                node = rightRotation(node);
            }
        }
        else if (fator < -1)
        {
            if (treeBalanceFator(node->left) < 0)
            {
                // RR???
                node = leftRotation(node);
            }
            else
            {
                // RL???
                node->right = rightRotation(node->right);
                node = leftRotation(node);
            }
        }
        else
        {
            //???????????????
            return;
        }
    }

    void del(Node *&node, T val)
    {
        if (node == NULL)
        {
            return;
        }
        if (val < node->val)
        {
            del(node->left, val);
        }
        else if (val > node->val)
        {
            del(node->right, val);
        }
        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                delete node;
                node = NULL;
            }
            else if (node->left == NULL)
            {
                node = node->right;
            }
            else if (node->right == NULL)
            {
                node = node->left;
            }
            else
            {
                Node* tmpParent;
                Node* tmp;
                if (treeBalanceFator(node) > 0)
                {
                    //????????????????????????,????????????????????????????????????node
                    tmpParent = node;
                    tmp = node->left;
                    if (tmp->right == NULL)
                    {
                        //????????????????????????????????????????????????
                        tmp->right = node->right;
                        tmp->height = height(tmp);
                        delete node;
                        node = tmp;
                    }
                    else
                    {
                        while (tmp->right != NULL)
                        {
                            tmpParent = tmp;
                            tmp = tmp->right;
                        }
                        tmpParent->right = tmp->right;
                        tmpParent->height = height(tmpParent);
                        tmp->left = node->left;
                        tmp->right = node->right;
                        delete node;
                        node = tmp;
                        node->height = height(node);
                    }
                }
                else
                {
                    //????????????????????????,????????????????????????????????????node
                    tmpParent = node;
                    tmp = node->right;
                    if (tmp->left == NULL)
                    {
                        //????????????????????????????????????????????????
                        tmp->left = node->left;
                        tmp->height = height(tmp);
                        delete node;
                        node = tmp;
                    }
                    else
                    {
                        while (tmp->left != NULL)
                        {
                            tmpParent = tmp;
                            tmp = tmp->left;
                        }
                        tmpParent->left = tmp->right;
                        tmpParent->height = height(tmpParent);
                        tmp->left = node->left;
                        tmp->right = node->right;
                        delete node;
                        node = tmp;
                        node->height = height(node);
                    }
                }
            }
        }
    }

    void insert(Node *&node, T val)
    {
        if (node == NULL)
        {
            node = new Node(val);
        }
        else if (val < node->val)
        {
            insert(node->left, val);
            node->height = height(node);
        }
        else
        {
            insert(node->right, val);
            node->height = height(node);
        }
        treeReBalance(node);
    }
};

int main()
{
    AVL<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    cout << tree.PerOrder() << endl;
    tree.del(5);
    cout << tree.PerOrder() << endl;
    tree.del(1);
    cout << tree.PerOrder() << endl;
}