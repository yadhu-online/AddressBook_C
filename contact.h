#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
#define RESET   "\033[0m"
#define RED     "\033[1;91m"
#define GREEN   "\033[1;92m"
#define YELLOW  "\033[1;93m"
#define BLUE    "\033[1;94m"
#define MAGENTA "\033[1;95m"
#define CYAN    "\033[1;96m"
#define WHITE   "\033[1;97m"

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

int namevalidate(char []); 
int phonevalidate(char [],AddressBook *addressBook); 
int emailvalidate(char [],AddressBook *addressBook);

#endif
