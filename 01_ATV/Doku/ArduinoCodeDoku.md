# Dokumentation und Anleitung für das FTS

## Sehr leichte Bedienungsanleitung:

1. Das FTS auf die schwarze Linie setzten.
2. Das FTS einschalten.
3. Wurde das FTS schon in dieser Umgebung genutzt?
    - __Ja?__ Dann ist das FTS schon kalibriert und man kann getrost warten. Das FTS lädt automatisch die letzten Einstellungen und fährt, nachdem es sich kalibriert hat, selbstständig los. 
    - __Nein?__ Dann einen Schritt zurück treten und warten, bis das FTS anfängt und wieder aufhört sich zu drehen. Das FTS ist jetzt kalibriert, die Werte werden gespeichert und das FTS muss für den Einsatz in dieser Umgebung nicht erneut kalibriert werden. (Es wird immer nur eine Kalibration gespeichert, bei _hin und her_ wechseln, muss logischerweise neu kalibriert werden)
4. Das FTS ist jetzt einsatzbereit und sollte selbstständig losfahren.

_Troubleshooting: Im Zweifel das FTS einfach noch einmal neu kalibrieren. Es kann auch sein, dass der Untergrund zu wenig Kontrast bietet oder dass die Sensorleiste beschmutzt ist. Sollte dies alles nicht der Fall sein, könnte jemand im Code rumgepfuscht haben, oder Bauteile sind kaputt. Bei Zweiterem __Viel Spaß!__, sollte Punkt eins der Fall sein, einfach dranbleiben, vielleicht steht hier ja noch was hilfreiches!_

## Wie funktioniert das FTS und was soll der Code?

### Grundlegend

Das FTS orientiert sich an einer schwarzen (dunkel sollte sie sein) Linie. Dies geschieht wie folgt: An der unteren Seite des FTS ist eine Sensorleiste angebracht, diese Sensoren senden Infrarotlicht und messen die Menge an Licht, die vom Untergrund reflektiert wird. Im Code wird festgelegt, welche Messdiode verwendet werden. Die Sensoren stellen jetzt automatisch fest, wo auf der Linie sie sich befinden. (Wer das genauer wissen will, soll sich die `readLine()` Funktion in der QTR Doku anschauen.) Diese Position wird jetzt so nach unten korrigiert, dass ein Wert von Null ausgegeben wird, sobald sich das FTS genau über der Linie befindet.

Ist die Position von Null verschieden, so wird sie als Error aufgefasst und bestimmt den neuen Motorspeed der rechten und linken Motoren. Diese neue Geschwindigkeit wird außerdem von KP/KD Reglern beeinflusst, die den _Error_ der letzten Messung berücksichtigen.

Außerdem werden die Motorgeschwindigkeiten auf ein Maximum und ein Minimum beschränkt.

### Wie funktioniert die Kalibration

Die Sensoren müssen bei jedem Neustart neu kalibriert werden. Dazu verwendet man entweder die Werte der letzten Kalibrierung, oder man aktiviert durch Drücken des kleinen Knopfes die Neukalibrierung. Dazu dreht sich das FTS für eine gegebenen Zeitraum im Kreis und stellt so Mini- und Maximalwerte für die Sensoren fest. Danach werden die Werte an bestimmten Stellen im eeprom gespeichert, aus dem auch die _letzte Kalibrierung_ heraus gelesen wird.

Weitere Dokumentation ist im Code selbst zu finden.

-- 24.04.18