#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include "Ausleiherliste.h"
#include "Buchliste.h"
#include "DateiManager.h"

// Lange fuer die einzelnen Attribute in einem Buch
#define STRINGSIZE 128

// Warten bis Enter gedrueckt wird
void waitforinput()
{
    puts("");
    puts("Druecken Sie ENTER um fortzufahren");
    getchar();
    puts("");
}

//Buch loeschen
void buch_loeschen(Element *head)
{
    char isbn[STRINGSIZE];
    puts("********** Buch loeschen **********");
    puts("Bitte geben Sie die ISBN-Nummer des Buches ein:");
    // ISBN einlesen
    gets(isbn);
    // Wenn Bich mit ISBN in DB, dann Buch aus Liste loeschen
    if (contains(head, isbn))
    {
        deleteElement(head, isbn);
        puts("Das Buch wurde geloescht");
    }
    else
    {
        puts("Das Buch mit dieser ISBN-Nummer konnte nicht gefunden werden");
    }
    waitforinput();
}


//Buch einfuegen
void buch_einfuegen(Element *head)
{
    char isbn[STRINGSIZE];
    char titel[STRINGSIZE];
    char autor[STRINGSIZE];
    int anzahl;
    puts("********** Buch einfuegen **********");
    puts("Bitte geben Sie die nachfolgenden Werte ein");
    puts("ISBN-Nummer eingeben (ISBN im Nachhinein nicht editierbar):");
    // ISBN einlesen
    gets(isbn);
    //Wenn ISBN noch nioht registriert ist in Liste
    if (!contains(head, isbn))
    {
        //Daten nacheinander eingeben
        puts("Buchtitel eingeben:");
        gets(titel);
        puts("Autor eingeben:");
        gets(autor);
        puts("Anzahl der Exemplare eingeben:");
        scanf("%d", &anzahl);
        puts("");

        //Falls noch mit getchar eingelesen wird, ist die Eingabe Fehlerhaft (Buchstaben enthalten) und b wird auf false gesetzet

        bool b = true;
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
                b = false;
        }
        if (b)
        {
            // ANzahl muss >= 0 sein
            if (anzahl >= 0)
            {
                AusleiherElement *ausleiherhead = createAusleiherList();
                insertHead(head, isbn, titel, autor, anzahl, ausleiherhead);
                puts("Das Buch wurde hinzugefuegt");
            }
            else
            {
                puts("Bitte bei Anzahl eine positive Zahl eingeben");
            }
        }
        else
        {
            puts("Fehler bei der Eingabe. Bitte bei Anzahl eine ganze Zahl eingeben");
        }
    }
    else
    {
        puts("Es existiert bereits ein Buch mit dieser ISBN-Nummer");
    }


    waitforinput();
}


// Bich Infos anzeigen
void buch_info(Element *head)
{
    char isbn[STRINGSIZE];
    puts("********** Buch Informationen **********");
    puts("Bitte geben Sie die ISBN-Nummer des Buches ein:");
    // ISBN einlesen
    gets(isbn);
    // Wenn Liste enthaelt ISBN:
    if (contains(head, isbn)) {
        // Element mit ISBN holen und Werte ausgeben, verfuegbar = anzahl - listgroesse
        Element *book = getElement(head, isbn);
        int verfuegbar = book->anzahl - getAusleiherSize(book->ausleiherhead);
        printf("ISBN: %s\nTitel: %s\nAutor: %s\nAnzahl: %d\nVerfuegbar: %d\n", book->isbn, book->titel, book->autor, book->anzahl, verfuegbar);
    } else {
        puts("Es wurde kein Buch mit dieser ISBN gefunden");
    }
    waitforinput();
}


