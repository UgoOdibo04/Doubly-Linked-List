#include <iostream>
using namespace std;

template<typename T> 
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next; 
        Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size_;
    
public: 
DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}     //Default Constructor
 ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }   //Decontructor 
  DoublyLinkedList(const DoublyLinkedList& second) : head(nullptr), tail(nullptr), size_(0) {
        Node* current = second.head;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
  }     //Copy Contructor
  DoublyLinkedList& operator=(const DoublyLinkedList& second) {
        if (this != &second) {
            
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
            size_ = 0;

           
            Node* current = second.head;
            while (current != nullptr) {
                push(current->data);
                current = current->next;
            }
        }
        return *this;
    }   //Overide Assigment 
  int size() const {
        return size_;
    }               //Size Function
  T& at(int index) {
        if (index < 0 || index >= size_) {
            throw out_of_range("Out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }               //At Function
  void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }             //Print Function
  void push(const T& newdata) {
        Node* newNode = new Node(newdata);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size_++;
    }    //Push Function
  void pop() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        size_--;
    }                     //Pop Function
  void insert(const T& data, int pos) {
        if (pos < 0 || pos > size_) {
            throw out_of_range("Out of range");
        }
        if (pos == 0) {
            Node* newNode = new Node(data);
            newNode->next = head;
            if (head) {
                head->prev = newNode;
            } else {
                tail = newNode;
            }
            head = newNode;
        } else if (pos == size_) {
            push(data);
        } else {
            Node* current = head;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            Node* newNode = new Node(data);
            newNode->prev = current;
            newNode->next = current->next;
            current->next->prev = newNode;
            current->next = newNode;
        }
        size_++;
    }  //Insert Function
  void remove(int pos) {
        if (pos < 0 || pos >= size_) {
            throw out_of_range("Out of range");
        }
        if (pos == 0) {
            Node* temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
        } else if (pos == size_ - 1) {
            pop();
        } else {
            Node* current = head;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        size_--;
    }              //Remove function
};
void test(){
    DoublyLinkedList<int> dll;
    
    dll.push(1);
    dll.push(2);
    dll.push(3);
    
    DoublyLinkedList<int> dllCopy = dll;
    
    dllCopy.push(4);
    dllCopy.remove(1);
    dllCopy.remove(0);
    dllCopy.insert(5, 1);
    
    dll.print();
    dllCopy.print();
    
    dll = dllCopy;
    dll.print();
}

int main(){
    test();
    
    
    
    
    return 0;
}
