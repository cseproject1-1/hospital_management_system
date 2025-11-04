#include "hospital.h"

void patientMenu(void) {
    int choice;
    int running;

    running = 1;

    while(running == 1) {
        printf("\n");
        showHeader("PATIENT MANAGEMENT");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Back to Admin Menu\n");
        printf("=========================================\n");
        printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);

        clearBuffer();

        switch(choice) {
            case PATIENT_ADD:
                addPatient();
                break;
            case PATIENT_VIEW:
                viewAllPatients();
                break;
            case PATIENT_SEARCH:
                searchPatient();
                break;
            case PATIENT_UPDATE:
                updatePatient();
                break;
            case PATIENT_DELETE:
                deletePatient();
                break;
            case PATIENT_BACK:
                running = 0;
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    }
}

void addPatient(void) {
    int newId;
    int valid;

    if(patientCount >= MAX_PATIENTS) {
        printf("\nError: Patient database is full!\n");
        pressEnter();
        return;
    }

    printf("\n--- Add New Patient ---\n");

    /* Auto-generate ID */
    if(patientCount == 0) {
        newId = 1;
    } else {
        newId = patients[patientCount - 1].id + 1;
    }
    patients[patientCount].id = newId;

    /* Get patient name */
    printf("Enter Patient Name: ");
    fgets(patients[patientCount].name, MAX_NAME, stdin);
    patients[patientCount].name[strcspn(patients[patientCount].name, "\n")] = 0;

    /* Get age with validation */
    valid = 0;
    while(valid == 0) {
        printf("Enter Age (0-120): ");
        scanf("%d", &patients[patientCount].age);
        clearBuffer();

        if(patients[patientCount].age >= 0 && patients[patientCount].age <= 120) {
            valid = 1;
        } else {
            printf("Invalid age! Please enter between 0 and 120.\n");
        }
    }

    /* Get gender with validation */
    valid = 0;
    while(valid == 0) {
        printf("Enter Gender (M/F): ");
        scanf("%c", &patients[patientCount].gender);
        clearBuffer();

        if(patients[patientCount].gender == 'M' || patients[patientCount].gender == 'm' ||
           patients[patientCount].gender == 'F' || patients[patientCount].gender == 'f') {
            if(patients[patientCount].gender == 'm') {
                patients[patientCount].gender = 'M';
            }
            if(patients[patientCount].gender == 'f') {
                patients[patientCount].gender = 'F';
            }
            valid = 1;
        } else {
            printf("Invalid gender! Please enter M or F.\n");
        }
    }

    /* Get blood group with validation */
    valid = 0;
    while(valid == 0) {
        printf("Enter Blood Group (A+, A-, B+, B-, AB+, AB-, O+, O-): ");
        fgets(patients[patientCount].bloodGroup, 5, stdin);
        patients[patientCount].bloodGroup[strcspn(patients[patientCount].bloodGroup, "\n")] = 0;

        if(strcmp(patients[patientCount].bloodGroup, "A+") == 0 ||
           strcmp(patients[patientCount].bloodGroup, "A-") == 0 ||
           strcmp(patients[patientCount].bloodGroup, "B+") == 0 ||
           strcmp(patients[patientCount].bloodGroup, "B-") == 0 ||
           strcmp(patients[patientCount].bloodGroup, "AB+") == 0 ||
           strcmp(patients[patientCount].bloodGroup, "AB-") == 0 ||
           strcmp(patients[patientCount].bloodGroup, "O+") == 0 ||
           strcmp(patients[patientCount].bloodGroup, "O-") == 0) {
            valid = 1;
        } else {
            printf("Invalid blood group!\n");
        }
    }

    /* Get contact */
    printf("Enter Contact Number (10 digits): ");
    fgets(patients[patientCount].contact, MAX_CONTACT, stdin);
    patients[patientCount].contact[strcspn(patients[patientCount].contact, "\n")] = 0;

    /* Get address */
    printf("Enter Address: ");
    fgets(patients[patientCount].address, MAX_ADDRESS, stdin);
    patients[patientCount].address[strcspn(patients[patientCount].address, "\n")] = 0;

    /* Get disease */
    printf("Enter Disease/Condition: ");
    fgets(patients[patientCount].disease, 50, stdin);
    patients[patientCount].disease[strcspn(patients[patientCount].disease, "\n")] = 0;

    /* Get admission date */
    printf("Enter Admission Date (DD/MM/YYYY): ");
    fgets(patients[patientCount].admissionDate, 15, stdin);
    patients[patientCount].admissionDate[strcspn(patients[patientCount].admissionDate, "\n")] = 0;

    patientCount = patientCount + 1;
    savePatients();

    printf("\nPatient added successfully! Patient ID: %d\n", newId);
    pressEnter();
}

void viewAllPatients(void) {
    int i;

    if(patientCount == 0) {
        printf("\nNo patients found!\n");
        pressEnter();
        return;
    }

    printf("\n--- All Patients ---\n");
    printf("%-5s %-20s %-5s %-7s %-10s %-15s %-20s\n",
           "ID", "Name", "Age", "Gender", "Blood", "Contact", "Disease");
    printf("--------------------------------------------------------------------------------\n");

    i = 0;
    while(i < patientCount) {
        printf("%-5d %-20s %-5d %-7c %-10s %-15s %-20s\n",
               patients[i].id,
               patients[i].name,
               patients[i].age,
               patients[i].gender,
               patients[i].bloodGroup,
               patients[i].contact,
               patients[i].disease);
        i = i + 1;
    }

    pressEnter();
}

void searchPatient(void) {
    int searchType;
    int searchId;
    char searchName[MAX_NAME];
    int i;
    int found;

    printf("\n--- Search Patient ---\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter search type: ");
    scanf("%d", &searchType);
    clearBuffer();

    if(searchType == 1) {
        printf("Enter Patient ID: ");
        scanf("%d", &searchId);
        clearBuffer();

        i = searchPatientByID(searchId);

        if(i != -1) {
            printf("\n--- Patient Found ---\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Gender: %c\n", patients[i].gender);
            printf("Blood Group: %s\n", patients[i].bloodGroup);
            printf("Contact: %s\n", patients[i].contact);
            printf("Address: %s\n", patients[i].address);
            printf("Disease: %s\n", patients[i].disease);
            printf("Admission Date: %s\n", patients[i].admissionDate);
        } else {
            printf("\nPatient not found!\n");
        }
    } else if(searchType == 2) {
        printf("Enter Patient Name: ");
        fgets(searchName, MAX_NAME, stdin);
        searchName[strcspn(searchName, "\n")] = 0;

        found = 0;
        i = 0;

        while(i < patientCount) {
            if(strstr(patients[i].name, searchName) != NULL) {
                if(found == 0) {
                    printf("\n--- Search Results ---\n");
                }
                printf("\nID: %d\n", patients[i].id);
                printf("Name: %s\n", patients[i].name);
                printf("Age: %d\n", patients[i].age);
                printf("Disease: %s\n", patients[i].disease);
                found = 1;
            }
            i = i + 1;
        }

        if(found == 0) {
            printf("\nNo patients found with that name!\n");
        }
    }

    pressEnter();
}
