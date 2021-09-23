#ifndef Lista_n_hpp
#define Lista_n_hpp

#include <iostream>
#include <cstring>

using namespace std;

template<typename T> 
class List
{
    private:
    class Node
    {
        public:
        T value;
        Node* next;

        ~Node();
        Node();
        Node(T val);
        Node(Node &&) = default;
        Node(const Node &) = default;
        Node &operator=(Node &&) = default;
        Node &operator=(const Node &) = default;
    };
    Node *head = NULL;
    int size;

    public:
    ~List();
    List();
    bool empty();
    void push_back(T val);
    void pop_back();
    void print();
    void remove(T val);
    int length();
    List(List<T> && lista);
    List(const List<T> & lista);
    List(initializer_list<T> lista);
    void swap(int i, int j);
    void swap_value(T val, int i);
    T get_value(int n);

    protected:
    Node* search(T val)
    {
        if(!empty)
        {
            Node *terazniejszy = head;
            while(terazniejszy != 0)
            {
                if(terazniejszy->value == val)
                {
                    return terazniejszy;
                }
                terazniejszy = terazniejszy->next;
            }
        }
        return head;
    };

};

template<typename T>
class Compare1
{
    public:
    static bool comp (T a, T b)
    {
        return a <= b;
    }
};


template<typename T>
class Compare2
{
    public:
    static bool comp (T a, T b)
    {
        return a >= b;
    }
};


template<typename T>
class Compare1<T*>
{
    public:
    static bool comp (T a, T b)
    {
        return *a <= *b;
    }
};


template<typename T>
class Compare2<T*>
{
    public:
    static bool comp (T a, T b)
    {
        return *a >= *b;
    }
};


template<>
class Compare1 <const char*>
{
    public:
    static bool comp (const char* a, const char* b)
    {
        return strcmp(a,b) <= 0;
    }
};


template<>
class Compare2 <const char*>
{
    public:
    static bool comp (const char* a, const char* b)
    {
        return strcmp(a,b) >= 0;
    }
};

template<typename T, typename C = Compare1<T>>
bool check(List<T> &lista);

template<typename T, typename C = Compare1<T>>
List<T> sort(List<T> &lista);
//---------------------------------------------------------------------------------
template <typename T>
List<T>::Node::Node()
{
	value = 0;
	next = 0;
}
template <typename T>
List<T>::Node::Node(T val)
{
	value = val;
	next = 0;
}
template <typename T>
List<T>::Node::~Node()
{
}
//---------------------------------------------------------------------------------

template <typename T>
List<T>::List()
{
	head = NULL;
    size = 0;
}
template <typename T>
List<T>::~List()
{   
    if(!empty())
    {
        Node *terazniejszy = head;
        Node *pom;
        while (terazniejszy != 0)
        {
            pom = terazniejszy;
            terazniejszy = terazniejszy->next;
            delete pom;
        }
        
    }
}
template <typename T>
bool List<T>::empty()
{
	return head == NULL;
}

template <typename T>
void List<T>::push_back(T val)
{
    Node *nowy = new Node(val);
    if(empty())
    {
        head = nowy;
    }
    else
    {
        Node *terazniejszy = head;
        while(terazniejszy->next != 0)
        {
            terazniejszy = terazniejszy->next;
        }
        terazniejszy->next = nowy;
    }
    size += 1;
}

template <typename T>
void List<T>::pop_back()
{
    if(!empty())
    {
        Node *terazniejszy = head;
        if(terazniejszy->next == 0)
        {
            delete terazniejszy;
            head->next = 0;
        }
        else
        {
            while(terazniejszy->next->next != 0)
            {
                terazniejszy = terazniejszy->next;
            }
            delete terazniejszy->next;
            terazniejszy->next = 0;
        }
        
        size -=1;
    }
}

template <typename T>
void List<T>::print()
{
    if(!empty())
    {
        Node *terazniejszy = head;
        while(terazniejszy != 0)
        {
            cout << terazniejszy->value << endl;
            terazniejszy = terazniejszy->next;
        }
    }
}

template <typename T>
void List<T>::remove(T val)
{
    if(!empty())
    {
        if(head->value == val)
        {
            if(head->next != 0)
            {
                Node *pom = head;
                head = head->next;
                delete pom;
            }
            else
            {
                head = NULL;
            }
            size -=1;
        }
        else
        {
            Node *terazniejszy = head;
            while(terazniejszy->next != 0)
            {
                if(terazniejszy->next->value == val)
                {
                    Node *pom = terazniejszy->next;
                    if(terazniejszy->next->next == 0)
                    {
                        terazniejszy->next = 0;
                    }
                    else
                    {                    
                        terazniejszy->next = terazniejszy->next->next;
                    }
                    size -= 1;
                    delete pom;
                }
                terazniejszy = terazniejszy->next;
            }
        }
        

    }
}

template <typename T>
int List<T>::length()
{
    return size;
}
template<typename T>
List<T>::List(List<T> &&lista)
{
    if (lista.size == 0)
        head = NULL;
    else
    {
        head = new Node();
        Node *terazniejszy = head;
        Node *pom = lista.head;
        for (int i = 0; i < lista.size; i++)
        {
            terazniejszy->value = pom->value;
            terazniejszy->next = new Node();
            terazniejszy = terazniejszy->next;
        }
    }
    size = lista.size;
}


template<typename T>
List<T>::List(const List<T> & lista)
{
    if (lista.size == 0)
        head = NULL;
    else
    {
        head = new Node();
        Node *terazniejszy = head;
        Node *pom = lista.head;
        for (int i = 0; i < lista.size; i++)
        {
            terazniejszy->value = pom->value;
            terazniejszy->next = new Node();
            terazniejszy = terazniejszy->next;
        }
    }
    size = lista.size;
}


template<typename T>
List<T>::List(initializer_list<T> list)
{
    head = NULL;
    int dl = list.size();
    for (int i = 0; i < dl; i++)
    {
        push_back(*(list.begin() + i));
    }
}

template<typename T>
T List<T>::get_value(int i)
{
    if(!empty() && i < size)
    {
        Node *terazniejszy = head;
        while(i > 0)
        {
            terazniejszy = terazniejszy->next;
            i--;
        }
        return terazniejszy->value;

    }
    else
    {
        throw std::invalid_argument("Argument out of range.");
    }
    
}

template <typename T>
void List<T>::swap(int i, int j)
{
    T pom = get_value(i);
    T pom2 = get_value(j);
    swap_value(pom, j);
    swap_value(pom2, i);
}

template <typename T>
void List<T>::swap_value(T val, int i)
{
    if(!empty())
    {
        Node *terazniejszy = head;
        while(i > 0)
        {
            terazniejszy = terazniejszy->next;
            i--;
        }
        terazniejszy->value = val;
    }
    
}

//---------------------------------------------------------------------------------
template<class T, class C = Compare1<T>>
bool check(List<T> &lista)
{
    for (int i = 0; i < lista.length() - 1; i++)
    {
        T a = lista.get_value(i);
        T b = lista.get_value(i+1);

        if (!(C::comp(a,b)))
        {
            return false;
        }
    }
    return true;
}

template<typename T, typename C = Compare1<T>>
List<T> sort(List<T> &lista)
{
    int dl = lista.length();
    for(int i=0; i < dl; i++)
    {
        for(int j=0; j < dl - 1; j++)
        {
            T a = lista.get_value(j);
            T b = lista.get_value(j+1);
            if (!(C::comp(a,b)))
            {
                lista.swap(j, j+1);
            }
        }
    }
    return lista;
}
#endif