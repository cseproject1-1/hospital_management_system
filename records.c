#include "hospital.h"

void medicalRecordsMenu(void) {
    int choice;
    int running;

    running = 1;

    while(running == 1) {
        printf("\n");
        showHeader("MEDICAL RECORDS MANAGEMENT");
        printf("1. Add Diagnosis/Record\n");
        printf("2. View Patient History\n");
        printf("3. Add Prescription to Record\n");
        printf("4. Back to Admin Menu\n");
        printf("=========================================\n");
           printf("Enter your choice\033[33;6;91m:\033[0m ");
        printf(YELLOW);scanf("%d", &choice);printf(RESET);

        clearBuffer();

        switch(choice) {
            case RECORD_ADD:
                addDiagnosis(-1);
                break;
            case RECORD_VIEW_HISTORY:
                viewPatientHistory();
                break;
            case RECORD_ADD_PRESCRIPTION:
                addPrescription();
                break;
            case RECORD_BACK:
                running = 0;
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    }
}

void addDiagnosis(int doctorId) {
    int newId;
    int patId;
    int docId;
    int patIndex;
    int docIndex;

    if(recordCount >= MAX_RECORDS) {
        printf("\nError: Medical records database is full!\n");
        pressEnter();
        return;
    }

    printf("\n--- Add Medical Record ---\n");

    /* Get patient ID */
    printf("Enter Patient ID: ");
    scanf("%d", &patId);
    clearBuffer();

    patIndex = searchPatientByID(patId);

    if(patIndex == -1) {
        printf("\nError: Patient not found!\n");
        pressEnter();
        return;
    }

    printf("Patient: %s\n", patients[patIndex].name);

    /* Get doctor ID */
    if(doctorId == -1) {
        printf("\nEnter Doctor ID: ");
        scanf("%d", &docId);
        clearBuffer();

        docIndex = searchDoctorByID(docId);

        if(docIndex == -1) {
            printf("\nError: Doctor not found!\n");
            pressEnter();
            return;
        }
    } else {
        docId = doctorId;
        docIndex = searchDoctorByID(docId);
    }

    if(docIndex != -1) {
        printf("Doctor: %s\n", doctors[docIndex].name);
    }

    /* Auto-generate record ID */
    if(recordCount == 0) {
        newId = 1;
    } else {
        newId = records[recordCount - 1].recordId + 1;
    }

    records[recordCount].recordId = newId;
    records[recordCount].patientId = patId;
    records[recordCount].doctorId = docId;

    /* Get diagnosis */
    printf("\nEnter Diagnosis: ");
    fgets(records[recordCount].diagnosis, MAX_DIAGNOSIS, stdin);
    records[recordCount].diagnosis[strcspn(records[recordCount].diagnosis, "\n")] = 0;

    /* Get prescription */
    printf("Enter Prescription: ");
    fgets(records[recordCount].prescription, MAX_PRESCRIPTION, stdin);
    records[recordCount].prescription[strcspn(records[recordCount].prescription, "\n")] = 0;

    /* Get visit date */
    printf("Enter Visit Date (DD/MM/YYYY): ");
    fgets(records[recordCount].visitDate, 15, stdin);
    records[recordCount].visitDate[strcspn(records[recordCount].visitDate, "\n")] = 0;

    /* Get treatment cost */
    printf("Enter Treatment Cost: Rs. ");
    scanf("%f", &records[recordCount].treatmentCost);
    clearBuffer();

    recordCount = recordCount + 1;
    saveRecords();

    printf("\nMedical record added successfully!\n");
    printf("Record ID: %d\n", newId);
    pressEnter();
}

void viewPatientHistory(void) {
    int patId;
    int patIndex;
    int i;
    int found;
    int docIndex;

    printf("\n--- View Patient History ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &patId);
    clearBuffer();

    patIndex = searchPatientByID(patId);

    if(patIndex == -1) {
        printf("\nPatient not found!\n");
        pressEnter();
        return;
    }

    printf("\n--- Medical History for %s ---\n", patients[patIndex].name);

    found = 0;
    i = 0;

    while(i < recordCount) {
        if(records[i].patientId == patId) {
            if(found == 0) {
                found = 1;
            }

            printf("\n--- Record #%d ---\n", records[i].recordId);

            docIndex = searchDoctorByID(records[i].doctorId);
            if(docIndex != -1) {
                printf("Doctor: Dr. %s\n", doctors[docIndex].name);
            } else {
                printf("Doctor ID: %d\n", records[i].doctorId);
            }

            printf("Visit Date: %s\n", records[i].visitDate);
            printf("Diagnosis: %s\n", records[i].diagnosis);
            printf("Prescription: %s\n", records[i].prescription);
            printf("Treatment Cost: Rs. %.2f\n", records[i].treatmentCost);
        }
        i = i + 1;
    }

    if(found == 0) {
        printf("\nNo medical records found for this patient.\n");
    }

    pressEnter();
}

void addPrescription(void) {
    int recId;
    int index;
    int i;
    int found;

    printf("\n--- Add Prescription to Record ---\n");
    printf("Enter Record ID: ");
    scanf("%d", &recId);
    clearBuffer();

    found = 0;
    index = -1;
    i = 0;

    while(i < recordCount) {
        if(records[i].recordId == recId) {
            found = 1;
            index = i;
            break;
        }
        i = i + 1;
    }

    if(found == 0) {
        printf("\nRecord not found!\n");
        pressEnter();
        return;
    }

    printf("\nCurrent Prescription: %s\n", records[index].prescription);
    printf("\nEnter New Prescription: ");
    fgets(records[index].prescription, MAX_PRESCRIPTION, stdin);
    records[index].prescription[strcspn(records[index].prescription, "\n")] = 0;

    saveRecords();

    printf("\nPrescription updated successfully!\n");
    pressEnter();
}

void updatePatient(void) {
    int patId;
    int patIndex;
    int valid;

    printf("\n--- Update Patient Information ---\n");
    printf("Enter Patient ID to update: ");
    scanf("%d", &patId);
    clearBuffer();

    patIndex = searchPatientByID(patId);

    if (patIndex == -1) {
        printf("\nError: Patient not found!\n");
        pressEnter();
        return;
    }

    printf("\n--- Updating Patient ID: %d ---\n", patId);
    printf("Current Name: %s\n", patients[patIndex].name);
    printf("Enter New Patient Name (or press Enter to keep current): ");
    fgets(patients[patIndex].name, MAX_NAME, stdin);
    patients[patIndex].name[strcspn(patients[patIndex].name, "\n")] = 0;


    printf("Current Age: %d\n", patients[patIndex].age);
    valid = 0;
    while(valid == 0) {
        printf("Enter New Age (0-120): ");
        scanf("%d", &patients[patIndex].age);
        clearBuffer();

        if(patients[patIndex].age >= 0 && patients[patIndex].age <= 120) {
            valid = 1;
        } else {
            printf("Invalid age! Please enter between 0 and 120.\n");
        }
    }

    printf("Current Gender: %c\n", patients[patIndex].gender);
    valid = 0;
    while(valid == 0) {
        printf("Enter New Gender (M/F): ");
        scanf("%c", &patients[patIndex].gender);
        clearBuffer();

        if(patients[patIndex].gender == 'M' || patients[patIndex].gender == 'm' ||
           patients[patIndex].gender == 'F' || patients[patIndex].gender == 'f') {
            if(patients[patIndex].gender == 'm') {
                patients[patIndex].gender = 'M';
            }
            if(patients[patIndex].gender == 'f') {
                patients[patIndex].gender = 'F';
            }
            valid = 1;
        } else {
            printf("Invalid gender! Please enter M or F.\n");
        }
    }

    printf("Current Blood Group: %s\n", patients[patIndex].bloodGroup);
    valid = 0;
    while(valid == 0) {
        printf("Enter New Blood Group (A+, A-, B+, B-, AB+, AB-, O+, O-): ");
        fgets(patients[patIndex].bloodGroup, 5, stdin);
        patients[patIndex].bloodGroup[strcspn(patients[patIndex].bloodGroup, "\n")] = 0;

        if(strcmp(patients[patIndex].bloodGroup, "A+") == 0 ||
           strcmp(patients[patIndex].bloodGroup, "A-") == 0 ||
           strcmp(patients[patIndex].bloodGroup, "B+") == 0 ||
           strcmp(patients[patIndex].bloodGroup, "B-") == 0 ||
           strcmp(patients[patIndex].bloodGroup, "AB+") == 0 ||
           strcmp(patients[patIndex].bloodGroup, "AB-") == 0 ||
           strcmp(patients[patIndex].bloodGroup, "O+") == 0 ||
           strcmp(patients[patIndex].bloodGroup, "O-") == 0) {
            valid = 1;
        } else {
            printf("Invalid blood group!\n");
        }
    }

    printf("Current Contact: %s\n", patients[patIndex].contact);
    printf("Enter New Contact Number (10 digits): ");
    fgets(patients[patIndex].contact, MAX_CONTACT, stdin);
    patients[patIndex].contact[strcspn(patients[patIndex].contact, "\n")] = 0;

    printf("Current Address: %s\n", patients[patIndex].address);
    printf("Enter New Address: ");
    fgets(patients[patIndex].address, MAX_ADDRESS, stdin);
    patients[patIndex].address[strcspn(patients[patIndex].address, "\n")] = 0;

    printf("Current Disease: %s\n", patients[patIndex].disease);
    printf("Enter New Disease/Condition: ");
    fgets(patients[patIndex].disease, 50, stdin);
    patients[patIndex].disease[strcspn(patients[patIndex].disease, "\n")] = 0;

    printf("Current Admission Date: %s\n", patients[patIndex].admissionDate);
    printf("Enter New Admission Date (DD/MM/YYYY): ");
    fgets(patients[patIndex].admissionDate, 15, stdin);
    patients[patIndex].admissionDate[strcspn(patients[patIndex].admissionDate, "\n")] = 0;

    savePatients();
    printf("\nPatient information updated successfully!\n");
    pressEnter();
}

void deletePatient(void) {
    int patId;
    int patIndex;
    char confirm;
    int i;

    printf("\n--- Delete Patient ---\n");
    printf("Enter Patient ID to delete: ");
    scanf("%d", &patId);
    clearBuffer();

    patIndex = searchPatientByID(patId);

    if (patIndex == -1) {
        printf("\nError: Patient not found!\n");
        pressEnter();
        return;
    }

    printf("\n--- Patient Found ---\n");
    printf("ID: %d\n", patients[patIndex].id);
    printf("Name: %s\n", patients[patIndex].name);
    printf("Age: %d\n", patients[patIndex].age);
    printf("Gender: %c\n", patients[patIndex].gender);
    printf("Blood Group: %s\n", patients[patIndex].bloodGroup);
    printf("Contact: %s\n", patients[patIndex].contact);
    printf("Address: %s\n", patients[patIndex].address);
    printf("Disease: %s\n", patients[patIndex].disease);
    printf("Admission Date: %s\n", patients[patIndex].admissionDate);

    printf("\nAre you sure you want to delete this patient? (Y/N): ");
    scanf(" %c", &confirm);
    clearBuffer();

    if (confirm == 'Y' || confirm == 'y') {
        for (i = patIndex; i < patientCount - 1; i++) {
            patients[i] = patients[i + 1];
        }
        patientCount--;
        savePatients();
        printf("\nPatient deleted successfully!\n");
    } else {
        printf("\nDeletion cancelled.\n");
    }

    pressEnter();
}
