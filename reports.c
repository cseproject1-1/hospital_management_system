// reports.c - Reports and statistics functions

#include "hospital.h"

void reportsMenu() {
    int choice;

    while(1) {
        showHeader("REPORTS & STATISTICS");
        printf("1. Patient Statistics\n");
        printf("2. Doctor Schedule\n");
        printf("3. Revenue Report\n");
        printf("4. Back to Main Menu\n");
         printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);
        clearBuffer();

        if(choice == 1) {
            generatePatientStats();
        }
        else if(choice == 2) {
            generateDoctorSchedule();
        }
        else if(choice == 3) {
            generateRevenueReport();
        }
        else if(choice == 4) {
            printf("\nGoing back...\n");
            break;
        }
        else {
            printf("\nWrong choice!\n");
        }

        if(choice != 4) {
            pressEnter();
        }
    }
}

void generatePatientStats() {
    showHeader("PATIENT STATISTICS");

    // Check if patients exist
    if(patientCount == 0) {
        printf("\nNo patients to analyze!\n");
        return;
    }

    printf("\nOVERVIEW\n");
    printf("========================================\n");
    printf("Total Patients: %d\n\n", patientCount);

    // Count males and females
    int maleCount = 0;
    int femaleCount = 0;
    int i;

    for(i = 0; i < patientCount; i = i + 1) {
        if(patients[i].gender == 'M' || patients[i].gender == 'm') {
            maleCount = maleCount + 1;
        }
        else {
            femaleCount = femaleCount + 1;
        }
    }

    printf("GENDER DISTRIBUTION\n");
    printf("========================================\n");
    printf("Male Patients:   %d (%.1f%%)\n", maleCount,
           (maleCount * 100.0) / patientCount);
    printf("Female Patients: %d (%.1f%%)\n\n", femaleCount,
           (femaleCount * 100.0) / patientCount);

    // Blood group statistics
    int aplus = 0, aminus = 0, bplus = 0, bminus = 0;
    int abplus = 0, abminus = 0, oplus = 0, ominus = 0;

    for(i = 0; i < patientCount; i = i + 1) {
        if(strcmp(patients[i].bloodGroup, "A+") == 0) {
            aplus = aplus + 1;
        }
        else if(strcmp(patients[i].bloodGroup, "A-") == 0) {
            aminus = aminus + 1;
        }
        else if(strcmp(patients[i].bloodGroup, "B+") == 0) {
            bplus = bplus + 1;
        }
        else if(strcmp(patients[i].bloodGroup, "B-") == 0) {
            bminus = bminus + 1;
        }
        else if(strcmp(patients[i].bloodGroup, "AB+") == 0) {
            abplus = abplus + 1;
        }
        else if(strcmp(patients[i].bloodGroup, "AB-") == 0) {
            abminus = abminus + 1;
        }
        else if(strcmp(patients[i].bloodGroup, "O+") == 0) {
            oplus = oplus + 1;
        }
        else if(strcmp(patients[i].bloodGroup, "O-") == 0) {
            ominus = ominus + 1;
        }
    }

    printf("BLOOD GROUP DISTRIBUTION\n");
    printf("====================================\n");
    if(aplus > 0) printf("A+  : %d patient(s)\n", aplus);
    if(aminus > 0) printf("A-  : %d patient(s)\n", aminus);
    if(bplus > 0) printf("B+  : %d patient(s)\n", bplus);
    if(bminus > 0) printf("B-  : %d patient(s)\n", bminus);
    if(abplus > 0) printf("AB+ : %d patient(s)\n", abplus);
    if(abminus > 0) printf("AB- : %d patient(s)\n", abminus);
    if(oplus > 0) printf("O+  : %d patient(s)\n", oplus);
    if(ominus > 0) printf("O-  : %d patient(s)\n", ominus);

    // Age statistics
    int ageSum = 0;
    int minAge = 120;
    int maxAge = 0;

    for(i = 0; i < patientCount; i = i + 1) {
        ageSum = ageSum + patients[i].age;

        if(patients[i].age < minAge) {
            minAge = patients[i].age;
        }

        if(patients[i].age > maxAge) {
            maxAge = patients[i].age;
        }
    }

    printf("\nAGE STATISTICS\n");
    printf("====================================\n");
    printf("Average Age: %.1f years\n", (float)ageSum / patientCount);
    printf("Youngest:    %d years\n", minAge);
    printf("Oldest:      %d years\n", maxAge);
}

