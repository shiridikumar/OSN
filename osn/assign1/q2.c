#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
char* strrev(char *s)
{
    if (! *s)
        return s;
    int end = strlen(s) - 1, start = 0;

    char temp;
    while (end > start)
    {
        temp = s[end];
        s[end] = s[start];
        s[start] = temp;
        end--;
        start++;
    }
    return s;
}
char *getfile_name(char *string)
{

    int i;
    for (i = strlen(string) - 1; i >= 0; i--)
    {
        if (string[i] == '/' || string[i] == '\\')
        {
            break;
        }
    }
    char *string2 = (char *)calloc(strlen(string - i), sizeof(char));
    strncpy(string2, string + i + 1, strlen(string));
    return string2;
}
int main(int argc, char *argv[])

{
    char *a = getfile_name(argv[1]);
    int f = open(argv[1], O_RDONLY);
    struct stat dir;
    char destination[] = "Assignment/";
    if (stat("/Assignment", &dir) == -1)
    {
        #ifdef _WIN32
            _mkdir("Assignment2", 0700);
            chmod("/Assignment",S_IRWXU);
                char destination[] = "Assignment\\";
        #else
            mkdir("Assignment",0700);
            chmod("/Assignment",S_IRWXU);
            char destination[] = "Assignment/";
        #endif
    }
    else
    {
        perror("Directory");
    }
    strcat(destination,"2_");
    strcat(destination, a);
    int f1 = open(destination, O_WRONLY | O_CREAT);
    chmod(destination,S_IRWXU);
    int buffer_size = 1024 * 1024;
    int parts=argv[2][0]-'0';
    int part=argv[3][0]-'0';
    char *buff = (char *)calloc(1024 * 1024, sizeof(char));
    struct stat file;
    stat(argv[1], &file);
    long long file_size = file.st_size;
    float fs = file_size;
    int part_size=file_size/parts;float ps=part_size;
    lseek(f, file_size, SEEK_SET);
    int res, index=0;
    long long end_point=part_size*(part)-1,start_point=(part_size*part)-part_size;
    long long i = end_point - buffer_size;
    char percent[20];
    while (i > start_point)
    {
        lseek(f, i, SEEK_SET);
        res = read(f, buff, buffer_size);
        strrev(buff);
        index++;
        sprintf(percent, "%.2f %%\r", ((buffer_size * index) / (ps)) * 100);
        write(1, percent, strlen(percent));
        lseek(1, 0, SEEK_SET);
        fflush(stdout);
        write(f1, buff, buffer_size);
        i -= buffer_size;
    }
    
    if (i <= start_point)
    {
        lseek(f, start_point, SEEK_SET);
        res = read(f, buff,i+buffer_size+1);
        buff[i + buffer_size+1] = '\0';
        strrev(buff);
        write(f1, buff, part_size);
        sprintf(percent, "%.2f %%\n", 100.0);

    }
        write(1, percent, strlen(percent));
}