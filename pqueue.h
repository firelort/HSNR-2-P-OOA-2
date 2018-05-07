//
// Created by hartings on 04.05.18.
//

#ifndef OOA2_PQUEUE_H
#define OOA2_PQUEUE_H

using namespace std;

class MyException {
        private:
        string _error;

        public:
        MyException(string error);
        string msg();
};

struct PriorityQueueEntry{
    float priority;
    string value;
    PriorityQueueEntry(float getPriority, string getValue);
};

class PriorityQueue {
private:
    int _size;
    int _last;
    PriorityQueueEntry **_entrys;
    bool isFull(void);
    bool isAlmostFull(void);
    void changeArray(int Richtung);
    void privateRemove( int toggle, string value);
public:
    PriorityQueue(int size = 100);
    ~PriorityQueue(void);
    void insert(string value, float priority);
    string extractMin(void);
    void decreaseKey(string value, float priority);
    void remove(string value);
    bool isEmpty(void);
    void gimme();
};

#endif //OOA2_PQUEUE_H
