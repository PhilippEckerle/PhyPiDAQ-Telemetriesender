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
was je nach Leistung des Rechners einige Minuten dauern kann. 

## Zusammenbau des Telemetriesenders
## Anwendungshinweise
### Datenübertragung über WLAN
### Datenübertragung über BLE
