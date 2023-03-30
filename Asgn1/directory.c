/*
 -------------------------------------
 File: directory.c
 Project: Assignment 1
 -------------------------------------
 Author:  Osaka Khamphavong
 ID:      200700130
 Email:   Kham0130@mylaurier.ca
 Version  2023-01-21
 -------------------------------------
 */

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main() // define the main function
{
    char options[10];
    char cwd[1000]; // for number 3 and 4
    DIR *directory;
    struct dirent *direcread;
    while (1)
    {
        printf("Selects the option(s) appropriately by entering the number:\n"); // print the statement.
        printf(" Enter 1 for creating a directory\n");
        printf(" Enter 2 for removing a directory\n");
        printf(" Enter 3 for printing working directory\n");
        printf(" Enter 4 for changing directory one level up\n");
        printf(" Enter 5 for reading the content of directory\n");
        printf(" Enter 6 for closing the current directory\n");
        printf(" Enter q for exit the program\n");
        scanf("%s", options);
        // create directory
        if (strcmp(options, "1") == 0)
        {
            char name[20];
            printf("Enter the Directory you want to create:\n");
            scanf("%s", name);
            int status = mkdir(name, 0777);
            if (status == 0)
            {
                printf("Directory created successfully.\n");
            }
            else
            {
                printf("Failed to create directory.\n");
            }
        }
        // remove directory
        else if (strcmp(options, "2") == 0)
        {
            char name[20];
            printf("Enter the directory you want to remove:\n");
            scanf("%s", name);
            int status = rmdir(name);
            if (status == 0)
            {
                printf("Directory is removed successfully.\n");
            }
            else
            {
                printf("Failed to remove directory.\n");
            }
        }
        // get current working directory
        else if (strcmp(options, "3") == 0)
        {
            // Get the current working directory
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                printf("Current working directory is: %s\n", cwd);
            }
            else
            {
                printf("getcwd() error");
                return 1;
            }
        }
        // changing directory to the level above current directory
        else if (strcmp(options, "4") == 0)
        {
            int status = chdir("..");
            if (status == 0)
            {
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                {
                    printf("Working directory before operation: %s\n", cwd);
                }
            }
            else
            {
                printf("chdir() error");
                return 1;
            }
            // quit program
        }
        // open and then read directory contents
        else if (strcmp(options, "5") == 0)
        {
            directory = opendir(cwd);
            if (directory == NULL)
            {
                printf("opendir() error");
                return 1;
            }
            // Read the contents of the directory
            printf("\n");
            while ((direcread = readdir(directory)) != NULL)
            {
                printf("%s\n", direcread->d_name);
            }
        }
        // close the directory
        else if (strcmp(options, "6") == 0)
        {
            if (directory != NULL)
            {
                int status = closedir(directory);
                if (status == 0)
                {
                    printf("Directory closed successfully.\n");
                }
                else
                {
                    printf("No directory is currently open.\n");
                }
            }
        }
        else if (strcmp(options, "q") == 0)
        {
            break;
        }
    }
}
