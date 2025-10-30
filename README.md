# Hospital Management System - With Doctor Authentication

## 🆕 NEW FEATURE: Doctor Authentication System

Now doctors can log in with username and password!

## Updated Files

You need to update these files:

### 1. **hospital.h** (Updated)
- Added `username` and `password` fields to Doctor structure
- Added `doctorLogin()` function declaration

### 2. **doctor.c** (Updated)
- Added doctor login functionality
- Username and password setup during doctor registration
- 3 login attempts before lockout
- Updated menu to include login option

## How to Use Doctor Authentication

### Step 1: Add a Doctor with Credentials

1. Run the program
2. Go to **Doctor Management** (option 2)
3. Select **Add New Doctor** (option 2)
4. Enter doctor details including:
   - Name
   - Specialization
   - Contact
   - Experience
   - Fee
   - **Username** (new!)
   - **Password** (new!)

Example:
```
Enter doctor name: John Smith
Enter specialization: Cardiology
Enter contact number: 1234567890
Enter years of experience: 10
Enter consultation fee: 150
Enter username (for login): drjohn
Enter password: john123
```

### Step 2: Login as Doctor

1. Go to **Doctor Management**
2. Select **Doctor Login** (option 1)
3. Enter your username and password
4. You get 3 attempts

Example:
```
=========================================
  DOCTOR LOGIN
=========================================

Enter username: drjohn
Enter password: john123

Login successful! Welcome Dr. John Smith
```

## Features

✅ **Secure Login**: Username and password required
✅ **3 Attempts**: Prevents brute force attacks
✅ **Easy Setup**: Create credentials during doctor registration
✅ **View Usernames**: Can see usernames in doctor list
✅ **Update Credentials**: Can change username/password later

## Updated Menu Structure

### Doctor Management Menu
```
1. Doctor Login          <- NEW!
2. Add New Doctor
3. View All Doctors
4. Search Doctor
5. Update Doctor
6. Back to Main Menu
```

## Security Features (Beginner Level)

- **Password Storage**: Plain text (beginner style - in real apps, use hashing!)
- **Login Attempts**: Maximum 3 attempts
- **Access Control**: Login required before accessing doctor features
- **Credential Update**: Doctors can update their own password

## Code Changes Summary

### Doctor Structure (hospital.h)
```c
struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    char contact[15];
    int experience;
    float consultationFee;
    char username[30];      // NEW
    char password[30];      // NEW
};
```

### New Function (doctor.c)
```c
int doctorLogin() {
    // Returns doctor ID if successful
    // Returns -1 if failed
}
```

## Sample Test Scenario

1. **Add First Doctor:**
   - Username: `admin`
   - Password: `admin123`

2. **Try to Login:**
   - Success: Welcome message
   - Fail: "Invalid username or password!"

3. **Wrong Password 3 Times:**
   - Result: "Too many failed attempts! Access denied."

## Notes for Beginners

### Why This Is Beginner-Style:

✅ **Simple string comparison** - No encryption
✅ **Plain text passwords** - Easy to understand
✅ **Basic counter** - Simple attempt tracking
✅ **Direct return values** - Easy to follow logic

### In Real Applications:

❌ Never store passwords in plain text!
✅ Use password hashing (bcrypt, SHA-256)
✅ Use secure session management
✅ Add password complexity requirements
✅ Add account lockout after failed attempts

## Compilation

Same as before:

```bash
gcc main.c patient.c doctor.c appointment.c records.c reports.c fileops.c utils.c -o hospital.exe
```

## Testing the Authentication

### Test Case 1: Successful Login
```
Username: drjohn
Password: john123
Expected: "Login successful! Welcome Dr. John Smith"
```

### Test Case 2: Wrong Password
```
Username: drjohn
Password: wrongpass
Expected: "Invalid username or password!"
```

### Test Case 3: Non-existent User
```
Username: nobody
Password: anything
Expected: "Invalid username or password!"
```

### Test Case 4: Too Many Attempts
```
Attempt 1: Wrong password
Attempt 2: Wrong password
Attempt 3: Wrong password
Expected: "Too many failed attempts! Access denied."
```

## Future Enhancements (Ideas)

- Password encryption
- "Forgot password" feature
- Doctor dashboard after login
- View only assigned patients
- Track login history
- Admin account for managing doctors
- Password complexity requirements
- Session timeout

## Updated File List

1. ✅ hospital.h (UPDATED)
2. ✅ doctor.c (UPDATED)
3. ✅ main.c (no change)
4. ✅ patient.c (no change)
5. ✅ appointment.c (no change)
6. ✅ records.c (no change)
7. ✅ reports.c (no change)
8. ✅ fileops.c (no change)
9. ✅ utils.c (no change)

Only **2 files changed**! Easy to update! 😊

## Important Reminder

After updating the code:
1. Delete old `.dat` files (or they won't have username/password fields)
2. Add new doctors with credentials
3. Test the login system

Happy coding! 🎉
