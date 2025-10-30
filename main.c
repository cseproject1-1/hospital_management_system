// main.c - Main program file

#include "hospital.h"

// Initialize global variables
struct Patient patients[MAX_PATIENTS];
struct Doctor doctors[MAX_DOCTORS];
struct Appointment appointments[MAX_APPOINTMENTS];
struct MedicalRecord records[MAX_RECORDS];

int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;
int recordCount = 0;

int main() {
    int choice;

    // Load data from files
    loadPatients();
    loadDoctors();
    loadAppointments();
    loadRecords();

    printf("\n=========================================\n");
    printf("   HOSPITAL MANAGEMENT SYSTEM\n");
    printf("=========================================\n");

    // Main loop
    while(1) {
        printf("\n=========================================\n");
        printf("           MAIN MENU\n");
        printf("=========================================\n");
        printf("1. Patient Management\n");
        printf("2. Doctor Management\n");
        printf("3. Appointment Management\n");
        printf("4. Medical Records\n");
        printf("5. Reports\n");
        printf("6. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        // Check choice using if-else
        if(choice == 1) {
            patientMenu();
        }
        else if(choice == 2) {
            doctorMenu();
        }
        else if(choice == 3) {
            appointmentMenu();
        }
        else if(choice == 4) {
            medicalRecordsMenu();
        }
        else if(choice == 5) {
            reportsMenu();
        }
        else if(choice == 6) {
            printf("\n=========================================\n");
            printf("   Thank you for using HMS!\n");
            printf("   Goodbye!\n");
            printf("=========================================\n");
            break;
        }
        else {
            printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
