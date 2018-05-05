# Protokoll vom 27.01.18

Nachdem die bis hier her verwandten Bauteile immer wieder Probleme bereiteten, haben wir uns dazu entschieden einen neuen Line-Following Sensor zu verbauen. Das jetzt verbaute Teil ist der **QTR-8RC LINE SENSOR**.

Dank Finetuning, schafft es der Roboter jetzt, problemlos der Linie zu folgen. Dabei gibt der Sensor Werte von 0 bis 4000 aus. Im Code korrigieren wir diese Werte konstant um 2000 herunter. Damit erreichen wir, dass der Roboter bei einem gelesenen Wert von 0 geradeaus fährt.

Momentan korrigiert der Roboter bei einer gelesenen Null nicht nur nicht gegen, sondern sendet kein Signal an den Motor. Meist wird aber nur sehr kurz eine Null gelesen und der Roboter _rollt_ noch so lange _aus_, bis er wieder einen anderen Wert als Null liest. Stellt man den Roboter aber ohne _Schwung_ auf eine schwarze Fläche, bleibt er einfach stehen. Diese Tatsache würde es einem also ermöglichen, den Roboter auf einer Schwarzen Fläche erst einmal anzuhalten.

Rückwärtsfahren gestaltete sich allerdings erst einmal schwierig. Man kann das FTS zwar rückwärts fahren lassen, dabei funktioniert das Linie-following allerdings nicht mehr. Hier müsste der Code wahrscheinlich angepasst werden.
