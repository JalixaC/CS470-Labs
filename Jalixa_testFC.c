#include "Jalixa_libFC.h"
#include <ctype.h>  // For tolower()

// Function to display the menu
void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
}

int main() {
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is Jalixa Castillo\n\n"
                          "I am a computer science student,in their second to last quarter.\n"
			  "I like computers and learning more about them.\n"
                          "This project involves creating a file system library in C.\n"
                          "I hope you find my code understandable and useful!";
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    while (1) {
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:  // Creating a file with fileCreate()
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin); //grabbing the user's input
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Openning a file with fileOpen()
                printf("Enter the filename to open: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                file_index = fileOpen(filename);
                if (file_index == -1) { //storing index for other options
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file with fileWrite()
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);

                    if (fileWrite(file_index, introduction) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file with fileRead()
		//if index is not -1, there is a file that exists
		 if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                 } else {
		    int bytes = fileRead(file_index, buffer, sizeof(buffer) - 1);
    			if (bytes > 0) {
       				 buffer[bytes] = '\0';  // Null-terminate the string
				//telling the user the bytes read
      				 printf("Read %d bytes:\n%s\n", bytes, buffer);
   			 } else {
        			printf("Failed to read the file.\n");
   			 }
		}
                break;

	    case 5: //Close a file with fileClose()
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
		   if(fileClose(file_index) == 0) { //if return value is 0
			//worked properly 
		        printf("Closed file successfully!");
		   }else{
			printf("Error closing file");
			return -1;
		   }
		}
		break;

	    case 6: //Deleting a file with fileDelete()
                printf("Enter the filename to delete: ");
                fgets(filename, MAX_FILENAME, stdin);//user input 
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileDelete(filename) != 0) {
                    printf("Error deleting file.\n");
                }
                waitForUser();
                break;

            case 7:  // Exitting with 0
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}
