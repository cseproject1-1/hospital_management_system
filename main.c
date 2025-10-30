// main.c - Main program file with authentication

#include "hospital.h"
struct Patient patients[MAX_PATIENTS];
struct Doctor doctors[MAX_DOCTORS];
struct Appointment appointments[MAX_APPOINTMENTS];
struct MedicalRecord records[MAX_RECORDS];

int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;
int recordCount = 0;
// Initialize global variables

int loggedInDoctorId = -1; // -1 means no doctor logged in

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
        printf("1. Doctor Login\n");
        printf("2. Doctor Registration\n");
        printf("3. Admin/Staff Panel\n");
        printf("4. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        // Check choice using if-else
        if(choice == 1) {
            // Doctor Login
            int doctorId = doctorLogin();
            if(doctorId != -1) {
                loggedInDoctorId = doctorId;
                doctorDashboard(doctorId);
                loggedInDoctorId = -1; // Logout after dashboard
            }
        }
        else if(choice == 2) {
            // Doctor Registration
            doctorRegister();
        }
        else if(choice == 3) {
            // Admin/Staff Panel - needs password
            char password[20];
            printf("\nEnter Admin Password: ");
            scanf("%s", password);
            clearBuffer();

            if(strcmp(password, "admin123") == 0) {
                printf("\nAccess Granted!\n");
                pressEnter();

                // Admin submenu
                int adminChoice;
                while(1) {
                    printf("\n=========================================\n");
                    printf("         ADMIN/STAFF PANEL\n");
                    printf("=========================================\n");
                    printf("1. Patient Management\n");
                    printf("2. Doctor Management\n");
                    printf("3. Appointment Management\n");
                    printf("4. Medical Records\n");
                    printf("5. Reports\n");
                    printf("6. Back to Main Menu\n");
                    printf("=========================================\n");
                    printf("Enter your choice: ");
                    scanf("%d", &adminChoice);
                    clearBuffer();

                    if(adminChoice == 1) {
                        patientMenu();
                    }
                    else if(adminChoice == 2) {
                        doctorMenu();
                    }
                    else if(adminChoice == 3) {
                        appointmentMenu();
                    }
                    else if(adminChoice == 4) {
                        medicalRecordsMenu();
                    }
                    else if(adminChoice == 5) {
                        reportsMenu();
                    }
                    else if(adminChoice == 6) {
                        printf("\nReturning to main menu...\n");
                        break;
                    }
                    else {
                        printf("\nInvalid choice! Please try again.\n");
                    }
                }
            }
            else {
                printf("\nAccess Denied! Wrong password.\n");
                pressEnter();
            }
        }
        else if(choice == 4) {
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
