#include "hospital.h"

int doctorLogin(void) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int attempts;
    int i;
    int found;
    int doctorId;

    printf("\n--- Doctor Login ---\n");

    attempts = 0;

    while(attempts < 3) {
        printf("\nEnter Username: ");
        fgets(username, MAX_USERNAME, stdin);
        username[strcspn(username, "\n")] = 0;

        printf("Enter Password: ");
        fgets(password, MAX_PASSWORD, stdin);
        password[strcspn(password, "\n")] = 0;

        found = 0;
        i = 0;
        doctorId = -1;

        while(i < doctorCount) {
            if(doctors[i].isRegistered == 1) {
                if(strcmp(doctors[i].username, username) == 0) {
                    if(strcmp(doctors[i].password, password) == 0) {
                        found = 1;
                        doctorId = doctors[i].id;
                        break;
                    }
                }
            }
            i = i + 1;
        }

        if(found == 1) {
            printf("\nLogin Successful!\n");
            printf("Welcome, Dr. %s\n", doctors[i].name);
            pressEnter();
            return doctorId;
        } else {
            attempts = attempts + 1;
            printf("\nInvalid username or password!\n");
            printf("Attempts remaining: %d\n", 3 - attempts);
        }
    }

    printf("\nLogin failed! Maximum attempts reached.\n");
    pressEnter();
    return -1;
}

void doctorRegister(void) {
    int newId;
    char password2[MAX_PASSWORD];
    int passwordMatch;
    int usernameValid;

    if(doctorCount >= MAX_DOCTORS) {
        printf("\nError: Doctor database is full!\n");
        pressEnter();
        return;
    }

    printf("\n--- Doctor Registration ---\n");

    /* Auto-generate ID */
    if(doctorCount == 0) {
        newId = 1;
    } else {
        newId = doctors[doctorCount - 1].id + 1;
    }
    doctors[doctorCount].id = newId;

    /* Get doctor details */
    printf("Enter Your Name: ");
    fgets(doctors[doctorCount].name, MAX_NAME, stdin);
    doctors[doctorCount].name[strcspn(doctors[doctorCount].name, "\n")] = 0;

    printf("Enter Specialization: ");
    fgets(doctors[doctorCount].specialization, 50, stdin);
    doctors[doctorCount].specialization[strcspn(doctors[doctorCount].specialization, "\n")] = 0;

    printf("Enter Contact Number: ");
    fgets(doctors[doctorCount].contact, MAX_CONTACT, stdin);
    doctors[doctorCount].contact[strcspn(doctors[doctorCount].contact, "\n")] = 0;

    printf("Enter Years of Experience: ");
    scanf("%d", &doctors[doctorCount].experience);
    clearBuffer();

    printf("Enter Consultation Fee: ");
    scanf("%f", &doctors[doctorCount].consultationFee);
    clearBuffer();

    /* Get unique username */
    usernameValid = 0;
    while(usernameValid == 0) {
        printf("\nCreate Username: ");
        fgets(doctors[doctorCount].username, MAX_USERNAME, stdin);
        doctors[doctorCount].username[strcspn(doctors[doctorCount].username, "\n")] = 0;

        if(checkUsernameExists(doctors[doctorCount].username) == 1) {
            printf("Username already exists! Please choose another.\n");
        } else {
            usernameValid = 1;
        }
    }

    /* Get password with confirmation */
    passwordMatch = 0;
    while(passwordMatch == 0) {
        printf("Create Password: ");
        fgets(doctors[doctorCount].password, MAX_PASSWORD, stdin);
        doctors[doctorCount].password[strcspn(doctors[doctorCount].password, "\n")] = 0;

        printf("Confirm Password: ");
        fgets(password2, MAX_PASSWORD, stdin);
        password2[strcspn(password2, "\n")] = 0;

        if(strcmp(doctors[doctorCount].password, password2) == 0) {
            passwordMatch = 1;
        } else {
            printf("Passwords do not match! Please try again.\n\n");
        }
    }

    doctors[doctorCount].isRegistered = 1;

    doctorCount = doctorCount + 1;
    saveDoctors();

    printf("\nRegistration Successful!\n");
    printf("Your Doctor ID is: %d\n", newId);
    printf("You can now login with your username and password.\n");
    pressEnter();
}

void doctorDashboard(int doctorId) {
    int choice;
    int running;
    int index;

    index = searchDoctorByID(doctorId);

    if(index == -1) {
        printf("\nError: Doctor not found!\n");
        return;
    }

    running = 1;

    while(running == 1) {
        printf("\n");
        printf("=========================================\n");
        printf("       DOCTOR DASHBOARD\n");
        printf("   Welcome, Dr. %s\n", doctors[index].name);
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

        switch(choice) {
            case DASHBOARD_MY_PATIENTS:
                viewMyPatients(doctorId);
                break;
            case DASHBOARD_MY_APPOINTMENTS:
                viewMyAppointments(doctorId);
                break;
            case DASHBOARD_MY_RECORDS:
                viewMyRecords(doctorId);
                break;
            case DASHBOARD_ADD_RECORD:
                addDiagnosis(doctorId);
                break;
            case DASHBOARD_LOGOUT:
                printf("\nLogging out...\n");
                running = 0;
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    }
}

void viewMyPatients(int doctorId) {
    int i;
    int j;
    int found;
    int patientIndex;
    int patientIds[MAX_PATIENTS];
    int uniqueCount;
    int alreadyAdded;

    printf("\n--- My Patients ---\n");

    uniqueCount = 0;
    i = 0;

    /* Find all unique patients treated by this doctor */
    while(i < recordCount) {
        if(records[i].doctorId == doctorId) {
            alreadyAdded = 0;
            j = 0;

            while(j < uniqueCount) {
                if(patientIds[j] == records[i].patientId) {
                    alreadyAdded = 1;
                    break;
                }
                j = j + 1;
            }

            if(alreadyAdded == 0) {
                patientIds[uniqueCount] = records[i].patientId;
                uniqueCount = uniqueCount + 1;
            }
        }
        i = i + 1;
    }

    if(uniqueCount == 0) {
        printf("You have not treated any patients yet.\n");
        pressEnter();
        return;
    }

    printf("Total Patients: %d\n\n", uniqueCount);

    i = 0;
    while(i < uniqueCount) {
        patientIndex = searchPatientByID(patientIds[i]);

        if(patientIndex != -1) {
            printf("Patient ID: %d\n", patients[patientIndex].id);
            printf("Name: %s\n", patients[patientIndex].name);
            printf("Age: %d\n", patients[patientIndex].age);
            printf("Disease: %s\n", patients[patientIndex].disease);
            printf("Contact: %s\n\n", patients[patientIndex].contact);
        }

        i = i + 1;
    }

    pressEnter();
}