void generateDoctorSchedule() {
    showHeader("DOCTOR SCHEDULE");

    // Check if doctors exist
    if(doctorCount == 0) {
        printf("\nNo doctors in database!\n");
        return;
    }

    printf("\nDOCTOR AVAILABILITY & APPOINTMENTS\n");
    printf("=================================================================\n\n");

    int i, j;

    // Loop through each doctor
    for(i = 0; i < doctorCount; i = i + 1) {
        printf("Dr. %s (%s)\n", doctors[i].name, doctors[i].specialization);
        printf("Contact: %s | Fee: $%.2f\n", doctors[i].contact,
               doctors[i].consultationFee);

        // Count appointments for this doctor
        int apptCount = 0;
        printf("Appointments:\n");

        for(j = 0; j < appointmentCount; j = j + 1) {
            if(appointments[j].doctorId == doctors[i].id) {
                // Find patient name
                char pname[50] = "Unknown";
                int k;
                for(k = 0; k < patientCount; k = k + 1) {
                    if(patients[k].id == appointments[j].patientId) {
                        strcpy(pname, patients[k].name);
                        break;
                    }
                }

                printf("  - %s at %s on %s [%s]\n",
                       pname,
                       appointments[j].time,
                       appointments[j].date,
                       appointments[j].status);
                apptCount = apptCount + 1;
            }
        }

        if(apptCount == 0) {
            printf("  No appointments scheduled\n");
        }

        printf("Total Appointments: %d\n", apptCount);
        printf("---------------------------------------------------------------\n");
    }
}

void generateRevenueReport() {
    showHeader("REVENUE REPORT");

    // Check if records exist
    if(recordCount == 0) {
        printf("\nNo medical records available!\n");
        return;
    }

    printf("\nFINANCIAL SUMMARY\n");
    printf("====================================\n\n");

    // Calculate total revenue
    float totalRevenue = 0;
    int i;

    for(i = 0; i < recordCount; i = i + 1) {
        totalRevenue = totalRevenue + records[i].treatmentCost;
    }

    printf("Total Revenue: $%.2f\n", totalRevenue);
    printf("Total Treatments: %d\n", recordCount);
    printf("Average Treatment Cost: $%.2f\n\n", totalRevenue / recordCount);

    // Revenue by doctor
    printf("REVENUE BY DOCTOR\n");
    printf("====================================\n");

    int j;
    for(i = 0; i < doctorCount; i = i + 1) {
        float doctorRevenue = 0;

        // Calculate revenue for this doctor
        for(j = 0; j < recordCount; j = j + 1) {
            if(records[j].doctorId == doctors[i].id) {
                doctorRevenue = doctorRevenue + records[j].treatmentCost;
            }
        }

        if(doctorRevenue > 0) {
            printf("Dr. %-20s: $%10.2f (%.1f%%)\n",
                   doctors[i].name,
                   doctorRevenue,
                   (doctorRevenue / totalRevenue) * 100);
        }
    }

    // Appointment statistics
    int scheduledCount = 0;
    int completedCount = 0;
    int cancelledCount = 0;

    for(i = 0; i < appointmentCount; i = i + 1) {
        if(strcmp(appointments[i].status, "Scheduled") == 0) {
            scheduledCount = scheduledCount + 1;
        }
        else if(strcmp(appointments[i].status, "Completed") == 0) {
            completedCount = completedCount + 1;
        }
        else if(strcmp(appointments[i].status, "Cancelled") == 0) {
            cancelledCount = cancelledCount + 1;
        }
    }

    printf("\nAPPOINTMENT STATISTICS\n");
    printf("====================================\n");
    printf("Total Appointments: %d\n", appointmentCount);
    printf("Scheduled:          %d\n", scheduledCount);
    printf("Completed:          %d\n", completedCount);
    printf("Cancelled:          %d\n", cancelledCount);
}
