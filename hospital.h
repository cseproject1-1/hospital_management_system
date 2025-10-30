// hospital.h - Header file with all definitions

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum limits
#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_APPOINTMENTS 200
#define MAX_RECORDS 200

// Patient structure
struct Patient {
    int id;
    char name[50];
    int age;
    char gender;
    char bloodGroup[5];
    char contact[15];
    char address[100];
    char disease[50];
    char admissionDate[15];
};

// Doctor structure - with authentication
struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    char contact[15];
    int experience;
    float consultationFee;
    char username[30];
    char password[30];
    int isRegistered; // 1 = registered, 0 = not registered
};

// Appointment structure
struct Appointment {
    int appointmentId;
    int patientId;
    int doctorId;
    char date[15];
    char time[10];
    char status[20];
};

// Medical Record structure
struct MedicalRecord {
    int recordId;
    int patientId;
    int doctorId;
    char diagnosis[200];
    char prescription[500];
    char visitDate[15];
    float treatmentCost;
};

// Global arrays - DECLARE with extern (not define here!)
extern struct Patient patients[MAX_PATIENTS];
extern struct Doctor doctors[MAX_DOCTORS];
extern struct Appointment appointments[MAX_APPOINTMENTS];
extern struct MedicalRecord records[MAX_RECORDS];

// Global counters - DECLARE with extern
extern int patientCount;
extern int doctorCount;
extern int appointmentCount;
extern int recordCount;

// Global variable for logged in doctor
extern int loggedInDoctorId;

// Authentication functions
int doctorLogin();
void doctorRegister();
void doctorDashboard(int doctorId);
void viewMyPatients(int doctorId);
void viewMyAppointments(int doctorId);
void viewMyRecords(int doctorId);

// Patient functions
void patientMenu();
void addPatient();
void viewAllPatients();
void searchPatient();
void updatePatient();
void deletePatient();

// Doctor functions (Admin)
void doctorMenu();
void addDoctor();
void viewAllDoctors();
void searchDoctor();
void updateDoctor();

// Appointment functions
void appointmentMenu();
void bookAppointment();
void viewAllAppointments();
void cancelAppointment();
void viewTodayAppointments();

// Medical record functions
void medicalRecordsMenu();
void addDiagnosis();
void viewPatientHistory();
void addPrescription();

// Report functions
void reportsMenu();
void generatePatientStats();
void generateDoctorSchedule();
void generateRevenueReport();

// File functions
void savePatients();
void loadPatients();
void saveDoctors();
void loadDoctors();
void saveAppointments();
void loadAppointments();
void saveRecords();
void loadRecords();

// Helper functions
int searchPatientByID(int id);
int searchDoctorByID(int id);
int searchAppointmentByID(int id);
int checkUsernameExists(char username[]);
void clearBuffer();
void pressEnter();
void showHeader(char *title);

#endif
