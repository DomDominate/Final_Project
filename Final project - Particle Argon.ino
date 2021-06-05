// This #include statement was automatically added by the Particle IDE.
#include <JsonParserGeneratorRK.h>

// This #include statement was automatically added by the Particle IDE.
#include <I2CSlaveRK.h>


I2CSlave device(Wire, 0x10, 1);

int x = 0;
int old_x = 0;
int volume;

void upload(double volume)
{
    JsonWriterStatic<256> jw;
    {
        JsonWriterAutoObject obj (&jw);
        jw.insertKeyValue("volume",volume);
    }
    Particle.publish("volume", jw.getBuffer(), PRIVATE);
}    

void receiveEvent(int howMany) {
    
    x = Wire.read();          // receive byte as an integer
    Serial.print("Water surface drop: ");
    Serial.println(x);            // print the integer
    volume = 3.14159264 * 5.5 * 5.5 * x;
}

void setup() {
    Wire.begin(0x10);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event
    Serial.begin();           // start serial for output
}

void loop() {
    delay(100);
    
    if (old_x != x)
    {
        Serial.print("Volume of water decreased: ");
        Serial.println(volume);
        upload(volume);
        Particle.publish("Water_bowl_status","Dog just drank water");
    }
    old_x = x;
}