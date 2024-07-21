# C-Embedded-System

An embedded system written in C to operate a drone 

can be run with the command line args 
`--batteryPercent (0-100) --wings {4, 6, 8} --batteryCap number --weight number`

makes use of multithreading and ensures threads are safely freed once they are no longer required.

safely allocates and deallocates memory during the program.