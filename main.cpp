

//
// Copied from the template and slightly added. Version 1.0
//
#include <iostream>
#include "pqueue2.h"
#include <time.h>

using namespace std;
#define MAX 100000
#define TestC 10

char *randomString(int size) {
    char *str = (char *) malloc((size + 1) * sizeof(char));
    for (int i = 0; i < size; i++) {
        str[i] = (char) ((rand() % 26) + 'A');
    }
    str[size] = '\0';
    return str;
}

void time(void);

int main() { //TESTREIBER
    srand(time(NULL));
    int i, j = 0;
    char *strings[MAX];
    PriorityQueue<string> *pq = new PriorityQueue<string>(2);
    cout << "-------- Testtreiber Start ---------" << endl;
    //Array könnte zu klein sein, da die Größe des Arrays 2 beträgt und wir 6 Elemente einfügen

    try {
        for (int k = 0; k < 6; k++) {
            pq->insert(to_string(k), rand() % 100);
        }

    } catch (MyException e) {
        cout << e.msg() << endl;
    }
    cout << "Es sollte kein Fehler ausgegeben werden. Fall 0 abgeschlossen" << endl << endl;

    //Es werden 7 von 6 Elemente entfernt.
    try {
        for (int l = 0; l < 7; l++) {
            pq->extractMin();
        }
    } catch (MyException e) {
        cout << e.msg() << endl;
    }
    cout << "Es sollte ein Fehler ausgegeben werden. Fall 1 abgeschlosssen" << endl << endl;

    //Einfüngen und löschen von einem Element wird geprüft.
    try {
        pq->insert("Hello World", 20);
        pq->remove("Hello World");

    } catch (MyException e) {
        cout << e.msg() << endl;
    }
    cout << "Es sollte kein Fehler ausgegeben werden. Fall 2 abgeschlossen" << endl << endl;

    //Entfernen eines Elements, welches nicht verfügbar ist.
    try {
        pq->remove("YAHWS");

    } catch (MyException e) {
        cout << e.msg() << endl;
    }
    cout << "Es sollte ein Fehler ausgegeben werden. Fall 3 abgeschlossen" << endl << endl;

    //Testen der Decreasekey funktion
    try {
        pq->insert("Text 1", 10);
        pq->insert("Text 2", 20);
        pq->insert("Text 3", 30);
        pq->decreaseKey("Text 2", 5);
        cout << "Erwartet: Text 2 - Ausgabe:" << pq->extractMin() << endl;
        cout << "Erwartet: Text 1 - Ausgabe:" << pq->extractMin() << endl;
        cout << "Erwartet: Text 3 - Ausgabe:" << pq->extractMin() << endl;

    } catch (MyException e) {
        cout << e.msg() << endl;
    }
    cout << "Es sollte kein Fehler ausgegebn werden. Fall 4 abgeschlossen" << endl << endl;
    try {
        cout << "Erwartet: Das Array ist leer - Ausgabe: "; //Text ist im Buffer
        if (pq->isEmpty())
            cout << "Das Array ist leer" << endl;
        else
            cout << "Das Array ist nicht leer" << endl;

        pq->insert("Hello World", 100);

        cout << "Erwartet: Das Array ist nicht leer - Ausgabe: ";
        if (pq->isEmpty())
            cout << "Das Array ist leer." << endl;
        else
            cout << "Das Array ist nicht leer." << endl;

    } catch (MyException e) {
        cout << e.msg() << endl;
    }
    cout << "Es sollte kein Fehler ausgegeben werden. Fall 5 abgeschlossen" << endl << endl;
    cout << "-------- Testtreiber Ende -------------" << endl << endl;


//time(); // Wenn Zeitmessung benötigt wieder einkommentieren
return 0;
}


void time() {
    try {
        int i;
        char *strings[MAX];
        clock_t tic, toc;

        srand(time(NULL));
        for (i = 0; i < MAX; i++) {
            strings[i] = randomString(8);
        }
        PriorityQueue<string> *pq = new PriorityQueue<string>();
        tic = clock();
        for (i = 0; i < MAX; i++) {
            pq->insert(strings[i], rand() % 100);
        }
        toc = clock();

        printf("Insertion time: %.10f\n", (float) (toc - tic) / CLOCKS_PER_SEC);
        printf("Debugger: Tic: %f - Toc: %f\n", (float) tic / CLOCKS_PER_SEC,
               (float) toc / CLOCKS_PER_SEC); //Added for debugging reasons

        tic = clock();
        for (i = 0; i < MAX; i++) {
            pq->extractMin();
        }
        toc = clock();

        printf("Extract time: %.10f\n", (float) (toc - tic) / CLOCKS_PER_SEC);
        printf("Debugger: Tic: %f - Toc: %f\n", (float) tic / CLOCKS_PER_SEC,
               (float) toc / CLOCKS_PER_SEC); //Added for debugging reasons
        delete pq;
        for (i = 0; i < MAX; i++) {
            free(strings[i]);
        }

    } catch (MyException e) {
        cout << e.msg() << endl;
    }


}