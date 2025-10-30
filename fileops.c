// fileops.c - File operations for saving and loading data

#include "hospital.h"

void savePatients() {
    FILE *file;
    file = fopen("patients.dat", "wb");

    if(file == NULL) {
        printf("Error: Cannot save patient data!\n");
        return;
    }

    fwrite(patients, sizeof(struct Patient), patientCount, file);
    fclose(file);
}

void loadPatients() {
    FILE *file;
    file = fopen("patients.dat", "rb");

    if(file == NULL) {
        printf("No previous patient data found. Starting fresh.\n");
        patientCount = 0;
        return;
    }

    patientCount = 0;

    // Read patients one by one
    while(1) {
        int result = fread(&patients[patientCount], sizeof(struct Patient), 1, file);

        if(result == 1) {
            patientCount = patientCount + 1;
        }
        else {
            break;
        }
    }

    fclose(file);
    printf("Loaded %d patient record(s).\n", patientCount);
}

void saveDoctors() {
    FILE *file;
    file = fopen("doctors.dat", "wb");

    if(file == NULL) {
        printf("Error: Cannot save doctor data!\n");
        return;
    }

    fwrite(doctors, sizeof(struct Doctor), doctorCount, file);
    fclose(file);
}

void loadDoctors() {
    FILE *file;
    file = fopen("doctors.dat", "rb");

    if(file == NULL) {
        printf("No previous doctor data found. Starting fresh.\n");
        doctorCount = 0;
        return;
    }

    doctorCount = 0;

    // Read doctors one by one
    while(1) {
        int result = fread(&doctors[doctorCount], sizeof(struct Doctor), 1, file);

        if(result == 1) {
            doctorCount = doctorCount + 1;
        }
        else {
            break;
        }
    }

    fclose(file);
    printf("Loaded %d doctor record(s).\n", doctorCount);
}

void saveAppointments() {
    FILE *file;
    file = fopen("appointments.dat", "wb");

    if(file == NULL) {
        printf("Error: Cannot save appointment data!\n");
        return;
    }

    fwrite(appointments, sizeof(struct Appointment), appointmentCount, file);
    fclose(file);
}

void loadAppointments() {
    FILE *file;
    file = fopen("appointments.dat", "rb");

    if(file == NULL) {
        printf("No previous appointment data found. Starting fresh.\n");
        appointmentCount = 0;
        return;
    }

    appointmentCount = 0;

    // Read appointments one by one
    while(1) {
        int result = fread(&appointments[appointmentCount], sizeof(struct Appointment), 1, file);

        if(result == 1) {
            appointmentCount = appointmentCount + 1;
        }
        else {
            break;
        }
    }

    fclose(file);
    printf("Loaded %d appointment record(s).\n", appointmentCount);
}

void saveRecords() {
    FILE *file;
    file = fopen("medical_records.dat", "wb");

    if(file == NULL) {
        printf("Error: Cannot save medical records!\n");
        return;
    }

    fwrite(records, sizeof(struct MedicalRecord), recordCount, file);
    fclose(file);
}

void loadRecords() {
    FILE *file;
    file = fopen("medical_records.dat", "rb");

    if(file == NULL) {
        printf("No previous medical records found. Starting fresh.\n");
        recordCount = 0;
        return;
    }

    recordCount = 0;

    // Read records one by one
    while(1) {
        int result = fread(&records[recordCount], sizeof(struct MedicalRecord), 1, file);

        if(result == 1) {
            recordCount = recordCount + 1;
        }
        else {
            break;
        }
    }

    fclose(file);
    printf("Loaded %d medical record(s).\n", recordCount);
}
