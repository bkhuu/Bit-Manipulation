// Brandon Khuu G00975967
// CS 262, Lab Section 207
// Project 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sms.h"

#define BIG 160

#define LIL 120

// Set all the elements in the array to null
void ClearArray(char *array, size_t arraySize)
{
   int i;
   // Loop until reach the end of the array
   for (i = 0; i < arraySize; i++)
   {
      array[i] = 0; // Set element to null
   }
}

// Take each byte from the array named origArray, and pack them into the array named packedArray
void PackArray(unsigned char *packedArray, size_t packedArraySize, unsigned char *origArray, size_t origArraySize)
{
   int i = 0;
   int j = 0;
   // Loop until reach the end of both arrays
   while (i < packedArraySize && j < origArraySize)
   {
      packedArray[i] = origArray[j] | (origArray[j + 1] << 6); // A | B << 6
      packedArray[i + 1] = (origArray[j + 1] >> 2) | (origArray[j + 2] << 4); // B >> 2 | C << 4
      packedArray[i + 2] = (origArray[j + 2] >> 4) | (origArray[j + 3] << 2); // C >> 4 | D << 2
      i += 3;
      j += 4;
   }
}

// Unpack the packed bits from the array named packedArray into individual bytes, and store each byte in the array named newArray
void UnpackArray(unsigned char *newArray, size_t newArraySize, unsigned char *packedArray, size_t packedArraySize)
{
   int i = 0;
   int j = 0;
   // Loop until reach the end of both arrays
   while (i < newArraySize && j < packedArraySize)
   {
      // 1 << 2, 1 >> 2
      newArray[i] = packedArray[j] << 2; // Split shifts into two statements
      newArray[i] = newArray[i] >> 2;
		
      // 1 >> 6 | (2 << 4, 2 >> 2)
      newArray[i + 1] = packedArray[j + 1] << 4; // Split shifts into two statements
      newArray[i + 1] = newArray[i + 1] >> 2;	
      newArray[i + 1] = (packedArray[j] >> 6) | newArray[i + 1];

      // 2 >> 4 | (3 << 6, 3 >> 2)
      newArray[i + 2] = packedArray[j + 2] << 6; // Split shifts into two statements
      newArray[i + 2] = newArray[i + 2] >> 2;	
      newArray[i + 2] = (packedArray[j + 1] >> 4) | newArray[i + 2];

      // 3 >> 2
      newArray[i + 3] = packedArray[j + 2] >> 2;		
      i += 4;
      j += 3;
   }
}

int main(int argc, char *argv[])
{
   FILE *output, *input; // Create file variables
   char buffer[BIG]; // Buffer to read input
   char buffbuff[BIG]; // Extra buffer to clear the input stream
   char filename[BIG]; // String to hold filenames
   unsigned char unpackedArray[BIG];
   unsigned char packedArray[LIL];
   char choice = 0;
   int on = 1;
   int i;

   while (on == 1)
   {
      printf("Pack and save a line of text...........P or p\n");
      printf("Unpack and print a line of text........U or u\n");
      printf("Quit the program.......................Q or q\n");
      printf("\n");
      printf("Enter a choice: "); // Prompt the user for valid input
      fgets(buffer, BIG, stdin);  // Read the input from the keyboard and store it in the input variable
      sscanf(buffer, "%c", &choice);  // Extract the character value from input and store it in choice
      printf("\n");

      switch (choice)
      {
         case 'P':
         case 'p':
            printf("Enter a filename in which to save the packed array: "); // Prompt the user for an output file
            fgets(buffer, BIG, stdin);  // Read the input from the keyboard and store it in the buffer
	    sscanf(buffer, "%s", filename); // Extract the string from buffer and store it in filename
	    
	    ClearArray(buffbuff, sizeof(buffbuff)); // Clear the buffer
	    
	    printf("\n");
	    printf("Enter a line of text to pack and save: "); // Prompt the user for a message
            fgets(buffbuff, BIG, stdin);  // Read the input from the keyboard and store it in the buffer
	    // Copy first 159 characters from buffbuff to buffer
	    for (i = 0; i < BIG; i++) {
               buffer[i] = buffbuff[i];
            }
            buffer[strlen(buffer) - 1] = 0; // Set the newline character in buffer to null
	    // Clear the input stream
	    while (buffbuff[strlen(buffbuff) - 1] != '\n') {
               fgets(buffbuff, BIG, stdin);
            }
            
            output = fopen(strcat(filename, ".sms"), "w"); // Open output file
	    if (output == NULL) { // Make sure file was opened properly
               printf("Couldn't open the file...\n"); // Print error message
               break;
            }

            // Convert ASCII to GMUSCII
	    for (i = 0; i < BIG; i++) {
               unpackedArray[i] = CharToSMS((unsigned char) buffer[i]);
            }

	    PackArray(packedArray, sizeof(packedArray), unpackedArray, sizeof(unpackedArray)); // Pack the message
            fwrite(packedArray, sizeof(unsigned char), LIL, output); // Write to output file
	    
	    printf("\n");
	    
	    fclose(output); // Close the output file
            break;
         case 'U':
         case 'u':
            printf("Enter a filename which contains a packed array: "); // Prompt the user for an output file
            fgets(buffer, BIG, stdin);  // Read the input from the keyboard and store it in the buffer
	    sscanf(buffer, "%s", filename); // Extract the string from buffer and store it in filename
            input = fopen(strcat(filename, ".sms"), "r"); // Open output file
            if (input == NULL) { // Make sure file was opened properly
               printf("Couldn't open the file...\n"); // Print error message
               break;
            }
            
	    ClearArray(buffer, sizeof(buffer)); // Clear the buffer

	    fread(packedArray, sizeof(unsigned char), LIL, input); // Read from input file
            UnpackArray(unpackedArray, sizeof(unpackedArray), packedArray, sizeof(packedArray)); // Unpack the message	    
	    
	    // Convert GMUSCII to ASCII
	    for (i = 0; i < BIG; i++) {
               buffer[i] = SMSToChar(unpackedArray[i]);
            }
            
	    printf("\n");
	    printf("%s\n", buffer); // Display the unpacked message
            printf("\n");

	    fclose(input); // Close the input file
            break;
         case 'Q':
         case 'q':
            on = 0; // Exit the program

            printf("Thanks for using GMU SMS System.\n");
            break;	   
         default:
            printf("Not a valid choice.\n"); // Display error message.
      }
   }
   return 0;
}


