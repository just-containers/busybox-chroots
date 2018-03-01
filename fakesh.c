#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

/* this program does the following:
 * remove /bin/sh
 * relink /bin/sh -> busybox
 * call qemu busybox sh
 * relink /bin/sh -> sh.fake
 */

extern char **environ;

__attribute__ ((noreturn))
void usage(char *prog, int code) {
    fprintf(stderr,"Usage: %s program\n",prog);
    exit(code);
}

void restore_realsh(void) {
    unlink("/bin/sh");
    symlink("busybox","/bin/sh");
}

void restore_fakesh(void) {
    unlink("/bin/sh");
    symlink("sh.fake","/bin/sh");
}

int main(int argc, char *argv[]) {
    pid_t child_pid;
    int child_status = 0;
    int termsig = 0;
    int exitcode = 0;
    int i = 0;
    int newargc = argc + 5;
    char **newargv = NULL;

    restore_realsh();

    child_pid = fork();

    if(child_pid == -1) {
        fprintf(stderr,"Fork failed?! Jeez that's no good\n");
        restore_fakesh();
        return 1;
    }

    if(child_pid == 0) {
        newargv = (char **)malloc(sizeof(char *) * newargc);
        if(newargv == NULL) {
            fprintf(stderr,"Unable to allocate memory for newargv\n");
            return 1;
        }
        newargv[0] = "/bin/qemu-static";
        newargv[1] = "-execve";
        newargv[2] = "-0";
        newargv[3] = argv[0];
        newargv[4] = "/bin/busybox";
        for(i=1;i<argc;i++) {
            newargv[i+4] = argv[i];
        }
        newargv[i+4] = NULL;

        execve("/bin/qemu-static",newargv,environ);
        fprintf(stderr,"Error execing: %s\n",strerror(errno));
        return 1;
    }

    waitpid(child_pid,&child_status,0);

    if(WIFEXITED(child_status)) {
        exitcode = WEXITSTATUS(child_status);
    } else if(WIFSIGNALED(child_status)) {
        termsig = WTERMSIG(child_status);
    }

    restore_fakesh();

    if(termsig != 0) {
        kill(0,termsig);
        sleep(5);
        return 1;
    }

    return exitcode;
}
