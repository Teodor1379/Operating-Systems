#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <err.h>
#include <errno.h>



const char* ERROR_EXEC = "Error while executing command!";



void executingCommandSafe(const char*, const char*);




int main(void) {
    executingCommandSafe("/bin/date", "date");

    return 0;
}



void executingCommandSafe(const char* commandPath, const char* nameCommand) {
    assert(commandPath  !=  NULL);
    assert(nameCommand  !=  NULL);

    int result = execl(commandPath, nameCommand, (char*)(NULL));

    if (result == -1) {
        err(1, "%s: %s", ERROR_EXEC, commandPath);
    }
}
