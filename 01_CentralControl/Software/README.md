# File Sepcfication

---

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
