
#include <ros/ros.h>
#include <string>
#include <serial.serial.h>


serial::Serial * serial_conn = nullptr;

void closeSerialConnection(){
 ROS_INFO("Closing connection on port %s", serial_conn->getPort().c_str());
 serial_conn->close();
 delete serial_conn;
  
}

void setupSerialConnection(){
  if (serial_conn != nullptr){
   serial_conn->close();
   delete serial_conn; 
  }
  
  ROS_INFO("Creating serial connection on port: %s, Baud Rate: %d with timeout time: %d", fd.c_str(), baud_rate, timeout);
  serial_conn = new serial::Serial(fd, (u_int32_t) baud_rate, serial::Timeout::simpleTimeout(timeout));
}

std::string serial_out(std::string serial_out_string, bool expect_response = true)
{
    serial_conn->write(serial_out_string); // dont really care about size of the message, let the firmware deal with that

    if (!expect_response)
    {
        return "";
    }

    return serial_conn->readline(65536ul,"\r\n");
}

void setup(){
 Serial.begin(9600); //serial comm at 9600 bits per second
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);
 
}


void getNameOfDevice(){
  Serial.print("DPS");
}

void DPH(){
 
 
 int sensorValue = analogRead(A0); // reading in on analogue pin 0
 float voltage = sensorValue * (5.0/255.0); //0 to 5V at int 0 to 255
 Serial.println(voltage);
}

void LRG(){
  int sensorVal = analogRead(A1);
  Serial.print("Analog Read : ");
  Serial.print(sensorVal);
  
  float voltage = sensorVal * (5.0/255.0);
  analogWrite(13, map(voltage, 0, 255, 0, 5));
  Serial.print(",4-bit PWM value : ");
  Serial.println(map(voltage, 0, 255, 0, 5));
}


int main(int argc, char ** argv){
  setup();
  getNameOfDevice();
  DPH();
  LRG();
}