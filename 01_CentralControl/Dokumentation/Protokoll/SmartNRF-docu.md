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

On Raspberry start mosquitto and RF24Gateway with follwing command.
```shell
mosquitto
sudo /home/pi/rf24libs/RF24Gateway/examples/RF24GatewayNode
```

[Test Code](https://github.com/nRF24/RF24Ethernet/blob/master/examples/MQTT/mqtt_basic/mqtt_basic.ino)


[Rapi RF24 MQTT Install Video](https://www.youtube.com/watch?annotation_id=annotation_3313246909&feature=iv&src_vid=rBAIqAaRu0g&v=KZ5x1NF-Emc)

[Install Atom](https://fedoramagazine.org/install-atom-fedora/)

[Install PlattformIO](http://docs.platformio.org/en/latest/ide/atom.html)

+ installed Atom Packages (RF24, RF24Mesh, RF24Ethernet, RF24Gateway, [PubSubClient](https://github.com/knolleary/pubsubclient))
+ insall Clang for Code completition
```shell
sudo yum install clang
```

[Plattform IO error fix](https://raw.githubusercontent.com/platformio/platformio-core/develop/scripts/99-platformio-udev.rules)

####Remarks

The [graphic](#img) illustrate that the RaspberryPi is used as central for communication. So every message will recieved by this component and broadcast to every Arduino. There is no way to configurate a radio connection between more than four components without using this classic Server-Client-Architecture.

####SmartNRF-API for Arduino



####SmartNRF-API for RaspberryPi

Configurate the RapiGateway

On RaPi you have to shell.
```shell
pi@linkit:~ $ sudo ./rf24libs/RF24Gateway/examples/RF24GatewayNode
```
