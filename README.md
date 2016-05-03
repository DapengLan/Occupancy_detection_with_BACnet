#NES15_HEVC

##Requirment
- Hardware:
Beaglebone black;
Infared sensors.
- Software: BACnet

## Introduction
The project is occupancy detection of a room. It detects the number of people entering or exiting a door. 
It is implemented on top of a open source BACNET stack  (http://sourceforge.net/projects/bacnet/files/bacnet-stack/bacnet-stack-0.8.0/ )

Running /demo/server/bacserv on a linux device will make the device a BACNET server.

We have modified the /demo/server/main.c file to have the functionality of people detection and update the relevant BACNET object accordingly.

Modified file is in the /demo/server
  --add the control of the Infared sensors
  --add the people counting algorithm
  
In the linux system, 
Running the server on the beaglebone:

./bin/bacser 123

Runnung the client on laptop.

./bin/bacwi

./bin/bacrp 123 13 0 85

The demo video can be found at the Youtube: 
https://www.youtube.com/watch?v=DQc1_J9LGl4

Thx.

