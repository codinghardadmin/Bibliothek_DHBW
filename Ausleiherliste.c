#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include "Ausleiherliste.h"

// Erstellt eine AusleiherListe und gibt den Listenkopf zurueck, Speicherbedarf von head und tail wird allokiert
AusleiherElement *createAusleiherList ()
{
    AusleiherElement *head = malloc (sizeof (AusleiherElement));
    AusleiherElement *tail = malloc (sizeof (AusleiherElement));
    head->next = tail->next = tail;
    return head;
}

// Ein neues AusleiherElement wird an der Stelle nach dem Head eingefuegt. Die Funktion erwartet einen Namen. Das AusleiherElement wird allokiert.
void insertAusleiherHead (AusleiherElement *head, char name[])
{
    AusleiherElement *e = malloc (sizeof (AusleiherElement));
    strcpy(e->name, name);
    e->next = head->next;
    head->next = e;
}

// Loescht Das AusleiherElement mit dem uebergebenen String aus der Liste und macht den Speicher frei.
void deleteAusleiherElement (AusleiherElement *head, char name[])
{
    for (AusleiherElement *p = head; p->next != p->next->next; p = p->next)
    {
        if (strcmp(p->next->name, name))
        {
            AusleiherElement *e = p->next;
            p->next = e->next;
            free (e);
        }
    }
}

//Loescht alle AusleiherElemente und macht den Speicher frei
void deleteAllAusleiherElements (AusleiherElement *head)
{
    for (AusleiherElement *p = head; p->next != p->next->next; p = p->next)
    {
        AusleiherElement *e = p->next;
        p->next = e->next;
        free (e);
    }
}

//Gibt die Größe der Liste der AusleiherElemente zurueck.
int getAusleiherSize (AusleiherElement *head)
{
    int size = 0;
    for (AusleiherElement *e = head->next; e != e->next; e = e->next)
        size++;
    return size;
}

// Gibt zurueck, ob der uebergebene Namer in der AusleiherListe vorhanden ist
bool containsAusleiher (AusleiherElement *head, char name[])
{
    for (AusleiherElement *e = head->next; e != e->next; e = e->next)
    {
        if (strcmp(e->name, name) == 0) return true;
    }
    return false;
}

// Wandelt den uebergebenen String (A;B;C) in eine AusleiherListe um und gibt diese zurueck
// Abgetrennt werden die Element im String mit einem Sekmikolon
AusleiherElement *parseToList(char str[])
{
    AusleiherElement *ausleiherhead = createAusleiherList();
    char delimiter[] = ";";
    char *name;
    name = strtok(str, delimiter);                      // Erstes Abtrennen durch das Semikolon
    while(name != NULL)                                 // Solange der Wert != NULL ist, werden weitere Namen der AusleiherListe hinzugefuegt
    {
        insertAusleiherHead(ausleiherhead, name);
        name = strtok(NULL, delimiter);
    }
    return ausleiherhead;
}
