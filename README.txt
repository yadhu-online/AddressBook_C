Address Book in C (Console Application)

This project is a simple console-based Address Book application written in C.
It allows users to store and manage contact details such as name, phone number, and email, with data persisted to a file.

Features

* Create new contacts
* Search contacts by -name, phone, or email
* Edit existing contacts
* Delete contacts with confirmation
* List all saved contacts
* Save contacts to a file (`contacts.txt`)
* Load contacts automatically at startup

Project Structure

.
├── main.c        // Program entry point & menu
├── contact.c     // Core address book logic
├── contact.h     // Structures, macros, and prototypes
├── file.c        // File handling (save/load)
├── file.h        // File handling declarations
└── contacts.txt  // Auto-generated data file

How It Works

* Contacts are stored in an `AddressBook` structure.
* Data is saved in **CSV format** inside `contacts.txt`.
* Input validation is applied for:
  -> Names (alphabets and spaces only)
  -> Phone numbers (unique, 10 digits, non-zero start)
  -> Email IDs (basic format validation and uniqueness)
* ANSI color codes are used for better terminal readability.

How to Compile and Run

bash
gcc main.c contact.c file.c -o address_book
./address_book

or

gcc*.c
./a.out

Main menu:
                ADDRESS BOOK MENU:
                1. Create contact
                2. Search contact
                3. Edit contact
                4. Delete contact
                5. List all contacts
                6. Save contacts
                7. Exit

Notes

* Designed for **learning purposes** (structures, file handling, validation, menus).
* Works best on **Linux / Unix terminals** that support ANSI escape codes.
* No dynamic memory allocation is used.


Author

Developed as a C programming project to practice:

* Modular programming
* File I/O
* Input validation
* Struct-based data management


