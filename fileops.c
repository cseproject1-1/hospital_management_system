#include "hospital.h"

void savePatients(void) {
    FILE *file;

    file = fopen("patients.dat", "wb");

    if(file == NULL) {
        printf("Error: Cannot open patients file for writing!\n");
        return;
    }

    fwrite(patients, sizeof(struct Patient), patientCount, file);
    fclose(file);
}

void loadPatients(void) {
    FILE *file;
    int count;

    file = fopen("patients.dat", "rb");

    if(file == NULL) {
        printf("No patient data file found. Starting fresh.\n");
        patientCount = 0;
        return;
    }

    count = 0;
    while(fread(&patients[count], sizeof(struct Patient), 1, file) == 1) {
        count = count + 1;
    }

    patientCount = count;
    fclose(file);
    printf("Loaded %d patient records.\n", patientCount);
}

void saveDoctors(void) {
    FILE *file;

    file = fopen("doctors.dat", "wb");

    if(file == NULL) {
        printf("Error: Cannot open doctors file for writing!\n");
        return;
    }

    fwrite(doctors, sizeof(struct Doctor), doctorCount, file);
    fclose(file);
}

void loadDoctors(void) {
    FILE *file;
    int count;

    file = fopen("doctors.dat", "rb");

    if(file == NULL) {
        printf("No doctor data file found. Starting fresh.\n");
        doctorCount = 0;
        return;
    }

    count = 0;
    while(fread(&doctors[count], sizeof(struct Doctor), 1, file) == 1) {
        count = count + 1;
    }

    doctorCount = count;
    fclose(file);
    printf("Loaded %d doctor records.\n", doctorCount);
}

void saveAppointments(void) {
    FILE *file;

    file = fopen("appointments.dat", "wb");

    if(file == NULL) {
        printf("Error: Cannot open appointments file for writing!\n");
        return;
    }

    fwrite(appointments, sizeof(struct Appointment), appointmentCount, file);
    fclose(file);
}

void loadAppointments(void) {
    FILE *file;
    int count;

    file = fopen("appointments.dat", "rb");

    if(file == NULL) {
        printf("No appointment data file found. Starting fresh.\n");
        appointmentCount = 0;
        return;
    }

    count = 0;
    while(fread(&appointments[count], sizeof(struct Appointment), 1, file) == 1) {
        count = count + 1;
    }

    appointmentCount = count;
    fclose(file);
    printf("Loaded %d appointment records.\n", appointmentCount);
}

void saveRecords(void) {
    FILE *file;

    file = fopen("medical_records.dat", "wb");

    if(file == NULL) {
        printf("Error: Cannot open medical records file for writing!\n");
        return;
    }

    fwrite(records, sizeof(struct MedicalRecord), recordCount, file);
    fclose(file);
}

void loadRecords(void) {
    FILE *file;
    int count;

    file = fopen("medical_records.dat", "rb");

    if(file == NULL) {
        printf("No medical records file found. Starting fresh.\n");
        recordCount = 0;
        return;
    }

    count = 0;
    while(fread(&records[count], sizeof(struct MedicalRecord), 1, file) == 1) {
        count = count + 1;
    }

    recordCount = count;
    fclose(file);
    printf("Loaded %d medical records.\n", recordCount);
}
