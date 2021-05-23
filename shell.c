#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>


#define LEN_HOSTNAME	30
#define MAX_LEN_LINE    100

int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
    char *getcwd(char *buf, size_t size);
    char *getwd(char *buf);
    char *get_current_dir(void);
    char *buf;
    size_t size;


    printf("\033[47;30m  Welcome~!   Welcome~!   Welcome~!   Welcome~! \033[0m\n");
    printf("\033[47;30m  ⎛⎝(•‿•)⎠⎞   ⎛⎝(•‿•)⎠⎞   ⎛⎝(•‿•)⎠⎞   ⎛⎝(•‿•)⎠⎞ \033[0m\n");
    printf("\033[47;30m   Shell commands :  ls,clear,exit,pwd,my pwd   \033[0m\n");
    printf("\033[47;30m ls command options(-l,-f,-F,-a,-R,-d,-t,-h,-al)\033[0m\n");
    printf("\033[47;30m   Go to higher directory : Just input dir name \033[0m\n");

    while (true) {
        char *s;
        int len;
        char hostname[LEN_HOSTNAME + 1];
        char buf[1024];
        getcwd(buf, 1024);

        memset(hostname, 0x00, sizeof(hostname));
        gethostname(hostname, LEN_HOSTNAME);
        printf("%s""@""%s"":""%s""/MyShell$ ",getpwuid(getuid())->pw_name,hostname,buf);


        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }

        len = strlen(command);

        printf("%d\n", len);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }
        printf("\033[47;34m[%s]\033[0m\n", command);


        /* exit */
        if(!strcmp( command , "exit" )){
            printf("\033[47;31mExit Shell\033[0m\n");
            break;
        }


        if(!strcmp( command , s)){
          chdir(s);
        }

        pid = fork();

        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "\033[47;31mwaitpid failed\033[0m\n");
            }
            printf("\033[47;30mChild process terminated\033[0m\n");
            if (WIFEXITED(status)) {
                printf("\033[47;30mExit status is %d\033[0m\n", WEXITSTATUS(status));
            }
        }
        else {  /* child */
            ret = execve(args[0], args, NULL);
            /*  ls  */
            if(!strcmp( command , "ls" )){
              if(execlp("ls","ls",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -a" )){
              if(execlp("ls","ls","-a",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -al" )){
              if(execlp("ls","ls","-al",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -f" )){
              if(execlp("ls","ls","-f",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -F" )){
              if(execlp("ls","ls","-F",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -R" )){
              if(execlp("ls","ls","-R",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -d" )){
              if(execlp("ls","ls","-d",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -t" )){
              if(execlp("ls","ls","-t",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -h" )){
              if(execlp("ls","ls","-h",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "ls -l" )){
              if(execlp("ls","ls","-l",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "clear" )){
                system("clear");
            }

            if(!strcmp( command , "pwd" )){
              if(execlp("pwd","pwd",NULL)==-1){
                perror("execlp");
              }
            }

            if(!strcmp( command , "my pwd" )){
                printf("%s\n", buf );
            }


            if (ret < 0) {
                fprintf(stderr, "\033[47;31mexecve failed\033[0m\n");
                return 1;
            }
        }
    }
    return 0;
}
