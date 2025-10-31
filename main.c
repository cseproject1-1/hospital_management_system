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


    char banner[]="\n|   \033[1m \033[91m HOSPITAL MANAGEMENT SYSTEM            \033[0m|\n";
    for(int i=15;banner[i]!='\0';i++)
    {
        delay(.5);
        printf("=");
    }
    for(int i=0;banner[i]!=NULL;i++)
    {
        delay(1);
        printf("%c",banner[i]);
    }
     for(int i=15;banner[i]!=NULL;i++)
    {
        delay(.5);
        printf("=");
    }
    printf("\n");
    char banner2[]="\n|  \033[1m \033[91m    MAIN MENU          \033[0m |\n";
    // Main loop
    while(1) {
       for(int i=15;banner2[i]!='\0';i++)
    {
        delay(.5);
        printf("=");
    }
    for(int i=0;banner2[i]!=NULL;i++)
    {
        delay(1);
        printf("%c",banner2[i]);
    }
     for(int i=15;banner2[i]!=NULL;i++)
    {
        delay(.5);
        printf("=");
    }
    printf("\n");delay(2);
        printf("1. Doctor Login\n");delay(2);
        printf("2. Doctor Registration\n");delay(2);
        printf("3. Admin/Staff Panel\n");delay(2);
        printf("4. Exit\n");delay(2);
        printf("=========================================\n");delay(2);
        printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);

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
            printf("\nEnter Admin Password\033[33;6;91m:\033[0m  ");
            printf(YELLOW);scanf("%s", password);printf(RESET);
            clearBuffer();

            if(strcmp(password, "2407020") == 0) {
                printf(GREEN"\nAccess Granted!\n"RESET);
                pressEnter();

                // Admin submenu
                int adminChoice;
                 char banner3[]="\n| \033[91m  \033[1m \033[91m          ADMIN/STAFF PANEL          \033[0m|\n";
                while(1) {system("cls");
                    for(int i=20;banner3[i]!='\0';i++)
                        {
                                delay(.5);
                                printf("=");
                                }
                        for(int i=0;banner3[i]!=NULL;i++)
                    {
                            delay(1);
                            printf("%c",banner3[i]);
                        }
                            for(int i=20;banner3[i]!=NULL;i++)
                            {
                                   delay(.5);
                                    printf("=");
                            }

                    printf("\n");delay(.5);
                    printf("1. Patient Management\n");delay(.5);
                    printf("2. Doctor Management\n");delay(.5);
                    printf("3. Appointment Management\n");delay(.5);
                    printf("4. Medical Records\n");delay(.5);
                    printf("5. Reports\n");delay(.5);
                    printf("6. Back to Main Menu\n");delay(.5);
                    printf("=========================================\n");delay(.5);
                    printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &adminChoice);printf(RESET);

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
                printf(RED"\nAccess Denied! Wrong password.\n"RESET);
                pressEnter();system("cls");
            }
        }
        else if(choice == 4) {system("cls");
          char banner4[]="\n| \033[1m \033[91m Thank you for using HMS! \033[0m|";
          char banner5[]="\n|     \033[1m \033[91m   Goodbye!           \033[0m|\n";
            for(int i=15;banner4[i]!='\0';i++)
    {
        delay(.5);
        printf("=");
    }
    for(int i=0;banner4[i]!=NULL;i++)
    {
        delay(1);
        printf("%c",banner4[i]);
    }
     for(int i=0;banner5[i]!=NULL;i++)
    {
        delay(1);
        printf("%c",banner5[i]);
    }
     for(int i=15;banner4[i]!=NULL;i++)
    {
        delay(.5);
        printf("=");
    }break;
        }

        else {system("cls");
            printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
