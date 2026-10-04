#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

/* =========================================================
   LIST CONTACTS
   ========================================================= */

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    if (addressBook->contactCount == 0)
    {
        printf("\n[ERROR] No contacts available.\n");
        return;
    }

    Contact temp;

    /* Validate sort choice */
    if (sortCriteria < 1 || sortCriteria > 3)
    {
        printf("\n[ERROR] Invalid sort criteria.\n");
        return;
    }

    /* Bubble Sort */
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            int result = 0;

            if (sortCriteria == 1)
            {
                result = strcmp(addressBook->contacts[j].name,
                                addressBook->contacts[j + 1].name);
            }
            else if (sortCriteria == 2)
            {
                result = strcmp(addressBook->contacts[j].phone,
                                addressBook->contacts[j + 1].phone);
            }
            else
            {
                result = strcmp(addressBook->contacts[j].email,
                                addressBook->contacts[j + 1].email);
            }

            if (result > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf("\n");
    printf("================================================================================\n");
    printf("                              CONTACT LIST\n");
    printf("================================================================================\n");
    printf("%-5s %-20s %-15s %-30s\n",
           "No.", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("Total Contacts: %d\n", addressBook->contactCount);
    printf("================================================================================\n");
}


/* =========================================================
   INITIALIZE ADDRESS BOOK
   ========================================================= */

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    loadContactsFromFile(addressBook);

    if (addressBook->contactCount == 0)
    {
        populateAddressBook(addressBook);
    }
}


/* =========================================================
   SAVE AND EXIT
   ========================================================= */

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}


/* =========================================================
   CREATE CONTACT
   ========================================================= */

void createContact(AddressBook *addressBook)
{
    Contact newContact;
    int valid, duplicate;

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("\n[ERROR] Address Book is full.\n");
        return;
    }

    printf("\n");
    printf("============================================\n");
    printf("               CREATE CONTACT               \n");
    printf("============================================\n");

    /* NAME */

    printf("Enter Name  : ");
    scanf(" %49[^\n]", newContact.name);

    /* Validate name */
    for (int i = 0; newContact.name[i] != '\0'; i++)
    {
        if (!((newContact.name[i] >= 'A' &&
               newContact.name[i] <= 'Z') ||
              (newContact.name[i] >= 'a' &&
               newContact.name[i] <= 'z') ||
               newContact.name[i] == ' '))
        {
            printf("\n[ERROR] Name must contain only letters and spaces.\n");
            return;
        }
    }

    /* PHONE */

    do
    {
        valid = 1;
        duplicate = 0;

        printf("Enter Phone : ");
        scanf("%19s", newContact.phone);

        if (strlen(newContact.phone) != 10)
        {
            valid = 0;
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                if (newContact.phone[i] < '0' ||
                    newContact.phone[i] > '9')
                {
                    valid = 0;
                    break;
                }
            }
        }

        if (!valid)
        {
            printf("[ERROR] Enter exactly 10 digits.\n");
            continue;
        }

        /* Duplicate phone check */

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone,
                       newContact.phone) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate)
        {
            printf("[ERROR] Phone number already exists.\n");
        }

    } while (!valid || duplicate);


    /* EMAIL */

    do
    {
        int atCount = 0;
        int atPosition = -1;
        int dotAfterAt = 0;

        valid = 1;
        duplicate = 0;

        printf("Enter Email : ");
        scanf("%49s", newContact.email);

        int length = strlen(newContact.email);

        /* Count @ and check spaces */

        for (int i = 0; newContact.email[i] != '\0'; i++)
        {
            if (newContact.email[i] == ' ')
            {
                valid = 0;
                break;
            }

            if (newContact.email[i] == '@')
            {
                atCount++;
                atPosition = i;
            }
        }

        if (atCount != 1)
        {
            valid = 0;
        }

        if (valid &&
            (atPosition == 0 ||
             atPosition == length - 1))
        {
            valid = 0;
        }

        /* Find dot after @ */

        if (valid)
        {
            for (int i = atPosition + 1; i < length; i++)
            {
                if (newContact.email[i] == '.')
                {
                    dotAfterAt = 1;
                    break;
                }
            }

            if (!dotAfterAt)
            {
                valid = 0;
            }
        }

        if (valid &&
            (newContact.email[atPosition + 1] == '.' ||
             newContact.email[length - 1] == '.'))
        {
            valid = 0;
        }

        if (!valid)
        {
            printf("[ERROR] Invalid email. Example: name@gmail.com\n");
            continue;
        }

        /* Duplicate email check */

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email,
                       newContact.email) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate)
        {
            printf("[ERROR] Email already exists.\n");
        }

    } while (!valid || duplicate);


    /* STORE CONTACT */

    addressBook->contacts[addressBook->contactCount] = newContact;
    addressBook->contactCount++;


    printf("\n");
    printf("============================================\n");
    printf("        CONTACT CREATED SUCCESSFULLY        \n");
    printf("============================================\n");
    printf("Name  : %s\n", newContact.name);
    printf("Phone : %s\n", newContact.phone);
    printf("Email : %s\n", newContact.email);
    printf("============================================\n");
}


