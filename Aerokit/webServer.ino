// SSID & Password
const char* ssid = "HIER_SSID_ANGEBEN";  // Enter your SSID here
const char* password = "HIER_PASSWORT_ANGEBEN";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)
static String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>Aerokit v0.1</h1>\
</body>\
</html>";


void setupWebServer() {
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
}

void webServerWork() {
  server.handleClient();
}



// Handle root url (/)
void handle_root() {
// HTML & CSS contents which display on the web server
//Werte in Strings umwandeln
  String co2 = String(co2Gehalt, DEC) + " ppm";
  String hum = String(luftfeuchte, 2) + " %";
  String temp = String(temperatur, 2) + " &deg;C";
  String room = "Klassenraum: ";
  room += roomNumber;



  startHTMLDoc("Aerokit v0.1");
  appendParagraph(room);
  startTable();
  startTableRecord();
  appendTableData("CO2 Gehalt: ", co2);
  endTableRecord();
  startTableRecord();
  appendTableData("Luftfeuchtigkeit: ", hum);
  endTableRecord();
  startTableRecord();
  appendTableData("Temperatur: ", temp);
  endTableRecord();
  endTable();
  appendAmpel();
  endHTMLDoc();
  
  server.send(200, "text/html", HTML);
}
void appendAmpel() {
//Ampel generieren
  String ampelFarbenString = String(ampelFarbe, HEX);
  String ampel = "<table>\
<tr>\
<td>Beurteilung des CO2 Gehalts: </td>\
<td bgcolor=\"#";
  ampel += ampelFarbenString;
  ampel += "\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>\
</tr>\
</table>";

  appendFree(ampel);
}
void startHTMLDoc(String header) {
  HTML = "<!DOCTYPE html>\
<html>\
<body text=\"silver\" bgcolor=\"black\">\
<h1>Aerokit v0.1</h1>\n";
}
void appendFree(String code) {
  HTML += code;
}
void appendParagraph(String text) {
  HTML += "<p>";
  HTML += text;
  HTML += "</p>\n";
}
void startTable() {
  HTML += "<table border=\"1\">\n";
}
void startTableRecord() {
  HTML += "<tr>\n";
}
void appendTableData(String label, String value) {
  HTML += "<td>";
  HTML += label;
  HTML += "</td>\n";
  HTML += "<td>";
  HTML += value;
  HTML += "</td>\n";
}
void endTableRecord() {
  HTML += "</tr>\n";
}
void endTable() {
  HTML += "</table>\n";
}
void endHTMLDoc() {
//refresh einmal pro sekunde  
  HTML += "</body>\n<meta http-equiv=\"refresh\" content=\"1\">";
  HTML += "\n</html>";
}
