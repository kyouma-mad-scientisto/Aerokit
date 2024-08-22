# Aerokit

Dieses Projekt habe ich für den Makeathon 2020 umgesetzt.<br />
Die Anforderung bestand darin, eine CO2-Ampel für Klassenzimmer zu entwickeln.<br />
Da es zwischen CO2 Gehalt der Luft und Virenlast einen direkten Zusammenhang gibt, kann man durch Ermittlung des CO2 Gehaltes der Luft bestimmen, wann der optimale Zeitpunkt zum lüften des Klassenzimmers gekommen ist, um einerseits das Ansteckungsrisiko zu reduzieren und andererseits weiterhin im Winter sinnvoll heizen zu können.<br />
Im Klassenzimmer ist also ein Gerät mit einer RGB LED, welches farblich signalisiert, wann gelüftet werden muss. Darüberhinaus gibt es eine Webanbindung, die das auslesen der Messwerte ermöglicht.<br />

Die benötigte Hardware wurde von den Organisatoren des Makeathons zur Verfügung gestellt und enthielt:<br />

1x ESP32 Kit mit OLED Display<br />
1x SCD30 (CO2 Sensor)<br />
1x RGB LED<br />
1x Steckbrett<br />
diverse Verbindungskabel<br />

Bei meiner Implementierung habe ich zusätzlich noch ein LoRa Funkmodul ergänzt, welches die Daten verschlüsselt per LoRa an eine zentrale Stelle übermitteln kann, da zentralisierung eine wichtige Anforderung war, um alle Messdaten zu sammeln und evtl. nicht jeder Klassenraum über WLAN verfügt.<br />

Schaltung CO2-Ampel<br />
![CO2-Ampel](https://github.com/kyouma-mad-scientisto/Aerokit/blob/main/CO2-Ampel.png)

Schaltung LoRa Empfänger<br />
![LoRa Empfänger](https://github.com/kyouma-mad-scientisto/Aerokit/blob/main/CO2-Empf%C3%A4nger.JPG)

