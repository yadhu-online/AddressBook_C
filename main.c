/*  Title: Address Book Project
    Description: create an AddressBook (console-based contact management system) in which we can 
    create,edit,delete and save the contact details.
    Main menu:
                ADDRESS BOOK MENU:
                1. Create contact
                2. Search contact
                3. Edit contact
                4. Delete contact
                5. List all contacts
                6. Save contacts
                7. Exit
     */

#include <stdio.h>
#include "contact.h"

int main() {
    int choice=0,sortChoice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf(YELLOW"\n========================\n");
        printf("| ADDRESS BOOK MENU:   |\n");
        printf("========================\n");
        printf("| 1. Create contact    |\n");
        printf("| 2. Search contact    |\n");
        printf("| 3. Edit contact      |\n");
        printf("| 4. Delete contact    |\n");
        printf("| 5. List all contacts |\n");
    	printf("| 6. Save contacts     |\n");		
        printf("| 7. Exit              |\n");
        printf("========================\n"RESET);
        printf(WHITE"Enter your choice: "RESET);
        if (scanf("%d", &choice)==0)   //invalid if user input other than decimal value
        {
            printf(RED"Invalid input. Try again.\n"RESET);
            while (getchar() != '\n'); //clear buffer
            continue;
        }
        switch (choice) { // switch case to select desired option
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf(GREEN"Saved ✔\n"RESET);
                saveContactsToFile(&addressBook);
                break;
            case 7:  //exit
                return 0;
            default:
                printf(RED"Invalid choice! Please try again.\n"RESET); //Invalid promt message
        }
    } while (choice != 7); //countinue looping if user enter value other than 1-7
    
       return 0;
}