/* =========================================================
   SEARCH CONTACT
   ========================================================= */

void searchContact(AddressBook *addressBook)
{
    int choice;
    int found = 0;
    char search[50];

    printf("\n");
    printf("============================================\n");
    printf("               SEARCH CONTACT               \n");
    printf("============================================\n");
    printf("  1. Search by Name\n");
    printf("  2. Search by Phone\n");
    printf("  3. Search by Email\n");
    printf("--------------------------------------------\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    if (choice < 1 || choice > 3)
    {
        printf("\n[ERROR] Invalid choice.\n");
        return;
    }

    printf("Enter search value: ");
    scanf(" %49[^\n]", search);


    /* NAME VALIDATION */

    if (choice == 1)
    {
        if (strlen(search) == 0)
        {
            printf("\n[ERROR] Invalid name.\n");
            return;
        }

        for (int i = 0; search[i] != '\0'; i++)
        {
            if (!((search[i] >= 'A' && search[i] <= 'Z') ||
                  (search[i] >= 'a' && search[i] <= 'z') ||
                   search[i] == ' '))
            {
                printf("\n[ERROR] Name must contain only letters and spaces.\n");
                return;
            }
        }
    }


    /* PHONE VALIDATION */

    else if (choice == 2)
    {
        if (strlen(search) != 10)
        {
            printf("\n[ERROR] Enter exactly 10 digits.\n");
            return;
        }

        for (int i = 0; search[i] != '\0'; i++)
        {
            if (search[i] < '0' || search[i] > '9')
            {
                printf("\n[ERROR] Phone must contain only digits.\n");
                return;
            }
        }
    }


    /* EMAIL VALIDATION */

    else
    {
        int atCount = 0;
        int atPosition = -1;
        int dotAfterAt = 0;
        int length = strlen(search);

        for (int i = 0; search[i] != '\0'; i++)
        {
            if (search[i] == ' ')
            {
                printf("\n[ERROR] Spaces are not allowed in email.\n");
                return;
            }

            if (search[i] == '@')
            {
                atCount++;
                atPosition = i;
            }
        }

        if (atCount != 1 ||
            atPosition == 0 ||
            atPosition == length - 1)
        {
            printf("\n[ERROR] Invalid email format.\n");
            return;
        }

        for (int i = atPosition + 1; i < length; i++)
        {
            if (search[i] == '.')
            {
                dotAfterAt = 1;
                break;
            }
        }

        if (!dotAfterAt ||
            search[atPosition + 1] == '.' ||
            search[length - 1] == '.')
        {
            printf("\n[ERROR] Invalid email format.\n");
            return;
        }
    }


    /* SEARCH */

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 &&
             strcmp(addressBook->contacts[i].name, search) == 0) ||

            (choice == 2 &&
             strcmp(addressBook->contacts[i].phone, search) == 0) ||

            (choice == 3 &&
             strcmp(addressBook->contacts[i].email, search) == 0))
        {
            printf("\n");
            printf("============================================\n");
            printf("               CONTACT FOUND                \n");
            printf("============================================\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            printf("============================================\n");

            found = 1;
        }
    }

    if (!found)
    {
        printf("\n--------------------------------------------\n");
        printf("[ERROR] Contact not found.\n");
        printf("--------------------------------------------\n");
    }
}


