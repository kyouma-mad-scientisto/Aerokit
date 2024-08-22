aktuelle Version: v2

Die erste Version war nur ein Zwischenstand, bitte löschen.


Genutzte Bibliotheken:

-standard Libs für den ESP32 welche im Arduino Core enthalten sind (z.B. WiFi, Webserver...)
-Wire Lib für I²C Kommunikation
-Sparkfun SCD30 Lib
-Heltec Lib
-Crypto-LW, Simon-Speck Implementierung (  https://rweather.github.io/arduinolibs/classSpeck.html  )


Vorhandene/implementierte Funktionen:

-auslesen der Sensordaten
-auswerten der Sensordaten (Ampel)
-Ausgabe der Sensordaten auf dem OLED sowie dem Webinterface (Client Mode, SSID und PSK müssen im Quelltext hinterlegt worden sein)
-Ampel als LED und im Webinterface als Balken
-Abfrage der Sensordaten per LoRa, einfache Implementierung mit 32-Bit Adressen und Speck ECC Verschlüsselung (Pre-shared Key)
