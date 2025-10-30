# Hospital Management System - CRUSH Configuration

## Build Commands
```bash
# Build with CodeBlocks (recommended)
codeblocks HospitalManagementSystem.cbp

# Manual GCC compilation (alternative)
gcc -Wall -g *.c -o hospital
```

## Code Style Guidelines
- **File Organization**: Each module has separate .c/.h files (patient.c, doctor.c, etc.)
- **Naming**: Snake_case for functions and variables, PascalCase for struct names
- **Headers**: Always include "hospital.h" first, then standard library headers
- **Functions**: Group related functions in files (patient functions in patient.c)
- **Global Variables**: Use extern declarations in header, define in main.c
- **Error Handling**: Check array bounds before insertion
- **Input Validation**: Use clearBuffer() after scanf to handle input properly

## Project Structure
- Main entry point: main.c
- Header: hospital.h (contains all structs and function declarations)
- Modules: patient.c, doctor.c, appointment.c, records.c, reports.c, utils.c, fileops.c
- Data files: patients.dat (and similar for other entities)

## Development Notes
- Uses CodeBlocks project file (.cbp) for IDE integration
- No automated tests - manual testing required
- Data persistence through binary files (*.dat)
- Console-based interface with clear menu structure