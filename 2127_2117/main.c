#include <stdio.h>
#include "database.h"
#include "student.h"
#include "course.h"
#include "sDB.h"

int main(void) {
    StudentDatabase* db = createDatabase();
    const char* inputFile = "input.txt";
    const char* outputFile = "2127_2117.out";

    parseInput(db, inputFile);

    storeOutput(db, outputFile);
    return 0;
}

