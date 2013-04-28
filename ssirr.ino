/*Released under GPL2.0 or later

SSIRR v.10
a Simple Serial IR Receiver

Based on an example program from Shirriff's blog. This adds the 
necessary output info needed to use Shiriff's IR library to send
signals.
This version of this program is meant to be as simple as possible
for the task at hand. Tested and working with Mega2560. 

File edited and re-released by dave@xtechgeek.com

Point a remote at the receiver, push a button. Info can be viewed
from Arduino serial monitor. Record the received info and the button 
it corrosponds with. 
Sometimes the receiver is succeptable to interference, it is very
easy to notice and dismiss the false signals.

Enjoy
*/


//This program requires Shiriff's IR library found here: https://github.com/shirriff/Arduino-IRremote

#include <IRremote.h> 

const int RECV_PIN = 4;
//pin 4 is connected to timer pin on mega2560. MUST connect IR receiver here.
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true); //enables use of the Arduino Mega's LED to signal IR reception
  Serial.println("SSIRR ready: feed me remote codes...");
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.decode_type == NEC) {
      Serial.println("Signal type:  NEC ");
    } else if (results.decode_type == SONY) {
      Serial.println("Signal type:  SONY ");
    } else if (results.decode_type == RC5) {
      Serial.println("Signal type:  RC5 ");
    } else if (results.decode_type == RC6) {
      Serial.println("Signal type:  RC6 ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.println("Signal type:  UNKNOWN ");//info provided with Unknown signals may not be useful as it's Hex and not RAW?
    }
    Serial.print("Hex value:    0x");Serial.println(results.value,HEX);//the singal type (above), hex value, and number of bits is the necessary info to send IR using Shiriff's IR library.
    Serial.print("Bitcount:     ");Serial.print(results.bits);Serial.println(" bits");
    Serial.println(""); //just to put a space between received codes.
    irrecv.resume(); // Receive the next value
  }
}
