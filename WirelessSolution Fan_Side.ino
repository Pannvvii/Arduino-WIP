#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}
void returnStatus(char x){
  uint8_t data[3] = {x};
  nrf24.send(data, sizeof(data));
  nrf24.waitPacketSent();
  Serial.println("Sent a reply");
}
void loop() {
  if (nrf24.available())
  {  
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got request: ");
      Serial.println((char*)buf);
      if ((char*)buf == "41"){
        digitalWrite(4,HIGH);
        returnStatus("A01");
      }
      else if ((char*)buf == "40"){
        digitalWrite(4,LOW);
        returnStatus("A00");
      }
      else if ((char*)buf == "51"){
        digitalWrite(4,HIGH);
        returnStatus("A11");
      }
      else if ((char*)buf == "50"){
        digitalWrite(4,LOW);
        returnStatus("A10");
      }
      else if ((char*)buf == "61"){
        digitalWrite(4,HIGH);
        returnStatus("A21");
      }
      else if ((char*)buf == "60"){
        digitalWrite(4,LOW);
        returnStatus("A20");
      }
      else if ((char*)buf == "71"){
        digitalWrite(4,HIGH);
        returnStatus("A31");
      }
      else if ((char*)buf == "70"){
        digitalWrite(4,LOW);
        returnStatus("A30");
      }
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}
