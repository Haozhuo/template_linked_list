#include <iostream>
#include <string>
#include <cassert>
using namespace std;

template<typename T>
class linkedList
{
public:
    linkedList();
    linkedList(const linkedList& other);
    ~linkedList();
    linkedList& operator=(const linkedList& rhs);
    void addToFront(const T& value);
    void addToRear(const T& value);
    bool insertAfterValue(const T& targetValue, const T& value);
    bool insertAtIndex(int index, const T& value);
    bool deleteOneValue(const T& value);
    bool deleteIndex(int index);
    void deleteAllValue(const T& value);
    int size() const;
    void print() const;
private:
    struct Node
    {
        T m_value;
        Node* m_next;
    };
    
    Node* m_head;
    int m_size;
};

template<typename T>
linkedList<T>::linkedList():m_head(nullptr), m_size(0)
{}

template<typename T>
linkedList<T>::linkedList(const linkedList<T>& other)
{
    m_size = other.m_size;
    Node* pThis;
    Node* pOther = other.m_head;
    
    
    while(pOther != nullptr)
    {
        if(m_head == nullptr)
        {
            m_head = new Node;
            m_head->m_value = pOther->m_value;
            m_head->m_next = nullptr;
            pThis = m_head;
        }
        
        else
        {
            pThis->m_next = new Node;
            pThis->m_next->m_value = pOther->m_value;
            pThis->m_next->m_next = nullptr;
            pThis = pThis->m_next;
        }
        
        pOther = pOther->m_next;
    }
}

template<typename T>
linkedList<T>::~linkedList()
{
    Node* curr;
    while(m_head != nullptr)
    {
        curr = m_head->m_next;
        delete m_head;
        m_head = curr;
    }
}

template<typename T>
linkedList<T>& linkedList<T>::operator=(const linkedList<T>& rhs)
{
    if(this != &rhs)
    {
        Node* curr;
        while(m_head != nullptr)
        {
            curr = m_head->m_next;
            delete m_head;
            m_head = curr;
        }
        
        m_size = rhs.m_size;
        Node* pThis;
        Node* pOther = rhs.m_head;
        
        if(rhs.m_head != nullptr)
        {
            m_head = new Node;
            m_head->m_value = rhs.m_head->m_value;
            m_head->m_next = nullptr;
            pOther = pOther->m_next;
        }
        
        pThis = m_head;
        
        while(pOther != nullptr)
        {
            Node* temp = new Node;
            temp->m_value = pOther->m_value;
            temp->m_next = nullptr;
            pThis->m_next = temp;
            pThis = pThis->m_next;
            pOther = pOther->m_next;
        }
    }
    return *this;
}



template<typename T>
void linkedList<T>::addToFront(const T& value)
{
    Node* newNode = new Node;
    newNode->m_value = value;
    newNode->m_next = m_head;
    m_head = newNode;
    m_size++;
}

template<typename T>
void linkedList<T>::addToRear(const T& value)
{
    Node* newNode = new Node;
    newNode->m_value = value;
    newNode->m_next = nullptr;
    
    if(m_head == nullptr)
    {
        m_head = newNode;
        m_size++;
        return;
    }
    
    Node* p = m_head;
    for(; p->m_next != nullptr; p = p->m_next)
        ;
    
    p->m_next = newNode;
    m_size++;
    return;
}

template<typename T>
bool linkedList<T>::insertAfterValue(const T& targetValue, const T& value)
{
    Node* p;
    for(p = m_head; p != nullptr && p->m_value != targetValue; p = p->m_next)
        ;
    
    if(p != nullptr)
    {
        Node* newNode = new Node;
        newNode->m_value = value;
        newNode->m_next = p->m_next;
        p->m_next = newNode;
        m_size++;
        return true;
    }
    
    return false;
}

template<typename T>
bool linkedList<T>::insertAtIndex(int index, const T& value)
{
    if(index >= m_size)
        return false;
    
    Node* newNode = new Node;
    newNode->m_value = value;
    
    if(index == 0)
    {
        newNode->m_next = m_head;
        m_head = newNode;
    }
    
    else
    {
        Node* p = m_head;
        for(int i = 0; i < index - 1; i++)
            p = p->m_next;
        
        newNode->m_next = p->m_next;
        p->m_next = newNode;
    }
    
    m_size++;
    return true;
}

template<typename T>
bool linkedList<T>::deleteOneValue(const T& value)
{
    if(m_head == nullptr)
        return false;
    
    Node* p;
    Node* curr;
    for(curr = m_head; curr != nullptr && curr->m_value != value; p = curr,curr = curr->m_next)
        ;
    
    if(curr != nullptr)
    {
        if(curr == m_head)
            m_head = curr->m_next;
        else
            p->m_next = curr->m_next;
        delete curr;
        m_size--;
        return true;
    }
    
    return false;
}

template<typename T>
bool linkedList<T>::deleteIndex(int index)
{
    if(index >= m_size)
        return false;
    
    Node* p;
    Node* curr = m_head;
    for(int i = 0; i < index; i++)
    {
        p = curr;
        curr = curr->m_next;
    }
    
    if(curr == m_head)
        m_head = curr->m_next;
    
    else
        p->m_next = curr->m_next;
    
    delete curr;
    m_size--;
    return true;
}

template<typename T>
void linkedList<T>::deleteAllValue(const T& value)
{
    Node* p;
    Node* curr = m_head;
    
    while(curr != nullptr)
    {
        if(curr->m_value == value)
        {
            if(curr == m_head)
            {
                m_head = curr->m_next;
                delete curr;
                m_size--;
                curr = m_head;
            }
            
            else
            {
                p->m_next = curr->m_next;
                delete curr;
                m_size--;
                curr = p->m_next;
            }
        }
        
        else
        {
            p = curr;
            curr = curr->m_next;
        }
    }
}

template<typename T>
int linkedList<T>::size() const
{
    return m_size;
}

template<typename T>
void linkedList<T>::print() const
{
    Node* p = m_head;
    for(; p != nullptr; p = p->m_next)
        cout << p->m_value << " ";
}












