

//TMP36 Pin Variables
int sensorPin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                   //the resolution is 10 mV / degree centigrade with a
                   //500 mV offset to allow for negative temperatures
int led1 = 11;
int led2 = 12;
int led3 = 13;

float lowReading = 104.0;         //brown - left(VIN) -> 5V
float highReading = 228.0;        //red - middle(VOUT) -> A0
float lowTemperature = 2.0;       //orange - right(GROUND) -> GND
float highTemperature = 61.6;
float slope;
//float actualReading;
float actualTemperature;

void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  slope = (highReading - lowReading) / (highTemperature - lowTemperature);
}
 
void loop()                     // run over and over again
{
 testingProcess();
 //calibrationProcess();
}

void calibrationProcess()
{
 int reading = analogRead(sensorPin);  
 Serial.print(reading); Serial.println(" reading");

 delay(10000);
}

void testingProcess()
{
  //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 Serial.print(reading); Serial.println(" reading");

 float voltage = reading * 5.0;
 voltage /= 1024.0;
 Serial.print(voltage); Serial.println(" voltage");

 actualTemperature = ((reading - lowReading) / slope) + lowTemperature;
 
 Serial.print(actualTemperature); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (actualTemperature * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");

 lightUp(actualTemperature);
 
 delay(10000);
}

void lightUp(float temp)
{
  if(temp >= 30.0 && temp < 59.9){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
 }
  else if(temp >= 0.0 && temp < 29.9){
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led3, LOW);
  }
  else if(temp >= 60.0 && temp <= 100.0){
    digitalWrite(led3, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  } 
}
