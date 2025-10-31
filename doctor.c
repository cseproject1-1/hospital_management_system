// doctor.c - Doctor management and authentication functions

#include "hospital.h"

// Doctor Login Function
int doctorLogin() {
    char username[30];
    char password[30];
    int attempts = 0;
    int maxAttempts = 3;

    showHeader("DOCTOR LOGIN");

    while(attempts < maxAttempts) {
        printf("Enter username: ");
        scanf("%s", username);
        clearBuffer();

        printf("Enter password: ");
        scanf("%s", password);
        clearBuffer();

        // Check if username and password match
        int i;
        for(i = 0; i < doctorCount; i = i + 1) {
            if(doctors[i].isRegistered == 1) {
                if(strcmp(doctors[i].username, username) == 0) {
                    if(strcmp(doctors[i].password, password) == 0) {
                        printf("\n*** Login successful! ***\n");
                        printf("Welcome Dr. %s\n", doctors[i].name);
                        pressEnter();
                        return doctors[i].id; // Return doctor ID
                    }
                }
            }
        }

        attempts = attempts + 1;
        printf("\n*** Invalid username or password! ***\n");
        printf("Attempts remaining: %d\n\n", maxAttempts - attempts);
    }

    printf("\n*** Too many failed attempts! Access denied. ***\n");
    pressEnter();
    return -1; // Login failed
}

// Doctor Registration Function
void doctorRegister() {
    showHeader("DOCTOR REGISTRATION");

    // Check if full
    if(doctorCount >= MAX_DOCTORS) {
        printf("\nDatabase full! Cannot register more doctors.\n");
        pressEnter();
        return;
    }

    struct Doctor newDoctor;

    // Auto generate ID
    newDoctor.id = doctorCount + 1;
    printf("Doctor ID: %d (Auto-generated)\n\n", newDoctor.id);

    // Get doctor name
    printf("Enter your full name: ");
    fgets(newDoctor.name, 50, stdin);
    int len = strlen(newDoctor.name);
    if(newDoctor.name[len-1] == '\n') {
        newDoctor.name[len-1] = '\0';
    }

    // Get specialization
    printf("Enter specialization (e.g., Cardiology, Neurology): ");
    fgets(newDoctor.specialization, 50, stdin);
    len = strlen(newDoctor.specialization);
    if(newDoctor.specialization[len-1] == '\n') {
        newDoctor.specialization[len-1] = '\0';
    }

    // Get contact
    printf("Enter contact number: ");
    scanf("%s", newDoctor.contact);
    clearBuffer();

    // Get experience
    printf("Enter years of experience: ");
    scanf("%d", &newDoctor.experience);
    clearBuffer();

    // Get consultation fee
    printf("Enter consultation fee: $");
    scanf("%f", &newDoctor.consultationFee);
    clearBuffer();

    // Get username - check if exists
    int usernameValid = 0;
    while(usernameValid == 0) {
        printf("\nEnter username (for login): ");
        scanf("%s", newDoctor.username);
        clearBuffer();

        if(checkUsernameExists(newDoctor.username) == 1) {
            printf("*** Username already exists! Try another. ***\n");
        }
        else {
            usernameValid = 1;
        }
    }

    // Get password
    printf("Enter password: ");
    scanf("%s", newDoctor.password);
    clearBuffer();

    // Confirm password
    char confirmPassword[30];
    printf("Confirm password: ");
    scanf("%s", confirmPassword);
    clearBuffer();

    if(strcmp(newDoctor.password, confirmPassword) != 0) {
        printf("\n*** Passwords do not match! Registration failed. ***\n");
        pressEnter();
        return;
    }

    // Mark as registered
    newDoctor.isRegistered = 1;

    // Add to array
    doctors[doctorCount] = newDoctor;
    doctorCount = doctorCount + 1;

    // Save to file
    saveDoctors();

    printf("\n*** Registration successful! ***\n");
    printf("Doctor ID: %d\n", newDoctor.id);
    printf("Name: Dr. %s\n", newDoctor.name);
    printf("Username: %s\n", newDoctor.username);
    printf("\nYou can now login with your credentials.\n");
    pressEnter();
}

