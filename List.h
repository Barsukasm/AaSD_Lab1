
template <typename T>
class List{
private:
    int size;//размер списка
    Node *head;//указатель на начало списка
public:
    List();//конструктор по умолчанию
    List(List<T> &list);//конструктор копирования
    ~List();//деструктор

    //методы интерфейса
    void AddItem(T t);//добавление нового элемента в начало списка
    bool AddItemByNumber(T t, int pos);//добавление элемента в позицию с номером pos
    void CleanList();//очистка списка
    bool DeleteItem();//удаление из начала списка
    bool DeleteByNumber(int pos);//удалить элемент с номером pos
    bool DeleteByValue(T t);//удаление элемента по значению
    int FindItem(T t);//опрос списка на наличие заданного значения
    T FindItemByNumber(int pos);//чтение элемента с индексом pos
    int GetPos(T t);//получение позиции элемента с заданным значением
    bool isEmpty();//проверка списка на пустоту
    int GetSize();//получить длинну списка
    bool ChangeValue(T t, int pos);//изменить значение с заданным номером в списке

    class Iterator{
        List<T> *list;//текущий список
    public:
        Iterator(List<T> &t);
        Iterator &operator++(int);//переход к следующему элементу
        T& operator*();//перегрузка указателя
        T &begin();//установка на начало списка
        bool inList();//проверка на нахождение внутри списка
    };

    friend class Iterator;

    class Node{
        T Item;
        Node *next;
        Node(T t);//конструктор элемента
        Node();//конструктор по умолчанию
        ~Node();//деструктор
    };

    friend class Node;
};


template <T>
List::List() {
    head=NULL;
    size=0;
}

