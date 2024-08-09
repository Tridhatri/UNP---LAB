#include "student.h"
#include "database.h"
#include "course.h"
#include "sDB.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// function to creating a new student using student structure 
StudentNode* createStudent(int rollNo, char* name, float cgpa, int numSubjects) {
    StudentNode* student = (StudentNode*)malloc(sizeof(StudentNode));
    student->rollNo = rollNo;
    strcpy(student->name, name);
    student->cgpa = cgpa;
    student->numSubjects = numSubjects;
    student->coursesHead = NULL;
    student->prev = NULL;
    student->next = NULL;
    return student;
}


// function to add a new student 
void addStudent(StudentDatabase* db, int rollNo, char* name, float cgpa, int numSubjects) {
    if (rollNo <= 0) {
        printf("Please enter a valid roll no to add the student\n");
        return;
    }

    StudentNode* current = db->head;
    while (current) {
        if (current->rollNo == rollNo) {
            printf("Student with roll no %d is already present. Please consider adding a student with a different roll no.\n", rollNo);
            return;
        }
        current = current->next;
    }

    StudentNode* student = createStudent(rollNo, name, cgpa, numSubjects);
    if (!db->head) {
        db->head = student;
    } else {
        current = db->head;
        while (current->next) {
            current = current->next;
        }
        current->next = student;
        student->prev = current;
    }
}


// function to modify an existing student's cgpa
void modifyStudent(StudentDatabase* db, int rollNo, float newCgpa) {
    if (rollNo <= 0) {
        printf("Please enter a valid roll no to modify the student\n");
        return;
    }
    if (newCgpa < 0 || newCgpa > 10) {
        printf("Please enter a valid cgpa to modify the student\n");
        return;
    }

    StudentNode* student = db->head;
    while (student && student->rollNo != rollNo) {
        student = student->next;
    }

    if (student) {
        student->cgpa = newCgpa;
    } else {
        printf("No student with roll no %d found. Please consider adding the student first.\n", rollNo);
    }
}


// function to delete student from the database
void deleteStudent(StudentDatabase* db, int rollNo) {
    if (rollNo <= 0) {
        printf("Please enter a valid roll no to delete the student\n");
        return;
    }

    StudentNode* student = db->head;
    while (student && student->rollNo != rollNo) {
        student = student->next;
    }

    if (student) {
        if (student->prev) {
            student->prev->next = student->next;
        }
        if (student->next) {
            student->next->prev = student->prev;
        }
        if (student == db->head) {
            db->head = student->next;
        }
        CourseNode* course = student->coursesHead;
        while (course) {
            CourseNode* temp = course;
            course = course->next;
            free(temp);
        }
        free(student);
    } else {
        printf("No student with roll no %d found. Please consider adding the student first.\n", rollNo);
    }
}