// Buch ausleihen
void buch_ausleihen(Element *head)
{
    char isbn[STRINGSIZE];
    char name[STRINGSIZE];
    puts("********** Buch ausleihen **********");
    puts("Bitte geben Sie die ISBN-Nummer des Buches ein:");
    //ISBN einlesen
    gets(isbn);
    // Wenn ISBN enthalten ist:
    if (contains(head, isbn)) {
        Element *book = getElement(head, isbn);
        // Wenn noch Exemplare verfuegbar sind
        if (book->anzahl > getAusleiherSize(book->ausleiherhead))
        {
            // Name einegeben und in liste hinzufuegen. verfuegbare exemplare berechnen
            printf("Wer moechte das Buch mit dem Titel '%s' ausleihen:\n", book->titel);
            gets(name);
            insertAusleiherHead(book->ausleiherhead, name);
            int verfuegbar = book->anzahl - getAusleiherSize(book->ausleiherhead);
            printf("Das Buch wurde erfolgreich ausgeliehen. Es sind noch %d freie(s) Exemplare verfuegbar\n", verfuegbar);
        }
        else puts("Von diesem Buch sind leider keine freien Exemplare mehr erhaeltlich");
    } else {
        puts("Es wurde kein Buch mit dieser ISBN gefunden");
    }
    waitforinput();
}


// Buch zurueckgeben
void buch_zurueckgeben(Element *head)
{
    char isbn[STRINGSIZE];
    char name[STRINGSIZE];
    puts("********** Buch zurueckgeben **********");
    puts("Bitte geben Sie die ISBN-Nummer des Buches ein:");
    // ISBN einlesen
    gets(isbn);
    // falls isbn in liste enthalten ist
    if (contains(head, isbn)) {
        Element *book = getElement(head, isbn);
        // Falls Buecherueberhaupt ausgeliehen wurden
        if (getAusleiherSize(book->ausleiherhead) > 0)
        {
            printf("Wer moechte das Buch mit dem Titel '%s' zurueckgeben:\n", book->titel);
            gets(name);
            // Der eingelesene Name testen, ob er in der ausleiherliste vorhanden ist
            if (containsAusleiher(book->ausleiherhead, name))
            {
                // Element mit dem Namen aus der Liste loeschen
                deleteAusleiherElement(book->ausleiherhead, name);
                printf("Das Buch wurde erfolgreich zurueckgegeben. Es sind nun %d freie(s) Exemplare verfuegbar\n", (book->anzahl - getAusleiherSize(book->ausleiherhead)));
            }
            else puts("Die eingegebene Person hat dieses Buch nicht ausgeliehen");
        }
        else puts("Von diesem Buch wurden keine Exemplare vergeben");
    } else {
        puts("Es wurde kein Buch mit dieser ISBN gefunden");
    }
    waitforinput();
}


// Buch bearbeiten
void buch_bearbeiten(Element *head)
{
    char isbn[STRINGSIZE];
    char titel[STRINGSIZE];
    char autor[STRINGSIZE];
    int anzahl;
    puts("********** Buch bearbeiten **********");
    puts("Bitte geben Sie die ISBN-Nummer des Buches ein:");
    // ISBN einlesen
    gets(isbn);
    // Falls ISBN in Liste enthalten ist
    if (contains(head, isbn)) {
        Element *book = getElement(head, isbn);

        // Daten eingeben
        puts("Buchtitel eingeben:");
        gets(titel);
        puts("Autor eingeben:");
        gets(autor);
        puts("Anzahl der Exemplare eingeben:");
        scanf("%d", &anzahl);
        puts("");

        // Abfrage ob noch ein Char eingelesen wird: Wenn ja, wird b auf false gesetzet -> Es war keine Zahl sondern zB ein Buchstabe enthalten
        bool b = true;
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
                b = false;
        }
        if (b)
        {
            // Falls anzahl >= 0 ist
            if (anzahl >= 0)
            {
                // Eigenschaten des Buches setzen / aktualisieren
                strcpy(book->titel,titel);
                strcpy(book->autor,autor);
                book->anzahl = anzahl;
                puts("Das Buch wurde erfolgreich geaendert");
            }
            else
            {
                puts("Bitte bei Anzahl eine positive Zahl eingeben");
            }
        }
        else
        {
            puts("Fehler bei der Eingabe. Bitte bei Anzahl eine ganze Zahl eingeben");
        }


    } else {
        puts("Es wurde kein Buch mit dieser ISBN gefunden");
    }
}

