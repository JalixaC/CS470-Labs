#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    pid_t pid;
    int status; 
    const int numberOfChildren =10;

    //Array of commands
    char  *commands[][3]={
        {"ls", "-l",NULL},  //command to list directory contents
        {"echo", "Hello from  child process", NULL},   //printing to screen command
        {"date",NULL,NULL}, //presenting the date to the user with time
    	{"echo", "Hello Jalixa", NULL}, //printing to screen with my name
    	{"touch","childMake.txt",NULL}, //make a file named childMake.txt
    	{"mkdir", "childDir",NULL}, //command to make a directory
    	{"echo","Hello again",NULL}, //command to say hello again
    	{"touch","child7.txt",NULL}, //creating another file
    	{"pwd","-P",NULL}, //preseting the path of the current direcory we are in
    	{"mkdir","childFolder2",NULL}, }; //making another directory

   printf("Parent process PID:  %d\n", getpid()); 

    //using a for loop to create 10 new children
   for  (int i = 0; i <numberOfChildren; i++) {
      pid = fork(); //the fork() creates a new child and returns 0 when it's created 
      
    //error handling if the child isn't able to be created, when pid is less then 0
      if (pid<0){   
	perror("Fork failed");
	exit(EXIT_FAILURE);
	
	//if pid returns 0, then we are in the child and the child was created
     }else if (pid ==0){ 
	printf("Child Process  PID: %d - Executing Commands: %s\n", getpid(), commands[i][0]);
	//executes the commands in the array
	execvp(commands[i][0],commands[i]);
	perror("Exec failed");
        exit(EXIT_FAILURE);
    }
    }
    
   printf("print out history: -----\n");
    //makes the parent wait for the child to finish execution 
   while ((pid=wait(&status))>0){
        printf("Child process with PID  %d finished \n",pid);
   }
return EXIT_SUCCESS;
}
