#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <SoftwareSerial.h>
SoftwareSerial BT(8,7);
int porta_A0 = A0;
int porta_D3 = 4;
int lectura_analogica = 0;
int lectura_digital = 0;
MPU6050 sensor;
int gx, gy, gz;
boolean choque=false;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(porta_A0, INPUT);
  pinMode(porta_D3, INPUT);
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");
}

void loop() {

   
   lectura_analogica = analogRead(porta_A0);
   lectura_digital = digitalRead(porta_D3);
   // Serial.print("Lectura Analogica");
    //Serial.println(lectura_analogica);
  


  sensor.getRotation(&gx, &gy, &gz);
  float gx_deg_s = gx * (250.0/32768.0);
  float gy_deg_s = gy * (250.0/32768.0);
  float gz_deg_s = gz * (250.0/32768.0);

     //Serial.print(gx_deg_s);
    // Serial.print(gy_deg_s);
     //Serial.print(gz_deg_s);
  if(gx_deg_s < -190 && lectura_analogica > 1021 && lectura_digital == 1){
    choque=true;
  }else if(gx_deg_s > 190 && lectura_analogica > 1021 && lectura_digital == 1 ){
    choque=true;
  }else if(gy_deg_s > 190 && lectura_analogica == 1021 && lectura_digital == 1  || gy_deg_s < -190 && lectura_analogica > 1021 && lectura_digital == 1){
  choque=true;
  }else if(gz_deg_s > 100 && lectura_analogica == 1023 && lectura_digital == 1 || gz_deg_s < -100 && lectura_analogica > 1021 && lectura_digital == 1){
  choque=true;
  }

  if(choque==true){
    Serial.println('C');
    BT.write('C');
    BT.print('C');
    Serial.println("entro");
    choque = false;
    delay(20000);
    
    }

};
