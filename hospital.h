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



// Regular colors
#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Bright colors
#define BBLACK      "\033[90m"
#define BRED        "\033[91m"
#define BGREEN      "\033[92m"
#define BYELLOW     "\033[93m"
#define BBLUE       "\033[94m"
#define BMAGENTA    "\033[95m"
#define BCYAN       "\033[96m"
#define BWHITE      "\033[97m"

// Background colors
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

// Text attributes
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"
#define HIDDEN      "\033[8m"
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
void delay(float sec);
#endif
