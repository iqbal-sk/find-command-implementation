#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int is_directory(char *file_name,char *cur_path);
void search(char *cur_path,char *file);

bool found = false;
int main()
{
    char file[100];
    // Starting directory to search for given file.
    char home[300] = "/home/smiqbal";
    printf("Enter the file name you want to search:\n");
    scanf("%s",file);
    search(home,file); //recursivly search for file starting from /home/smiqbal
}

void search(char *cur_path,char *file)
{
        DIR *dir;
        dir = opendir(cur_path);
        if(dir==NULL)
        {
            printf("There is no such directory  %s\n",cur_path);
            exit(1);
        }
        struct dirent *dp;
        char sub_directories[20][300]; //in order to store sub directories under cur_path
        int sub_dir_count=0,i=0;


        while((dp = readdir(dir)) != NULL )
        {
            if( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") ) continue;

            if(is_directory(dp->d_name,cur_path)) //if it is a sub directory we store absolute path of that sub_directory in sub_directories[]
            {
                strcpy(sub_directories[sub_dir_count],cur_path); //cur_path will be stored
                strcat(sub_directories[sub_dir_count],"/");
                strcat(sub_directories[sub_dir_count],dp->d_name); //absolute_path of sub_directory stored.
                sub_dir_count++;
            }

                if(strcmp(file,dp->d_name) == 0) //if file found
                {
                    found = true;
                    printf("File Found at : ");
                    printf("%s", cur_path);
                    printf("/%s\n", file);
                }

        }

        // searches in the sub directories under current_path recursivly
        for(i=0;i<sub_dir_count;i++)
        {
            search(sub_directories[i], file);
        }

        if(strcmp(cur_path,"/home/smiqbal")==0 && found == false)
        {
            printf("File not present !!\n");
        }


}

int is_directory(char *file_name,char *cur_path)
{
    struct stat sb;
    char abs_path[300];
    strcpy(abs_path,cur_path);
    strcat(abs_path,"/");
    strcat(abs_path,file_name);
    if (stat(abs_path, &sb) == 0 && S_ISDIR(sb.st_mode)) return 1;
    else return 0;
}
