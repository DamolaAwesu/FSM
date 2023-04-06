# FSM
FSM implementation in C

This repo contains my take on implementing Finite State Machines in C. The design here is largely based on the "Optimal FSM Implementation" pattern described in Miro Samek's brilliant "Practical StateCharts in C/C++" book. The FSM itself is largely a generic event processor which allows for concrete derivations based of it. 

The main functionalities of the FSM are implemented in the FSM .c/.h files and a sample concrete FSM based of an example state diagram in the PSiCC book, CParser, is implemented in the CParser .c/.h files. A test application to validate the implementation is implemented in main.c.
