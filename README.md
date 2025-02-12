
# Lighting System Desciption

Lighting system written in SystemC. Each person passing through the door generates a pulse, which allows us to calculate how many people are currently in the room. If there is a minimum of one person in the room, the light turns on. The system handles the appearance of errors and the handling of all possible movement variations.

# Compilation command on Linux

```
g++ -o simulation simulation.cpp -I/usr/local/systemc-2.3.3/include -L/usr/local/systemc-2.3.3/lib-linux64 -lsystemc
```

Map of the rooms:

![enter image description here](https://i.imgur.com/WvPSla6.png)

# Screenshots:

![enter image description here](https://i.imgur.com/Wf48EuL.png)

![enter image description here](https://i.imgur.com/2T3WWjE.png)

![enter image description here](https://i.imgur.com/GYlIgX0.png)

![enter image description here](https://i.imgur.com/EkWxdSU.png)