// Doctor Dashboard - after login
void doctorDashboard(int doctorId) {
    int choice;

    // Find doctor name
    char doctorName[50] = "Doctor";
    int i;
    for(i = 0; i < doctorCount; i = i + 1) {
        if(doctors[i].id == doctorId) {
            strcpy(doctorName, doctors[i].name);
            break;
        }
    }

    while(1) {
        printf("\n=========================================\n");
        printf("   DOCTOR DASHBOARD\n");
        printf("   Welcome, Dr. %s\n", doctorName);
        printf("=========================================\n");
        printf("1. View My Patients\n");
        printf("2. View My Appointments\n");
        printf("3. View My Medical Records\n");
        printf("4. Add Medical Record\n");
        printf("5. Logout\n");
        printf("=========================================\n");
         printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);
        clearBuffer();

        if(choice == 1) {
            viewMyPatients(doctorId);
        }
        else if(choice == 2) {
            viewMyAppointments(doctorId);
        }
        else if(choice == 3) {
            viewMyRecords(doctorId);
        }
        else if(choice == 4) {
            // Add medical record for this doctor
            addDiagnosis();
        }
        else if(choice == 5) {
            printf("\nLogging out...\n");
            printf("Goodbye Dr. %s!\n", doctorName);
            pressEnter();
            break;
        }
        else {
            printf("\nInvalid choice!\n");
        }

        if(choice != 5) {
            pressEnter();
        }
    }
}

// View patients treated by this doctor
void viewMyPatients(int doctorId) {
    showHeader("MY PATIENTS");

    printf("Patients treated by you:\n\n");

    int found = 0;
    int i, j;

    // Go through all records
    for(i = 0; i < recordCount; i = i + 1) {
        if(records[i].doctorId == doctorId) {
            // Find patient details
            for(j = 0; j < patientCount; j = j + 1) {
                if(patients[j].id == records[i].patientId) {
                    if(found == 0) {
                        printf("%-5s %-20s %-5s %-10s %-20s\n",
                               "ID", "Name", "Age", "Blood", "Disease");
                        printf("----------------------------------------------------------------\n");
                        found = 1;
                    }

                    printf("%-5d %-20s %-5d %-10s %-20s\n",
                           patients[j].id,
                           patients[j].name,
                           patients[j].age,
                           patients[j].bloodGroup,
                           patients[j].disease);
                    break;
                }
            }
        }
    }

    if(found == 0) {
        printf("You have not treated any patients yet.\n");
    }
}

// View appointments for this doctor
void viewMyAppointments(int doctorId) {
    showHeader("MY APPOINTMENTS");

    printf("Your scheduled appointments:\n\n");

    int found = 0;
    int i, j;

    for(i = 0; i < appointmentCount; i = i + 1) {
        if(appointments[i].doctorId == doctorId) {
            if(found == 0) {
                printf("%-6s %-20s %-12s %-8s %-15s\n",
                       "Appt ID", "Patient", "Date", "Time", "Status");
                printf("----------------------------------------------------------------\n");
                found = 1;
            }

            // Find patient name
            char pname[50] = "Unknown";
            for(j = 0; j < patientCount; j = j + 1) {
                if(patients[j].id == appointments[i].patientId) {
                    strcpy(pname, patients[j].name);
                    break;
                }
            }

            printf("%-6d %-20s %-12s %-8s %-15s\n",
                   appointments[i].appointmentId,
                   pname,
                   appointments[i].date,
                   appointments[i].time,
                   appointments[i].status);
        }
    }

    if(found == 0) {
        printf("You have no appointments scheduled.\n");
    }
}

// View medical records created by this doctor
void viewMyRecords(int doctorId) {
    showHeader("MY MEDICAL RECORDS");

    printf("Medical records created by you:\n\n");

    int found = 0;
    int i, j;

    for(i = 0; i < recordCount; i = i + 1) {
        if(records[i].doctorId == doctorId) {
            // Find patient name
            char pname[50] = "Unknown";
            for(j = 0; j < patientCount; j = j + 1) {
                if(patients[j].id == records[i].patientId) {
                    strcpy(pname, patients[j].name);
                    break;
                }
            }

            printf("Record ID: %d\n", records[i].recordId);
            printf("Patient: %s\n", pname);
            printf("Date: %s\n", records[i].visitDate);
            printf("Diagnosis: %s\n", records[i].diagnosis);
            printf("Prescription: %s\n", records[i].prescription);
            printf("Cost: $%.2f\n", records[i].treatmentCost);
            printf("========================================\n");
            found = 1;
        }
    }

    if(found == 0) {
        printf("You have not created any medical records yet.\n");
    }
}

