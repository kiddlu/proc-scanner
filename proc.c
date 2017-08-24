#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define __USE_GNU 1
#include <fcntl.h>

#include "queue.h"
#include "proc.h"

static unsigned long get_flags(const char *path)
{
    FILE *fp = fopen(path, "r");
    char line[LINE_MAX];
    unsigned long flags;

    if(!fp){
        printf("Can't open file %s\n", path);
        exit(EXIT_FAILURE);
    }

    while(fgets(line, sizeof(line), fp) != NULL) {
      if(strstr(line, "flags:")) {
          char *p = strrchr(line, '\t');
          flags = strtoul(p+1, NULL, 8);
          break;
      }
    }

    fclose(fp);
    return flags;
}

static void getpid_to_str(char *str){
    char *end = str;
    end += sprintf(end, "%lu", (unsigned long)getpid());
    *end = '\0';
    return;
}

stat_t proc_scan(void)
{   
    stat_t info = {0};

    char fdinfo_path[PATH_MAX] = {0};
    char file_path[PATH_MAX] = {0};
    char self_pid[LINE_MAX] = {0};
    
    DIR *proc_dir, *fdinfo_dir;
    struct dirent *ptr;
    unsigned long flags;

    getpid_to_str(self_pid);

    if (!(proc_dir = opendir("/proc"))) {
        printf("Can't opendir /proc\n");
        exit(EXIT_FAILURE);
    }
    while (ptr = readdir(proc_dir)) {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0 ||
           strcmp(ptr->d_name, self_pid) == 0)
            continue;
        if (ptr->d_name[0] <= '0' || ptr->d_name[0] > '9')
            continue;
         
        sprintf(fdinfo_path, "/proc/%s/fdinfo", ptr->d_name);
        if (!(fdinfo_dir = opendir(fdinfo_path))) {
            printf("Can't opendir %s\n", fdinfo_path);
            exit(EXIT_FAILURE);
        }
        while (ptr = readdir(fdinfo_dir)) {
            if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){
                continue;
            }
            sprintf(file_path, "%s/%s", fdinfo_path, ptr->d_name);
            flags = get_flags(file_path);
            if(flags & O_DIRECT) {
                info.direct++;
            } else if(flags & O_SYNC){
                info.sync++;
            } else {
                info.normal++;
            }
        }
        closedir(fdinfo_dir);
    }
    closedir(proc_dir);
    return info;
}
