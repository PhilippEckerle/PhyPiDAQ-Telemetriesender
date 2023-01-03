# Anleitung zum Aufsetzen des Telemetriesenders

Die Anleitung setzt einen fertig aufgesetzten Raspberry Pi voraus. Eine Anleitung für die Installation 
des Betriebssystems "Raspberry Pi OS Full" sowie dessen Bedienung findet sich in der 
[PhyPiDAQ-Dokumentation](https://github.com/GuenterQuast/PhyPiDAQ/blob/master/Dokumentation.md#31-wie-setze-ich-den-raspberry-pi-auf-).
Diese Anleitung beschränkt sich auf die reine Nutzung der Sende- und Empfangsprogramme zur Übertragung von Beschleunigungsdaten; 
eine Verwendung im Rahmen von PhyPiDAQ ist noch nicht implementiert. Eine Anleitung zur Nutzung des Telemetriesenders im Rahmen von PhyPiDAQ ist geplant.

## Benötigtes Material

Für den Telemetriesenders:
* Einen Mikrocontroller des Typs Arduino Nano RP2040 Connect
* Eine Batteriehalterung mit Deckel und Schalter
* Batterien entsprechend der gewählten Batteriehalterung

Hilfsmittel:
* Einen Lötkolben mit Lötzinn
* Einen Rechner mit Internetzugang
* Ein USB-Kabel
* Klebeband oder sonstige Möglichkeiten zur Befestigung

## Einrichten der Arduino IDE

Für die Programmierung des Mikrocontrollers wird die Arduino-Entwicklungsumgebung
verwendet, die [hier](https://www.arduino.cc/en/software) heruntergeladen werden kann. 
Zur Auswahl stehen die ältere Version "Arduino IDE 1.8.x" sowie die neuere
Version "Arduino IDE 2.0.x" (Stand 2022). Die folgende Anleitung bezieht sich auf die
ältere Version, kann aber auch für die neuere Version verwendet werden, wobei bei der
neuen Version ein häufigeres Auftreten von Fehlfunktionen möglich ist. Nach erfolgreicher
Installation wird die Arduino IDE geöffnet. Für die Programmierung des Boards muss zuerst der 
entsprechende Core heruntergeladen werden. Dazu wird unter "Werkzeuge" > "Board" der Boardverwalter aufgerufen:

![Aufrufen des Boardverwalters](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/Boardverwalter.png)

Durch Klicken öffnet sich ein Fenster, auf welchem die Cores für verschiedene Arduino-Modelle und 
Serien aufgelistet sind und durch Klicken auf "Installieren" heruntergeladen werden können. 
Für das hier verwendete Board muss das Paket "Arduino Mbed OS Nano Boards" ausgewählt werden:

![Auswählen des Cores](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/Core%20ausw%C3%A4hlen.png)

Unter "Werkzeuge" > "Board" findet sich nun in der Liste unterhalb der Boardverwaltung
der Name des heruntergeladenen Pakets. Unter diesem kann nun das verwendete Board
"Arduino Nano RP2040 Connect" ausgewählt werden:

![Auswählen des Boards](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/Board%20ausw%C3%A4hlen.png)

Die Sendeprogramme für WLAN und Bluetooth verwenden spezifische Bibliotheken, die
eigens heruntergeladen werden müssen. Diese sind:

* Arduino_LSM6DSOX
* PubSubClient
* WiFiNINA
* ArduinoBLE

Über den Pfad "Werkzeuge" > "Bibliotheken verwalten" können beliebige Bibliotheken
gesucht und heruntergeladen werden. Durch Klicken öffnet sich ein neues
Fenster, in welchem die gewünschte Bibliothek durch Eingabe in die Suchzeile automatisch
gesucht und aus der gefundenen Auswahl heruntergeladen werden kann.

![Verwalten der Bibliotheken](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/Bibliotheken%20verwalten.png)

## Herunterladen der der Sende- und Empfangsprogramme

Die Sende- und Empfangsprogramme für die Datenübertragung mit WLAN und Bluetooth LE finden 
sich Ordnern [WLAN-Übertragung (MQTT)](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/tree/main/WLAN-%C3%9Cbertragung%20(MQTT)) 
und [BLE-Übertragung](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/tree/main/BLE-%C3%9Cbertragung) dieses Repositories. 
Die Empfangsprogramme können direkt auf den Raspberry Pi heruntergeladen werden. Die 
Sendeprogramme sind als Ordner angelegt; diese werden auf den Rechner mit der installierten
Arduino IDE heruntergeladen und in den Ordner "Arduino" verschoben, der bei der Installation
automatisch erstellt wird und über welchen die IDE alle Arduino-Programme verwaltet. Um das
Sendeprogramm aufzurufen, wird der Order geöffnet und darin die gleichnamige "ino"-Datei 
(auch Sketch genannt) mit einem Doppelklick geöffnet. Alternativ kann auch zuerst die Arduino 
IDE geöffnet und durch Klicken auf den nach oben zeigenden Pfeil auf der Kopfleiste der Sketch 
ausgewählt und aufgerufen werden. Zum Laden des Sendeprogramms auf das Arduino-Board muss 
dieses über ein USB-Kabel mit einem Rechner verbunden werden. Dabei ist zu beachten, dass das 
USB-Kabel zum Datentransfer geeignet sein muss, da manche USB-Kabel lediglich als Ladekabel 
fungieren und nur über Adern zur Stromversorgung verfügen. Das mit dem Board mitgelieferte 
weiße USB-Kabel ist hierfür geeignet. Ist das Board auf diese Weise mit dem Rechner verbunden, 
wird in den meisten Fällen automatisch der Port erkannt, über welchen der Rechner mit dem 
Board kommuniziert. Andernfalls muss dieser manuell über den Pfad "Werkzeuge" > "Port" 
eingestellt werden. Über den nach rechts zeigenden Pfeil in der Kopfleiste wird das Hochladen gestartet,
was je nach Leistung des Rechners einige Minuten dauern kann. Für die WLAN-Datenübertragung
mit dem MQTT-Protokoll müssen müssen im Sendeprogramm vor dem Hochladen auf das Board 
Einstellungen vorgenommen werden, die weiter unten im Abschnitt "Anwendungshinweise" näher
erläutert werden.

## Zusammenbau des Telemetriesenders

Das Arduino-Board kann über die Pins "GND" und "VIN" mit einer Spannung von 4 V bis
20 V versorgt werden. Als portable Spannungsversorgung eignen sich
Batteriehalterungen mit einer Abdeckung, einem Schalter, und zwei Adern als Plus- und
Minusleitung. Die folgenden Abbildungen geben einen Überblick über verschiedene
geeignete Modelle.

![6V](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/6%20V.jpg "Batteriehalterung für 6 V")
![9V](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/9%20V.jpg)

![4,5V](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/4%2C5%20V.png "Batteriehalterung für 4,5 V") 

Die rote Leitung wird mit dem Pin "VIN" verlötet, die schwarze Leitung mit dem Pin
"GND". Für ein sauberes Anlöten der Leitungen sollte darauf geachtet werden, mit der
Lötspitze sowohl den Draht als auch die Pin-Fläche zu erhitzen, damit das Lötzinn eine
beidseitige Verbindung herstellt und sich gut verteilt. Das Lötzinn wird in Form eines
Lötdrahts vorsichtig an der zu erhitzenden Stelle geschmolzen. Ein Verbinden der beiden
benachbarten Pins durch überschüssiges Lötzinn ist dabei zu vermeiden; dies führt zu
einem Kurzschluss. Schließlich muss noch das Board auf der Batteriehalterung fixiert 
werden. Ein Beispiel für einen fertigen Telemetriesender zeigt folgende 
Abbildung:

![fertiger Sender](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/fertiger%20Sender.jpg)

## Anwendungshinweise
### Datenübertragung über WLAN

Für die Datenübertragung über das WLAN-Netz wird das MQTT-Protokoll verwendet. Dazu 
muss auf dem Raspberry Pi der MQTT-Broker Mosquitto installiert werden. Eine Anleitung
dazu findet sich zum Beispiel [hier](https://www.elektronik-kompendium.de/sites/raspberry-pi/2709041.htm).
Für die Ausführung des Empfangsprogramms muss das Python-Modul paho-mqtt mit dem
Befehl

``pip3 install paho-mqtt``

im Terminal heruntergeladen werden.
Bevor das Sendeprogramm auf das Arduino-Board hochgeladen wird, müssen SSID und Passwort des 
WLAN's in der Datei "Einstellungen.h" eingegeben werden. Im Empfangsprogamm ist eine 
Steuerung implementiert, mit der das Senden der Daten an- und ausgeschaltet werden 
kann. Wird so das Empfangsprogramm auf der Thonny IDE ausgeführt, wird das Senden der 
Daten durch durch Eingabe des Buchstabens "s" in der Kommandozeile und Drücken von 
Enter gestartet. Die Eingabe des Buchstabens "e" stoppt das Senden der Daten. Mit den
auf dem Board verbauten Farb-LED's wird der Verbindungszustand signalisiert und 
Rückmeldung über mögliche Fehlfunktionen gegeben. Ein Leuchten der grünen LED signalisiert, 
dass keine Verbindung zum WLAN-Netz vorliegt. Leuchtet die blaue LED, liegt keine 
Verbindung zum Raspberry Pi vor. 

Eine Datenübertragung über WLAN bietet den Vorteil einer größeren Reichweite im 
Vergleich zu Bluetooth. Als Nachteile sind ein höherer Stromverbrauch des Telemetriesenders
und die Abhängigkeit vom Vorhandensein eines WLAN-Netzes zu nennen. Schwierigkeiten
können sich dadurch ergeben, dass WLAN-Netzwerke in der Schule häufig passwortgeschützt
sind und so ein Zugang nur mit Angabe der SSID und des zugehörigen WLAN-Schlüssels
nicht möglich ist. Als Lösung kann ein Pocket Router verwendet werden, der an einer
Steckdose angesteckt werden kann und so ein eigenes WLAN-Netz (ohne Verbindung zum
Internet) aufspannt, dessen Zugangsdaten beliebig angepasst werden können. Als Beispiel
sei das Modell [TL-WR710N](https://www.tp-link.com/de/home-networking/wifi-router/tl-wr710n/) 
vom Hersteller TP-Link genannt:

![TPlink](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/TP-Link.jpg)

### Datenübertragung über BLE
Während die Datenübertragung bei WLAN über einen Router als Vermittler stattfindet,
stellt Bluetooth eine Punkt-zu-Punkt-Übertragung vom Telemetriesender zum Raspberry
Pi dar. Damit entfällt die Notwendigkeit eines WLAN-Netzes und die damit verbundene
Eingabe der WLAN-Zugangsdaten im Sendeprogramm. Für die Ausführung des Empfangsprogramms
muss das Python-Modul BluePy heruntergeladen werden. Dazu werden folgende Befehle im 
Terminal eingegeben:

``sudo apt-get install python3-pip libglib2.0-dev``

``sudo pip3 install bluepy``

Zum Ein- und Ausschalten von Bluetooth Low Energy muss der Blueman-Bluetooth-Manager
verwendet werden. Dieser wird durch Eingabe des folgenden Befehls im Terminal installiert:

``sudo apt install bluetooth pi-bluetooth bluez Blueman``

Um eine Verbindung zwischen 
Telemetriesender und Raspberry Pi herzustellen, muss im PhyPiDAQ-Programm lediglich
die MAC-Adresse des verwendeten Arduino-Boards angegeben werden. Diese wird in
der Arduino IDE periodisch im Seriellen Monitor ausgegeben, wenn das Arduino-Board
über den USB-Anschluss mit dem Rechner verbunden ist und keine Bluetooth-Verbindung
vorliegt. Der Serielle Monitor wird durch Klicken auf das Lupen-Symbol oben rechts
auf der Benutzeroberfläche des Programms geöffnet. Für eine korrekte Darstellung der
ausgegebenen Daten muss darauf geachtet werden, dass die Baudrate (unten rechts) auf
115200 eingestellt ist. Damit der Verbindungsaufbau gelingt, muss der Telemetriesender
zwei bis drei Sekunden vor der PhyPiDAQ-Anwendung gestartet werden. Auch darf
nicht vergessen werden, die Bluetooth-Funktion des Raspberry PiŠs durch Klicken auf das
Desktop-Symbol oben rechts zu aktivieren.

Der einzige wesentliche Nachteil gegenüber der WLAN-Übertragung liegt in einer geringeren
Reichweite von etwa 5 Metern. Die genaue Reichweite und die Qualität der Übertragung
hängen insgesamt von der Räumlichkeit und von der Belastung des genutzten 2,4 GHz-Bandes 
durch umgebende WLAN-Netze ab. WLAN-Strahlung durch Handys und Router
wirkt tendenziell störend auf die Bluetooth-Übertragung.
