#include <systemc.h>
#include <iostream>
#include <string>

#define ROOM_COUNT 5
#define DOOR_COUNT 8

using namespace std;

struct DoorEvent {
    int door;
    bool direction;
};

int operations = 0;

ostream& operator<<(ostream& os, const DoorEvent& event) {
    os << "DoorEvent(door=" << event.door + 1
       << ", direction=" << (event.direction ? "down/right" : "up/left") << ")";
    return os;
}

struct RoomContext {
    bool direction;
    int room_count[ROOM_COUNT];
    bool door_activation[DOOR_COUNT];
};

SC_MODULE(OperationModule) {
    sc_fifo_out<DoorEvent> door_event_fifo;
    RoomContext* context;

    SC_CTOR(OperationModule) {
        SC_THREAD(process_operations);
    }

    void process_operations() {
        while (true) {
            char input;
            if(operations != 0){
    	cout<<endl;
    	cout<<endl;
        cout<<"-------------------------------------------";
        cout<<endl;
    	cout<<endl;
    	}
    	
        operations++;
            printf("Press 'R' to change direction up/left or down/right\n");
            if (context->direction == 0)
        {
            cout<<"Press a key (1-8) to choose a specific door \x1b[36m(down/right)\x1b[0m: ";
        }
        else
        {
            cout<<"Press a key (1-8) to choose a specific door \x1b[36m(up/left)\x1b[0m: ";
        }
            cin >> input;
            cout<<endl;

            if (input == 'r' || input == 'R') {
                context->direction = !context->direction;
                cout << "\x1b[36mDefault direction: "
                          << (context->direction ? "up/left\x1b[0m\n" : "down/right\x1b[0m\n");
            } 
            else if (input >= '1' && input <= '8') {
                int door = input - '1';
                DoorEvent event = {door, context->direction};
                door_event_fifo.write(event); // Przesyłanie zdarzenia do FIFO
                process_passage(event);
            } else {
                cout << "\x1b[31mInvalid input key!\x1b[0m\n" << endl;
            }

            wait(sc_time(1, SC_SEC)); // symulacja czasu
        }
    }

    void process_passage(const DoorEvent& event) {
        int door = event.door;
        bool direction = event.direction;
        switch (door) {
            case 0:
                if (direction == 0) { // CD1 - down
                    cout << "\x1b[36mChosen passage: CD1 - down\x1b[0m" << endl;
                    if (context->room_count[2] > 0) {
                        context->room_count[2]--;
                        context->room_count[3]++;
                    }
                } else { // CD1 - up
                    cout << "\x1b[36mChosen passage: CD1 - up\x1b[0m" << endl;
                    if (context->room_count[3] > 0) {
                        context->room_count[3]--;
                        context->room_count[2]++;
                    }
                }
                break;
            case 1:
                if (direction == 0) { // CD2 - right
                    cout << "\x1b[36mChosen passage: CD2 - right\x1b[0m" << endl;
                    if (context->room_count[2] > 0) {
                        context->room_count[2]--;
                        context->room_count[1]++;
                    }
                } else { // CD2 - left
                    cout << "\x1b[36mChosen passage: CD2 - left\x1b[0m" << endl;
                    if (context->room_count[1] > 0) {
                        context->room_count[1]--;
                        context->room_count[2]++;
                    }
                }
                break;
            case 2:
                if (direction == 0) { // CD3 - right
                    cout << "\x1b[36mChosen passage: CD3 - right\x1b[0m" << endl;
                    if (context->room_count[1] > 0) {
                        context->room_count[1]--;
                        context->room_count[4]++;
                    }
                } else { // CD3 - left
                    cout << "\x1b[36mChosen passage: CD3 - left\x1b[0m" << endl;
                    if (context->room_count[4] > 0) {
                        context->room_count[4]--;
                        context->room_count[1]++;
                    }
                }
                break;
            case 3:
                if (direction == 0) { // CD4 - right
                    cout << "\x1b[36mChosen passage: CD4 - right\x1b[0m" << endl;
                    if (context->room_count[4] > 0) {
                        context->room_count[4]--;
                    }
                } else { // CD4 - left
                    cout << "\x1b[36mChosen passage: CD4 - left\x1b[0m" << endl;
                    if (context->room_count[4] < 9) {
                        context->room_count[4]++;
                    }
                }
                break;
            case 4:
                if (direction == 0) { // CD5 - down
                    cout << "\x1b[36mChosen passage: CD5 - down\x1b[0m" << endl;
                    if (context->room_count[1] < 9) {
                        context->room_count[1]++;
                    }
                } else { // CD5 - up
                    cout << "\x1b[36mChosen passage: CD5 - up\x1b[0m" << endl;
                    if (context->room_count[1] > 0) {
                        context->room_count[1]--;
                    }
                }
                break;
            case 5:
                if (direction == 0) { // CD6 - down
                    cout << "\x1b[36mChosen passage: CD6 - down\x1b[0m" << endl;
                    if (context->room_count[0] > 0) {
                        context->room_count[0]--;
                    }
                } else { // CD6 - up
                    cout << "\x1b[36mChosen passage: CD6 - up\x1b[0m" << endl;
                    if (context->room_count[0] < 9) {
                        context->room_count[0]++;
                    }
                }
                break;
            case 6:
                if (direction == 0) { // CD7 - right
                    cout << "\x1b[36mChosen passage: CD7 - right\x1b[0m" << endl;
                    if (context->room_count[3] > 0) {
                        context->room_count[3]--;
                        context->room_count[0]++;
                    }
                } else { // CD7 - left
                    cout << "\x1b[36mChosen passage: CD7 - left\x1b[0m" << endl;
                    if (context->room_count[0] > 0) {
                        context->room_count[0]--;
                        context->room_count[3]++;
                    }
                }
                break;
            case 7:
                if (direction == 0) { // CD8 - down
                    cout << "\x1b[36mChosen passage: CD8 - down\x1b[0m" << endl;
                    if (context->room_count[1] > 0) {
                        context->room_count[1]--;
                        context->room_count[0]++;
                    }
                } else { // CD8 - up
                    cout << "\x1b[36mChosen passage: CD8 - up\x1b[0m" << endl;
                    if (context->room_count[0] > 0) {
                        context->room_count[0]--;
                        context->room_count[1]++;
                    }
                }
                break;
        }
        cout<<endl;
    }
};

