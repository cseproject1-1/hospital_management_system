// patient.c - Patient management functions

#include "hospital.h"

void patientMenu() {
    int choice;

    while(1) {
        showHeader("PATIENT MANAGEMENT");
        printf("1. Add New Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Back to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        if(choice == 1) {
            addPatient();
        }
        else if(choice == 2) {
            viewAllPatients();
        }
        else if(choice == 3) {
            searchPatient();
        }
        else if(choice == 4) {
            updatePatient();
        }
        else if(choice == 5) {
            deletePatient();
        }
        else if(choice == 6) {
            printf("\nGoing back...\n");
            break;
        }
        else {
            printf("\nWrong choice!\n");
        }

        if(choice != 6) {
            pressEnter();
        }
    }
}

void addPatient() {
    showHeader("ADD NEW PATIENT");

    // Check if full
    if(patientCount >= MAX_PATIENTS) {
        printf("\nDatabase full! Cannot add more patients.\n");
        return;
    }

    // Create new patient
    struct Patient p;

    // Auto ID
    p.id = patientCount + 1;
    printf("Patient ID: %d\n\n", p.id);

    // Get name
    printf("Enter name: ");
    fgets(p.name, 50, stdin);
    int len = strlen(p.name);
    if(p.name[len-1] == '\n') {
        p.name[len-1] = '\0';
    }

    // Get age
    printf("Enter age: ");
    scanf("%d", &p.age);
    clearBuffer();

    // Validate age
    while(p.age < 0 || p.age > 120) {
        printf("Invalid age! Enter again (0-120): ");
        scanf("%d", &p.age);
        clearBuffer();
    }

    // Get gender
    printf("Enter gender (M/F): ");
    scanf("%c", &p.gender);
    clearBuffer();

    // Validate gender
    while(p.gender != 'M' && p.gender != 'F' && p.gender != 'm' && p.gender != 'f') {
        printf("Invalid! Enter M or F: ");
        scanf("%c", &p.gender);
        clearBuffer();
    }

    // Get blood group
    printf("Enter blood group (A+, A-, B+, B-, AB+, AB-, O+, O-): ");
    scanf("%s", p.bloodGroup);
    clearBuffer();

    // Get phone
    printf("Enter phone number: ");
    scanf("%s", p.contact);
    clearBuffer();

    // Get address
    printf("Enter address: ");
    fgets(p.address, 100, stdin);
    len = strlen(p.address);
    if(p.address[len-1] == '\n') {
        p.address[len-1] = '\0';
    }

    // Get disease
    printf("Enter disease: ");
    fgets(p.disease, 50, stdin);
    len = strlen(p.disease);
    if(p.disease[len-1] == '\n') {
        p.disease[len-1] = '\0';
    }

    // Get date
    printf("Enter admission date (DD/MM/YYYY): ");
    scanf("%s", p.admissionDate);
    clearBuffer();

    // Add to array
    patients[patientCount] = p;
    patientCount = patientCount + 1;

    // Save
    savePatients();

    printf("\nPatient added successfully!\n");
    printf("Patient ID: %d, Name: %s\n", p.id, p.name);
}

void viewAllPatients() {
    showHeader("PATIENT LIST");

    // Check if empty
    if(patientCount == 0) {
        printf("\nNo patients found!\n");
        return;
    }

    printf("\nTotal Patients: %d\n\n", patientCount);

    // Print header
    printf("%-5s %-20s %-5s %-8s %-10s %-15s %-20s\n",
           "ID", "Name", "Age", "Gender", "Blood", "Contact", "Disease");
    printf("--------------------------------------------------------------------------------\n");

    // Print all patients using loop
    int i;
    for(i = 0; i < patientCount; i = i + 1) {
        printf("%-5d %-20s %-5d %-8c %-10s %-15s %-20s\n",
               patients[i].id,
               patients[i].name,
               patients[i].age,
               patients[i].gender,
               patients[i].bloodGroup,
               patients[i].contact,
               patients[i].disease);
    }
}

