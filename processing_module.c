#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/door_chooser_fifo"

void displayError() {
    printf("\x1b[31mError occured!\n");
    printf("Resetting the system...\x1b[0m\n");
}

void showHEX(int room, int peopleCount) {
    switch (peopleCount) {
        case 0:
            printf("In room S%d - nobody\n", room + 1);
            break;
        case 1:
            printf("In room S%d - 1 person\n", room + 1);
            break;
        case 2:
            printf("In room S%d - 2 people\n", room + 1);
            break;
        case 3:
            printf("In room S%d - 3 people\n", room + 1);
            break;
        case 4:
            printf("In room S%d - 4 people\n", room + 1);
            break;
        case 5:
            printf("In room S%d - 5 people\n", room + 1);
            break;
        case 6:
            printf("In room S%d - 6 people\n", room + 1);
            break;
        case 7:
            printf("In room S%d - 7 people\n", room + 1);
            break;
        case 8:
            printf("In room S%d - 8 people\n", room + 1);
            break;
        case 9:
            printf("In room S%d - 9 people\n", room + 1);
            break;
    }
}

void processing_loop() {
    bool y[8] = {false};
    int way = 0;
    int roomC[5] = {0, 0, 0, 0, 0};
    int error = 0;
    char key;
    int operations = 0;

    int fifo_fd = open(FIFO_PATH, O_RDONLY);
    if (fifo_fd < 0) {
        perror("Error opening FIFO");
        return;
    }

    while (1) {
    	if(operations != 0){
    	printf("\n\n");
        printf("-------------------------------------------");
        printf("\n\n");
    	}
    	
        operations++;
        int bytes_read = read(fifo_fd, &key, sizeof(char));
        if (bytes_read < 1) {
            continue; // Jeżeli nic nie zostało odczytane, kontynuuj
        }

        int index = key - '1';
        bool is_direction_change = false;

        if (key == 'r' || key == 'R') {
            is_direction_change = true;
            if (way == 0) {
                way = 1;
                printf("\x1b[36mDefault direction: up/left\x1b[0m\n");
            } else {
                way = 0;
                printf("\x1b[36mDefault direction: down/right\x1b[0m\n");
            }
        } else if (index >= 0 && index < 8) {
            y[index] = true;
        } else {
            printf("\x1b[31mInvalid input key!\x1b[0m");
            continue;
        }

        
        
        
        printf("\x1b[36m");

        if (index >= 0 && index < 8) {
            switch (index) {
                case 0:
                    if (way == 0) {
                        printf("Chosen passage: CD1 - down\n");
                        roomC[2]--;
                        roomC[3]++;
                    } else {
                        printf("Chosen passage: CD1 - up\n");
                        roomC[2]++;
                        roomC[3]--;
                    }
                    break;
                case 1:
                    if (way == 0) {
                        printf("Chosen passage: CD2 - right\n");
                        roomC[1]++;
                        roomC[2]--;
                    } else {
                        printf("Chosen passage: CD2 - left\n");
                        roomC[1]--;
                        roomC[2]++;
                    }
                    break;
                case 2:
                    if (way == 0) {
                        printf("Chosen passage: CD3 - right\n");
                        roomC[4]++;
                        roomC[1]--;
                    } else {
                        printf("Chosen passage: CD3 - left\n");
                        roomC[1]++;
                        roomC[4]--;
                    }
                    break;
                case 3:
                    if (way == 0) {
                        printf("Chosen passage: CD4 - right\n");
                        roomC[4]--;
                    } else {
                        printf("Chosen passage: CD4 - left\n");
                        roomC[4]++;
                    }
                    break;
                case 4:
                    if (way == 0) {
                        printf("Chosen passage: CD5 - down\n");
                        roomC[1]++;
                    } else {
                        printf("Chosen passage: CD5 - up\n");
                        roomC[1]--;
                    }
                    break;
                case 5:
                    if (way == 0) {
                        printf("Chosen passage: CD6 - down\n");
                        roomC[0]--;
                    } else {
                        printf("Chosen passage: CD6 - up\n");
                        roomC[0]++;
                    }
                    break;
                case 6:
                    if (way == 0) {
                        printf("Chosen passage: CD7 - right\n");
                        roomC[0]++;
                        roomC[3]--;
                    } else {
                        printf("Chosen passage: CD7 - left\n");
                        roomC[3]++;
                        roomC[0]--;
                    }
                    break;
                case 7:
                    if (way == 0) {
                        printf("Chosen passage: CD8 - down\n");
                        roomC[0]++;
                        roomC[1]--;
                    } else {
                        printf("Chosen passage: CD8 - up\n");
                        roomC[0]--;
                        roomC[1]++;
                    }
                    break;
            }
        }

        error = 0;
        for (int i = 0; i < 5; i++) {
            if (roomC[i] < 0) {
                error++;
            }
        }

        if (error > 0) {
            displayError();
            for (int i = 0; i < 5; i++) {
                roomC[i] = 0;
            }
        } else {
            for (int i = 0; i < 5; i++) {
                showHEX(i, roomC[i]);
            }
            for (int i = 0; i < 5; i++) {
                if (roomC[i] > 0) {
                    printf("\x1b[0mS%d light state: \x1b[32mON\x1b[0m\n", i + 1);
                } else {
                    printf("\x1b[0mS%d light state: \x1b[31mOFF\x1b[0m\n", i + 1);
                }
            }
        }

        printf("\x1b[0m");
    }

    close(fifo_fd);
}

int main() {
    processing_loop();
    return 0;
}

