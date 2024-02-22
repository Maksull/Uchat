#include "../inc/server.h"

// Function to make the current process a daemon
void init_daemon() {
    // Declare variables to hold process ID and session ID
    
    // Fork the process to create a child process
    // Fork the process
    //if () { // Check if fork failed
        // If fork fails, log the error and exit the program
        // Log fork error
        // Exit the program with failure status
    //}

    // If we're in the parent process, print the child process id and exit
    //if () { // Check if parent process
        // Print child process ID
         // Exit the program with success status
    //}

    // Set umask to 0 to allow full access to files
    
    // Create a new session for the child process to become the session leader
    // Create a new session
    //if () { // Check if creating session failed
        // If creating session fails, log the error and exit the program
        // Log setsid error
        // Exit the program with failure status
    //}

    // Reset the handling of termination signal(SIGTERM) to default
}
