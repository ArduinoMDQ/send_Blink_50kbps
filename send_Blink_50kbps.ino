// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int ledHIGH    = 1;
const int ledLOW     = 0;
const int LED=13;
const char ID_TX=0x80;
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
START_INIT:

    if(CAN_OK == CAN.begin(CAN_50KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS inicio ok!");
    }
    else
    {
        Serial.println("CAN BUS fallo al iniciar");
        Serial.println("Reinicio CAN BUS otra vez");
        delay(2000);
        goto START_INIT;
    }
}


unsigned char stmpON[8] = {ledHIGH, 1, 1, 3, ledLOW, 5, 6, 7};
unsigned char stmpOFF[8] = {ledHIGH, 1, 0, 3, ledLOW, 5, 6, 7};


void recepcion()

{
 
    unsigned char len = 0;
    unsigned char buf[8];
 if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned char canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Dispositivo ID: ");
        Serial.println(canId);
        
         if(buf[2]==1){
             Serial.println("El Led se Encendio.");
        digitalWrite(LED,HIGH);
        }else{
           Serial.println("El Led se Apago.");
         digitalWrite(LED,LOW);}
        }
    
   Serial.println("-----------------------------");

}




void loop()
{   Serial.println("Dato enviado");
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(ID_TX,0, 8, stmpON);
    delay(50);     
    recepcion();
    delay(2000);                       // send data per 100ms
  
    CAN.sendMsgBuf(ID_TX,0, 8, stmpOFF);
    delay(50);     
    recepcion();
    delay(2000); 
     
   
    
    
    
}



/***
******************************************************************************************************
  END FILE
*********************************************************************************************************/
