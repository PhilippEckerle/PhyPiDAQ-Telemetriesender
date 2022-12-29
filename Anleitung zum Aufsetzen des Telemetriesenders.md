# Anleitung zum Aufsetzen des Telemetriesenders
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
entsprechende Core heruntergeladen werden. Dazu wird unter "Werkzeuge" > "Board" der Boardverwalter aufgerufen.

![Aufrufen des Boardverwalters](https://github.com/PhilippEckerle/PhyPiDAQ-Telemetriesender/blob/main/Bilder/Boardverwalter.png)

Durch Klicken öffnet sich ein Fenster, auf welchem die Cores für verschiedene Arduino-Modelle und 
Serien aufgelistet sind und durch Klicken auf "Installieren" heruntergeladen werden können. 
Für das hier verwendete Board muss das Paket "Arduino Mbed OS Nano Boards" ausgewählt werden.

## Laden des Sendeprogramms auf das Arduino-Board
## Zusammenbau des Telemetriesenders
## Anwendungshinweise
### Datenübertragung über WLAN
### Datenübertragung über BLE
