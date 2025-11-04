#include "hospital.h"

/* Global variable definitions */
struct Patient patients[MAX_PATIENTS];
struct Doctor doctors[MAX_DOCTORS];
struct Appointment appointments[MAX_APPOINTMENTS];
struct MedicalRecord records[MAX_RECORDS];
int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;
int recordCount = 0;
int loggedInDoctorId = -1;

int main() {
    int choice;
    int loginResult;
    char adminPassword[50];
    int adminChoice;
    int running;

    /* Load all data from files */
    loadPatients();
    loadDoctors();
    loadAppointments();
    loadRecords();
    running = 1;

    while(running == 1) {

        banner();
        printf("1. Doctor Login\n");
        printf("2. Doctor Registration\n");
        printf("3. Admin/Staff Panel\n");
        printf("4. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);
 clearBuffer();
 cls;
        switch(choice) {
            case MAIN_LOGIN:
                loginResult = doctorLogin();
                if(loginResult != -1) {
                    loggedInDoctorId = loginResult;
                    doctorDashboard(loggedInDoctorId);
                    loggedInDoctorId = -1;
                }
                break;

            case MAIN_REGISTER:
                doctorRegister();
                break;

            case MAIN_ADMIN:
                printf("\nEnter Admin Password: ");
                fgets(adminPassword, 50, stdin);
                adminPassword[strcspn(adminPassword, "\n")] = 0;

                if(strcmp(adminPassword, "admin123") == 0) {
                        cls;
                    printf(GREEN"\nAdmin Access Granted!\n"RESET);
                    pressEnter();
                    adminChoice = 0;

                    while(adminChoice != ADMIN_BACK) {
                        printf("\n");
                        showHeader(" ADMIN/STAFF PANEL ");
                        printf("=========================================\n");
                        printf("1. Patient Management\n");
                        printf("2. Doctor Management\n");
                        printf("3. Appointment Management\n");
                        printf("4. Medical Records\n");
                        printf("5. Reports\n");
                        printf("6. Back to Main Menu\n");
                        printf("=========================================\n");
                        printf("Enter your choice\033[33;6;91m:\033[0m ");
                        printf(YELLOW);scanf("%d", &adminChoice);printf(RESET);

                        clearBuffer();

                        switch(adminChoice) {
                            case ADMIN_PATIENT:
                                cls;
                                patientMenu();
                                break;
                            case ADMIN_DOCTOR:
                                cls;
                                doctorMenu();
                                break;
                            case ADMIN_APPOINTMENT:
                                cls;
                                appointmentMenu();
                                break;
                            case ADMIN_RECORDS:
                                cls;
                                medicalRecordsMenu();
                                break;
                            case ADMIN_REPORTS:
                                cls;
                                reportsMenu();
                                break;
                            case ADMIN_BACK:
                                printf(RED"\nReturning to Main Menu...\n"RESET);
                                break;
                            default:
                                printf(RED"\nInvalid choice!\n"RESET);
                        }
                    }
                } else {

                    printf(RED"\nInvalid Password! Access Denied.\n"RESET);
                    pressEnter();
                }
                break;

            case MAIN_EXIT:
                cls;
                    bybanner();
                printf(RED"\nExiting...\n"RESET);
                running = 0;
                break;

            default:
                cls;
                printf(RED"\nInvalid choice! Please try again.\n"RESET);
                pressEnter();
        }
    }

    return 0;
}
