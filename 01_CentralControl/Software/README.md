# File Sepcfication


[TOC]

---
##LinkitRF24 vs. LinkitRF24Client

LinkitRF24 is just a simple code from [here](http://tmrh20.github.io/RF24Ethernet/mqtt_basic_8ino-example.html) without any encapsulation. And LinkitRF24Client tries to reach encapsulation. This was tried with Atom-PlattformIDE. The current error given by Litner-Build is located at error\build\_linkitRF24Client.txt.


## starup_mailer.py

Used to send the ip address of the Raspberry Pi after startup, which is given by the DHCP server.
The automatic execution is configured with `crontab`.

## Web_view

Old version of HMI display for Raspberry Pi with **Python Flask** as framework.

Frontend:

+ Bootstrap
+ Highcharts, draw charts with data
+ DataTables, display raw data

Data Persistence:

+ Flask_SQLALCHEMY

Database:

+ SQLite3
