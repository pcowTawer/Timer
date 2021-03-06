#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc!=2 && argc!=3)
    {
        printf("Format: timer <Program path> [<File name>]");
        return 1;
    }

    char* txt_file_name = (char*)malloc(sizeof(char) * 255);
    
    if (argc == 3)
    {
        snprintf(txt_file_name, sizeof(char) * 255, "%s", argv[2]);
    } 
    else
    {
        txt_file_name = "timer.txt";
    }

    if(!(strcmp(argv[1], "help")) || (!strcmp(argv[1], "/?")))
    {
        printf("Creates a file (default timer.txt) that contains the program start time, program end time, program runtime");
        printf("Format: timer <program path> [<file name>]");
        return 0;
    }
    FILE *f;
    if (!(f = fopen(argv[1], "rt")))
    {
        printf("Can't open program: %s", argv[1]);
        return 1;
    }
    fclose(f);
    char* command_start = (char*)malloc(sizeof(char) * 255);
    char* command_write = (char*)malloc(sizeof(char) * 255);
    char* command_add =   (char*)malloc(sizeof(char) * 255);
    snprintf(command_start, sizeof(char) * 255, "%s%s", "start /w ", argv[1]);
    snprintf(command_write, sizeof(char) * 255, "%s%s", "echo %time% > ", txt_file_name);
    snprintf(command_add, sizeof(char) * 255, "%s%s", "echo %time% >> ", txt_file_name);

    system(command_write);
    system(command_start);
    system(command_add);
    
    free(command_write);
    free(command_start);
    free(command_add);

    f = fopen(txt_file_name, "r+t");
    char buf;
    int hour1 = 0, hour2 = 0;
    int min1 = 0, min2 = 0;
    double sec1 = 0, sec2 = 0;


    fscanf(f, "%c", &buf);
    hour1 += 10 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    hour1 += (int)buf - 48;
    fscanf(f, "%c", &buf);
    
    fscanf(f, "%c", &buf);
    min1 += 10 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    min1 += (int)buf - 48;
    fscanf(f, "%c", &buf);

    fscanf(f, "%c", &buf);
    sec1 += 10 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    sec1 += (int)buf - 48;
    fscanf(f, "%c", &buf);
    fscanf(f, "%c", &buf);
    sec1 += 0.1 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    sec1 += 0.01 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    fscanf(f, "%c", &buf);

    fscanf(f, "%c", &buf);
    hour2 += 10 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    hour2 += (int)buf - 48;
    fscanf(f, "%c", &buf);

    fscanf(f, "%c", &buf);
    min2 += 10 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    min2 += (int)buf - 48;
    fscanf(f, "%c", &buf);

    fscanf(f, "%c", &buf);
    sec2 += 10 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    sec2 += (int)buf - 48;
    fscanf(f, "%c", &buf);
    fscanf(f, "%c", &buf);
    sec2 += 0.1 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    sec2 += 0.01 * ((int)buf - 48);
    fscanf(f, "%c", &buf);
    fseek(f, 0, SEEK_END);

    double result = hour2*3600 - hour1*3600 + min2*60 - min1*60 + sec2 - sec1;
    char* result_print;
    fprintf(f, "%.2f", result);

    fclose(f);
    return 0;
}