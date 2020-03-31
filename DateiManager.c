#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include "DateiManager.h"
#include "Ausleiherliste.h"
#include "Buchliste.h"

// Laenge des Strings für den Integer
#define INTSTRINGSIZE 8
// Laenge des Strings fuer die Attribute
#define STRINGSIZE 128
// Laenge des Strings für den Gesamtstring des Ausleiherliste
#define LISTSTRINGSIZE 1024
// Laenge fuer Liste fuer ein Entry, also ein Bucheintrag
#define ENTRYSTRING 2048

// Leadt die Datei buecher.txt und wandelt diese in einer Buecherliste mit Ausleiherliste um und gibt dann dann Kopf der Liste zurueck
Element *loadBookFile()
{
    // Neue Liste erstellen, FILE erstellen und lesen
    Element *head = createList();
    FILE *fp;
    char str[STRINGSIZE];
    fp = fopen("buecher.txt" , "r");
    if(fp != NULL) {
            // Definieren der Variablen
           int counter = 0;
           char isbn[STRINGSIZE];
           char titel[STRINGSIZE];
           char autor[STRINGSIZE];
           char stranzahl[STRINGSIZE];
           char strausleiher[STRINGSIZE];
           int anzahl;
           AusleiherElement *ausleiherhead;
           // Zeilenweise die Datei lesen und den counter hochzaehlen, um zu sehen, welches Attribut jetzt gelesen wird.
           while(fgets(str, sizeof str, fp))
           {
               int len = strlen(str);
               if(str[len-1] == '\n')
               {
                   str[len-1] = 0;
               }
               switch(counter)
               {
                case 0:
                    strcpy(isbn, str);
                    break;
                case 1:
                    strcpy(titel, str);
                    break;
                case 2:
                    strcpy(autor, str);
                    break;
                case 3:
                    strcpy(stranzahl, str);
                    sscanf(stranzahl, "%d", &anzahl);
                    break;
                case 4:
                    // Hier wird die Ausleiherliste zum String konvertiert und das Buchelement hinzugefuegt
                    strcpy(strausleiher, str);
                    ausleiherhead = parseToList(strausleiher);
                    insertHead(head, isbn, titel, autor, anzahl, ausleiherhead);
                    break;
                default:
                    puts("Fehler beim Laden der Datei");
               }
               // counter immer um 1 erhoeht und nach der 5. Zeile wieder auf 1 gesetzt (Neues Buch beginnt, welches wieder in 5 Zeilen gespeichert wurde)
               counter++;
               if (counter == 5)
               {
                   counter = 0;
               }
           }
    }
    else
    {
        // Erstellen der neuen Datei, wenn diese noch nicht vorhanden ist
        fopen("buecher.txt" , "w");
    }
    // Schliessen der Datei (und Speichern)
    fclose(fp);
    return head;
}


// Speichert in der Datei buecher.txt Die Buecherliste mit der dazugehörigen Ausleiherliste ab und braucht beim Aufruf den Kopf der Buecherliste
void saveBookFile(Element *head)
{
    // Oeffnet die Datei zum Schreiben
    FILE *fp;
    fp = fopen("buecher.txt" , "w");
    // Durch die ganze Liste iterieren und somit hat man jedes Buch(Element) e
    for (Element *e = head->next; e != e->next; e = e->next)
    {
        // String zusammensetzen, jedes Attribut in eine neue Zeile
        char entry[ENTRYSTRING] = "";
        strcat(entry, e->isbn);
        strcat(entry, "\n");
        strcat(entry, e->titel);
        strcat(entry, "\n");
        strcat(entry, e->autor);
        strcat(entry, "\n");

        //Zahl anzahl in String anzahl umwandeln
        char stranzahl[INTSTRINGSIZE] = "";
        sprintf(stranzahl, "%d", e->anzahl);
        strcat(entry, stranzahl);
        strcat(entry, "\n");

        // Zusammenfuegen der Ausleiherliste in einen String durch Iteriern durch die Liste und abtrennen durch ein Semikolon
        AusleiherElement *ausleiherhead = e->ausleiherhead;
        char ausleiherstring[LISTSTRINGSIZE] = "";
        for (AusleiherElement *ae = ausleiherhead->next; ae != ae->next; ae = ae->next)
        {
            if (ausleiherhead->next != ae) { strcat(ausleiherstring, ";"); }
            strcat(ausleiherstring, ae->name);
        }
        strcat(entry, ausleiherstring);
        strcat(entry, "\n");

        // Entrystring in Datei speichern
        fputs(entry, fp);
    }
    // Datei speichern und schliessen
    fclose(fp);
}
