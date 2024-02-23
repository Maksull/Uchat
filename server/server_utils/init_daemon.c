#include "../inc/server.h"

static void fork_process()
{
    // Fork the process
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // If in the parent process, print the child process ID and exit
    if (pid > 0)
    {
        printf("The process id is: %d\n", pid);
        exit(EXIT_SUCCESS);
    }
}

static void create_new_session()
{
    // Create a new session for the child process to become the session leader
    pid_t sid = setsid();
    if (sid < 0)
    {
        perror("setsid");
        exit(EXIT_FAILURE);
    }
}

// Function to make the current process a daemon
void init_daemon()
{
    // Fork the process to create a child process
    fork_process();

     // Change the file mode mask to allow full access to files
    umask(0);

    // Create a new session for the child process to become the session leader
    create_new_session();

    // Reset the handling of termination signal to default
    signal(SIGTERM, SIG_DFL);
}
