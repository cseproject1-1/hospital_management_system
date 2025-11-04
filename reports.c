#include "hospital.h"

void reportsMenu(void) {
    int choice;
    int running;

    running = 1;

    while(running == 1) {
        printf("\n");
        showHeader("REPORTS AND STATISTICS");
        printf("1. Patient Statistics\n");
        printf("2. Doctor Schedule\n");
        printf("3. Revenue Report\n");
        printf("4. Back to Admin Menu\n");
        printf("=========================================\n");
         printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);

        clearBuffer();

        switch(choice) {
            case REPORT_PATIENT_STATS:
                generatePatientStats();
                break;
            case REPORT_DOCTOR_SCHEDULE:
                generateDoctorSchedule();
                break;
            case REPORT_REVENUE:
                generateRevenueReport();
                break;
            case REPORT_BACK:
                running = 0;
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    }
}

void generatePatientStats(void) {
    int i;
    int maleCount;
    int femaleCount;
    int bloodCounts[8];
    int totalAge;
    int minAge;
    int maxAge;
    float avgAge;
    char *bloodGroups[8] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    int j;

    if(patientCount == 0) {
        printf("\nNo patient data available!\n");
        pressEnter();
        return;
    }

    printf("\n--- Patient Statistics Report ---\n");

    /* Initialize counters */
    maleCount = 0;
    femaleCount = 0;
    totalAge = 0;
    minAge = 999;
    maxAge = 0;

    j = 0;
    while(j < 8) {
        bloodCounts[j] = 0;
        j = j + 1;
    }

    /* Calculate statistics */
    i = 0;
    while(i < patientCount) {
        /* Gender count */
        if(patients[i].gender == 'M') {
            maleCount = maleCount + 1;
        } else if(patients[i].gender == 'F') {
            femaleCount = femaleCount + 1;
        }

        /* Age statistics */
        totalAge = totalAge + patients[i].age;

        if(patients[i].age < minAge) {
            minAge = patients[i].age;
        }

        if(patients[i].age > maxAge) {
            maxAge = patients[i].age;
        }

        /* Blood group count */
        j = 0;
        while(j < 8) {
            if(strcmp(patients[i].bloodGroup, bloodGroups[j]) == 0) {
                bloodCounts[j] = bloodCounts[j] + 1;
                break;
            }
            j = j + 1;
        }

        i = i + 1;
    }

    avgAge = (float)totalAge / patientCount;

    /* Display statistics */
    printf("\nTotal Patients: %d\n", patientCount);
    printf("\n--- Gender Distribution ---\n");
    printf("Male: %d (%.2f%%)\n", maleCount, (float)maleCount * 100 / patientCount);
    printf("Female: %d (%.2f%%)\n", femaleCount, (float)femaleCount * 100 / patientCount);

    printf("\n--- Age Statistics ---\n");
    printf("Minimum Age: %d\n", minAge);
    printf("Maximum Age: %d\n", maxAge);
    printf("Average Age: %.2f\n", avgAge);

    printf("\n--- Blood Group Distribution ---\n");
    i = 0;
    while(i < 8) {
        if(bloodCounts[i] > 0) {
            printf("%s: %d patients (%.2f%%)\n",
                   bloodGroups[i],
                   bloodCounts[i],
                   (float)bloodCounts[i] * 100 / patientCount);
        }
        i = i + 1;
    }

    pressEnter();
}

