#include "hospital.h"

void appointmentMenu(void) {
    int choice;
    int running;

    running = 1;

    while(running == 1) {
        printf("\n");
        showHeader("APPOINTMENT MANAGEMENT");
        printf("1. Book Appointment\n");
        printf("2. View All Appointments\n");
        printf("3. Cancel Appointment\n");
        printf("4. View Today's Appointments\n");
        printf("5. Back to Admin Menu\n");
        printf("=========================================\n");
           printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);

        clearBuffer();

        switch(choice) {
            case APPOINTMENT_BOOK:
                bookAppointment();
                break;
            case APPOINTMENT_VIEW:
                viewAllAppointments();
                break;
            case APPOINTMENT_CANCEL:
                cancelAppointment();
                break;
            case APPOINTMENT_TODAY:
                viewTodayAppointments();
                break;
            case APPOINTMENT_BACK:
                running = 0;
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    }
}

void bookAppointment(void) {
    int newId;
    int patId;
    int docId;
    int patIndex;
    int docIndex;
    int i;

    if(appointmentCount >= MAX_APPOINTMENTS) {
        printf("\nError: Appointment database is full!\n");
        pressEnter();
        return;
    }

    printf("\n--- Book Appointment ---\n");

    /* Show available doctors */
    printf("\n--- Available Doctors ---\n");
    i = 0;
    while(i < doctorCount) {
        printf("ID: %d | Name: %s | Specialization: %s\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialization);
        i = i + 1;
    }

    /* Get patient ID */
    printf("\nEnter Patient ID: ");
    scanf("%d", &patId);
    clearBuffer();

    patIndex = searchPatientByID(patId);

    if(patIndex == -1) {
        printf("\nError: Patient not found!\n");
        pressEnter();
        return;
    }

    /* Get doctor ID */
    printf("Enter Doctor ID: ");
    scanf("%d", &docId);
    clearBuffer();

    docIndex = searchDoctorByID(docId);

    if(docIndex == -1) {
        printf("\nError: Doctor not found!\n");
        pressEnter();
        return;
    }

    /* Auto-generate appointment ID */
    if(appointmentCount == 0) {
        newId = 1;
    } else {
        newId = appointments[appointmentCount - 1].appointmentId + 1;
    }

    appointments[appointmentCount].appointmentId = newId;
    appointments[appointmentCount].patientId = patId;
    appointments[appointmentCount].doctorId = docId;

    /* Get appointment date */
    printf("Enter Appointment Date (DD/MM/YYYY): ");
    fgets(appointments[appointmentCount].date, 15, stdin);
    appointments[appointmentCount].date[strcspn(appointments[appointmentCount].date, "\n")] = 0;

    /* Get appointment time */
    printf("Enter Appointment Time (HH:MM): ");
    fgets(appointments[appointmentCount].time, 10, stdin);
    appointments[appointmentCount].time[strcspn(appointments[appointmentCount].time, "\n")] = 0;

    /* Set status */
    strcpy(appointments[appointmentCount].status, "Scheduled");

    appointmentCount = appointmentCount + 1;
    saveAppointments();

    printf("\nAppointment booked successfully!\n");
    printf("Appointment ID: %d\n", newId);
    printf("Patient: %s\n", patients[patIndex].name);
    printf("Doctor: %s\n", doctors[docIndex].name);
    pressEnter();
}

void viewAllAppointments(void) {
    int i;
    int patIndex;
    int docIndex;

    if(appointmentCount == 0) {
        printf("\nNo appointments found!\n");
        pressEnter();
        return;
    }

    printf("\n--- All Appointments ---\n");

    i = 0;
    while(i < appointmentCount) {
        patIndex = searchPatientByID(appointments[i].patientId);
        docIndex = searchDoctorByID(appointments[i].doctorId);

        printf("\n--- Appointment #%d ---\n", appointments[i].appointmentId);

        if(patIndex != -1) {
            printf("Patient: %s (ID: %d)\n",
                   patients[patIndex].name,
                   appointments[i].patientId);
        } else {
            printf("Patient ID: %d\n", appointments[i].patientId);
        }

        if(docIndex != -1) {
            printf("Doctor: Dr. %s (ID: %d)\n",
                   doctors[docIndex].name,
                   appointments[i].doctorId);
        } else {
            printf("Doctor ID: %d\n", appointments[i].doctorId);
        }

        printf("Date: %s\n", appointments[i].date);
        printf("Time: %s\n", appointments[i].time);
        printf("Status: %s\n", appointments[i].status);

        i = i + 1;
    }

    pressEnter();
}

void cancelAppointment(void) {
    int apptId;
    int index;
    char confirm;

    printf("\n--- Cancel Appointment ---\n");
    printf("Enter Appointment ID: ");
    scanf("%d", &apptId);
    clearBuffer();

    index = searchAppointmentByID(apptId);

    if(index == -1) {
        printf("\nAppointment not found!\n");
        pressEnter();
        return;
    }

    printf("\nAppointment Details:\n");
    printf("Date: %s\n", appointments[index].date);
    printf("Time: %s\n", appointments[index].time);
    printf("Current Status: %s\n", appointments[index].status);

    printf("\nAre you sure you want to cancel? (Y/N): ");
    scanf("%c", &confirm);
    clearBuffer();

    if(confirm == 'Y' || confirm == 'y') {
        strcpy(appointments[index].status, "Cancelled");
        saveAppointments();
        printf("\nAppointment cancelled successfully!\n");
    } else {
        printf("\nCancellation aborted.\n");
    }

    pressEnter();
}

void viewTodayAppointments(void) {
    char todayDate[15];
    int i;
    int found;
    int patIndex;
    int docIndex;

    printf("\n--- Today's Appointments ---\n");
    printf("Enter Today's Date (DD/MM/YYYY): ");
    fgets(todayDate, 15, stdin);
    todayDate[strcspn(todayDate, "\n")] = 0;

    found = 0;
    i = 0;

    while(i < appointmentCount) {
        if(strcmp(appointments[i].date, todayDate) == 0) {
            if(found == 0) {
                printf("\n%-10s %-20s %-20s %-10s %-15s\n",
                       "Appt ID", "Patient", "Doctor", "Time", "Status");
                printf("--------------------------------------------------------------------------------\n");
                found = 1;
            }

            patIndex = searchPatientByID(appointments[i].patientId);
            docIndex = searchDoctorByID(appointments[i].doctorId);

            printf("%-10d ",
                   appointments[i].appointmentId);

            if(patIndex != -1) {
                printf("%-20s ", patients[patIndex].name);
            } else {
                printf("%-20s ", "Unknown");
            }

            if(docIndex != -1) {
                printf("%-20s ", doctors[docIndex].name);
            } else {
                printf("%-20s ", "Unknown");
            }

            printf("%-10s %-15s\n",
                   appointments[i].time,
                   appointments[i].status);
        }
        i = i + 1;
    }

    if(found == 0) {
        printf("\nNo appointments scheduled for %s\n", todayDate);
    }

    pressEnter();
}
