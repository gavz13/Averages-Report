//
//  main.c
//  averagesUpgradedwithJSON
//
//  Created by Gavin Cullen on 2024/07/30.
//

#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_RECORDS 100

typedef struct {
    char name[50];
    int score;
    char grade;
} StudentRecord;

StudentRecord records[MAX_RECORDS];
int numRecords = 0;

void addRecord(void) {
    if (numRecords < MAX_RECORDS) {
        printf("Enter student name: ");
        scanf("%49s", records[numRecords].name);
        printf("Enter student score: ");
        scanf("%d", &records[numRecords].score);

        if (records[numRecords].score >= 90) {
            records[numRecords].grade = 'A';
        } else if (records[numRecords].score >= 80) {
            records[numRecords].grade = 'B';
        } else if (records[numRecords].score >= 70) {
            records[numRecords].grade = 'C';
        } else if (records[numRecords].score >= 60) {
            records[numRecords].grade = 'D';
        } else {
            records[numRecords].grade = 'F';
        }

        numRecords++;
        printf("Record added successfully!\n");
    } else {
        printf("Maximum number of records reached.\n");
    }
}

void displayRecords(void) {
    printf("Student Records:\n");
    for (int i = 0; i < numRecords; i++) {
        printf("Name: %s, Score: %d, Grade: %c\n", records[i].name, records[i].score, records[i].grade);
    }
}

void saveRecordsToJson(void) {
    json_object *root = json_object_new_array();
    for (int i = 0; i < numRecords; i++) {
        json_object *records = json_object_new_object();
        json_object_object_add(record, "name", json_object_new_string(records[i].name));
        json_object_object_add(record, "score", json_object_new_int(records[i].score));
        json_object_object_add(record, "grade", json_object_new_string(&records[i].grade));
        json_object_array_add(root, record);
    }

    FILE *fp = fopen("records.json", "w");
    if (fp) {
        fprintf(fp, "%s", json_object_to_json_string(root));
        fclose(fp);
    }

    json_object_put(root);
}

int main(void) {
    int choice;
    while (1) {
        printf("1. Add new record\n");
        printf("2. Display all records\n");
        printf("3. Save records to JSON file\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                saveRecordsToJson();
                printf("Records saved to records.json\n");
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
