#ifndef DATABASE
#define DATABASE
#include "student.h"

struct StudentDatabase {
    StudentNode* head;
};

StudentDatabase* createDatabase(void);
void storeOutput(StudentDatabase* db, const char* filename);
void parseInput(StudentDatabase* db, const char* filename);

#endif
