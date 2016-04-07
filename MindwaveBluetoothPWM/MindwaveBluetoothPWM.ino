////////////////////////////////////////////////////////////////////////
// 
// Project Uplift : Lift The World With Your Mind Tower
// The MIT License (MIT)
// Copyright (c) 2016 Zachary Valenti
//
////////////////////////////////////////////////////////////////////////


//Pins used
const int fan_pwm_pin = 9;
const int fan_relay_pin = 3;


#define BAUDRATE 57600

//Increase both numbers to make the game more challenging
//Always keep MEDITATION_HIGH_THRESHOLD > MEDITATION_LOW_THRESHOLD
#define MEDITATION_HIGH_THRESHOLD  85
#define MEDITATION_LOW_THRESHOLD   75

//Command codes for communication with the Mindwave Headset
#define SYNC                 0xAA
#define CONNECT              0xC0
#define DISCONNECT           0xC1
#define AUTOCONNECT          0xC2
#define EXCODE               0x55
#define POOR_SIGNAL          0x02
#define ATTENTION            0x04
#define MEDITATION           0x05
#define BLINK                0x16
#define HEADSET_CONNECTED    0xD0
#define HEADSET_NOT_FOUND    0xD1
#define HEADSET_DISCONNECTED 0xD2
#define HEADSET_DENIED       0xD3
#define STANDBY_SCAN         0xD4
#define EXTENDED_CASE        0x80  
#define ASIC_EEG_POWER       0x83


// checksum variables
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

// system variables
long lastReceivedPacket = 0;
boolean receivedMeditation = false;


//////////////////////////
// Microprocessor Setup //
//////////////////////////

void setup() 
{
  //Set pins to outputs
  pinMode(fan_relay_pin, OUTPUT);
  pinMode(fan_pwm_pin, OUTPUT);
  
  //Turn fans OFF from the start
  digitalWrite(fan_relay_pin, HIGH);  
  analogWrite(fan_pwm_pin, 0);  
  
  //Initialize serial communication
  Serial.begin(BAUDRATE);
  
  
  //////////////////////////////////
  // Startup test sequence of fan //
  //////////////////////////////////
  
  //Turn on relay fan
  digitalWrite(fan_relay_pin, LOW);
  
  //Gradually increase speed of PWM fan
  for (int i = 0; i < 256; i++)
  {
    analogWrite(fan_pwm_pin, i);
    delay(100);
  }
  delay(5000);
  
  //Turn PWM fan off.
  analogWrite(fan_pwm_pin, 0);
  
  //Turn off relay fan
  digitalWrite(fan_relay_pin, LOW);
}



/////////////
//MAIN LOOP//
/////////////

void loop() {  
  

  
  
  ReadPacket();
  if(receivedMeditation) {
    ControlBall(meditation);  
  }  
}



////////////////////////////////
// Read data from Serial UART //
////////////////////////////////

byte ReadOneByte() 
{
  int ByteRead;
  
  while(!Serial.available());  // Wait until something is available
  ByteRead = Serial.read();    // Read it

  return ByteRead;
}


//Decode mindwave packet
//_Format_
//Byte 1: SYNC
//Byte 2: SYNC
//Byte 3: Payload Length  (if longer than 169 we don't care about this packet)
//Byte 4-(3+Payload Length): Payload data
//Byte 4+Payload Length: checksum (sum of payload bytes subtracted from 255)

//Payload consists of Data types, sometimes followed by data
void ReadPacket(void)
{
  if(ReadOneByte()==SYNC)    //Byte 1
  {
    if(ReadOneByte()==SYNC)  //Byte 2
    {
      payloadLength = ReadOneByte();  //Byte 3
      if(payloadLength > 169)
        return;
      generatedChecksum = 0;
      for(int i = 0; i<payloadLength; i++)  //Payload bytes
      {
        digitalWrite(4,1);
        payloadData[i] = ReadOneByte();
        digitalWrite(4,0);
      }
      checksum = ReadOneByte();        //Checksum byte
      for(int i=0;i<payloadLength;i++)
      {
        generatedChecksum+=payloadData[i];
      }  
      generatedChecksum=0xFF-generatedChecksum;
      if(checksum == generatedChecksum)    //only decode packet if the checksum is valid
      {
        digitalWrite(5,1);
        for(int i=0; i<payloadLength; i++)
        {
          switch(payloadData[i])
          {
            case POOR_SIGNAL:
              i++;
              poorQuality=payloadData[i];
              break;
            case ATTENTION:
              i++;
              attention=payloadData[i];
              break;
            case MEDITATION:
              i++;
              digitalWrite(6,1);
              meditation=payloadData[i];
              receivedMeditation=true;              //If we received the meditation data then we indicate the need to process packet
              digitalWrite(6,0);
              break;
            case ASIC_EEG_POWER:      //We don't care about the raw data
              i+=25;
              break;
            case EXTENDED_CASE:
              i+=3;
              break;
            default:
              break;
          }
        }
        digitalWrite(5,0);
      }
    }
  }
}



////////////////////////////////////////////////
// Control the fan(s) that controls the ball  //
////////////////////////////////////////////////

void ControlBall(byte meditate)
{       
  
  //Set PWM for fan speed
  int fan_speed = map(meditate, 0, 100, 0, 255);    //Meditation value goes from 0 (stressed) to 100 (relaxed)
  analogWrite(fan_pwm_pin, fan_speed);
    
  
  if(meditate > MEDITATION_HIGH_THRESHOLD)
  {
    //Turn on fan connected to relay
    digitalWrite(fan_relay_pin, HIGH);
  }
  
  else if(meditate < MEDITATION_LOW_THRESHOLD)
  {
    //Turn off fan connected to relay
    digitalWrite(fan_relay_pin, LOW);
  }
  
  //clear process flag until we get new data
  receivedMeditation = false;
}


