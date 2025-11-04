#include "hospital.h"

void viewMyAppointments(int doctorId) {
    int i;
    int found;
    int patientIndex;

    printf("\n--- My Appointments ---\n");

    found = 0;
    i = 0;

    while(i < appointmentCount) {
        if(appointments[i].doctorId == doctorId) {
            if(found == 0) {
                printf("%-10s %-15s %-12s %-10s %-20s\n",
                       "Appt ID", "Patient Name", "Date", "Time", "Status");
                printf("----------------------------------------------------------------\n");
                found = 1;
            }

            patientIndex = searchPatientByID(appointments[i].patientId);

            if(patientIndex != -1) {
                printf("%-10d %-15s %-12s %-10s %-20s\n",
                       appointments[i].appointmentId,
                       patients[patientIndex].name,
                       appointments[i].date,
                       appointments[i].time,
                       appointments[i].status);
            }
        }
        i = i + 1;
    }

    if(found == 0) {
        printf("No appointments found.\n");
    }

    pressEnter();
}

void viewMyRecords(int doctorId) {
    int i;
    int found;
    int patientIndex;

    printf("\n--- My Medical Records ---\n");

    found = 0;
    i = 0;

    while(i < recordCount) {
        if(records[i].doctorId == doctorId) {
            if(found == 0) {
                found = 1;
            }

            patientIndex = searchPatientByID(records[i].patientId);

            printf("\n--- Record #%d ---\n", records[i].recordId);

            if(patientIndex != -1) {
                printf("Patient: %s (ID: %d)\n",
                       patients[patientIndex].name,
                       patients[patientIndex].id);
            } else {
                printf("Patient ID: %d\n", records[i].patientId);
            }

            printf("Visit Date: %s\n", records[i].visitDate);
            printf("Diagnosis: %s\n", records[i].diagnosis);
            printf("Prescription: %s\n", records[i].prescription);
            printf("Treatment Cost: Rs. %.2f\n", records[i].treatmentCost);
        }
        i = i + 1;
    }

    if(found == 0) {
        printf("No medical records found.\n");
    }

    pressEnter();
}

void doctorMenu(void) {
    int choice;
    int running;

    running = 1;

    while(running == 1) {
        printf("\n");
        showHeader("DOCTOR MANAGEMENT");
        printf("1. Add Doctor (Manual)\n");
        printf("2. View All Doctors\n");
        printf("3. Search Doctor\n");
        printf("4. Update Doctor\n");
        printf("5. Back to Admin Menu\n");
        printf("=========================================\n");
           printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);

        clearBuffer();

        switch(choice) {
            case DOCTOR_ADD:
                addDoctor();
                break;
            case DOCTOR_VIEW:
                viewAllDoctors();
                break;
            case DOCTOR_SEARCH:
                searchDoctor();
                break;
            case DOCTOR_UPDATE:
                updateDoctor();
                break;
            case DOCTOR_BACK:
                running = 0;
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    }
}

void addDoctor(void) {
    int newId;

    if(doctorCount >= MAX_DOCTORS) {
        printf("\nError: Doctor database is full!\n");
        pressEnter();
        return;
    }

    printf("\n--- Add Doctor (Admin) ---\n");

    if(doctorCount == 0) {
        newId = 1;
    } else {
        newId = doctors[doctorCount - 1].id + 1;
    }
    doctors[doctorCount].id = newId;

    printf("Enter Doctor Name: ");
    fgets(doctors[doctorCount].name, MAX_NAME, stdin);
    doctors[doctorCount].name[strcspn(doctors[doctorCount].name, "\n")] = 0;

    printf("Enter Specialization: ");
    fgets(doctors[doctorCount].specialization, 50, stdin);
    doctors[doctorCount].specialization[strcspn(doctors[doctorCount].specialization, "\n")] = 0;

    printf("Enter Contact: ");
    fgets(doctors[doctorCount].contact, MAX_CONTACT, stdin);
    doctors[doctorCount].contact[strcspn(doctors[doctorCount].contact, "\n")] = 0;

    printf("Enter Experience (years): ");
    scanf("%d", &doctors[doctorCount].experience);
    clearBuffer();

    printf("Enter Consultation Fee: ");
    scanf("%f", &doctors[doctorCount].consultationFee);
    clearBuffer();

    strcpy(doctors[doctorCount].username, "");
    strcpy(doctors[doctorCount].password, "");
    doctors[doctorCount].isRegistered = 0;

    doctorCount = doctorCount + 1;
    saveDoctors();

    printf("\nDoctor added successfully! Doctor ID: %d\n", newId);
    pressEnter();
}

