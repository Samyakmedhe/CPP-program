#include <iostream>
using namespace std;

template <class T>
struct node {
    T data;
    struct node<T>* next;
};

template <class T>
class SinglyCircularLL {
private:
    node<T>* first;
    node<T>* last;

public:
    SinglyCircularLL();

    void InsertFirst(T);
    void Reverse();
    void Display();
};

template <class T>
SinglyCircularLL<T>::SinglyCircularLL() {
    first = nullptr;
    last = nullptr;
}

template <class T>
void SinglyCircularLL<T>::InsertFirst(T value) {
    node<T>* newn = new node<T>;
    newn->data = value;

    if (first == nullptr && last == nullptr) {
        first = newn;
        last = newn;
        newn->next = first;  // circular link
    } else {
        newn->next = first;
        first = newn;
        last->next = first;  // maintain circular link
    }
}

template <class T>
void SinglyCircularLL<T>::Reverse() {
    if (first == nullptr || first == last) {
        return;  // empty or single node, no need to reverse
    }

    node<T>* prev = last;
    node<T>* current = first;
    node<T>* next = nullptr;

    do {
        next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    } while (current != first);

    // Swap first and last pointers
    node<T>* temp = first;
    first = last;
    last = temp;
}

template <class T>
void SinglyCircularLL<T>::Display() {
    if (first == nullptr) {
        cout << "List is empty\n";
        return;
    }
    node<T>* temp = first;
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != first);
    cout << "(back to start)\n";
}

int main() {
    SinglyCircularLL<int> list;

    list.InsertFirst(10);
    list.InsertFirst(20);
    list.InsertFirst(30);
    list.InsertFirst(40);

    cout << "Original list:\n";
    list.Display();

    list.Reverse();

    cout << "Reversed list:\n";
    list.Display();

    return 0;
}