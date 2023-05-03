#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 20

// Function to add a new contact to the phonebook
void add_contact() {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    FILE *fptr;
    fptr = fopen("phonebook.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter phone number: ");
    scanf("%s", phone_number);
    fprintf(fptr, "%s,%s,%s\n", name, email,phone_number);
    fclose(fptr);
    printf("Contact added successfully.\n");
}
//edit a contact
void edit_contact() {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    char search_name[MAX_NAME_LENGTH];
    int found = 0;
    FILE *fptr, *temp_ptr;
    fptr = fopen("phonebook.txt", "r");
    temp_ptr = fopen("temp.txt", "w");
    if (fptr == NULL || temp_ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter name of contact to edit: ");
    scanf("%s", search_name);
    while (fscanf(fptr, "%[^,],%[^,],%s\n", name, email, phone_number) != EOF) {
        if (stricmp(name, search_name) == 0) {
            printf("Enter new email: ");
            scanf("%s", email);
            printf("Enter new phone number: ");
            scanf("%s", phone_number);
            fprintf(temp_ptr, "%s,%s,%s\n", name, email, phone_number);
            found = 1;
        } else {
            fprintf(temp_ptr, "%s,%s,%s\n", name, email, phone_number);
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    } else {
        fclose(fptr);
        fclose(temp_ptr);
        remove("phonebook.txt");
        rename("temp.txt", "phonebook.txt");
        printf("Contact edited successfully.\n");
    }
}


// delete a contact
void delete_contact() {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    char search_name[MAX_NAME_LENGTH];
    int found = 0;
    FILE *fptr, *temp;
    fptr = fopen("phonebook.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter name to delete: ");
    scanf("%s", search_name);
    while (fscanf(fptr, "%[^,],%[^,],%s\n", name, email, phone_number) != EOF) {
        if (stricmp(name, search_name) == 0) {
            found = 1;
        } else {
            fprintf(temp, "%s,%s,%s\n", name, email, phone_number);
        }
    }
    fclose(fptr);
    fclose(temp);
    if (!found) {
        printf("Contact not found.\n");
    } else {
        remove("phonebook.txt");
        rename("temp.txt", "phonebook.txt");
        printf("Contact deleted successfully.\n");
    }
}


// Function to search for a contact in the phonebook
void search_contact() {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    char search_name[MAX_NAME_LENGTH];
    int found = 0;
    FILE *fptr;
    fptr = fopen("phonebook.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter name to search for: ");
    scanf("%s", search_name);
    while (fscanf(fptr, "%[^,],%[^,],%s\n", name, email, phone_number) != EOF) {
        if (stricmp(name, search_name) == 0) {
            printf("Name: %s\n", name);
            printf("Email: %s\n", email);
            printf("Phone number: %s\n", phone_number);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
    fclose(fptr);
}

// Function to display all contacts in the phonebook
void display_contacts() {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    FILE *fptr;
    fptr = fopen("phonebook.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    while (fscanf(fptr, "%[^,],%[^,],%s\n", name, email, phone_number) != EOF) {
        printf("Name: %s\n", name);
        printf("Email: %s\n", email);
        printf("Phone number: %s\n", phone_number);
        printf("\n");
    }
    fclose(fptr);
}

// Main function to display menu and handle user input
int main() {
    int choice;
    do {
        printf("Phonebook Management System\n");
        printf("1. Add contact\n");
        printf("2. Search contact\n");
        printf("3. Display all contacts\n");
        printf("4. Delete a contact\n");
        printf("5. Edit a contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                search_contact();
                break;
            case 3:
                display_contacts();
                break;
            case 4:
                delete_contact() ;
                break;
            case 5:
                edit_contact() ;
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
        printf("\n");
    } while (choice != 6);
    return 0;
}
