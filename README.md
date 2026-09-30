Problem and Solution Summary
Struct Design: This program shows an airline flight reservation. It uses a struct, which bundles an integer ID, an assignment status flag (assigned), and string arrays for the customer's first and last names. I implemented two distinct arrays of this structure, outbound and inbound, to manage the 24 seats per flight. 

Menu Architecture: The interface shows a multi-tiered menu architecture. I used conditional logic nesting within execution loops. The main() loop handles navigation between the outbound and inbound flights. It then passes the seat arrays into a localized secondMenu() loop. This is where users can view empty seats, list reservations alphabetically, or modify passenger assignments. To prevent any freezes when testing the script, I implemented processing loops to check if the input returns End of File inside the scanf(). This verifies that the application terminates cleanly instead of spinning into an infinite loop when reading the commands. 

Input Stream & Buffer Analysis
A remaining newline (\n) could remain in the input if you use scanf() or getchar() and then switch to fgets(). fgets() ignores the user's input and immediately reads that newline. To fix the issue, I used the leftover characters using a loop, like while ((c = getchar()) != '\n' && c != EOF); before calling fgets().

AI Test Harness Evaluation
I used ChatGPT to test the C program and asked it to use inputs like huge strings, special control characters, and text with no lagging newline. The tests quickly found two big problems: buffer overflows and infinite loops when the program hit the end of the file (EOF) while clearing the buffer. To fix this, I changed the code to use fgets() instead of scanf().