/* =========================================================
   EDIT CONTACT
   ========================================================= */

void editContact(AddressBook *addressBook)
{
    int searchChoice, editChoice;
    int found = -1;

    char search[50];
    char newValue[50];

    printf("\n");
    printf("============================================\n");
    printf("                EDIT CONTACT                \n");
    printf("============================================\n");
    printf("  1. Find by Name\n");
    printf("  2. Find by Phone\n");
    printf("  3. Find by Email\n");
    printf("--------------------------------------------\n");
    printf("Enter your choice: ");

    scanf("%d", &searchChoice);

    if (searchChoice < 1 || searchChoice > 3)
    {
        printf("\n[ERROR] Invalid choice.\n");
        return;
    }

    printf("Enter search value: ");
    scanf(" %49[^\n]", search);


    /* PHONE SEARCH VALIDATION */

    if (searchChoice == 2)
    {
        if (strlen(search) != 10)
        {
            printf("\n[ERROR] Enter exactly 10 digits.\n");
            return;
        }

        for (int i = 0; search[i] != '\0'; i++)
        {
            if (search[i] < '0' || search[i] > '9')
            {
                printf("\n[ERROR] Phone must contain only digits.\n");
                return;
            }
        }
    }


    /* FIND CONTACT */

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((searchChoice == 1 &&
             strcmp(addressBook->contacts[i].name, search) == 0) ||

            (searchChoice == 2 &&
             strcmp(addressBook->contacts[i].phone, search) == 0) ||

            (searchChoice == 3 &&
             strcmp(addressBook->contacts[i].email, search) == 0))
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("\n[ERROR] Contact not found.\n");
        return;
    }


    printf("\n");
    printf("============================================\n");
    printf("               CONTACT FOUND                \n");
    printf("============================================\n");
    printf("Name  : %s\n", addressBook->contacts[found].name);
    printf("Phone : %s\n", addressBook->contacts[found].phone);
    printf("Email : %s\n", addressBook->contacts[found].email);
    printf("============================================\n");


    printf("\n");
    printf("--------------------------------------------\n");
    printf("             SELECT FIELD TO EDIT           \n");
    printf("--------------------------------------------\n");
    printf("  1. Name\n");
    printf("  2. Phone\n");
    printf("  3. Email\n");
    printf("--------------------------------------------\n");
    printf("Enter your choice: ");

    scanf("%d", &editChoice);


    /* EDIT NAME */

    if (editChoice == 1)
    {
        printf("Enter new name: ");
        scanf(" %49[^\n]", newValue);

        for (int i = 0; newValue[i] != '\0'; i++)
        {
            if (!((newValue[i] >= 'A' && newValue[i] <= 'Z') ||
                  (newValue[i] >= 'a' && newValue[i] <= 'z') ||
                   newValue[i] == ' '))
            {
                printf("\n[ERROR] Name must contain only letters and spaces.\n");
                return;
            }
        }

        strcpy(addressBook->contacts[found].name, newValue);

        printf("\n[SUCCESS] Name updated successfully.\n");
    }


    /* EDIT PHONE */

    else if (editChoice == 2)
    {
        printf("Enter new phone: ");
        scanf("%19s", newValue);

        if (strlen(newValue) != 10)
        {
            printf("\n[ERROR] Enter exactly 10 digits.\n");
            return;
        }

        for (int i = 0; newValue[i] != '\0'; i++)
        {
            if (newValue[i] < '0' || newValue[i] > '9')
            {
                printf("\n[ERROR] Phone must contain only digits.\n");
                return;
            }
        }

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (i != found &&
                strcmp(addressBook->contacts[i].phone,
                       newValue) == 0)
            {
                printf("\n[ERROR] Phone number already exists.\n");
                return;
            }
        }

        strcpy(addressBook->contacts[found].phone, newValue);

        printf("\n[SUCCESS] Phone updated successfully.\n");
    }


    /* EDIT EMAIL */

    else if (editChoice == 3)
    {
        int atCount = 0;
        int atPosition = -1;
        int dotAfterAt = 0;

        printf("Enter new email: ");
        scanf("%49s", newValue);

        int length = strlen(newValue);

        for (int i = 0; newValue[i] != '\0'; i++)
        {
            if (newValue[i] == ' ')
            {
                printf("\n[ERROR] Spaces are not allowed in email.\n");
                return;
            }

            if (newValue[i] == '@')
            {
                atCount++;
                atPosition = i;
            }
        }

        if (atCount != 1 ||
            atPosition == 0 ||
            atPosition == length - 1)
        {
            printf("\n[ERROR] Invalid email format.\n");
            return;
        }

        for (int i = atPosition + 1; i < length; i++)
        {
            if (newValue[i] == '.')
            {
                dotAfterAt = 1;
                break;
            }
        }

        if (!dotAfterAt ||
            newValue[atPosition + 1] == '.' ||
            newValue[length - 1] == '.')
        {
            printf("\n[ERROR] Invalid email format.\n");
            return;
        }

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (i != found &&
                strcmp(addressBook->contacts[i].email,
                       newValue) == 0)
            {
                printf("\n[ERROR] Email already exists.\n");
                return;
            }
        }

        strcpy(addressBook->contacts[found].email, newValue);

        printf("\n[SUCCESS] Email updated successfully.\n");
    }

    else
    {
        printf("\n[ERROR] Invalid edit choice.\n");
    }
}


