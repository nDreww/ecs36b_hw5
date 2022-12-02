# ECS36B Fall 2022 Homework 5 - Object Mobility
This program aims to represent "object mobility" by transferring objects from one server to another. Three servers (Grandma's Home, Forest, and Home) are created and objects are initially created in the "Home" server.
## Developers
Hanson Nguyen: 919227725  
Alfredo Nieto: 917137244  
_________: 919388431  
_________: 919388431
## How to run
Compile with make
```bash
make
```
Run servers in specific order (Grandma's Home->Forest->Home)
```bash
./grandmaHomeServer
./forestServer
./homeServer
```