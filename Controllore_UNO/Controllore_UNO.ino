/**
 * Controllore camera pulita
 *
 * Copyright 2016 Andrea Lacava <thecave003@gmail.com>
 * Contact me for question/ suggestions etc. at http://www.andrealacava.com/
 * Version 0.8 RELEASE CANDIDATE
 */

//Sensore interno pressione costants
const int sensorPinInPres = A1;
const float conv_factorOne = 1.009f;
const float conv_factorTwo = 0.027508f;
//fattori di conversioni del segnale in bit a volt sono gli stessi del sensore ambientale


//MPXA6115AU/T1 enviroment_pression Handling costants
const int sensorPinPress = A0;
const float v_s = 5.0;
const float v_sbit = 1024.0f;
const float offeset = 0.095f;
const float factor = 0.009f;
const float to_mbar = 10.0f;

//KY015 Handling constants
const int DHpin = 8;
byte dat [5];

//execution time
unsigned long i =0;

//Sensore interno
void internal_pression_Handling(){
  int iPresVal = analogRead(sensorPinInPres);
  float bar_out = ((iPresVal/v_sbit)*v_s*conv_factorOne)+conv_factorTwo;

  Serial.print(bar_out,DEC);

  }


//MPXA6115AU/T1
void enviroment_pression_Handling(){

  int sensorPresVal = analogRead(sensorPinPress);
  float v_out = (sensorPresVal/v_sbit)*v_s;
  float pres = ((v_out/v_s)+offeset)/factor;
  float pres_bar = pres*to_mbar; /* 1 bar = 100 kPA */

 /* Serial.print(sensorPresVal);
  Serial.print(';');
  Serial.print(v_out,DEC);
  Serial.print(';');
  Serial.print(pres,DEC);
  Serial.print(';');*/
  Serial.print(pres_bar,DEC);
  }


//KY015 read data aux
byte read_data () {
  byte data;
  for (int i = 0; i < 8; i ++) {
    if (digitalRead (DHpin) == LOW) {
      while (digitalRead (DHpin) == LOW); // wait for 50us
      delayMicroseconds (30); // determine the duration of the high level to determine the data is '0 'or '1'
      if (digitalRead (DHpin) == HIGH)
        data |= (1 << (7-i)); // high front and low in the post
      while (digitalRead (DHpin) == HIGH); // data '1 ', wait for the next one receiver
     }
  }
return data;
}

void KY015Handling(){

  digitalWrite (DHpin, LOW); // bus down, send start signal
  delay (30); // delay greater than 18ms, so DHT11 start signal can be detected

  digitalWrite (DHpin, HIGH);
  delayMicroseconds (40); // Wait for DHT11 response

  pinMode (DHpin, INPUT);
  while (digitalRead (DHpin) == HIGH);
  delayMicroseconds (80); // DHT11 response, pulled the bus 80us
  if (digitalRead (DHpin) == LOW);
  delayMicroseconds (80); // DHT11 80us after the bus pulled to start sending data

  for (int i = 0; i < 4; i ++) // receive temperature and humidity data, the parity bit is not considered
    dat[i] = read_data ();

  pinMode (DHpin, OUTPUT);
  digitalWrite (DHpin, HIGH); // send data once after releasing the bus, wait for the host to open the next Start signal
  Serial.print(';');
  Serial.print(dat [0], DEC); // display the humidity-bit integer;
  Serial.print('.');
  Serial.print(dat [1], DEC); // display the humidity decimal places;
  Serial.print(';');
  Serial.print(dat [2], DEC); // display the temperature of integer bits;
  Serial.print('.');
  Serial.print(dat [3], DEC); // display the temperature of decimal places;
  Serial.print(';');

  }

void setup() {
  Serial.begin (9600);
  pinMode (DHpin, OUTPUT);
  delay(2000);
  Serial.println("Enviroment pressure Sensor;;;;KY015 Sensor;;Internal pressure sensor");
  Serial.println(/*"Sensor value;Vout;Enviroment pressure KPa;"*/"Enviroment pressure mBar; Humidity %; Temp °C; Internal pressure;Time");
}

void loop() {
  enviroment_pression_Handling();
  KY015Handling();
  internal_pression_Handling();
  Serial.print(';');
  Serial.println(i);
  i++;
  delay(10000); //ogni 10 secondi deve lavorare
}
