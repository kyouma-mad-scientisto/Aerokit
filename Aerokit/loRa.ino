#define SpreadingFactor 10
#define CodeRate 8
#define Bandwidth 125E3
#define TX_Power 20 

#define Packetsize 16
//Adressen dieses Moduls und des Clients, welcher per LoRa anfragt
const uint32_t ADDRESS_OF_OTHER_MODULE = 0xF08AC7FF;
const uint32_t ADDRESS_OF_THIS_MODULE = 0x0FA87CFF;


//Encryption
Speck speck;
const char key[16] = {"Make@thon112020"};    //Preshared Key


void setupLoRa() {
  //set key for encryption
  speck.setKey((byte*)key, 16);

  LoRa.setTxPower(TX_Power, RF_PACONFIG_PASELECT_PABOOST);
  LoRa.setSignalBandwidth(Bandwidth);
  LoRa.setCodingRate4(CodeRate);
  LoRa.enableCrc();
  LoRa.setSpreadingFactor(SpreadingFactor);
}
void sendPacket() {
/* Paketaufbau:
 * Little Endian
 * Byte 0 - 3 = uint32_t ID der Gegenstelle
 * Byte 4 - 5 = uint16_t co2
 * Byte 6 - 10 = char feuchte[5]  (999,99)  (C-String ohne Nullterminierung)
 * Byte 11 - 15 = char temperatur[5] (999,99)  (C-String ohne Nullterminierung)
 * 
 */
    byte puffer[Packetsize];
    memcpy(puffer, &ADDRESS_OF_OTHER_MODULE, sizeof(uint32_t));
    memcpy(&puffer[sizeof(uint32_t)], &co2Gehalt, sizeof(uint16_t));

    uint8_t digits = 4;
    char tempArr[7];
    String feuchte = String(luftfeuchte);
    feuchte.toCharArray(tempArr, 7);
    if(luftfeuchte >= 100) digits = 5;
    if(digits == 4) {
      puffer[sizeof(uint32_t)+sizeof(uint16_t)] = '0';  //Padding fuer Hunderterstelle
      memcpy(&puffer[sizeof(uint32_t)+sizeof(uint16_t)+1], tempArr, 2);  //da zwei Stellen vor Komma
    } else {
        memcpy(&puffer[sizeof(uint32_t)+sizeof(uint16_t)], tempArr, 3);  //da drei Stellen vor Komma
    }
    memcpy(&puffer[sizeof(uint32_t)+sizeof(uint16_t)+1+3], tempArr, 2);  //da zwei Stellen nach Komma
    String temp = String(temperatur);
    temp.toCharArray(tempArr, 7);
    if(temperatur >= 100) digits = 5;
    if(digits == 4) {
      puffer[sizeof(uint32_t)+sizeof(uint16_t)] = '0';  //Padding fuer Hunderterstelle
      memcpy(&puffer[sizeof(uint32_t)+sizeof(uint16_t)+1], tempArr, 2);  //da zwei Stellen vor Komma
    } else {
        memcpy(&puffer[sizeof(uint32_t)+sizeof(uint16_t)], tempArr, 3);  //da drei Stellen vor Komma
    }
    memcpy(&puffer[sizeof(uint32_t)+sizeof(uint16_t)+1+3], tempArr, 2);  //da zwei Stellen nach Komma
        
    LoRa.beginPacket(Packetsize);   //Implizite Header
    speck.encryptBlock(puffer,puffer);                            //daten verschluesseln
    LoRa.write(puffer, Packetsize);
    LoRa.endPacket();    
}
void receivePacket() {
/* Paketaufbau:
 * Little Endian
 * Byte 0 - 3 = uint32_t ID dieses Moduls
 * Byte 4 - 15 = 0
 * 
 */
 int16_t incomingPacketSize = LoRa.parsePacket();
  if(incomingPacketSize == Packetsize) {
    byte puffer[Packetsize];
    LoRa.readBytes(puffer, Packetsize);
//ankommende Daten entschluesseln
    speck.decryptBlock(puffer,puffer);
    uint32_t addressReceived = 0;
//Adresse aus Puffer einlesen
    for(uint8_t i = 0,j = 0; i<sizeof(uint32_t) ; i++,j+=8) {
      addressReceived |= ((uint32_t)puffer[i] << j);
    }
//falls adresse korrekt, code ausfuehren  
    if(addressReceived == ADDRESS_OF_THIS_MODULE) {
      sendPacket();
    }
  }
}
