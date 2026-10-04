#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;

    initialize(&addressBook);

    do
    {
        printf("\n");
        printf("============================================\n");
        printf("              ADDRESS BOOK SYSTEM           \n");
        printf("============================================\n");
        printf("  1. Create Contact\n");
        printf("  2. Search Contact\n");
        printf("  3. Edit Contact\n");
        printf("  4. Delete Contact\n");
        printf("  5. List All Contacts\n");
        printf("  6. Save & Exit\n");
        printf("============================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\n------------- CREATE CONTACT ---------------\n");
                createContact(&addressBook);
                break;

            case 2:
                printf("\n------------- SEARCH CONTACT ---------------\n");
                searchContact(&addressBook);
                break;

            case 3:
                printf("\n-------------- EDIT CONTACT ----------------\n");
                editContact(&addressBook);
                break;

            case 4:
                printf("\n------------- DELETE CONTACT ---------------\n");
                deleteContact(&addressBook);
                break;

            case 5:
            {
                int sortChoice;

                printf("\n");
                printf("============================================\n");
                printf("               LIST CONTACTS                \n");
                printf("============================================\n");
                printf("  1. Sort by Name\n");
                printf("  2. Sort by Phone\n");
                printf("  3. Sort by Email\n");
                printf("--------------------------------------------\n");
                printf("Enter your choice: ");

                scanf("%d", &sortChoice);

                listContacts(&addressBook, sortChoice);
                break;
            }

            case 6:
                printf("\n============================================\n");
                printf("          SAVING CONTACTS...                \n");
                printf("============================================\n");

                saveContactsToFile(&addressBook);

                printf("       Exiting Address Book System           \n");
                printf("============================================\n");
                break;

            default:
                printf("\n[ERROR] Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}