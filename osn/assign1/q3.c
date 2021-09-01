#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

//User defined function for combining two strings
char *combine(char *a, char *b, char *c)
{
    int i;
    for (i = 0; i < strlen(a); i++)
    {
        c[i] = a[i];
    }
    int j;
    for (j = 0; j < strlen(b); j++)
    {
        c[j + i] = b[j];
    }
    return c;
}

//user defined function for extracting filename from a given path
char *getfile_name(char *string, char *result)
{

    int i;
    for (i = strlen(string) - 1; i >= 0; i--)
    {
        if (string[i] == '/' || string[i] == '\\')
        {
            break;
        }
    }
    //  char string2[strlen(string)-i] ;
    strncpy(result, string + i + 1, strlen(string));
    return result;
}

//Function to print permisisions for a file/directory
int permissions(const char *path, char file[])
{
    struct stat ret;

    if (stat(path, &ret) == -1)
    {
        perror("File");
    }
    else
    {
        write(1,"Directory exists\n\n",18);
        char temp[200];
        sprintf(temp, "User has read permission on %s: %s\n", file, (ret.st_mode & S_IRUSR) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
        sprintf(temp, "User has write permission on %s: %s\n", file, (ret.st_mode & S_IWUSR) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
        sprintf(temp, "User has execute permission on %s: %s\n", file, (ret.st_mode & S_IXUSR) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
        write(1,"\n",1);
        sprintf(temp, "Group has read permission on %s: %s\n", file, (ret.st_mode & S_IRGRP) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
        sprintf(temp, "Group has write permission on %s: %s\n", file, (ret.st_mode & S_IWGRP) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
        sprintf(temp, "Group has read permission on %s: %s\n", file, (ret.st_mode & S_IXGRP) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
         write(1,"\n",1);
        sprintf(temp, "Others has read permission on %s: %s\n", file, (ret.st_mode & S_IROTH) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
        sprintf(temp, "Others has read permission on %s: %s\n", file, (ret.st_mode & S_IWOTH) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
        sprintf(temp, "Others has read permission on %s: %s\n", file, (ret.st_mode & S_IXOTH) > 0 ? "Yes" : "No");
        write(1, temp, strlen(temp));
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char result[100];
    char *filename = getfile_name(argv[1], result);

    char prefix1[] = "Assignment/1_";
    char c[strlen(prefix1) + strlen(filename)];
    char prefix2[] = "Assignment/2_";
    char d[strlen(prefix2) + strlen(filename)];
    

    char *combined1 = combine(prefix1, filename, c);
    permissions(combined1, "output_file_1");
    write(1, "\n", 1);

    
    char *combined2 = combine(prefix2, filename, d);
    permissions(combined2, "output_file_2");
    write(1, "\n", 1);


    permissions("Assignment", "directory");

    return 0;
}