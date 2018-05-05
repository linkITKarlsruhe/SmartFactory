#!/usr/bin/env python
#in main this will configurate itself
from __future__ import print_function
import time
from RF24 import *
import RPi.GPIO as GPIO

#address pipes
pipes = [0xE7E7E7E7E7, 0xC2C2C2C2C2]


##########################################
def sendPayload(channel=0,payload):
    ack = False;
    # First, stop listening so we can talk
    radio.stopListening()
    # Send the payload
    if(radio.write(payload)):
        ack = radio.available()
    else:
        print("Sending failed")

    fil.write("send: "+payload+" "+ack+"\n")
    # Now, resume listening so we catch the next packets.
    radio.startListening()
    return ack

def recievedPayload():
    if radio.available():
        while radio.available():
            len = radio.getDynamicPayloadSize()
            receive_payload = radio.read(len)
            print('Got payload size={} value="{}"'.format(len, receive_payload.decode('utf-8')))

    return receive_payload


    if __name__ == "__main__":
        #configurate the radio
        # RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and  set 'this->device = "/dev/spidev0.0";;' or as listed in /dev
        radio = RF24(22, 0);

        #open logging faile
        fil = open("logfile",'w')
        # Setup for connected IRQ pin, GPIO 24 on RPi B+; uncomment to activate
        #irq_gpio_pin = RPI_BPLUS_GPIO_J8_18
        #irq_gpio_pin = 24
        #min_payload_size = 4
        #max_payload_size = 32
        #payload_size_increments_by = 1
        #next_payload_size = min_payload_size
        #inp_role = 'none'
        #send_payload = b'ABCDEFGHIJKLMNOPQRSTUVWXYZ789012'
        #millis = lambda: int(round(time.time() * 1000))

        print('SmartNRF.py')
        radio.begin()
        radio.enableDynamicPayloads()
        radio.setRetries(5,15)
        radio.openWritingPipe(pipes[1])
        radio.openReadingPipe(1,pipes[0])
        radio.startListening()
        radio.printDetails()
        while 1:
            time.sleep(1000)
            rec = recievedPayload()
            print("recieved pal:"+rec)
            fil.write(rec+"\n")
