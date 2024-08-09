#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "course.h"
#include "student.h"
#include "sDB.h"


// function to create a new database using StudentDatabase structure
// we will be traversing this database throughout our project
StudentDatabase* createDatabase(void) {
    StudentDatabase* db = (StudentDatabase*)malloc(sizeof(StudentDatabase));
    db->head = NULL;
    return db;
}


// function to write the final resultant database in the file entered in main.c file
void storeOutput(StudentDatabase* db, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Unable to find the output file\n");
        perror("Unable to find the output file\n");
        return;
    }
    StudentNode* student = db->head;
    while (student) {
        fprintf(file, "%d, %s, %.1f, %d\n", student->rollNo, student->name, student->cgpa, student->numSubjects);
        CourseNode* course = student->coursesHead;
        while (course) {
            fprintf(file, "%d, %d\n", course->courseCode, course->marks);
            course = course->next;
        }
        student = student->next;
    }
    fclose(file);
}


// function to parse the input(.txt) file and perform commands given in it accordingly
void parseInput(StudentDatabase* studentDB, const char* inputFileName) {
    FILE* inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        printf("Unable to find the input file\n");
        perror("Unable to find the input file\n");
        return;
    }

    char currentLine[256];
    char currentCommand[50] = "initial";
    int currentStudentRollNo = -1;

    while (fgets(currentLine, sizeof(currentLine), inputFile)) {
        char* trimmedLine = strtok(currentLine, "\n");

        if (!trimmedLine || trimmedLine[0] == '#') {
            if (trimmedLine && strstr(trimmedLine, "initial database")) {
                strcpy(currentCommand, "initial");
            } 
            else if (trimmedLine && strstr(trimmedLine, "add student")) {
                strcpy(currentCommand, "addStudent");
            } 
            else if (trimmedLine && strstr(trimmedLine, "add course")) {
                strcpy(currentCommand, "addCourse");
            } 
            else if (trimmedLine && strstr(trimmedLine, "modify student")) {
                strcpy(currentCommand, "modifyStudent");
            } 
            else if (trimmedLine && strstr(trimmedLine, "modify course")) {
                strcpy(currentCommand, "modifyCourse");
            } 
            else if (trimmedLine && strstr(trimmedLine, "delete student")) {
                strcpy(currentCommand, "deleteStudent");
            } 
            else if (trimmedLine && strstr(trimmedLine, "delete course")) {
                strcpy(currentCommand, "deleteCourse");
            }
            continue;
        }

        char* lineTokens[4];
        int tokenCount = 0;
        char* token = strtok(trimmedLine, ", ");
        while (token) {
            lineTokens[tokenCount++] = token;
            token = strtok(NULL, ", ");
        }

        if (!strcmp(currentCommand, "initial")) {
            if (tokenCount == 4) {
                int studentRollNo = atoi(lineTokens[0]);
                currentStudentRollNo = studentRollNo;
                char* studentName = lineTokens[1];
                float studentCGPA = atof(lineTokens[2]);
                int totalSubjects = atoi(lineTokens[3]);
                addStudent(studentDB, studentRollNo, studentName, studentCGPA, totalSubjects);
            } else if (tokenCount == 2 && currentStudentRollNo != -1) {  
                int courseCode = atoi(lineTokens[0]);
                int courseMarks = atoi(lineTokens[1]);
                addCourseInitial(studentDB, currentStudentRollNo, courseCode, courseMarks);
            } else {
                printf("Invalid input encountered\n");
            }
        }  
        else if (strcmp(currentCommand, "addStudent") == 0 && tokenCount == 4) {
            int studentRollNo = atoi(lineTokens[0]);
            char* studentName = lineTokens[1];
            float studentCGPA = atof(lineTokens[2]);
            int totalSubjects = atoi(lineTokens[3]);
            addStudent(studentDB, studentRollNo, studentName, studentCGPA, totalSubjects);
        } 
        else if (strcmp(currentCommand, "addCourse") == 0 && tokenCount == 3) {
            int studentRollNo = atoi(lineTokens[0]);
            int courseCode = atoi(lineTokens[1]);
            int courseMarks = atoi(lineTokens[2]);
            addCourse(studentDB, studentRollNo, courseCode, courseMarks);
        } 
        else if (strcmp(currentCommand, "modifyStudent") == 0 && tokenCount == 2) {
            int studentRollNo = atoi(lineTokens[0]);
            float newCGPA = atof(lineTokens[1]);
            modifyStudent(studentDB, studentRollNo, newCGPA);
        } 
        else if (strcmp(currentCommand, "modifyCourse") == 0 && tokenCount == 3) {
            int studentRollNo = atoi(lineTokens[0]);
            int courseCode = atoi(lineTokens[1]);
            int newMarks = atoi(lineTokens[2]);
            modifyCourse(studentDB, studentRollNo, courseCode, newMarks);
        } 
        else if (strcmp(currentCommand, "deleteStudent") == 0 && tokenCount == 1) {
            int studentRollNo = atoi(lineTokens[0]);
            deleteStudent(studentDB, studentRollNo);
        } 
        else if (strcmp(currentCommand, "deleteCourse") == 0 && tokenCount == 2) {
            int studentRollNo = atoi(lineTokens[0]);
            int courseCode = atoi(lineTokens[1]);
            deleteCourse(studentDB, studentRollNo, courseCode);
        } else {
            printf("Invalid input encountered\n");
        }
    }
    fclose(inputFile);
}
