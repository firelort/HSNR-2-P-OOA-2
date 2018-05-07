#include <string>
#include <iostream>


#define ERSTESELEMENT 1
#define LETZTESELEMENT 2
#define UNBEKANNTESELEMENT 3
using namespace std;


class MyException {
private:
    string _error;

public:
    MyException(string error);
    string msg();
};

template <typename T>
struct PriorityQueueEntry{
    float priority;
    T value;
    PriorityQueueEntry(float getPriority, T getValue);
};
template <typename T>
class PriorityQueue {
private:
    int _size;
    int _last;
    PriorityQueueEntry<T> **_entrys;
    bool isFull(void);
    bool isAlmostFull(void);
    void changeArray(int Richtung);
    void privateRemove( int toggle, T value);
public:
    PriorityQueue(int size = 100);
    ~PriorityQueue(void);
    void insert(T value, float priority);
    T extractMin(void);
    void decreaseKey(T value, float priority);
    void remove(T value);
    bool isEmpty(void);
    void gimme();
};


MyException::MyException(string error) {
    _error = error;
}
string MyException::msg() {
    return _error;
}

template <typename T>
PriorityQueueEntry<T>::PriorityQueueEntry(float getPriority, T getValue) {
    priority = getPriority;
    value = getValue;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(int size) {
    _size = size;
    _last = -1;
    _entrys = new PriorityQueueEntry<T>*[size];
}
template <typename T>
PriorityQueue<T>::~PriorityQueue() {
    for (int i = 0; i < _last ; i++) {
        delete _entrys[i];
    }
    delete[] _entrys;
}


template <typename T>
void PriorityQueue<T>::changeArray(int richtung) {
    if (richtung == 1) {
        if (isFull() || isAlmostFull()) {
            PriorityQueueEntry<T> **newArray = new PriorityQueueEntry<T>*[_size * 2];
            for (int arraysize = 0; arraysize <= _last ; arraysize++) {
                newArray[arraysize] = _entrys[arraysize];
            }
            delete[](_entrys);
            _size *= 2;
            _entrys = newArray;
        }
    } else if (richtung == -1) {
        if ((_last+1) * 4 < _size) {
            PriorityQueueEntry<T> **newArray = new PriorityQueueEntry<T>*[_size / 2];
            for (int arraysize = 0; arraysize <= _last ; arraysize++) {
                newArray[arraysize] = _entrys[arraysize];
            }
            delete[](_entrys);
            _size /= 2;
            _entrys = newArray;
        }
    } else {
        throw MyException("Fehler 123");
    }
}
template <typename T>
bool PriorityQueue<T>::isFull() {
    return _last == (_size - 1);
}
template <typename T>
bool PriorityQueue<T>::isAlmostFull() {
    return _last > (_size - 2);
}
template <typename T>
bool PriorityQueue<T>::isEmpty() {
    return _last == -1;
}

template <typename T>
void PriorityQueue<T>::insert(T value, float priority) {
    if (_last == -1) { // ARRAY ist leer
        _last += 1;
        _entrys[_last] = new PriorityQueueEntry<T>(priority,value);
    } else {
        int i = 1;
        changeArray(1);
        if (priority < _entrys[0]->priority) {
            for (int arraysize = _last; arraysize >= 0; arraysize--) {
                _entrys[arraysize + 1] = _entrys[arraysize];
            }
            _entrys[0] = new PriorityQueueEntry<T>(priority, value);
            _last += 1;
        } else if (priority > _entrys[_last]->priority) {
            _last += 1;
            _entrys[_last] = new PriorityQueueEntry<T>(priority, value);
        } else {
            while (_entrys[i]->priority < priority) {
                i++;
            }
            if (priority > _entrys[_last]->priority) {
                throw MyException("Fehler A");
            }
            for (int arraysize = _last; arraysize >= i; arraysize--) {
                _entrys[arraysize + 1] = _entrys[arraysize];
            }
            _entrys[i] = new PriorityQueueEntry<T>(priority, value);
            _last += 1;
        }
    }
}
template <typename T>
T PriorityQueue<T>::extractMin() {
    T ret;
    if(_last == -1) {
        throw MyException("Bitte erst das Array mit Inhalt befüllen");
    }
    ret = _entrys[0]->value;
    privateRemove(ERSTESELEMENT, "");
    return ret;
}
template <typename T>
void PriorityQueue<T>::privateRemove(int toggle, T value) {
    if (_last == -1) {
        throw MyException("Das Element wurde nicht gefunden.");
    }
    int i = 0;

    switch(toggle) {
        case ERSTESELEMENT:
            delete _entrys[0];
            for (int arraysize = 0; arraysize < _last; arraysize++ ) {
                _entrys[arraysize] = _entrys[arraysize + 1];
            }
            break;
        case LETZTESELEMENT:
            delete _entrys[_last];
            break;
        case UNBEKANNTESELEMENT:
            i = 0;
            while(_entrys[i]->value != value && i < _last) {
                i++;
            }
            if (_entrys[i]->value != value) {
                throw MyException("Das Element wurde nicht gefunden.");
            }
            delete _entrys[i];
            for (int arraysize = i; arraysize < _last; arraysize++) {
                _entrys[arraysize] = _entrys[arraysize+1];
            }
            break;
        default:
            break;
    }
    _last -= 1;
    changeArray(-1);
}
template <typename T>
void PriorityQueue<T>::remove(T value) {
    if (_last == -1) {
        throw MyException("Fehler B");
    }
    if (_entrys[0]->value == value) {
        privateRemove(ERSTESELEMENT, "");
    } else if(_entrys[_last]->value == value) {
        privateRemove(LETZTESELEMENT, "");
    } else {
        privateRemove(UNBEKANNTESELEMENT, value);
    }
}

template <typename T>
void PriorityQueue<T>::decreaseKey(T value, float priority) {
    remove(value);
    insert(value,priority);
}
template <typename T>
void PriorityQueue<T>::gimme() {
    for(int i = 0; i < _size;i++) {
        if (i <= _last) {
            cout << _entrys[i]->value << " " << _entrys[i]->priority << " " <<_entrys[i] << endl;
        } else {
            cout << _entrys[i] << endl;
        }
    }

}
