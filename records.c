// records.c - Medical records management functions

#include "hospital.h"

void medicalRecordsMenu() {
    int choice;

    while(1) {
        showHeader("MEDICAL RECORDS");
        printf("1. Add Diagnosis\n");
        printf("2. View Patient History\n");
        printf("3. Add Prescription\n");
        printf("4. Back to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        if(choice == 1) {
            addDiagnosis();
        }
        else if(choice == 2) {
            viewPatientHistory();
        }
        else if(choice == 3) {
            addPrescription();
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

void addDiagnosis() {
    showHeader("ADD DIAGNOSIS");

    // Check if full
    if(recordCount >= MAX_RECORDS) {
        printf("\nDatabase full! Cannot add more records.\n");
        return;
    }

    // Check patients
    if(patientCount == 0) {
        printf("\nNo patients in database!\n");
        return;
    }

    // Create new record
    struct MedicalRecord r;

    // Auto ID
    r.recordId = recordCount + 1;
    printf("Record ID: %d\n\n", r.recordId);

    // Get patient ID
    printf("Enter Patient ID: ");
    scanf("%d", &r.patientId);
    clearBuffer();

    // Check if patient exists
    int pfound = 0;
    int pindex = -1;
    int i;
    for(i = 0; i < patientCount; i = i + 1) {
        if(patients[i].id == r.patientId) {
            pfound = 1;
            pindex = i;
            break;
        }
    }

    if(pfound == 0) {
        printf("\nPatient not found!\n");
        return;
    }

    printf("Patient: %s\n", patients[pindex].name);

    // Get doctor ID
    printf("Enter Doctor ID: ");
    scanf("%d", &r.doctorId);
    clearBuffer();

    // Check if doctor exists
    int dfound = 0;
    int dindex = -1;
    for(i = 0; i < doctorCount; i = i + 1) {
        if(doctors[i].id == r.doctorId) {
            dfound = 1;
            dindex = i;
            break;
        }
    }

    if(dfound == 0) {
        printf("\nDoctor not found!\n");
        return;
    }

    printf("Doctor: Dr. %s\n\n", doctors[dindex].name);

    // Get diagnosis
    printf("Enter diagnosis: ");
    fgets(r.diagnosis, 200, stdin);
    int len = strlen(r.diagnosis);
    if(r.diagnosis[len-1] == '\n') {
        r.diagnosis[len-1] = '\0';
    }

    // Get prescription
    printf("Enter prescription: ");
    fgets(r.prescription, 500, stdin);
    len = strlen(r.prescription);
    if(r.prescription[len-1] == '\n') {
        r.prescription[len-1] = '\0';
    }

    // Get date
    printf("Enter visit date (DD/MM/YYYY): ");
    scanf("%s", r.visitDate);
    clearBuffer();

    // Get cost
    printf("Enter treatment cost: $");
    scanf("%f", &r.treatmentCost);
    clearBuffer();

    // Add to array
    records[recordCount] = r;
    recordCount = recordCount + 1;

    // Save
    saveRecords();

    printf("\nMedical record added successfully!\n");
    printf("Record ID: %d\n", r.recordId);
}

void viewPatientHistory() {
    int patientId;

    showHeader("PATIENT MEDICAL HISTORY");

    printf("Enter Patient ID: ");
    scanf("%d", &patientId);
    clearBuffer();

    // Check if patient exists
    int pfound = 0;
    int pindex = -1;
    int i;
    for(i = 0; i < patientCount; i = i + 1) {
        if(patients[i].id == patientId) {
            pfound = 1;
            pindex = i;
            break;
        }
    }

    if(pfound == 0) {
        printf("\nPatient not found!\n");
        return;
    }

    printf("\nMedical History for: %s (ID: %d)\n", patients[pindex].name, patientId);
    printf("====================================================================\n\n");

    int found = 0;

    // Loop through records
    for(i = 0; i < recordCount; i = i + 1) {
        if(records[i].patientId == patientId) {
            // Find doctor name
            char dname[50] = "Unknown";
            int j;
            for(j = 0; j < doctorCount; j = j + 1) {
                if(doctors[j].id == records[i].doctorId) {
                    strcpy(dname, doctors[j].name);
                    break;
                }
            }

            printf("Record ID: %d\n", records[i].recordId);
            printf("Date: %s\n", records[i].visitDate);
            printf("Doctor: %s\n", dname);
            printf("Diagnosis: %s\n", records[i].diagnosis);
            printf("Prescription: %s\n", records[i].prescription);
            printf("Cost: $%.2f\n", records[i].treatmentCost);
            printf("========================================================\n");
            found = 1;
        }
    }

    if(found == 0) {
        printf("No medical records found for this patient.\n");
    }
}

void addPrescription() {
    int recordId;

    showHeader("ADD PRESCRIPTION");

    printf("Enter Record ID: ");
    scanf("%d", &recordId);
    clearBuffer();

    // Find record
    int index = -1;
    int i;
    for(i = 0; i < recordCount; i = i + 1) {
        if(records[i].recordId == recordId) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("\nRecord not found!\n");
        return;
    }

    printf("\nCurrent Prescription: %s\n", records[index].prescription);
    printf("\nEnter new/updated prescription: ");
    fgets(records[index].prescription, 500, stdin);
    int len = strlen(records[index].prescription);
    if(records[index].prescription[len-1] == '\n') {
        records[index].prescription[len-1] = '\0';
    }

    saveRecords();
    printf("\nPrescription updated successfully!\n");
}
