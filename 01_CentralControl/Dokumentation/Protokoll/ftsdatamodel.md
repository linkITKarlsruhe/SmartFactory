+ id, integer, automatic increase, primary key
+ time_stamp, TIMESTAMP
+ Sensorwert 8*[0,1000] integer (8 Sensoren)
	+ sensor1, integer, between 0 and 1000
	+ ...
	+ sensor8, integer, between 0 and 1000
+ Kalibrierung, 8*[0,2500] integer
	+ calibration1, integer, between 0 and 2500
	+ ...
	+ calibration8, integer, between 0 and 2500
+ PulsWeitenMOdulation 2*[0,255] integer (Für Jede Seite+)
	+ pulse_width_modulation_left, integer, between 0 and 255
	+ pulse_width_modulation_right, integer, between 0 and 255
+ Fährt oder nicht fährt {0,1} modelled as boolean valiable, True = is moving, False = stopped
	+ is_driving
+ Wert für die Falltür, Bool, True = Closed, False = Open
	+ door_status
+ Akkuladestand (aktuell nicht), integer, [0,100]
	+ battery_status, integer, between 0 and 100
