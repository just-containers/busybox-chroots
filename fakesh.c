#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

extern char **environ;


__attribute__ ((noreturn))
void usage(char *prog, int code) {
    fprintf(stderr,"Usage: %s program\n",prog);
    exit(code);
}

int main(int argc, char *argv[]) {
    int i = 0;
    int newargc = argc + 5;

    char **newargv = (char **)malloc(sizeof(char *) * newargc);
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
