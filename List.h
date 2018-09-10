#include <iostream>

#define INVALID_INDEX 0
#define EMPTY_LIST 1
#define ITERATOR_END 2

template <typename T>
class List{
public:
    List();//конструктор по умолчанию
    List(List<T> &list);//конструктор копирования
    ~List();//деструктор

    //методы интерфейса
    void AddItem(T t);//добавление нового элемента в список
    bool AddItemByNumber(T t, int pos);//добавление элемента в позицию с номером pos
    void CleanList();//очистка списка
    bool DeleteItem();//удаление из начала списка
    bool DeleteByNumber(int pos);//удалить элемент с номером pos
    bool DeleteByValue(T t);//удаление элемента по значению
    bool FindItem(T t);//опрос списка на наличие заданного значения
    T FindItemByNumber(int pos);//чтение элемента с индексом pos
    int GetPos(T t);//получение позиции элемента с заданным значением
    bool isEmpty();//проверка списка на пустоту
    int GetSize();//получить длинну списка
    bool ChangeValue(T t, int pos);//изменить значение с заданным номером в списке



    friend class Iterator;

    class Node{
    public:
        T *item;
        Node *next;
        Node(T t);//конструктор элемента
        Node();//конструктор по умолчанию
        ~Node();//деструктор
    };

    friend class Node;

    class Iterator{
        List<T> *list;//текущий список
        Node *cur;//указатель на текущий элемент
        bool status;//обошел список или нет

    public:
        Iterator(List<T> &t);
        Iterator &operator++(int);//переход к следующему элементу
        T& operator*();//перегрузка указателя
        T &begin();//установка на начало списка
        bool inList();//проверка на нахождение внутри списка
    };

private:
    int size;//размер списка
    Node *head;//указатель на начало списка
    Node *tail;//указатель на последний элемент списка
};

//------------Методы класса List---------------

//Конструктор по умолчанию
template <typename T>
List<T>::List() {
    head=NULL;
    tail=NULL;
    size=0;
}

//Конструктор клонирования
template <typename T>
List<T>::List(List<T> &list) {
    size = list.size;
    if(list.GetSize == 0){
        head->next=NULL;
        tail->next=NULL;
    } else{
        Node *t = list.head;
        for(int i=0;i<list.GetSize();i++){
            AddItem(t->item);
            t = t->next;
        }
    }
}

//Деструктор
template <typename T>
List<T>::~List() {
    CleanList();
}

//включение нового элемента в конец списка
template <typename T>
void List<T>::AddItem(T t) {
    if(size==0){
        head =new Node(t);
        tail=head;
        tail->next=head;
    } else{
        Node *tmp=new Node(t);
        tmp->next=head;
        tail->next=tmp;
        tail=tmp;
    }
    size++;
}

//включение нового значения в позицию с заданным номером
template <typename T>
bool List<T>::AddItemByNumber(T t, int pos) {
    if(pos>=size||pos<0) return false;
    else{
        Node *added = new Node(t);

        Node *tmp=head;
        int i=0;
        while (i!=pos){
            tmp=tmp->next;
            i++;
        }
        added->next=tmp->next;
        tmp->next=added;
        size++;
        if(pos==size-1){
            tail=added;
        }
        return true;
    }
}

template <typename T>
bool List<T>::DeleteItem() {
    bool removed= false;
    if(head==NULL) return removed;
    else{
        if(tail==head){
            delete head;
            head=NULL;
            tail=NULL;
            size--;
            removed=true;
        } else{
            tail->next=head->next;
            delete head;
            head=tail->next;
            size--;
            removed=true;
        }
        return removed;
    }
}

template <typename T>
bool List<T>::DeleteByNumber(int pos) {//переделать
    if(pos>=size||pos<0) return false;

    Node *tmp=head;
    Node *prev=tail;

    for(int i=0;i<size;i++){
        if(i==pos){
            prev->next=tmp->next;
            delete tmp;
            size--;
            if(i==0) head=tail->next;
            if(i==size-1) tail=prev;
            return true;
        }
        tmp=tmp->next;
        prev=prev->next;
    }
    return false;
}

template <typename T>
bool List<T>::DeleteByValue(T t) {
    Node *tmp=head;
    Node *prev=tail;

    for(int i=0;i<size;i++){
        if(*(tmp->item)==t){
            prev->next=tmp->next;
            delete tmp;
            size--;
            if(i==0) head=tail->next;
            if(i==size-1) tail=prev;
            return true;
        }
        tmp=tmp->next;
        prev=prev->next;
    }
    return false;
}

template <typename T>
void List<T>::CleanList() {
    Node* tmp;
    for(int i=0;i<size;i++){
        tmp = head->next;
        head->next=tmp->next;
        delete tmp;
    }
    head=NULL;
    tail=NULL;
    size=0;
}

template <typename T>
bool List<T>::FindItem(T t) {
    Node *tmp=head;
    for(int i=0;i<size;i++){
        if(*(tmp->item)==t) return true;//возвращаем true, если было найдено соответствующее значение
        tmp=tmp->next;
    }
    return false;//возвращает false, если значение не было найдено в списке
}

template <typename T>
T List<T>::FindItemByNumber(int pos) {
    if(pos>=size||pos<0) throw INVALID_INDEX;
    else{
        Node *tmp=head;
        int i=0;
        while (i!=pos){
            tmp=tmp->next;
            i++;
        }
        return *(tmp->item);
    }
}

template <typename T>
int List<T>::GetPos(T t) {
    Node *tmp=head;
    for(int i=0;i<size;i++){
        if(*(tmp->item)==t) return i;//возвращаем позицию, на которой было найдено соответствующее значение
        tmp=tmp->next;
    }
    return -1;//возвращает -1, если значение не было найдено в списке
}

template <typename T>
bool List<T>::isEmpty() {
    return (size>0)? false: true;
}

template <typename T>
int List<T>::GetSize() {
    return (!this->isEmpty())? size: throw EMPTY_LIST;
}

template <typename T>
bool List<T>::ChangeValue(T t, int pos) {
    if(pos>=size||pos<0) return false;
    else{
        Node *tmp=head;
        int i=0;
        while (i!=pos){
            tmp=tmp->next;
            i++;
        }
        *(tmp->item)=t;
        return true;
    }
}

//------------Методы класса Iterator------------
template <typename T>
List<T>::Iterator::Iterator(List<T> &t) {
    list=&t;
    cur=list->head;
    status = false;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++(int) {
    if(list->isEmpty()) throw EMPTY_LIST;
    cur=cur->next;
    status = true;
    //if(!inList()) throw ITERATOR_END;
    return *this;
}

template <typename T>
T& List<T>::Iterator::operator*() {
    if(inList()) return *(cur->item);
    else throw ITERATOR_END;
}

template <typename T>
T& List<T>::Iterator::begin() {
    if(list->isEmpty()) throw EMPTY_LIST;
    cur=list->head;
    status = false;
    return *(cur->item);
}

template <typename T>
bool List<T>::Iterator::inList() {
    return (!(cur==list->head&&status));//если мы уже один раз посещали голову списка и вернулись к ней, то итератор обошел весь список (возвращаем false)
}

//------------Методы класса Node---------------
template <typename T>
List<T>::Node::Node(){}

template <typename T>
List<T>::Node::Node(T t) {
    item=new T(t);
}

template <typename T>
List<T>::Node::~Node() {
    delete item;
}