#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "executor.h"
#include "AFHU_shell.h"

#define BUFFER_LEN 999

int main(int argc, char *argv[])
{
    // Initializing Input buffer and commands to 0 and defining/declaring them
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };

    char directory[999];

    //function in c that gets the pathname of where you are located and saves it to a variable,  more info: pubs.opengroup.org/onlinepubs/009695399/functions/getcwd.html
    getcwd(directory, 999);

    // #6. Command line prompt  - (first line that prints, it prints pathname of current directory followed by a doller sign
    path_Name(directory);

   
// Parse the commands provided using argc and argv and then send the values through functions to executor.c

    // An infinite loop taking commands from the user
    // fgets is stating take input from stdin and copy it to buffer (more specifically copy BUFFER_LEN amount (which is 999 here) into buffer)
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {	
     	char* argument_array[999];
	    
	// Perform string tokenization to get the command and argument

        //stripping the newline char
        if (buffer[strlen(buffer)-1] == '\n') {
            buffer[strlen(buffer)-1] = ' ';
        }

        // Tokenizing the string and saving each token into argument array
        char* token = strtok(buffer, " ");

        int i = 0;
        while (token != NULL) {
          argument_array[i++] = token;
          token = strtok(NULL, " ");
        }

        //First token element/argument is set as the command
        strcpy(command, argument_array[0]);


// if the command matches the preset commands call the function that will execute it
        
	// #1. - Internal commands:
	if (strcmp(command, "cd") == 0){
            ChangeDir(argument_array);
        }
        else if (strcmp(command, "clr") == 0){
            clearTerminal();
        }
        else if (strcmp(command, "dir") == 0){
            swd(directory);
        }
        else if (strcmp(command, "environ") == 0){
            environ();
        }
        else if (strcmp(command, "echo") == 0){
            //i is the size of the array thats filled defined above
            echo(argument_array, i);
        }
        else if (strcmp(command, "help") == 0){
            help();
        }
        else if (strcmp(command, "pause") == 0){
            mypause();
        }
	//else if (strcmp(command, "\0") == 0 || strcmp(command, "") == 0 || strcmp(command, " ") == 0 || command == 0 || command == NULL){}
	else if (command == 0){
	}
        else if (strcmp(command, "quit") == 0){
            return EXIT_SUCCESS;
        }
        // Unsupported command
        else{
            myPrint("Unsupported command, use help to display the manual\n", 31);
        }

	//keep updating Command Line Prompt
        getcwd(directory, 999);
	path_Name(directory);
    }
    return EXIT_SUCCESS;
}