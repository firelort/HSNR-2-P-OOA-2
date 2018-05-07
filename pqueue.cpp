//
// Created by hartings on 04.05.18.
//

#include <string>
#include <iostream>
#include "pqueue.h"

#define ERSTESELEMENT 1
#define LETZTESELEMENT 2
#define UNBEKANNTESELEMENT 3
using namespace std;



MyException::MyException(string error) {
    _error = error;
}
string MyException::msg() {
    return _error;
}

PriorityQueueEntry::PriorityQueueEntry(float getPriority, string getValue) {
    priority = getPriority;
    value = getValue;
}


PriorityQueue::PriorityQueue(int size) {
    _size = size;
    _last = -1;
    _entrys = new PriorityQueueEntry*[size];
}

PriorityQueue::~PriorityQueue() {
    for (int i = 0; i < _last ; i++) {
        delete _entrys[i];
    }
    delete[] _entrys;
}



void PriorityQueue::changeArray(int richtung) {
    if (richtung == 1) {
        if (isFull() || isAlmostFull()) {
            PriorityQueueEntry **newArray = new PriorityQueueEntry*[_size * 2];
            for (int arraysize = 0; arraysize <= _last ; arraysize++) {
                newArray[arraysize] = _entrys[arraysize];
            }
            delete[](_entrys);
            _size *= 2;
            _entrys = newArray;
        }
    } else if (richtung == -1) {
        if ((_last+1) * 4 < _size) {
            PriorityQueueEntry **newArray = new PriorityQueueEntry*[_size / 2];
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

bool PriorityQueue::isFull() {
    return _last == (_size - 1);
}
bool PriorityQueue::isAlmostFull() {
    return _last > (_size - 2);
}
bool PriorityQueue::isEmpty() {
    return _last == -1;
}

void PriorityQueue::insert(string value, float priority) {
    if (_last == -1) { // ARRAY ist leer
        _last += 1;
        _entrys[_last] = new PriorityQueueEntry(priority,value);
    } else {
        int i = 1;
        changeArray(1);
        if (priority < _entrys[0]->priority) {
            for (int arraysize = _last; arraysize >= 0; arraysize--) {
                _entrys[arraysize + 1] = _entrys[arraysize];
            }
            _entrys[0] = new PriorityQueueEntry(priority, value);
            _last += 1;
        } else if (priority > _entrys[_last]->priority) {
            _last += 1;
            _entrys[_last] = new PriorityQueueEntry(priority, value);
        } else {
            while (_entrys[i]->priority < priority) {
                i++;
            }
            if (priority > _entrys[_last]->priority) {
            throw MyException("Fehler");
            }
            for (int arraysize = _last; arraysize >= i; arraysize--) {
                _entrys[arraysize + 1] = _entrys[arraysize];
            }
            _entrys[i] = new PriorityQueueEntry(priority, value);
            _last += 1;
        }
    }
}

string PriorityQueue::extractMin() {
    string ret;
    if(_last == -1) {
        throw MyException("Bitte erst das Array mit Inhalt befüllen");
    }
    ret = _entrys[0]->value;
    privateRemove(ERSTESELEMENT, "");
    return ret;
}

void PriorityQueue::privateRemove(int toggle, string value) {
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

void PriorityQueue::remove(string value) {
    if (_last == -1) {
        throw MyException("Fehler.");
    }
    if (_entrys[0]->value == value) {
        privateRemove(ERSTESELEMENT, "");
    } else if(_entrys[_last]->value == value) {
        privateRemove(LETZTESELEMENT, "");
    } else {
        privateRemove(UNBEKANNTESELEMENT, value);
    }
}

void PriorityQueue::decreaseKey(string value, float priority) {
    remove(value);
    insert(value,priority);
}

void PriorityQueue::gimme() {
    for(int i = 0; i < _size;i++) {
        if (i <= _last) {
            cout << _entrys[i]->value << " " << _entrys[i]->priority << " " <<_entrys[i] << endl;
        } else {
            cout << _entrys[i] << endl;
        }
    }

}
