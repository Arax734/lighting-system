#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define FIFO_PATH "/tmp/door_chooser_fifo"

// Ustawienie trybu niebuforowanego na wejściu standardowym
void set_terminal_mode() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ICANON; // Wyłączanie trybu kanonicznego
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

// Przywrócenie domyślnego trybu terminala
void reset_terminal_mode() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ICANON; // Włączanie trybu kanonicznego
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void input_loop() {
    int fifo_fd;
    char key;

    // Otwórz FIFO do pisania
    fifo_fd = open(FIFO_PATH, O_WRONLY);
    if (fifo_fd < 0) {
        perror("Error opening FIFO");
        return;
    }

    // Ustaw tryb niebuforowany
    set_terminal_mode();

    // Główna pętla wejściowa
    while (1) {
        printf("Press 'R' to change direction up/left or down/right, or a key (1-8) to choose a specific door\n");
        printf("Your choice: ");
        key = getchar(); // Teraz oczekuje jedynie pojedynczego klawisza, bez potwierdzania przez "Enter"
        write(fifo_fd, &key, sizeof(char)); // Przekazuje pojedynczy klawisz do FIFO
        printf("\n\n");
    }

    // Przywróć domyślne ustawienia terminala
    reset_terminal_mode();

    // Zamknij FIFO
    close(fifo_fd);
}

int main() {
    input_loop();
    return 0;
}

