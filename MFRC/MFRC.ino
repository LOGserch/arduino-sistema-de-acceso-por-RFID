#include <SPI.h>      
#include <MFRC522.h>      

#define RST_PIN  9      // constante reset
#define SS_PIN  10      // constante slav

MFRC522 mfrc522(SS_PIN, RST_PIN);

//se crean arrays para almacenar UID permitidos
byte LecturaUID[4];        
byte Usuario1[4]= {0x30, 0xC8, 0x80, 0xA2} ;   
byte Usuario2[4]= {0x37, 0x3B, 0x0D, 0x89} ;    

void setup() {
  Serial.begin(9600);     
  SPI.begin();        // inicializa bus SPI
  mfrc522.PCD_Init();     // inicializa modulo lector
  Serial.println("Listo");    
}

void loop() {
  //condicionales para la lectura/respuesta de una tarjetaPICC
  if ( ! mfrc522.PICC_IsNewCardPresent())   
    return;           
  
  if ( ! mfrc522.PICC_ReadCardSerial())     
    return;           
    
    Serial.print("UID:");      
    for (byte i = 0; i < mfrc522.uid.size; i++) { 
      if (mfrc522.uid.uidByte[i] < 0x10){   
        Serial.print(" 0");       
        }
        else{           
          Serial.print(" ");        
          }
          Serial.print(mfrc522.uid.uidByte[i], HEX);    
          LecturaUID[i]=mfrc522.uid.uidByte[i];          
          }
          
          Serial.print("\t");                    
                    
          if(comparaUID(LecturaUID, Usuario1))    
            Serial.println("Bienvenido Usuario 1"); 
          else if(comparaUID(LecturaUID, Usuario2)) 
            Serial.println("Bienvenido Usuario 2"); 
           else           // si retorna falso
            Serial.println("No te conozco");              
                  
                  mfrc522.PICC_HaltA();     // detiene comunicacion con tarjeta                
}

boolean comparaUID(byte lectura[],byte usuario[]) 
{
  for (byte i=0; i < mfrc522.uid.size; i++){    
  if(lectura[i] != usuario[i])        
    return(false);          
  }
  return(true);           
}
