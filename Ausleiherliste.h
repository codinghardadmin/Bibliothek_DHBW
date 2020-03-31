#ifndef AUSLEIHERLISTE_H
#define AUSLEIHERLISTE_H

#define STRINGSIZE 128

struct _AusleiherElement
{
    char name[STRINGSIZE];
    struct _AusleiherElement *next;
};
typedef struct _AusleiherElement AusleiherElement;

AusleiherElement *createAusleiherList ();

void insertAusleiherHead (AusleiherElement *head, char name[]);

void deleteAusleiherElement (AusleiherElement *head, char name[]);

void deleteAllAusleiherElements (AusleiherElement *head);

int getAusleiherSize (AusleiherElement *head);

bool containsAusleiher (AusleiherElement *head, char name[]);

AusleiherElement *parseToList(char str[]);

#endif