void generateDoctorSchedule(void) {
    int i;
    int j;
    int docId;
    int docIndex;
    int appointmentFound;
    int patIndex;

    if(doctorCount == 0) {
        printf("\nNo doctor data available!\n");
        pressEnter();
        return;
    }

    printf("\n--- Doctor Schedule Report ---\n");

    i = 0;
    while(i < doctorCount) {
        docId = doctors[i].id;

        printf("\n--- Dr. %s (ID: %d) ---\n", doctors[i].name, docId);
        printf("Specialization: %s\n", doctors[i].specialization);

        appointmentFound = 0;
        j = 0;

        while(j < appointmentCount) {
            if(appointments[j].doctorId == docId) {
                if(appointmentFound == 0) {
                    printf("\nAppointments:\n");
                    printf("%-15s %-12s %-10s %-15s\n",
                           "Patient", "Date", "Time", "Status");
                    printf("-----------------------------------------------------\n");
                    appointmentFound = 1;
                }

                patIndex = searchPatientByID(appointments[j].patientId);

                if(patIndex != -1) {
                    printf("%-15s %-12s %-10s %-15s\n",
                           patients[patIndex].name,
                           appointments[j].date,
                           appointments[j].time,
                           appointments[j].status);
                } else {
                    printf("%-15s %-12s %-10s %-15s\n",
                           "Unknown",
                           appointments[j].date,
                           appointments[j].time,
                           appointments[j].status);
                }
            }
            j = j + 1;
        }

        if(appointmentFound == 0) {
            printf("No appointments scheduled.\n");
        }

        i = i + 1;
    }

    pressEnter();
}

void generateRevenueReport(void) {
    int i;
    int j;
    float totalRevenue;
    float doctorRevenue[MAX_DOCTORS];
    int doctorPatientCount[MAX_DOCTORS];
    int docIndex;

    if(recordCount == 0) {
        printf("\nNo revenue data available!\n");
        pressEnter();
        return;
    }

    printf("\n--- Revenue Report ---\n");

    /* Initialize arrays */
    i = 0;
    while(i < doctorCount) {
        doctorRevenue[i] = 0;
        doctorPatientCount[i] = 0;
        i = i + 1;
    }

    totalRevenue = 0;

    /* Calculate revenue */
    i = 0;
    while(i < recordCount) {
        totalRevenue = totalRevenue + records[i].treatmentCost;

        docIndex = searchDoctorByID(records[i].doctorId);

        if(docIndex != -1) {
            doctorRevenue[docIndex] = doctorRevenue[docIndex] + records[i].treatmentCost;
            doctorPatientCount[docIndex] = doctorPatientCount[docIndex] + 1;
        }

        i = i + 1;
    }

    /* Display revenue report */
    printf("\nTotal Revenue: Rs. %.2f\n", totalRevenue);
    printf("Total Medical Records: %d\n", recordCount);

    printf("\n--- Revenue by Doctor ---\n");
    printf("%-20s %-15s %-15s %-15s\n",
           "Doctor Name", "Patients", "Revenue", "Avg/Patient");
    printf("--------------------------------------------------------------------\n");

    i = 0;
    while(i < doctorCount) {
        if(doctorPatientCount[i] > 0) {
            printf("%-20s %-15d Rs. %-12.2f Rs. %-12.2f\n",
                   doctors[i].name,
                   doctorPatientCount[i],
                   doctorRevenue[i],
                   doctorRevenue[i] / doctorPatientCount[i]);
        }
        i = i + 1;
    }

    /* Appointment statistics */
    int scheduledCount = 0;
    int completedCount = 0;
    int cancelledCount = 0;

    i = 0;
    while(i < appointmentCount) {
        if(strcmp(appointments[i].status, "Scheduled") == 0) {
            scheduledCount = scheduledCount + 1;
        } else if(strcmp(appointments[i].status, "Completed") == 0) {
            completedCount = completedCount + 1;
        } else if(strcmp(appointments[i].status, "Cancelled") == 0) {
            cancelledCount = cancelledCount + 1;
        }
        i = i + 1;
    }

    printf("\n--- Appointment Summary ---\n");
    printf("Total Appointments: %d\n", appointmentCount);
    printf("Scheduled: %d\n", scheduledCount);
    printf("Completed: %d\n", completedCount);
    printf("Cancelled: %d\n", cancelledCount);

    pressEnter();
}
