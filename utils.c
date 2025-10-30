// utils.c - Utility and helper functions

#include "hospital.h"

void clearBuffer() {
    int c;
    while(1) {
        c = getchar();
        if(c == '\n' || c == EOF) {
            break;
        }
    }
}

void pressEnter() {
    printf("\nPress Enter to continue...");
    getchar();
}

void showHeader(char *title) {
    printf("\n");
    printf("====================================\n");
    printf("  %s\n", title);
    printf("====================================\n");
    printf("\n");
}

int searchPatientByID(int id) {
    int i;

    // Simple loop to search
    for(i = 0; i < patientCount; i = i + 1) {
        if(patients[i].id == id) {
            return i;
        }
    }

    return -1;
}

int searchDoctorByID(int id) {
    int i;

    // Simple loop to search
    for(i = 0; i < doctorCount; i = i + 1) {
        if(doctors[i].id == id) {
            return i;
        }
    }

    return -1;
}

int searchAppointmentByID(int id) {
    int i;

    // Simple loop to search
    for(i = 0; i < appointmentCount; i = i + 1) {
        if(appointments[i].appointmentId == id) {
            return i;
        }
    }

    return -1;
}

int checkUsernameExists(char username[]) {
    int i;

    // Check if username already exists
    for(i = 0; i < doctorCount; i = i + 1) {
        if(strcmp(doctors[i].username, username) == 0) {
            return 1; // Username exists
        }
    }

    return 0; // Username doesn't exist
}
