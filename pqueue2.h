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
    PriorityQueueEntry<T> **_entrys; // Array aus PriorityQueueEntry<T> Pointern
    bool isFull(void);
    bool isAlmostFull(void);
    void changeArray(int Richtung);
    void privateRemove( int toggle, T value); // Wird von extractMin und remove aufgerufen um sachen zu löschen
public:
    PriorityQueue(int size = 100);
    ~PriorityQueue(void);
    void insert(T value, float priority);
    T extractMin(void);
    void decreaseKey(T value, float priority);
    void remove(T value); // Entscheid nur wo gelöscht werden muss
    bool isEmpty(void);
    void print();
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
        delete _entrys[i]; //Erst die Elemente im Array löschen
    }
    delete[] _entrys; // Array löschen
}


template <typename T>
void PriorityQueue<T>::changeArray(int richtung) { //Prüft und verändert die Größe des Arrays(1 => Vergrößerung, -1 => Verkleinerung)
    if (richtung == 1) {
        if (isAlmostFull()) {
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
        return;
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
    changeArray(1);
    if (_last == -1) { // ARRAY ist leer. Element kann vorne eingefügt werden
        _last += 1;
        _entrys[_last] = new PriorityQueueEntry<T>(priority,value);
    } else {
        int i = 1;
        if (priority < _entrys[0]->priority) {// An Erste Position einfügen. Restliches Array 1 nach hinten schieben
            for (int arraysize = _last; arraysize >= 0; arraysize--) {
                _entrys[arraysize + 1] = _entrys[arraysize];
            }
            _entrys[0] = new PriorityQueueEntry<T>(priority, value);
            _last += 1;
        } else if (priority > _entrys[_last]->priority) { // An letzte Position einfügen.
            _last += 1;
            _entrys[_last] = new PriorityQueueEntry<T>(priority, value);
        } else { // Irgendwo einfügen. Position + restlichen 1 nach hinten schieben.
            while (_entrys[i]->priority < priority) {
                i++;
            }
            if (priority > _entrys[_last]->priority) {
                throw MyException("Element konnte nicht eingefügt werden");
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
    if(_last == -1) { // ARRAY ist lerr
        throw MyException("Bitte erst das Array mit Inhalt befüllen");
    }
    ret = _entrys[0]->value; //Value zwischen speichern
    privateRemove(ERSTESELEMENT, ""); // Remove aufrufen um 1. Element zu löschen.
    return ret;
}
template <typename T>
void PriorityQueue<T>::privateRemove(int toggle, T value) {
    if (_last == -1) {
        throw MyException("Das Array ist leer.");
    }
    int i = 0;

    switch(toggle) { // Aufgabe von remove und extractMin übernehmen
        case ERSTESELEMENT:
            delete _entrys[0]; // Array nach vorne schieben
            for (int arraysize = 0; arraysize < _last; arraysize++ ) {
                _entrys[arraysize] = _entrys[arraysize + 1];
            }
            break;
        case LETZTESELEMENT:
            delete _entrys[_last];
            break;
        case UNBEKANNTESELEMENT: //Element suchen und löschen + Array nach vorne verschieben
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
    changeArray(-1); // Prüfen ob Speicher gespart werden kann
}
template <typename T>
void PriorityQueue<T>::remove(T value) {
    if (_entrys[0]->value == value) {
        privateRemove(ERSTESELEMENT, ""); // Erstes Element löschen lassen
    } else if(_entrys[_last]->value == value) {
        privateRemove(LETZTESELEMENT, ""); // Letztes Element löschen lassen
    } else {
        privateRemove(UNBEKANNTESELEMENT, value); //Unbekanntes Element in privateRemove löschen lassen
    }
}

template <typename T>
void PriorityQueue<T>::decreaseKey(T value, float priority) {
    remove(value); // Altes Element löschen
    insert(value,priority); // Element mit neuer Priorität wieder einfügen
}
template <typename T>
void PriorityQueue<T>::print() { // Array ausgabe.
    for(int i = 0; i < _size;i++) {
        if (i <= _last) {
            cout << _entrys[i]->value << " " << _entrys[i]->priority << " " <<_entrys[i] << endl;
        } else {
            cout << _entrys[i] << endl;
        }
    }

}