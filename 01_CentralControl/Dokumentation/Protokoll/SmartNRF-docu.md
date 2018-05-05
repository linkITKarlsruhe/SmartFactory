#SmartNRF-Documentation

li.toctree-l3:first-child {
    display: none;
}

[TOC]


The "Smart" in SmartNRF is quite improvable.



##Task
We have several components listed:
 + Arduino Nano
 + Arduino
 + nRF24L01 Radiomodul
 + Raspberry Pi 3 Model B

 But right now we've focused on the simple Task
 to establish connection like:
![img](/img001.png)

Therefore we have to encapsulate the functionality of the nRF24L01 into an API for our purpose which is quite rudimentary.

This functionality is about *sending* , *recieving*  and *configurating* the nRF24L01.
Due to our hardware setting we'll implement the necassary sourcecode in C/C++ for Arduino and Python3 for RaspberryPi.

##Answer

####Remarks

The [graphic](#img) illustrate that the RaspberryPi is used as central for communication. So every message will recieved by this component and broadcast to every Arduino. There is no way to configurate a radio connection between more than four components without using this classic Server-Client-Architecture.

####SmartNRF-API for Arduino



####SmartNRF-API for RaspberryPi
