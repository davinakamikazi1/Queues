
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

vector<bool> destructTracker;

class Int {
public:
    int val{ -1 };
    void operator=(const Int& objToClone) {
        if (this != &objToClone) {
            destructTracker[val] = true;
            this->val = objToClone.val;
        }
    }
    ~Int() {
        destructTracker[val] = true;
    }
private:

};

class DestructorTester {
public:
    DestructorTester() {
        index.val = destructTracker.size();
        destructTracker.push_back(false);
    }
    ~DestructorTester() {
        destructTracker[index.val] = true;
    }
private:
    //int index{ -1 };
    Int index;
};


//This base class helps the assignment compile and run without any changes.
//Dot not modify it.  You will instead override the methods in the derived classes below.
template <typename T>
class BaseQueue {
public:
    BaseQueue() { }
    void push_back(const T& item) { cout << "This push_back() method is filler, override it in the derived class" << endl; }
    void pop_front() { cout << "This pop_front() method is filler, override it in the derived class" << endl; }
    T front() { cout << "This front() method is filler, override it in the derived class" << endl; T temp{}; return temp; }
    T back() { cout << "This back() method is filler, override it in the derived class" << endl; T temp{}; return temp; }
    int size() const { cout << "This size() method is filler, override it in the derived class" << endl; return 0; }

    // This just disables the copy/move constructors/assignments
    BaseQueue(const BaseQueue<T>& objToCopy) { cout << "This copy constructor is filler, override it in the derived class" << endl; }
    const BaseQueue<T>& operator=(const BaseQueue<T>& objToCopy) { cout << "This operator= is filler, override it in the derived class" << endl; return *this; };
    BaseQueue(BaseQueue<T>&& objToCopy) = delete;
    BaseQueue<T>& operator=(BaseQueue<T>&& objToCopy) = delete;
    // Assignment solution key: https://tinyurl.com/4j8mjhcz
private:
};

//**********************************
//Write your code below here
//**********************************
template <typename T>
class QueueForCS2420 : public BaseQueue<T> {
public:

    // TODO: Complete constructor, copy constructor, copy assignment, and destructor, and all other needed methods
    QueueForCS2420(const int capacity): max_size(capacity), current_size(0), front_index(0), back_index(0) {
        elements = new T[max_size];
    }

    ~QueueForCS2420(){
        delete[] elements;
    }
    QueueForCS2420(const QueueForCS2420<T>& objToCopy):max_size(objToCopy.max_size), current_size(objToCopy.current_size), front_index(objToCopy.front_index), back_index(objToCopy.back_index) {
        elements = new T[max_size];
        int j = objToCopy.front_index;
        for (int i = 0; i < current_size; i++) {
            elements[i] = objToCopy.elements[j];
            j = (j + 1) % max_size;
        }
    }
    const QueueForCS2420<T>& operator=(const QueueForCS2420<T>& objToCopy){
        if (this != &objToCopy) {
            if (elements != nullptr) {
                delete[] elements;
            }
            max_size = objToCopy.max_size;
            current_size = objToCopy.current_size;
            front_index = objToCopy.front_index;
            back_index = objToCopy.back_index;

            elements = new T[max_size];

            int j = objToCopy.front_index;
            for (int i = 0; i < current_size; i++) {
                elements[i] = objToCopy.elements[j];
                j = (j + 1) % max_size;
            }
        }
        return *this;
    }

    int size() const {
        return current_size;
    }
    void push_back(const T& item) {
        if (current_size == max_size) {
            //std::cout << "Error: Queue is full" << std::endl;
            return;
        }
        elements[back_index] = item;
        back_index = (back_index + 1) % max_size;
        current_size++;
    }


    // pop_front
    void pop_front() {
        if (current_size == 0) {
            //std::cout << "Error: Queue is empty" << std::endl;
            return;
        }
        front_index = (front_index + 1) % max_size;
        current_size--;
    }

    // front
    T front() {
        if (current_size == 0) {
            //std::cout << "Error: Queue is empty" << std::endl;
            throw std::out_of_range("Queue is empty");
        }
        return elements[front_index];
    }
    // back
    T back() {
        if (current_size == 0) {
            //std::cout << "Error: Queue is empty" << std::endl;
            throw std::out_of_range("Queue is empty");
        }
        int temp_back_index = (back_index == 0) * (max_size - 1) + (back_index - 1) * (back_index != 0);
        return elements[temp_back_index];
    }

private:
    // TODO: Supply the 5 needed data members
    T* elements;
    int max_size;
    int current_size;
    int front_index;
    int back_index;

};


//**********************************
//Write your code above here
//**********************************
