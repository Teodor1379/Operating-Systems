#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <err.h>
#include <errno.h>



const char* ERROR_EXEC = "Error while executing command!";



void executingCommandSafeArg1(const char*, const char*, const char*);



int main(void) {
    executingCommandSafeArg1("/bin/sleep", "sleep", "60");
}



void executingCommandSafeArg1(const char* commandPath, const char* nameCommand, const char* arg1) {
    assert(commandPath  !=  NULL);
    assert(nameCommand  !=  NULL);
    assert(arg1         !=  NULL);

    int result = execl(commandPath, nameCommand, arg1, 0);

    if (result == -1) {
        err(2, "%s: %s", ERROR_EXEC, commandPath);
    }
}
