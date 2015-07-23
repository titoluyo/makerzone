/*The "nunchuck_funcs.h" library was built by Tod E. Kurt.  More information about this library is available at:
http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available. */

#include <Wire.h>
#include "nunchuck_funcs.h"    

int loop_cnt=0;

byte accx,accy,accz,zbut,cbut,joyx,joyy;

void setup()
{
   Serial.begin(115200);
   nunchuck_setpowerpins();
   nunchuck_init(); // send the initilization handshake  
}

void loop()
{
       nunchuck_get_data();
       accx  = nunchuck_accelx(); // ranges from approx 70 - 182
       accy  = nunchuck_accely(); // ranges from approx 65 - 173
       accz  = nunchuck_accelz();
       zbut = nunchuck_zbutton();
       cbut = nunchuck_cbutton();
       joyx = nunchuck_joyx();
       joyy = nunchuck_joyy();
       Serial.print((byte)accx,DEC);
       Serial.print(",");  
       Serial.print((byte)accy,DEC);
       Serial.print(",");    
       Serial.print((byte)accz,DEC);
       Serial.print(",");    
       Serial.print(joyx, DEC); 
       Serial.print(",");         
       Serial.print(joyy, DEC);  
       Serial.print(",");        
       Serial.print((byte)zbut,DEC);
       Serial.print(",");  
       Serial.print((byte)cbut,DEC);
       Serial.print(",");  
       Serial.println("eol");
       delay(25);  //wait 25 ms
}




