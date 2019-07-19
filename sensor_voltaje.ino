/**
   Autor: Andrés Soriano Serrano
   Fecha: 17/07/2019
 
   Sensor de voltaje utilizado para medir el porcentaje de batería.
*/
#include  <LiquidCrystal.h>

// CONSTRUCTOR PARA LA PANTALLA LCD 16X2
// AQUI SE CONFIGURAN LOS PINES PARA LA COMUNICACION CON LA PANTALLA
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;   // seleccionar la entrada para el sensor
int sensorValue;         // variable que almacena el valor raw (0 a 1023)
float value;            // variable que almacena el voltaje (0.0 a 25.0)
 
void setup() {
  // INDICAMOS QUE TENEMOS CONECTADA UNA PANTALLA DE 16X2
  lcd.begin(16, 2);
  // MOVER EL CURSOR A LA PRIMERA POSICION DE LA PANTALLA Y BORRAR (0, 0)
  lcd.clear();
  // IMPRIMIR CADENA EN LA PRIMERA POSICION
  lcd.print(" Sensor_Voltaje ");
  // ESPERAR UN SEGUNDO
  delay(1000);
}
 
void loop() {
  // BORRAMOS TODA LA PANTALLA PARA ACTUALIZARLA CADA SEGUNDO
  lcd.clear();
  // IMPRIMIR UN ENCABEZADO
  lcd.print("Carga Restante");
 
  // REALIZAR LECTURA ANALOGICA EN PIN A0
  unsigned int val = analogRead(A0);
  // CONVERTIR ESE VALOR A VOLTAJE (ASUMIENDO QUE EL ARDUINO SE ALIMENTA A 5 VOLTS)
  //float volts = (val*5.00)/1024.00;
  //float v_percent = (volts/5)*100.00;
 
  // IMPRIMIR EL VALOR EN VOLTAJE, DESPUES DE LA LECTURA DEL ADC
  sensorValue = analogRead(sensorPin);// realizar la lectura
  value = mapsense(sensorValue, 0, 1023, 0.0, 25.0);// cambiar escala a 0.0 - 25.0
  /*----------------------------------------------------------------------------------------------------------------------*/
  //esta función se emplea para baterías de paneles solares donde el voltaje mínimo es de 21 voltios para arreglos de 24 voltios
  //value = fmap(sensorValue, 860, 1023, 21, 25.0);// cambiar escala a 0.0 - 25.0

  if (value>99.9)
  {
    lcd.setCursor(6, 1);
    lcd.print(100, 1);
    lcd.print("%");
  }
  else
  {
    lcd.setCursor(6, 1);
    lcd.print(value, 1);
    lcd.setCursor(10, 1);
    lcd.print("%");
  }
  // ESPERAR UN SEGUNDO ANTES DE CONTUNUAR
  delay(1000);
}
 
// cambio de escala entre floats
float mapsense(float x, float in_min, float in_max, float out_min, float out_max)
{
  float volts_sense = ((x-in_min)*(out_max-out_min)/(in_max-in_min))+out_min;
  float v_percent = ((volts_sense-out_min)/(out_max-out_min))*100.0;
  return v_percent;
}
