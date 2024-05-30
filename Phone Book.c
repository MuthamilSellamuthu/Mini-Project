#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_PHONE 15

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
} Contact;

void addContact();
void displayContacts();
void searchContact();
void deleteContact();

int main() {
    int choice;
    while(1) {
        printf("\nPhone Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character left by scanf

        switch(choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void addContact() {
    FILE *fp;
    Contact contact;

    fp = fopen("phonebook.dat", "ab");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name: ");
    fgets(contact.name, MAX_NAME, stdin);
    contact.name[strcspn(contact.name, "\n")] = '\0'; // Remove newline character

    printf("Enter phone number: ");
    fgets(contact.phone, MAX_PHONE, stdin);
    contact.phone[strcspn(contact.phone, "\n")] = '\0'; // Remove newline character

    fwrite(&contact, sizeof(Contact), 1, fp);
    fclose(fp);

    printf("Contact added successfully.\n");
}

void displayContacts() {
    FILE *fp;
    Contact contact;

    fp = fopen("phonebook.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nContacts List:\n");
    while(fread(&contact, sizeof(Contact), 1, fp)) {
        printf("Name: %s, Phone: %s\n", contact.name, contact.phone);
    }
    fclose(fp);
}

void searchContact() {
    FILE *fp;
    Contact contact;
    char searchName[MAX_NAME];
    int found = 0;

    fp = fopen("phonebook.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name to search: ");
    fgets(searchName, MAX_NAME, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove newline character

    while(fread(&contact, sizeof(Contact), 1, fp)) {
        if(strcmp(contact.name, searchName) == 0) {
            printf("Name: %s, Phone: %s\n", contact.name, contact.phone);
            found = 1;
            break;
        }
    }
    if(!found) {
        printf("Contact not found.\n");
    }
    fclose(fp);
}

void deleteContact() {
    FILE *fp, *temp;
    Contact contact;
    char deleteName[MAX_NAME];
    int found = 0;

    fp = fopen("phonebook.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    temp = fopen("temp.dat", "wb");
    if(temp == NULL) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    printf("Enter name to delete: ");
    fgets(deleteName, MAX_NAME, stdin);
    deleteName[strcspn(deleteName, "\n")] = '\0'; // Remove newline character

    while(fread(&contact, sizeof(Contact), 1, fp)) {
        if(strcmp(contact.name, deleteName) != 0) {
            fwrite(&contact, sizeof(Contact), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);

    if(found) {
        remove("phonebook.dat");
        rename("temp.dat", "phonebook.dat");
        printf("Contact deleted successfully.\n");
    } else {
        remove("temp.dat");
        printf("Contact not found.\n");
    }
}
