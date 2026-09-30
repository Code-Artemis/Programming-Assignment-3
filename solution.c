#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEATS 24

struct seat {
    int id;
    int assigned;     
    char last[50];
    char first[50];
};

struct seat outbound[SEATS];
struct seat inbound[SEATS];

void setupSeats(struct seat s[]) {
    int i;
    for (i = 0; i < SEATS; i++) {
        s[i].id = i + 1;
        s[i].assigned = 0;
        strcpy(s[i].last, "");
        strcpy(s[i].first, "");
    }
}

void countEmpty(struct seat s[]) {
    int i;
    int count = 0;
    for (i = 0; i < SEATS; i++) {
        if (s[i].assigned == 0) {
            count++;
        }
    }
    printf("There are %d empty seats.\n", count);
}

void listEmpty(struct seat s[]) {
    int i;
    printf("Empty seats: ");
    for (i = 0; i < SEATS; i++) {
        if (s[i].assigned == 0) {
            printf("%d ", s[i].id);
        }
    }
    printf("\n");
}

void ListSeats(struct seat s[]) {
    struct seat copy[SEATS];
    struct seat temp;
    int i, j;

    for (i = 0; i < SEATS; i++) {
        copy[i] = s[i];
    }

    for (i = 0; i < SEATS - 1; i++) {
        for (j = 0; j < SEATS - 1 - i; j++) {
            if (strcmp(copy[j].last, copy[j + 1].last) > 0) {
                temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }

    printf("Alphabetical list:\n");
    for (i = 0; i < SEATS; i++) {
        if (copy[i].assigned == 1) {
            printf("Seat %d: %s, %s\n", copy[i].id, copy[i].last, copy[i].first);
        }
    }
}

void assignSeat(struct seat s[]) {
    char input[20];
    char first[30];
    char last[30];
    int num;

    printf("Enter seat number to assign (q to abort): ");
    scanf("%19s", input);
    if (input[0] == 'q') {
        printf("Aborted.\n");
        return;
    }

    num = atoi(input);
    if (num < 1 || num > SEATS) {
        printf("Seat number must be 1 to %d.\n", SEATS);
        return;
    }
    if (s[num - 1].assigned == 1) {
        printf("That seat is already taken.\n");
        return;
    }

    printf("Enter first name (q to abort): ");
    scanf("%29s", first);
    if (first[0] == 'q' && first[1] == '\0') {
        printf("Aborted.\n");
        return;
    }

    printf("Enter last name (q to abort): ");
    scanf("%29s", last);
    if (last[0] == 'q' && last[1] == '\0') {
        printf("Aborted.\n");
        return;
    }

    strcpy(s[num - 1].first, first);
    strcpy(s[num - 1].last, last);
    s[num - 1].assigned = 1;
    printf("Seat %d assigned to %s %s.\n", num, first, last);
}

void deleteSeat(struct seat s[]) {
    char input[20];
    int num;

    printf("Enter seat number to delete (q to abort): ");
    scanf("%19s", input);
    if (input[0] == 'q') {
        printf("Aborted.\n");
        return;
    }

    num = atoi(input);
    if (num < 1 || num > SEATS) {
        printf("Seat number must be 1 to %d.\n", SEATS);
        return;
    }
    if (s[num - 1].assigned == 0) {
        printf("That seat is already empty.\n");
        return;
    }

    s[num - 1].assigned = 0;
    strcpy(s[num - 1].first, "");
    strcpy(s[num - 1].last, "");
    printf("Seat %d is now empty.\n", num);
}

void secondMenu(struct seat s[]) {
    char choice;

   while (1) {
        printf("\na) Show number of empty seats\n");
        printf("b) Show list of empty seats\n");
        printf("c) Show alphabetical list of seats\n");
        printf("d) Assign a customer to a seat assignment\n");
        printf("e) Delete a seat assignment\n");
        printf("f) Return to Main Menu\n");
        printf("Choice: ");
        
        //I put this in becasue if not, it will continually check for an end of file and buffer
        if (scanf(" %c", &choice) == EOF) {
            return; 
        }

        if (choice == 'a') {
            countEmpty(s);
        } else if (choice == 'b') {
            listEmpty(s);
        } else if (choice == 'c') {
            ListSeats(s);
        } else if (choice == 'd') {
            assignSeat(s);
        } else if (choice == 'e') {
            deleteSeat(s);
        } else if (choice == 'f') {
            return;
        } else {
            printf("Invalid choice.\n");
        }
    }
}

int main(void) {
    char choice;

    setupSeats(outbound);
    setupSeats(inbound);

        while (1) {
        printf("\na) Outbound Flight\n");
        printf("b) Inbound Flight\n");
        printf("c) Quit\n");
        printf("Choice: ");
        
        // I put this in for the same reason as above, to check for end of file and to make it not buffer
        if (scanf(" %c", &choice) == EOF) {
            break; 
        }

        if (choice == 'a') {
            secondMenu(outbound);
        } else if (choice == 'b') {
            secondMenu(inbound);
        } else if (choice == 'c') {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}