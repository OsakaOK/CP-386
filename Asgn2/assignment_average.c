/*
 -------------------------------------
 File: assignment_average.c
 Project: Assignment 2
 -------------------------------------
 Author:  Osaka Khamphavong
 ID:      200700130
 Email:   Kham0130@mylaurier.ca
 Version  2023-02-05
 -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define ROWS 10
#define COLS 6

// utility function
void calculate_average(int assignment_id, int grades[ROWS][COLS], int chapter_id)
{
    int sum = 0, i;
    for (i = 0; i < ROWS; i++)
    {
        sum += grades[i][assignment_id + (chapter_id - 1) * 2];
    }
    float avg = (float)sum / ROWS;
    printf("Assignment %d average for Chapter %d = %.5f\n", assignment_id + 1, chapter_id, avg);
}

int main()
{
    // read data from the file
    int grades[ROWS][COLS];
    FILE *fp;
    fp = fopen("sample_in_grades.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            fscanf(fp, "%d", &grades[i][j]);
        }
    }
    fclose(fp);

    int chapter_id;
    for (chapter_id = 1; chapter_id <= 3; chapter_id++)
    {
        // create GTA
        pid_t GTA_process = fork();
        if (GTA_process == 0)
        {
            int assignment_id;
            for (assignment_id = 0; assignment_id < 2; assignment_id++)
            {
                // create TA and print out result
                pid_t TA_process = fork();
                if (TA_process == 0)
                {
                    calculate_average(assignment_id, grades, chapter_id);
                    exit(0);
                }
                else
                {
                    wait(NULL);
                }
            }
            exit(0);
        }
        else
        {
            wait(NULL);
        }
    }
    return 0;
}
