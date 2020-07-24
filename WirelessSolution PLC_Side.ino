#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24;

void setup() {
  Serial.begin(9600);
  while (!Serial) 
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
    pinMode(A0,OUTPUT);
    pinMode(A1,OUTPUT);
    pinMode(A2,OUTPUT);
    pinMode(A3,OUTPUT);
    pinMode(4,INPUT);
    pinMode(5,INPUT);
    pinMode(6,INPUT);
    pinMode(7,INPUT);
}

void setIndicators(char m){
  if (m == "A01"){
    digitalWrite(A0,HIGH);
  }
  else if (m == "A00"){
    digitalWrite(A0,LOW);
  }
  else if (m == "A11"){
    digitalWrite(A0,HIGH);
  }
  else if (m == "A10"){
    digitalWrite(A1,LOW);
  }
  else if (m == "A21"){
    digitalWrite(A1,HIGH);
  }
  else if (m == "A20"){
    digitalWrite(A2,LOW);
  }
  else if (m == "A31"){
    digitalWrite(A3,HIGH);
  }
  else if (m == "A30"){
    digitalWrite(A3,LOW);
  }
}

void sendOnce(char x){
    uint8_t data[2] = {x};
    nrf24.send(data, sizeof(data));
    
    nrf24.waitPacketSent();
    // Now wait for a reply
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
  
    if (nrf24.waitAvailableTimeout(500))
    {   
      if (nrf24.recv(buf, &len))
      {
        Serial.print("got reply: ");
        Serial.println((char*)buf);
        setIndicators((char*)buf);
      }
      else
      {
        Serial.println("recv failed");
      }
    }
    else
    {
      Serial.println("No reply, is nrf24_server running?");
    }
}

void loop() {
 Serial.println("Sending Status");
  
  if (digitalRead(4) == HIGH){
    sendOnce("41");
  }
  else if (digitalRead(4) == LOW){
    sendOnce("40");
  }
  if (digitalRead(5) == HIGH){
    sendOnce("51");
  }
  else if (digitalRead(5) == LOW){
    sendOnce("50");
  }
  if (digitalRead(6) == HIGH){
    sendOnce("61");
  }
  else if (digitalRead(6) == LOW){
    sendOnce("60");
  }
  if (digitalRead(7) == HIGH){
    sendOnce("71");
  }
  else if (digitalRead(7) == LOW){
    sendOnce("70");
  }
  delay(200);
}