SC_MODULE(DisplayModule) {
    sc_fifo_in<DoorEvent> door_event_fifo;
    RoomContext* context;

    SC_CTOR(DisplayModule) {
        SC_THREAD(display_status);
    }

    void display_status() {
        while (true) {
            DoorEvent event;
            door_event_fifo.read(event); // czytanie zdarzeń z FIFO

        	for (int i = 0; i < 5; i++)
            {
                if (context->room_count[i] > 0)
                {
                    cout<<"S"<<i+1<<" light state: \x1b[32mON\x1b[0m"<<endl;
                }
                else
                {
                	cout<<"S"<<i+1<<" light state: \x1b[31mOFF\x1b[0m"<<endl;
                }
            }
            cout<<endl;
            for (int i = 0; i < ROOM_COUNT; i++) {
                switch(context->room_count[i]){
                	case 0:
                	cout<<"In room S"<<i+1<<" - nobody"<<endl;
                	break;
                	case 1:
                	cout<<"In room S"<<i+1<<" - 1 person"<<endl;
                	break;
                	default:
                	cout<<"In room S"<<i+1<<" - "<<context->room_count[i]<<" people"<<endl;
                	break;
                }
            }

            wait(sc_time(1, SC_SEC)); // symulacja czasu
        }
    }
};

int sc_main(int argc, char* argv[]) {
    sc_fifo<DoorEvent> door_fifo(10); // FIFO do komunikacji między modułami
    RoomContext* shared_context = new RoomContext(); // Wspólny kontekst przez wskaźnik

    // Inicjalizacja kontekstu
    shared_context->direction = false;
    for (int i = 0; i < ROOM_COUNT; i++) {
        shared_context->room_count[i] = 0;
    }
    for (int i = 0; i < DOOR_COUNT; i++) {
        shared_context->door_activation[i] = false;
    }

    // Konstrukcja modułów
    OperationModule operationModule("OperationModule");
    DisplayModule displayModule("DisplayModule");

    // Przypisanie wspólnego kontekstu przez wskaźnik
    operationModule.context = shared_context;
    displayModule.context = shared_context;

    // Powiązanie FIFO do komunikacji
    operationModule.door_event_fifo(door_fifo);
    displayModule.door_event_fifo(door_fifo);

    // Rozpoczęcie symulacji
    sc_start();

    delete shared_context;
    return 0;
}

