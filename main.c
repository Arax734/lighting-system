#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

void displayError()
{
    printf("\x1b[31mError occured!\n");
    printf("Resetting the system...\x1b[0m\n");
}

void showHEX(int room, int peopleCount, int led)
{
    switch (peopleCount)
    {
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

int main()
{
    bool y[8] = {false};
    int way = 0;
    int roomC[5] = {0, 0, 0, 0, 0};
    char key;
    bool qKeyHeld = false;

    while (1)
    {
        printf("Press 'R' to change direction up/left or down/right\n");

        if (way == 0)
        {
            printf("Press a key (1-8) to choose a specific door \x1b[36m(down/right)\x1b[0m\n");
        }
        else
        {
            printf("Press a key (1-8) to choose a specific door \x1b[36m(up/left)\x1b[0m\n");
        }

        key = _getch();

        int index = key - '1';

        if (index >= 0 && index < 8)
        {
            y[index] = true;
        }
        else
        {
            if (key == 'r' || key == 'R')
            {
                if (way == 0)
                {
                    way = 1;
                    printf("\x1b[36mDefault direction: up/left\x1b[0m\n");
                }
                else
                {
                    way = 0;
                    printf("\x1b[36mDefault direction: down/right\x1b[0m\n");
                }
            }
            else
            {
                printf("\x1b[31mInvalid input key!\x1b[0m\n");
            }
            continue;
        }

        printf("\x1b[36m");

        // // Przejscie CD1
        if (way == 0 && y[0] == true)
        {
            printf("Chosen passage: CD1 - down\n");
            y[0] = false;
            if (roomC[3] < 9)
            {
                roomC[3]++;
            }
            roomC[2]--;
        }
        else if (way == 1 && y[0] == true)
        {
            printf("Chosen passage: CD1 - up\n");
            y[0] = false;
            if (roomC[2] < 9)
            {
                roomC[2]++;
            }
            roomC[3]--;
        }

        // Przejscie CD2
        if (way == 0 && y[1] == true)
        {
            printf(" Chosen passage:CD2 - right\n");
            y[1] = false;
            if (roomC[1] < 9)
            {
                roomC[1]++;
            }
            roomC[2]--;
        }
        else if (way == 1 && y[1] == true)
        {
            printf("Chosen passage: CD2 - left\n");
            y[1] = false;
            if (roomC[2] < 9)
            {
                roomC[2]++;
            }
            roomC[1]--;
        }

        // Przejscie CD3
        if (way == 0 && y[2] == true)
        {
            printf("Chosen passage: CD3 - right\n");
            y[2] = false;
            if (roomC[4] < 9)
            {
                roomC[4]++;
            }
            roomC[1]--;
        }
        else if (way == 1 && y[2] == true)
        {
            printf("Chosen passage: CD3 - left\n");
            y[2] = false;
            if (roomC[1] < 9)
            {
                roomC[1]++;
            }
            roomC[4]--;
        }

        // Przejscie CD4
        if (way == 0 && y[3] == true)
        {
            printf("Chosen passage: CD4 - right\n");
            y[3] = false;
            roomC[4]--;
        }
        else if (way == 1 && y[3] == true)
        {
            printf("Chosen passage: CD4 - left\n");
            y[3] = false;
            if (roomC[4] < 9)
            {
                roomC[4]++;
            }
        }

        // Przejscie CD5
        if (way == 0 && y[4] == true)
        {
            printf("Chosen passage: CD5 - down\n");
            y[4] = false;
            if (roomC[1] < 9)
            {
                roomC[1]++;
            }
        }
        else if (way == 1 && y[4] == true)
        {
            printf("Chosen passage: CD5 - up\n");
            y[4] = false;
            roomC[1]--;
        }

        // Przejscie CD6
        if (way == 0 && y[5] == true)
        {
            printf("Chosen passage: CD6 - down\n");
            y[5] = false;
            roomC[0]--;
        }
        else if (way == 1 && y[5] == true)
        {
            printf("Chosen passage: CD6 - up\n");
            y[5] = false;
            if (roomC[0] < 9)
            {
                roomC[0]++;
            }
        }

        // Przejscie CD7
        if (way == 0 && y[6] == true)
        {
            printf("Chosen passage: CD7 - right\n");
            y[6] = false;
            if (roomC[0] < 9)
            {
                roomC[0]++;
            }
            roomC[3]--;
        }
        else if (way == 1 && y[6] == true)
        {
            printf("Chosen passage: CD7 - left\n");
            y[6] = false;
            if (roomC[3] < 9)
            {
                roomC[3]++;
            }
            roomC[0]--;
        }

        // Przejscie CD8
        if (way == 0 && y[7] == true)
        {
            printf("Chosen passage: CD8 - down\n");
            y[7] = false;
            if (roomC[0] < 9)
            {
                roomC[0]++;
            }
            roomC[1]--;
        }
        else if (way == 1 && y[7] == true)
        {
            printf("Chosen passage: CD8 - up\n");
            y[7] = false;
            if (roomC[1] < 9)
            {
                roomC[1]++;
            }
            roomC[0]--;
        }
        printf("\x1b[0m");
        int error = 0;
        for (int i = 0; i < 5; i++)
        {
            if (roomC[i] < 0)
            {
                error++;
            }
        }
        if (error > 0)
        {
            displayError();
            for (int i = 0; i < 5; i++)
            {
                roomC[i] = 0;
            }
            for (int i = 0; i < 8; i++)
            {
                y[i] = false;
            }
            way = 0;
        }
        else
        {

            for (int i = 0; i < 5; i++)
            {
                if (roomC[i] >= 0)
                {
                    showHEX(i, roomC[i], i);
                }
            }
            for (int i = 0; i < 5; i++)
            {
                if (roomC[i] > 0)
                {
                    // tutaj zaswiecic LED dla konkretnego pokoju
                    printf("S%d light state: \x1b[32mON\x1b[0m", i + 1);
                    printf("\n");
                }
                else
                {
                    // tutaj zgasic LED dla konkretnego pokoju
                    printf("S%d light state: \x1b[31mOFF\x1b[0m", i + 1);
                    printf("\n");
                }
            }
        }
    }

    return 0;
}
