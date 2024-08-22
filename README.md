# Aerokit

Dieses Projekt habe ich für den Makeathon 2020 umgesetzt.
Die Anforderung bestand darin, eine CO2-Ampel für Klassenzimmer zu entwickeln.
Da es zwischen CO2 Gehalt der Luft und Virenlast einen direkten Zusammenhang gibt, kann man durch Ermittlung des CO2 Gehaltes der Luft bestimmen, wann der optimale Zeitpunkt zum lüften des Klassenzimmers gekommen ist, um einerseits das Ansteckungsrisiko zu reduzieren und andererseits weiterhin im Winter sinnvoll heizen zu können.
Im Klassenzimmer ist also ein Gerät mit einer RGB LED, welches farblich signalisiert, wann gelüftet werden muss. Darüberhinaus gibt es eine Webanbindung, die das auslesen der Messwerte ermöglicht.

Die benötigte Hardware wurde von den Organisatoren des Makeathons zur Verfügung gestellt und enthielt:

1x ESP32 Kit mit OLED Display
1x SCD30 (CO2 Sensor)
1x RGB LED
1x Steckbrett
diverse Verbindungskabel

Bei meiner Implementierung habe ich zusätzlich noch ein LoRa Funkmodul ergänzt, welches die Daten verschlüsselt per LoRa an eine zentrale Stelle übermitteln kann, da zentralisierung eine wichtige Anforderung war, um alle Messdaten zu sammeln und evtl. nicht jeder Klassenraum über WLAN verfügt.
