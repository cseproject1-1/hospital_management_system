// appointment.c - Appointment management functions

#include "hospital.h"

void appointmentMenu() {
    int choice;

    while(1) {
        showHeader("APPOINTMENT MANAGEMENT");
        printf("1. Book Appointment\n");
        printf("2. View All Appointments\n");
        printf("3. Cancel Appointment\n");
        printf("4. View Today's Appointments\n");
        printf("5. Back to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        if(choice == 1) {
            bookAppointment();
        }
        else if(choice == 2) {
            viewAllAppointments();
        }
        else if(choice == 3) {
            cancelAppointment();
        }
        else if(choice == 4) {
            viewTodayAppointments();
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

void bookAppointment() {
    showHeader("BOOK APPOINTMENT");

    // Check if full
    if(appointmentCount >= MAX_APPOINTMENTS) {
        printf("\nDatabase full! Cannot book more appointments.\n");
        return;
    }

    // Check patients
    if(patientCount == 0) {
        printf("\nNo patients in database! Add patients first.\n");
        return;
    }

    // Check doctors
    if(doctorCount == 0) {
        printf("\nNo doctors in database! Add doctors first.\n");
        return;
    }

    // Create new appointment
    struct Appointment a;

    // Auto ID
    a.appointmentId = appointmentCount + 1;
    printf("Appointment ID: %d\n\n", a.appointmentId);

    // Get patient ID
    printf("Enter Patient ID: ");
    scanf("%d", &a.patientId);
    clearBuffer();

    // Check if patient exists
    int pfound = 0;
    int pindex = -1;
    int i;
    for(i = 0; i < patientCount; i = i + 1) {
        if(patients[i].id == a.patientId) {
            pfound = 1;
            pindex = i;
            break;
        }
    }

    if(pfound == 0) {
        printf("\nPatient not found!\n");
        return;
    }

    printf("Patient: %s\n\n", patients[pindex].name);

    // Show available doctors
    printf("Available Doctors:\n");
    printf("%-5s %-20s %-20s\n", "ID", "Name", "Specialization");
    printf("------------------------------------------------\n");
    for(i = 0; i < doctorCount; i = i + 1) {
        printf("%-5d %-20s %-20s\n", doctors[i].id, doctors[i].name,
               doctors[i].specialization);
    }

    // Get doctor ID
    printf("\nEnter Doctor ID: ");
    scanf("%d", &a.doctorId);
    clearBuffer();

    // Check if doctor exists
    int dfound = 0;
    int dindex = -1;
    for(i = 0; i < doctorCount; i = i + 1) {
        if(doctors[i].id == a.doctorId) {
            dfound = 1;
            dindex = i;
            break;
        }
    }

    if(dfound == 0) {
        printf("\nDoctor not found!\n");
        return;
    }

    printf("Doctor: Dr. %s (%s)\n", doctors[dindex].name,
           doctors[dindex].specialization);

    // Get date
    printf("\nEnter appointment date (DD/MM/YYYY): ");
    scanf("%s", a.date);
    clearBuffer();

    // Get time
    printf("Enter appointment time (HH:MM): ");
    scanf("%s", a.time);
    clearBuffer();

    // Set status
    strcpy(a.status, "Scheduled");

    // Add to array
    appointments[appointmentCount] = a;
    appointmentCount = appointmentCount + 1;

    // Save
    saveAppointments();

    printf("\nAppointment booked successfully!\n");
    printf("Appointment ID: %d\n", a.appointmentId);
    printf("Patient: %s\n", patients[pindex].name);
    printf("Doctor: Dr. %s\n", doctors[dindex].name);
    printf("Date & Time: %s at %s\n", a.date, a.time);
}

void viewAllAppointments() {
    showHeader("APPOINTMENT LIST");

    // Check if empty
    if(appointmentCount == 0) {
        printf("\nNo appointments found!\n");
        return;
    }

    printf("\nTotal Appointments: %d\n\n", appointmentCount);

    printf("%-6s %-10s %-20s %-20s %-12s %-8s %-15s\n",
           "Appt ID", "Pat ID", "Patient", "Doctor", "Date", "Time", "Status");
    printf("--------------------------------------------------------------------------------\n");

    // Print all appointments
    int i;
    for(i = 0; i < appointmentCount; i = i + 1) {
        // Find patient name
        char pname[50] = "Unknown";
        int j;
        for(j = 0; j < patientCount; j = j + 1) {
            if(patients[j].id == appointments[i].patientId) {
                strcpy(pname, patients[j].name);
                break;
            }
        }

        // Find doctor name
        char dname[50] = "Unknown";
        for(j = 0; j < doctorCount; j = j + 1) {
            if(doctors[j].id == appointments[i].doctorId) {
                strcpy(dname, doctors[j].name);
                break;
            }
        }

        printf("%-6d %-10d %-20s %-20s %-12s %-8s %-15s\n",
               appointments[i].appointmentId,
               appointments[i].patientId,
               pname,
               dname,
               appointments[i].date,
               appointments[i].time,
               appointments[i].status);
    }
}

void cancelAppointment() {
    int id;

    showHeader("CANCEL APPOINTMENT");

    printf("Enter Appointment ID to cancel: ");
    scanf("%d", &id);
    clearBuffer();

    // Find appointment
    int index = -1;
    int i;
    for(i = 0; i < appointmentCount; i = i + 1) {
        if(appointments[i].appointmentId == id) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("\nAppointment not found!\n");
        return;
    }

    // Check if already cancelled
    if(strcmp(appointments[index].status, "Cancelled") == 0) {
        printf("\nAppointment is already cancelled!\n");
        return;
    }

    printf("\nAre you sure you want to cancel this appointment? (Y/N): ");
    char confirm;
    scanf(" %c", &confirm);
    clearBuffer();

    if(confirm == 'Y' || confirm == 'y') {
        strcpy(appointments[index].status, "Cancelled");
        saveAppointments();
        printf("\nAppointment cancelled successfully!\n");
    }
    else {
        printf("\nCancellation aborted.\n");
    }
}

void viewTodayAppointments() {
    char today[15];

    showHeader("TODAY'S APPOINTMENTS");

    printf("Enter today's date (DD/MM/YYYY): ");
    scanf("%s", today);
    clearBuffer();

    int found = 0;

    printf("\nAppointments for %s:\n\n", today);
    printf("%-6s %-20s %-20s %-8s %-15s\n",
           "Appt ID", "Patient", "Doctor", "Time", "Status");
    printf("--------------------------------------------------------------------------------\n");

    // Loop through appointments
    int i;
    for(i = 0; i < appointmentCount; i = i + 1) {
        // Check if date matches
if(strcmp(appointments[i].date, today) == 0) {
            // Find patient name
            char pname[50] = "Unknown";
            int j;
            for(j = 0; j < patientCount; j = j + 1) {
                if(patients[j].id == appointments[i].patientId) {
                    strcpy(pname, patients[j].name);
                    break;
                }
            }

            // Find doctor name
            char dname[50] = "Unknown";
            for(j = 0; j < doctorCount; j = j + 1) {
                if(doctors[j].id == appointments[i].doctorId) {
                    strcpy(dname, doctors[j].name);
                    break;
                }
            }

            printf("%-6d %-20s %-20s %-8s %-15s\n",
                   appointments[i].appointmentId,
                   pname,
                   dname,
                   appointments[i].time,
                   appointments[i].status);
            found = 1;
        }
    }

    if(found == 0) {
        printf("\nNo appointments scheduled for %s\n", today);
    }
}
