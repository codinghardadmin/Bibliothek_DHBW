#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include "Buchliste.h"

// Erstellt eine (Buch)Liste und gibt den Listenkopf zurueck, Speicherbedarf von head und tail wird allokiert
Element *createList ()
{
    Element *head = malloc (sizeof (Element));
    Element *tail = malloc (sizeof (Element));
    head->next = tail->next = tail;
    return head;
}

// Ein neues (Buch)Element wird an der Stelle nach dem Head eingefuegt. Die Funktion erwartet einen Namen, ISBN, Titel, Autor, Anzahl und die Ausleiherliste zu dem Buch. Das (Buch)Element wird allokiert.
void insertHead (Element *head, char isbn[], char titel[], char autor[], int anzahl, AusleiherElement *ausleiherhead)
{
    Element *e = malloc (sizeof (Element));
    strcpy(e->isbn, isbn);
    strcpy(e->titel, titel);
    strcpy(e->autor, autor);
    e->anzahl = anzahl;
    e->ausleiherhead = ausleiherhead;
    e->next = head->next;
    head->next = e;
}

// Gibt Alle (Buch)Elemente mit ihren Eigenschaften aus. Geht die komplette AusleiherListe durch und fuegt zwischen den Namen ein Komma ein
void printList (Element *head)
{
    for (Element *e = head->next; e != e->next; e = e->next)
    {
        AusleiherElement *ausleiherhead = e->ausleiherhead;
        char ausleiherstring[120] = "";
        for (AusleiherElement *ae = ausleiherhead->next; ae != ae->next; ae = ae->next)
        {
            if (ausleiherhead->next != ae) { strcat(ausleiherstring, ","); }
            strcat(ausleiherstring, ae->name);
        }
        printf("ISBN: %s, Titel: %s, Autor: %s, Anzahl: %d, Ausleiher: %s\n", e->isbn, e->titel, e->autor, e->anzahl, ausleiherstring);
    }
    printf("\n");
}

// Gibt Alle (Buch)Elemente mit ihren Eigenschaften aus. Geht die komplette AusleiherListe durch und fuegt zwischen den Namen ein Komma ein
// Hier wird noch das keyword uebergeben, nach dem dann in ISBN, Titel und Autor von jedem Buch gesucht wird
void printSearchResults (Element *head, char keyword[])
{
    int n = 0;
    for (Element *e = head->next; e != e->next; e = e->next)
        if (strstr(e->isbn, keyword) != NULL || strstr(e->titel, keyword) != NULL || strstr(e->autor, keyword) != NULL)
        {
            int verfuegbar = e->anzahl - getAusleiherSize(e->ausleiherhead);
            n = n+1;
            printf("#%d Ergebnis\nISBN: %s\nTitel: %s\nAutor: %s\nAnzahl: %d\nVerfuegbar: %d\n\n", n, e->isbn, e->titel, e->autor, e->anzahl, verfuegbar);
        }
    printf("\nEs wurden %d Eintraege gefunden\n", n);
}

// Gitb das Element zurueck, das genau die ISBN enthaelt, welche uebergeben wurde
Element *getElement(Element *head, char isbn[])
{
    for (Element *e = head->next; e != e->next; e = e->next)
    {
        if (strcmp(e->isbn, isbn) == 0) return e;
    }
    return NULL;
}

// Geht die Liste durch und zaehlt bei jedem gefundenen Element eine Zaehlvariable hoch. Die Anzahl der Elemente wird zurueckgegeben
int getSize (Element *head)
{
    int size = 0;
    for (Element *e = head->next; e != e->next; e = e->next)
        size++;
    return size;
}

//Loescht das Element aus der Liste, welches der Eigenschaft ISBN entspricht, welche uebergeben wurde. Hierfuer wird durch die gesamte Buchliste iteriert und immer der String abgeglichen
void deleteElement (Element *head, char isbn[])
{
    for (Element *p = head; p->next != p->next->next; p = p->next)
    {
        if (strcmp(p->next->isbn, isbn) == 0)
        {
            Element *e = p->next;
            p->next = e->next;

            free (e);
        }
    }
}

// Gibt zurueck, ob ein Element in der Liste enthalten ist. Es wird durch die Liste iteriert und immer uebeprueft, ob die isbn vom Element die gleicht ist wie die uebergebene isbn
bool contains (Element *head, char isbn[])
{
    for (Element *e = head->next; e != e->next; e = e->next)
    {
        if (strcmp(e->isbn, isbn) == 0) return true;
    }
    return false;
}
