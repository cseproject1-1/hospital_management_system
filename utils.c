#include "hospital.h"

void clearBuffer(void) {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void pressEnter(void) {
    printf(YELLOW"\nPress Enter to continue..."RESET);
    getchar();
}
void delay(float sec)
{
    for(long long i=0;i<sec*10000000;i++)
    {
        //loading animation
    }
}
void showHeader(char *title) {
    int i;
    int border_len = 41; // The fixed border length
    int title_len = strlen(title);

    printf("\n");
    for (i = 0; i < border_len; i++) {
        printf("=");
        fflush(stdout);
        delay(.5);
    }
    printf("\n|\t");
    printf(RED "  ");
    printf(BOLD "  ");
    fflush(stdout);
    for (i = 0; i < title_len; i++) {
        printf("%c", title[i]);
        fflush(stdout);
        delay(1);    // Slower delay for typing (0.05 seconds = 50ms)
    }
    printf(RESET "\t\t|\n");

    // --- 3. Animate Bottom Border ---
    for (i = 0; i < border_len; i++) {
        printf("=");
        fflush(stdout);
        delay(0.5);   // 15ms delay
    }
    printf("\n");
}

int searchPatientByID(int id) {
    int i;
    int found;

    found = -1;
    i = 0;

    while(i < patientCount) {
        if(patients[i].id == id) {
            found = i;
            break;
        }
        i = i + 1;
    }

    return found;
}

int searchDoctorByID(int id) {
    int i;
    int found;

    found = -1;
    i = 0;

    while(i < doctorCount) {
        if(doctors[i].id == id) {
            found = i;
            break;
        }
        i = i + 1;
    }

    return found;
}

int searchAppointmentByID(int id) {
    int i;
    int found;

    found = -1;
    i = 0;

    while(i < appointmentCount) {
        if(appointments[i].appointmentId == id) {
            found = i;
            break;
        }
        i = i + 1;
    }

    return found;
}

int checkUsernameExists(char *username) {
    int i;
    int exists;

    exists = 0;
    i = 0;

    while(i < doctorCount) {
        if(strcmp(doctors[i].username, username) == 0) {
            exists = 1;
            break;
        }
        i = i + 1;
    }

    return exists;
}

void banner()
{
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
    printf("\n");

}
void bybanner()
{
      char banner4[]="\n| \033[1m \033[32m Thank you for using HMS! \033[0m|";
          char banner5[]="\n|     \033[1m \033[32m   Goodbye!           \033[0m|\n";
            for(int i=14;banner4[i]!='\0';i++)
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
     for(int i=14;banner4[i]!=NULL;i++)
    {
        delay(.5);
        printf("=");
    }
        }




