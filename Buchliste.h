#ifndef BUCHLISTE_H
#define BUCHLISTE_H

#include "Ausleiherliste.h"

#define STRINGSIZE 128

struct _Element
{
    char isbn[STRINGSIZE];
    char titel[STRINGSIZE];
    char autor[STRINGSIZE];
    int anzahl;
    AusleiherElement *ausleiherhead;
    struct _Element *next;
};
typedef struct _Element Element;

Element *createList ();

void insertHead (Element *head, char isbn[], char titel[], char autor[], int anzahl, AusleiherElement *ausleiherhead);

void printList (Element *head);

void printSearchResults (Element *head, char keyword[]);

Element *getElement(Element *head, char isbn[]);

int getSize (Element *head);

void deleteElement (Element *head, char isbn[]);

bool contains (Element *head, char isbn[]);

#endif
