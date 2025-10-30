// doctor.c - Doctor management functions

#include "hospital.h"

void doctorMenu() {
    int choice;

    while(1) {
        showHeader("DOCTOR MANAGEMENT");
        printf("1. Add New Doctor\n");
        printf("2. View All Doctors\n");
        printf("3. Search Doctor\n");
        printf("4. Update Doctor\n");
        printf("5. Back to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        if(choice == 1) {
            addDoctor();
        }
        else if(choice == 2) {
            viewAllDoctors();
        }
        else if(choice == 3) {
            searchDoctor();
        }
        else if(choice == 4) {
            updateDoctor();
        }
        else if(choice == 5) {
            printf("\nGoing back...\n");
            break;
        }
        else {
            printf("\nWrong choice!\n");
        }

        if(choice != 5) {
            pressEnter();
        }
    }
}

void addDoctor() {
    showHeader("ADD NEW DOCTOR");

    // Check if full
    if(doctorCount >= MAX_DOCTORS) {
        printf("\nDatabase full! Cannot add more doctors.\n");
        return;
    }

    // Create new doctor
    struct Doctor d;

    // Auto ID
    d.id = doctorCount + 1;
    printf("Doctor ID: %d\n\n", d.id);

    // Get name
    printf("Enter doctor name: ");
    fgets(d.name, 50, stdin);
    int len = strlen(d.name);
    if(d.name[len-1] == '\n') {
        d.name[len-1] = '\0';
    }

    // Get specialization
    printf("Enter specialization: ");
    fgets(d.specialization, 50, stdin);
    len = strlen(d.specialization);
    if(d.specialization[len-1] == '\n') {
        d.specialization[len-1] = '\0';
    }

    // Get contact
    printf("Enter contact number: ");
    scanf("%s", d.contact);
    clearBuffer();

    // Get experience
    printf("Enter years of experience: ");
    scanf("%d", &d.experience);
    clearBuffer();

    // Get fee
    printf("Enter consultation fee: ");
    scanf("%f", &d.consultationFee);
    clearBuffer();

    // Add to array
    doctors[doctorCount] = d;
    doctorCount = doctorCount + 1;

    // Save
    saveDoctors();

    printf("\nDoctor added successfully!\n");
    printf("Doctor ID: %d, Name: Dr. %s\n", d.id, d.name);
}

void viewAllDoctors() {
    showHeader("DOCTOR LIST");

    // Check if empty
    if(doctorCount == 0) {
        printf("\nNo doctors found!\n");
        return;
    }

    printf("\nTotal Doctors: %d\n\n", doctorCount);

    // Print header
    printf("%-5s %-20s %-20s %-15s %-8s %-10s\n",
           "ID", "Name", "Specialization", "Contact", "Exp(Yrs)", "Fee");
    printf("--------------------------------------------------------------------------------\n");

    // Print all doctors using loop
    int i;
    for(i = 0; i < doctorCount; i = i + 1) {
        printf("%-5d %-20s %-20s %-15s %-8d $%-9.2f\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialization,
               doctors[i].contact,
               doctors[i].experience,
               doctors[i].consultationFee);
    }
}

void searchDoctor() {
    int choice;

    showHeader("SEARCH DOCTOR");
    printf("1. Search by ID\n");
    printf("2. Search by Specialization\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clearBuffer();

    if(choice == 1) {
        int id;
        printf("\nEnter Doctor ID: ");
        scanf("%d", &id);
        clearBuffer();

        // Search using loop
        int found = 0;
        int i;
        for(i = 0; i < doctorCount; i = i + 1) {
            if(doctors[i].id == id) {
                // Doctor found
                printf("\nDoctor Found!\n");
                printf("----------------------------------------\n");
                printf("Doctor ID:        %d\n", doctors[i].id);
                printf("Name:             Dr. %s\n", doctors[i].name);
                printf("Specialization:   %s\n", doctors[i].specialization);
                printf("Contact:          %s\n", doctors[i].contact);
                printf("Experience:       %d years\n", doctors[i].experience);
                printf("Consultation Fee: $%.2f\n", doctors[i].consultationFee);
                found = 1;
                break;
            }
        }

        if(found == 0) {
            printf("\nDoctor with ID %d not found!\n", id);
        }
    }
    else if(choice == 2) {
        char spec[50];
        printf("\nEnter specialization: ");
        fgets(spec, 50, stdin);
        int len = strlen(spec);
        if(spec[len-1] == '\n') {
            spec[len-1] = '\0';
        }

        // Search using loop
        int found = 0;
        int i;
        printf("\nSearch Results:\n");
        printf("----------------------------------------\n");

        for(i = 0; i < doctorCount; i = i + 1) {
            // Check if specialization matches
            if(strstr(doctors[i].specialization, spec) != NULL) {
                printf("ID: %d, Dr. %s (%s), Fee: $%.2f\n",
                       doctors[i].id, doctors[i].name,
                       doctors[i].specialization, doctors[i].consultationFee);
                found = 1;
            }
        }

        if(found == 0) {
            printf("No doctors found with specialization '%s'\n", spec);
        }
    }
    else {
        printf("\nInvalid choice!\n");
    }
}

void updateDoctor() {
    int id;

    showHeader("UPDATE DOCTOR");

    printf("Enter Doctor ID to update: ");
    scanf("%d", &id);
    clearBuffer();

    // Find doctor
    int index = -1;
    int i;
    for(i = 0; i < doctorCount; i = i + 1) {
        if(doctors[i].id == id) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("\nDoctor not found!\n");
        return;
    }

    printf("\nCurrent doctor: Dr. %s\n", doctors[index].name);
    printf("\nWhat to update?\n");
    printf("1. Name\n");
    printf("2. Specialization\n");
    printf("3. Contact\n");
    printf("4. Experience\n");
    printf("5. Consultation Fee\n");
    printf("Enter choice: ");

    int choice;
    scanf("%d", &choice);
    clearBuffer();

    if(choice == 1) {
        printf("Enter new name: ");
        fgets(doctors[index].name, 50, stdin);
        int len = strlen(doctors[index].name);
        if(doctors[index].name[len-1] == '\n') {
            doctors[index].name[len-1] = '\0';
        }
    }
    else if(choice == 2) {
        printf("Enter new specialization: ");
        fgets(doctors[index].specialization, 50, stdin);
        int len = strlen(doctors[index].specialization);
        if(doctors[index].specialization[len-1] == '\n') {
            doctors[index].specialization[len-1] = '\0';
        }
    }
    else if(choice == 3) {
        printf("Enter new contact: ");
        scanf("%s", doctors[index].contact);
        clearBuffer();
    }
    else if(choice == 4) {
        printf("Enter new experience (years): ");
        scanf("%d", &doctors[index].experience);
        clearBuffer();
    }
    else if(choice == 5) {
        printf("Enter new consultation fee: ");
        scanf("%f", &doctors[index].consultationFee);
        clearBuffer();
    }
    else {
        printf("\nInvalid choice!\n");
        return;
    }

    saveDoctors();
    printf("\nDoctor updated successfully!\n");
}
