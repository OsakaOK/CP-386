/*
 -------------------------------------
 File: filecopy.c
 Project: Assignment 1
 -------------------------------------
 Author:  Osaka Khamphavong
 ID:      200700130
 Email:   Kham0130@mylaurier.ca
 Version  2023-01-21
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 3)
    {
        printf("Insufficient parameters passed.\n");
        exit(1);
    }

    // Open input file
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
    {
        printf("Error: Unable to open input file name: %s\n", argv[1]);
        exit(1);
    }

    // Create and open the file
    int output_fd = open(argv[2], O_RDWR, 0777);
    if (output_fd == -1)
    {
        printf("Error: Unable to open/create output file\n");
        exit(1);
    }

    // Copy data from input file to output file
    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0)
    {
        write(output_fd, buffer, bytes_read);
    }

    // Close files
    close(input_fd);
    close(output_fd);

    printf("The contents of %s have been successfully copied into the %s file\n", argv[1], argv[2]);
    return 0;
}