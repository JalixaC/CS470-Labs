#include "Jalixa_libFC.h"

// Global variables
FileEntry file_table[MAX_FILES];  // File table to track files
int file_count = 0;               // Number of files in the system

// Create a new file
int fileCreate(const char *filename) {

    // Check if file already exists
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
            return -1;
        }
    }

    // Create the file on the local disk
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to create file '%s'.\n", filename);
        return -1;
    }
    fclose(file);

    // Add file to the file table
    strcpy(file_table[file_count].filename, filename);
    file_table[file_count].size = 0;
    file_table[file_count].is_open = 0;  // File is closed
    file_count++;

    printf("File '%s' created successfully.\n", filename);
    return 0;
}

// Open a file
int fileOpen(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            if (file_table[i].is_open) {
                printf("Error: File '%s' is already open.\n", filename);
                return -1;
            }
            file_table[i].is_open = 1;  // Mark file as open
            printf("File '%s' opened successfully.\n", filename);
            return i;  // Return file index
        }
    }

    printf("Error: File '%s' not found.\n", filename);
    return -1;
}

// Write data to a file
int fileWrite(int file_index, const char *data) {

    if (!file_table[file_index].is_open) {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }

    int data_size = strlen(data);

    // Write data to the local file
    FILE *file = fopen(file_table[file_index].filename, "w");
    if (!file) {
        printf("Error: Unable to open file '%s' for writing.\n", file_table[file_index].filename);
        return -1;
    }
    fwrite(data, 1, data_size, file);
    fclose(file);

    file_table[file_index].size = data_size;
    printf("Data written to file '%s' successfully.\n", file_table[file_index].filename);
    return 0;
}

// Read data from a file
int fileRead(int file_index,char *buffer, int buffer_size){
//error checking index, for assurance of files in the array
   if(file_index <0 || file_index >= file_count) {
	printf("Error: file counts\n");
	return -1;
   }

//files needs to be opened , before being read 
    if (!file_table[file_index].is_open) {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }
//opening file 
    FILE *file = fopen(file_table[file_index].filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
//reading into buffer 
    int bytesRead = fread(buffer, 1, buffer_size, file);
    fclose(file);  // Close file
    buffer[bytesRead] = '\0';
    return bytesRead;    
}


// Close a file
int fileClose(int file_index){
//double checking file index, making sure file exists in array
    if (file_index < 0 || file_index >= file_count) {
        printf("Error: Invalid file index.\n");
        return -1;
    }
//if is_open of file is 0, file isn't open
    if (!file_table[file_index].is_open) {
        printf("Error: File '%s' is already closed.\n", file_table[file_index].filename);
        return -1;
    }
// Marking file as closed
    file_table[file_index].is_open = 0; 
    printf("File '%s' closed successfully.\n", file_table[file_index].filename);
    return 0;

}


// Delete a file
int fileDelete(const char *filename){
//looping through the array to fine file
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
	//using remove() to remove a file
            if (remove(file_table[i].filename) == 0) {
                printf("File '%s' deleted successfully.\n", filename);

                // Shifting remaining files in the table to fill the gap
                for (int j = i; j < file_count - 1; j++) {
                    file_table[j] = file_table[j + 1];
                }

		///reducing the file count
                file_count--;
                return 0;
            } else {
                perror("Error deleting file");
                return -1;
            }
        }
    }

    printf("Error: File '%s' not found.\n", filename);
    return -1;
}