void viewAllDoctors(void) {
    int i;

    if(doctorCount == 0) {
        printf("\nNo doctors found!\n");
        pressEnter();
        return;
    }

    printf("\n--- All Doctors ---\n");
    printf("%-5s %-20s %-20s %-8s %-10s\n",
           "ID", "Name", "Specialization", "Exp", "Fee");
    printf("------------------------------------------------------------------------\n");

    i = 0;
    while(i < doctorCount) {
        printf("%-5d %-20s %-20s %-8d Rs.%-10.2f\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialization,
               doctors[i].experience,
               doctors[i].consultationFee);
        i = i + 1;
    }

    pressEnter();
}

void searchDoctor(void) {
    int searchType;
    int searchId;
    char searchSpec[50];
    int i;
    int found;

    printf("\n--- Search Doctor ---\n");
    printf("1. Search by ID\n");
    printf("2. Search by Specialization\n");
    printf("Enter search type: ");
    scanf("%d", &searchType);
    clearBuffer();

    if(searchType == 1) {
        printf("Enter Doctor ID: ");
        scanf("%d", &searchId);
        clearBuffer();

        i = searchDoctorByID(searchId);

        if(i != -1) {
            printf("\n--- Doctor Found ---\n");
            printf("ID: %d\n", doctors[i].id);
            printf("Name: %s\n", doctors[i].name);
            printf("Specialization: %s\n", doctors[i].specialization);
            printf("Contact: %s\n", doctors[i].contact);
            printf("Experience: %d years\n", doctors[i].experience);
            printf("Consultation Fee: Rs. %.2f\n", doctors[i].consultationFee);
        } else {
            printf("\nDoctor not found!\n");
        }
    } else if(searchType == 2) {
        printf("Enter Specialization: ");
        fgets(searchSpec, 50, stdin);
        searchSpec[strcspn(searchSpec, "\n")] = 0;

        found = 0;
        i = 0;

        while(i < doctorCount) {
            if(strstr(doctors[i].specialization, searchSpec) != NULL) {
                if(found == 0) {
                    printf("\n--- Search Results ---\n");
                }
                printf("\nID: %d\n", doctors[i].id);
                printf("Name: %s\n", doctors[i].name);
                printf("Specialization: %s\n", doctors[i].specialization);
                printf("Fee: Rs. %.2f\n", doctors[i].consultationFee);
                found = 1;
            }
            i = i + 1;
        }

        if(found == 0) {
            printf("\nNo doctors found with that specialization!\n");
        }
    }

    pressEnter();
}

void updateDoctor(void) {
    int searchId;
    int index;
    float newFee;

    printf("\n--- Update Doctor ---\n");
    printf("Enter Doctor ID: ");
    scanf("%d", &searchId);
    clearBuffer();

    index = searchDoctorByID(searchId);

    if(index == -1) {
        printf("\nDoctor not found!\n");
        pressEnter();
        return;
    }

    printf("\nCurrent Fee: Rs. %.2f\n", doctors[index].consultationFee);
    printf("Enter New Consultation Fee: ");
    scanf("%f", &newFee);
    clearBuffer();

    doctors[index].consultationFee = newFee;
    saveDoctors();

    printf("\nDoctor updated successfully!\n");
    pressEnter();
}