// Admin functions for doctor management
void doctorMenu() {
    int choice;

    while(1) {
        showHeader("DOCTOR MANAGEMENT (ADMIN)");
        printf("1. Add Doctor (Manual)\n");
        printf("2. View All Doctors\n");
        printf("3. Search Doctor\n");
        printf("4. Update Doctor\n");
        printf("5. Back to Admin Menu\n");
         printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);
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
    showHeader("ADD DOCTOR (MANUAL)");

    if(doctorCount >= MAX_DOCTORS) {
        printf("\nDatabase full! Cannot add more doctors.\n");
        return;
    }

    struct Doctor d;

    d.id = doctorCount + 1;
    printf("Doctor ID: %d\n\n", d.id);

    printf("Enter doctor name: ");
    fgets(d.name, 50, stdin);
    int len = strlen(d.name);
    if(d.name[len-1] == '\n') {
        d.name[len-1] = '\0';
    }

    printf("Enter specialization: ");
    fgets(d.specialization, 50, stdin);
    len = strlen(d.specialization);
    if(d.specialization[len-1] == '\n') {
        d.specialization[len-1] = '\0';
    }

    printf("Enter contact number: ");
    scanf("%s", d.contact);
    clearBuffer();

    printf("Enter years of experience: ");
    scanf("%d", &d.experience);
    clearBuffer();

    printf("Enter consultation fee: ");
    scanf("%f", &d.consultationFee);
    clearBuffer();

    printf("Enter username: ");
    scanf("%s", d.username);
    clearBuffer();

    printf("Enter password: ");
    scanf("%s", d.password);
    clearBuffer();

    d.isRegistered = 1;

    doctors[doctorCount] = d;
    doctorCount = doctorCount + 1;

    saveDoctors();

    printf("\nDoctor added successfully!\n");
    printf("Doctor ID: %d, Name: Dr. %s\n", d.id, d.name);
}

void viewAllDoctors() {
    showHeader("ALL DOCTORS LIST");

    if(doctorCount == 0) {
        printf("\nNo doctors found!\n");
        return;
    }

    printf("\nTotal Doctors: %d\n\n", doctorCount);

    printf("%-5s %-20s %-20s %-15s %-8s %-10s %-15s\n",
           "ID", "Name", "Specialization", "Contact", "Exp(Yrs)", "Fee", "Username");
    printf("--------------------------------------------------------------------------------------------\n");

    int i;
    for(i = 0; i < doctorCount; i = i + 1) {
        printf("%-5d %-20s %-20s %-15s %-8d $%-9.2f %-15s\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialization,
               doctors[i].contact,
               doctors[i].experience,
               doctors[i].consultationFee,
               doctors[i].username);
    }
}

void searchDoctor() {
    int choice;

    showHeader("SEARCH DOCTOR");
    printf("1. Search by ID\n");
    printf("2. Search by Specialization\n");
     printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);
        clearBuffer();

    if(choice == 1) {
        int id;
        printf("\nEnter Doctor ID: ");
        scanf("%d", &id);
        clearBuffer();

        int found = 0;
        int i;
        for(i = 0; i < doctorCount; i = i + 1) {
            if(doctors[i].id == id) {
                printf("\nDoctor Found!\n");
                printf("----------------------------------------\n");
                printf("Doctor ID:        %d\n", doctors[i].id);
                printf("Name:             Dr. %s\n", doctors[i].name);
                printf("Specialization:   %s\n", doctors[i].specialization);
                printf("Contact:          %s\n", doctors[i].contact);
                printf("Experience:       %d years\n", doctors[i].experience);
                printf("Consultation Fee: $%.2f\n", doctors[i].consultationFee);
                printf("Username:         %s\n", doctors[i].username);
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

        int found = 0;
        int i;
        printf("\nSearch Results:\n");
        printf("----------------------------------------\n");

        for(i = 0; i < doctorCount; i = i + 1) {
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
    printf("6. Username\n");
    printf("7. Password\n");
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
    else if(choice == 6) {
        printf("Enter new username: ");
        scanf("%s", doctors[index].username);
        clearBuffer();
    }
    else if(choice == 7) {
        printf("Enter new password: ");
        scanf("%s", doctors[index].password);
        clearBuffer();
    }
    else {
        printf("\nInvalid choice!\n");
        return;
    }

    saveDoctors();
    printf("\nDoctor updated successfully!\n");
}
