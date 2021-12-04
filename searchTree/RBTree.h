#ifndef RBTREE
#define RETREE

enum RBTColor{RED,BLACK};
enum childDirection{LEFT,RIGHT};
template<typename T>
struct RBTNode
{
    T key;
    RBTColor color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;

    RBTNode(T value, RBTColor c, RBTNode<T> *p, RBTNode<T> *l, RBTNode<T> *r):
        key(value),color(c),parent(),left(l),right(r) {}
};

template<typename T>
class RBTree{
public:
    RBTree();
    ~RBTree();

    RBTNode<T>* search(T key);
    
    T minimun();
    T maximun();

    //找后继节点
    RBTNode<T>* successor(RBTNode<T>* x);

    //找前驱节点
    RBTNode<T>* predecessor(RBTNode<T>* x);

    void insert(T key);
    void remove(T key);
    void destroy();
    void print();

    private:
    RBTNode<T> *mRoot;

    
     // (递归实现)查找"红黑树x"中键值为key的节点
    RBTNode<T>* search(RBTNode<T>* x, T key) const;
    // 查找最小结点：返回tree为根结点的红黑树的最小结点。
    RBTNode<T>* minimum(RBTNode<T>* tree);
    // 查找最大结点：返回tree为根结点的红黑树的最大结点。
    RBTNode<T>* maximum(RBTNode<T>* tree);

    // 左旋
    void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
    // 右旋
    void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
    // 插入函数
    void insert(RBTNode<T>* &root, RBTNode<T>* node);
    // 插入修正函数
    void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
    // 删除函数
    void remove(RBTNode<T>* &root, RBTNode<T> *node);
    // 删除修正函数
    void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

    // 销毁红黑树
    void destroy(RBTNode<T>* &tree);

    // 打印红黑树
    void print(RBTNode<T>* tree, T key, int direction);

    //设置新的子节点
    void setChild(RBTNode<T>* parent,childDirection direction,RBTNode<T>* child);
    
};

#endif