void searchPatient() {
    int choice;

    showHeader("SEARCH PATIENT");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clearBuffer();

    if(choice == 1) {
        int id;
        printf("\nEnter Patient ID: ");
        scanf("%d", &id);
        clearBuffer();

        // Search using loop
        int found = 0;
        int i;
        for(i = 0; i < patientCount; i = i + 1) {
            if(patients[i].id == id) {
                // Patient found
                printf("\nPatient Found!\n");
                printf("----------------------------------------\n");
                printf("Patient ID:       %d\n", patients[i].id);
                printf("Name:             %s\n", patients[i].name);
                printf("Age:              %d years\n", patients[i].age);
                printf("Gender:           %c\n", patients[i].gender);
                printf("Blood Group:      %s\n", patients[i].bloodGroup);
                printf("Contact:          %s\n", patients[i].contact);
                printf("Address:          %s\n", patients[i].address);
                printf("Disease:          %s\n", patients[i].disease);
                printf("Admission Date:   %s\n", patients[i].admissionDate);
                found = 1;
                break;
            }
        }

        if(found == 0) {
            printf("\nPatient with ID %d not found!\n", id);
        }
    }
    else if(choice == 2) {
        char name[50];
        printf("\nEnter patient name: ");
        fgets(name, 50, stdin);
        int len = strlen(name);
        if(name[len-1] == '\n') {
            name[len-1] = '\0';
        }

        // Search using loop
        int found = 0;
        int i;
        for(i = 0; i < patientCount; i = i + 1) {
            if(strcmp(patients[i].name, name) == 0) {
                printf("\nPatient Found!\n");
                printf("ID: %d, Name: %s, Age: %d, Disease: %s\n",
                       patients[i].id, patients[i].name,
                       patients[i].age, patients[i].disease);
                found = 1;
                break;
            }
        }

        if(found == 0) {
            printf("\nPatient '%s' not found!\n", name);
        }
    }
    else {
        printf("\nInvalid choice!\n");
    }
}

void updatePatient() {
    int id;

    showHeader("UPDATE PATIENT");

    printf("Enter Patient ID to update: ");
    scanf("%d", &id);
    clearBuffer();

    // Find patient
    int index = -1;
    int i;
    for(i = 0; i < patientCount; i = i + 1) {
        if(patients[i].id == id) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("\nPatient not found!\n");
        return;
    }

    printf("\nCurrent patient: %s\n", patients[index].name);
    printf("\nWhat to update?\n");
    printf("1. Name\n");
    printf("2. Age\n");
    printf("3. Contact\n");
    printf("4. Address\n");
    printf("5. Disease\n");
    printf("Enter choice: ");

    int choice;
    scanf("%d", &choice);
    clearBuffer();

    if(choice == 1) {
        printf("Enter new name: ");
        fgets(patients[index].name, 50, stdin);
        int len = strlen(patients[index].name);
        if(patients[index].name[len-1] == '\n') {
            patients[index].name[len-1] = '\0';
        }
    }
    else if(choice == 2) {
        printf("Enter new age: ");
        scanf("%d", &patients[index].age);
        clearBuffer();
    }
    else if(choice == 3) {
        printf("Enter new contact: ");
        scanf("%s", patients[index].contact);
        clearBuffer();
    }
    else if(choice == 4) {
        printf("Enter new address: ");
        fgets(patients[index].address, 100, stdin);
        int len = strlen(patients[index].address);
        if(patients[index].address[len-1] == '\n') {
            patients[index].address[len-1] = '\0';
        }
    }
    else if(choice == 5) {
        printf("Enter new disease: ");
        fgets(patients[index].disease, 50, stdin);
        int len = strlen(patients[index].disease);
        if(patients[index].disease[len-1] == '\n') {
            patients[index].disease[len-1] = '\0';
        }
    }
    else {
        printf("\nInvalid choice!\n");
        return;
    }

    savePatients();
    printf("\nPatient updated successfully!\n");
}

void deletePatient() {
    int id;

    showHeader("DELETE PATIENT");

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);
    clearBuffer();

    // Find patient
    int index = -1;
    int i;
    for(i = 0; i < patientCount; i = i + 1) {
        if(patients[i].id == id) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("\nPatient not found!\n");
        return;
    }

    printf("\nAre you sure you want to delete patient '%s'? (Y/N): ",
           patients[index].name);
    char confirm;
    scanf(" %c", &confirm);
    clearBuffer();

    if(confirm == 'Y' || confirm == 'y') {
        // Shift all elements
        for(i = index; i < patientCount - 1; i = i + 1) {
            patients[i] = patients[i + 1];
        }

        patientCount = patientCount - 1;
        savePatients();

        printf("\nPatient deleted successfully!\n");
    }
    else {
        printf("\nDelete cancelled.\n");
    }
}
