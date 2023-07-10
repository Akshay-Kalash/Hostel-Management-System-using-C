#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int rollNumber;
    char roomNumber[10];
} Student;

// Function prototypes
void addStudent(Student* students, int* numStudents);
void displayStudents(const Student* students, int numStudents);
void searchStudentByRollNumber(const Student* students, int numStudents);
void sortStudentsByRollNumber(Student* students, int numStudents);
void saveStudentsToFile(const Student* students, int numStudents, const char* filename);
int loadStudentsFromFile(Student* students, int* numStudents, const char* filename);
void freeStudents(Student* students, int numStudents);
void clearInputBuffer();

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    char filename[50];

    printf("=== Hostel Management System ===\n\n");

    while (1) {
        printf("1. Add a student\n");
        printf("2. Display all students\n");
        printf("3. Search student by roll number\n");
        printf("4. Sort students by roll number\n");
        printf("5. Save student records to a file\n");
        printf("6. Load student records from a file\n");
        printf("7. Quit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addStudent(students, &numStudents);
                break;
            case 2:
                displayStudents(students, numStudents);
                break;
            case 3:
                searchStudentByRollNumber(students, numStudents);
                break;
            case 4:
                sortStudentsByRollNumber(students, numStudents);
                break;
            case 5:
                printf("Enter the filename to save student records: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveStudentsToFile(students, numStudents, filename);
                break;
            case 6:
                printf("Enter the filename to load student records: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                if (loadStudentsFromFile(students, &numStudents, filename)) {
                    printf("Student records loaded successfully.\n");
                }
                break;
            case 7:
                printf("Thank you for using the Hostel Management System.\n");
                freeStudents(students, numStudents);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    }
}

void addStudent(Student* students, int* numStudents) {
    if (*numStudents >= MAX_STUDENTS) {
        printf("Hostel is full. Cannot add more students.\n");
        return;
    }

    Student newStudent;

    printf("Enter the name of the student: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    while (1) {
        printf("Enter the roll number of the student: ");
        if (scanf("%d", &newStudent.rollNumber) != 1 || newStudent.rollNumber <= 0) {
            printf("Invalid roll number. Please enter a positive integer.\n");
            clearInputBuffer();
        } else {
            clearInputBuffer();
            break;
        }
    }

    printf("Enter the room number of the student: ");
    fgets(newStudent.roomNumber, sizeof(newStudent.roomNumber), stdin);
    newStudent.roomNumber[strcspn(newStudent.roomNumber, "\n")] = '\0';

    students[*numStudents] = newStudent;
    (*numStudents)++;

    printf("Student added successfully!\n");
}

void displayStudents(const Student* students, int numStudents) {
    if (numStudents == 0) {
        printf("No students in the hostel.\n");
        return;
    }

    printf("=== Hostel Students ===\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Room Number: %s\n\n", students[i].roomNumber);
    }
}

void searchStudentByRollNumber(const Student* students, int numStudents) {
    int rollNumber;
    printf("Enter the roll number to search: ");
    scanf("%d", &rollNumber);
    clearInputBuffer();

    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("=== Student Found ===\n");
            printf("Name: %s\n", students[i].name);
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Room Number: %s\n", students[i].roomNumber);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void sortStudentsByRollNumber(Student* students, int numStudents) {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {

(students[j].rollNumber > students[j + 1].rollNumber); {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Students sorted by roll number.\n");
}

void saveStudentsToFile(const Student* students, int numStudents, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%s;%d;%s\n", students[i].name, students[i].rollNumber, students[i].roomNumber);
    }

    fclose(file);
    printf("Student records saved to %s.\n", filename);
}

int loadStudentsFromFile(Student* students, int* numStudents, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return 0;
    }

    int count = 0;
    char line[200];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (count >= MAX_STUDENTS)
            break;

        line[strcspn(line, "\n")] = '\0';

        char* token = strtok(line, ";");
        strcpy(students[count].name, token);

        token = strtok(NULL, ";");
        students[count].rollNumber = atoi(token);

        token = strtok(NULL, ";");
        strcpy(students[count].roomNumber, token);

        count++;
    }

    fclose(file);
    *numStudents = count;

    printf("%d student records loaded from %s.\n", count, filename);
    return 1;
}

void freeStudents(Student* students, int numStudents) {
    // No dynamic memory allocation, so no need to free memory
}

void clearInputBuffer() {
    while (getchar() != '\n');
}
