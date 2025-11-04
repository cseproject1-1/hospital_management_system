#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum limits */
#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_APPOINTMENTS 200
#define MAX_RECORDS 200
#define MAX_NAME 50
#define MAX_CONTACT 15
#define MAX_ADDRESS 100
#define MAX_USERNAME 30
#define MAX_PASSWORD 30
#define MAX_DIAGNOSIS 200
#define MAX_PRESCRIPTION 500
#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BOLD        "\033[1m"
#define cls system("cls");

typedef enum {
    MAIN_LOGIN = 1,
    MAIN_REGISTER = 2,
    MAIN_ADMIN = 3,
    MAIN_EXIT = 4
} MainMenuOption;

typedef enum {
    DASHBOARD_MY_PATIENTS = 1,
    DASHBOARD_MY_APPOINTMENTS = 2,
    DASHBOARD_MY_RECORDS = 3,
    DASHBOARD_ADD_RECORD = 4,
    DASHBOARD_LOGOUT = 5
} DashboardOption;

typedef enum {
    ADMIN_PATIENT = 1,
    ADMIN_DOCTOR = 2,
    ADMIN_APPOINTMENT = 3,
    ADMIN_RECORDS = 4,
    ADMIN_REPORTS = 5,
    ADMIN_BACK = 6
} AdminOption;

typedef enum {
    PATIENT_ADD = 1,
    PATIENT_VIEW = 2,
    PATIENT_SEARCH = 3,
    PATIENT_UPDATE = 4,
    PATIENT_DELETE = 5,
    PATIENT_BACK = 6
} PatientMenuOption;

typedef enum {
    DOCTOR_ADD = 1,
    DOCTOR_VIEW = 2,
    DOCTOR_SEARCH = 3,
    DOCTOR_UPDATE = 4,
    DOCTOR_BACK = 5
} DoctorMenuOption;

typedef enum {
    APPOINTMENT_BOOK = 1,
    APPOINTMENT_VIEW = 2,
    APPOINTMENT_CANCEL = 3,
    APPOINTMENT_TODAY = 4,
    APPOINTMENT_BACK = 5
} AppointmentMenuOption;

typedef enum {
    RECORD_ADD = 1,
    RECORD_VIEW_HISTORY = 2,
    RECORD_ADD_PRESCRIPTION = 3,
    RECORD_BACK = 4
} RecordMenuOption;

typedef enum {
    REPORT_PATIENT_STATS = 1,
    REPORT_DOCTOR_SCHEDULE = 2,
    REPORT_REVENUE = 3,
    REPORT_BACK = 4
} ReportMenuOption;

/* Structure Definitions */
struct Patient {
    int id;
    char name[MAX_NAME];
    int age;
    char gender;
    char bloodGroup[5];
    char contact[MAX_CONTACT];
    char address[MAX_ADDRESS];
    char disease[50];
    char admissionDate[15];
};

struct Doctor {
    int id;
    char name[MAX_NAME];
    char specialization[50];
    char contact[MAX_CONTACT];
    int experience;
    float consultationFee;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int isRegistered;
};

struct Appointment {
    int appointmentId;
    int patientId;
    int doctorId;
    char date[15];
    char time[10];
    char status[20];
};

struct MedicalRecord {
    int recordId;
    int patientId;
    int doctorId;
    char diagnosis[MAX_DIAGNOSIS];
    char prescription[MAX_PRESCRIPTION];
    char visitDate[15];
    float treatmentCost;
};

/* Global variable declarations */
extern struct Patient patients[MAX_PATIENTS];
extern struct Doctor doctors[MAX_DOCTORS];
extern struct Appointment appointments[MAX_APPOINTMENTS];
extern struct MedicalRecord records[MAX_RECORDS];
extern int patientCount;
extern int doctorCount;
extern int appointmentCount;
extern int recordCount;
extern int loggedInDoctorId;

/* Function Prototypes - Patient Module */
void patientMenu(void);
void addPatient(void);
void viewAllPatients(void);
void searchPatient(void);
void updatePatient(void);
void deletePatient(void);

/* Function Prototypes - Doctor Module */
int doctorLogin(void);
void doctorRegister(void);
void doctorDashboard(int doctorId);
void viewMyPatients(int doctorId);
void viewMyAppointments(int doctorId);
void viewMyRecords(int doctorId);
void doctorMenu(void);
void addDoctor(void);
void viewAllDoctors(void);
void searchDoctor(void);
void updateDoctor(void);

/* Function Prototypes - Appointment Module */
void appointmentMenu(void);
void bookAppointment(void);
void viewAllAppointments(void);
void cancelAppointment(void);
void viewTodayAppointments(void);

/* Function Prototypes - Records Module */
void medicalRecordsMenu(void);
void addDiagnosis(int doctorId);
void viewPatientHistory(void);
void addPrescription(void);

/* Function Prototypes - Reports Module */
void reportsMenu(void);
void generatePatientStats(void);
void generateDoctorSchedule(void);
void generateRevenueReport(void);

/* Function Prototypes - File Operations */
void savePatients(void);
void loadPatients(void);
void saveDoctors(void);
void loadDoctors(void);
void saveAppointments(void);
void loadAppointments(void);
void saveRecords(void);
void loadRecords(void);

/* Function Prototypes - Utility Functions */
void clearBuffer(void);
void pressEnter(void);
void showHeader(char *title);
int searchPatientByID(int id);
int searchDoctorByID(int id);
int searchAppointmentByID(int id);
int checkUsernameExists(char *username);
void delay(float sec);
void banner();
void bybanner();
#endif