// Gibt Buchliste ein
void buchliste_anzeigen(Element *head)
{
    puts("********** Buchliste **********");
    // Size des Liste auslesen und Liste Ausgeben
    int size = getSize(head);
    printf("Anzahl der eingetragenen Buecher(ISBN unterschiedlich): %d\n", size);
    printList(head);
    waitforinput();
}


// Buch suchen
void buch_suchen(Element *head)
{
    puts("********** Buch suchen **********");
    puts("Suche nach ISBN, Titel oder Autor:");
    char keyword[STRINGSIZE];
    // keyword eingeben
    gets(keyword);
    // Nach Elementen mit diesem Keyword suchen
    printSearchResults(head, keyword);
    waitforinput();

}


// Informationen ausgeben
void information()
{
    puts("********** Informationen **********");
    puts("Im Verzeichnis muessen die Dateien buecher.txt und ausleiher.txt vorhanden sein.");
    puts("Werte fuer ein Buch eintragen:\n\nISBN\nNAME\nAUTOR\nANZAHL\nAUSLEIHER 1;AUSLEIHER 2;...)\n");
    puts("Falls keine Ausleiher vorhanden sind, einfach eine leere Zeile einfuegen.");
    waitforinput();
}


// Datei Speichern und Text ausgeben
void save(Element *head)
{
    saveBookFile(head);
    puts("Dateien wurden gespeichert.");
}


// Menue ausgeben
void printMenue()
{
    puts("********** Bibliotheksverwaltung **********");
    puts("a - Buch suchen");
    puts("b - Buch ausleihen");
    puts("c - Buch zurueckgeben");
    puts("d - Buch einfuegen");
    puts("e - Buch loeschen");
    puts("f - Buch bearbeiten");
    puts("g - Buch Informationen");
    puts("h - Buchliste anzeigen");
    puts("i - Informationen");
    puts("j - Speichern und beenden");
    puts("");
    puts("Bitte waehlen Sie die gewuenschte Option:");
}


// Main Funktion
int main()
{
    // buecherdatei laden und in head speichern
    Element *head = loadBookFile();

    // Endlosschleife, die durch den break Befehel spaeter verlassen werden kann
    while(true)
    {
        // Ausgabe Menue
        printMenue();

        // char Array eingabe deklarieren und Auf Eingabe des Benutzers warten und dann abfragen (Einagbe wird in chararray eingabe gespeichert)
        char eingabe[STRINGSIZE];
        gets(eingabe);

        puts("");

        if (strcmp(eingabe, "a") == 0)
            buch_suchen(head);
        else if (strcmp(eingabe, "b") == 0)
            buch_ausleihen(head);
        else if (strcmp(eingabe, "c") == 0)
            buch_zurueckgeben(head);
        else if (strcmp(eingabe, "d") == 0)
            buch_einfuegen(head);
        else if (strcmp(eingabe, "e") == 0)
            buch_loeschen(head);
        else if (strcmp(eingabe, "f") == 0)
            buch_bearbeiten(head);
        else if (strcmp(eingabe, "g") == 0)
            buch_info(head);
        else if (strcmp(eingabe, "h") == 0)
            buchliste_anzeigen(head);
        else if (strcmp(eingabe, "i") == 0)
            information();
        else if (strcmp(eingabe, "j") == 0)
        {
            // gespeichert und muit break wird die Schleife verlassen
            save(head);
            break;
        }
        else
        {
            // Falls keine gueltige Eingabe vorhanden ist
          puts("");
          puts("=> Ungueltige Eingabe <=");
          waitforinput();
        }
    }
    puts("Programm wird beendet");
    return 0;
}


