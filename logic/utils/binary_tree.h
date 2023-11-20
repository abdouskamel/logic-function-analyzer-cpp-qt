#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <typename T>
class BinaryTree
{
    public:
        BinaryTree(T const& value);
        // Copy constructor
        BinaryTree(BinaryTree<T> const& obj);
        ~BinaryTree();

        void setLeft(T const& value);
        void setRight(T const& value);

        BinaryTree<T>* getLeft(void);
        BinaryTree<T>* getRight(void);

        T getValue(void) const { return m_value; }
        void setValue(T const& value) { m_value = value; }

    protected:
        T m_value;
        BinaryTree<T> *m_left = nullptr,
                      *m_right = nullptr;

};

template <typename T>
BinaryTree<T>::BinaryTree(T const& value)
    : m_value(value)
{

}

// Copy constructor
template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T> const& obj)
    : m_value(obj.m_value)
{
    if(obj.m_left != nullptr)
    {
        if(m_left != nullptr)
        {
            delete m_left;
        }

        m_left = new BinaryTree<T>(*obj.m_left);
    }

    if(obj.m_right != nullptr)
    {
        if(m_right != nullptr)
        {
            delete m_right;
        }

        m_right = new BinaryTree<T>(*obj.m_right);
    }
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    if(m_left != nullptr)
    {
        delete m_left;
        m_left = nullptr;
    }

    if(m_right != nullptr)
    {
        delete m_right;
        m_right = nullptr;
    }
}

template <typename T>
void
BinaryTree<T>::setLeft(T const& value)
{
    if(m_left != nullptr)
    {
        delete m_left;
    }

    m_left = new BinaryTree<T>(value);
}

template <typename T>
void
BinaryTree<T>::setRight(T const& value)
{
    if(m_right != nullptr)
    {
        delete m_right;
    }

    m_right = new BinaryTree<T>(value);
}

template <typename T>
BinaryTree<T>*
BinaryTree<T>::getLeft(void)
{
    return m_left;
}

template <typename T>
BinaryTree<T>*
BinaryTree<T>::getRight(void)
{
    return m_right;
}

#endif // BINARY_TREE_H