/* =========================================================
   DELETE CONTACT
   ========================================================= */

void deleteContact(AddressBook *addressBook)
{
    int choice;
    int found = -1;
    char search[50];

    printf("\n");
    printf("============================================\n");
    printf("               DELETE CONTACT               \n");
    printf("============================================\n");
    printf("  1. Delete by Name\n");
    printf("  2. Delete by Phone\n");
    printf("  3. Delete by Email\n");
    printf("--------------------------------------------\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    if (choice < 1 || choice > 3)
    {
        printf("\n[ERROR] Invalid choice.\n");
        return;
    }

    printf("Enter search value: ");
    scanf(" %49[^\n]", search);


    /* PHONE VALIDATION */

    if (choice == 2)
    {
        if (strlen(search) != 10)
        {
            printf("\n[ERROR] Enter exactly 10 digits.\n");
            return;
        }

        for (int i = 0; search[i] != '\0'; i++)
        {
            if (search[i] < '0' || search[i] > '9')
            {
                printf("\n[ERROR] Phone must contain only digits.\n");
                return;
            }
        }
    }


    /* FIND CONTACT */

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 &&
             strcmp(addressBook->contacts[i].name, search) == 0) ||

            (choice == 2 &&
             strcmp(addressBook->contacts[i].phone, search) == 0) ||

            (choice == 3 &&
             strcmp(addressBook->contacts[i].email, search) == 0))
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("\n[ERROR] Contact not found.\n");
        return;
    }


    printf("\n");
    printf("============================================\n");
    printf("               CONTACT FOUND                \n");
    printf("============================================\n");
    printf("Name  : %s\n", addressBook->contacts[found].name);
    printf("Phone : %s\n", addressBook->contacts[found].phone);
    printf("Email : %s\n", addressBook->contacts[found].email);
    printf("============================================\n");


    /* DELETE BY SHIFTING */

    for (int i = found;
         i < addressBook->contactCount - 1;
         i++)
    {
        addressBook->contacts[i] =
            addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;


    printf("\n");
    printf("============================================\n");
    printf("        CONTACT DELETED SUCCESSFULLY        \n");
    printf("============================================\n");
}