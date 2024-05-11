import processing.serial.*;
import ddf.minim.*;
 
Serial myPort;
Minim minim;
AudioPlayer player;
byte pos1 = 1;
byte pos2 = 2;
byte pos3 = 3;
 
void setup()
{
  // In the next line, you'll need to change this based on your USB port name
  myPort = new Serial(this, "/dev/tty.usbmodem101", 9600);
  minim = new Minim(this);
 
  // Put in the name of your sound file below, and make sure it is in the same directory
  
}
 
void draw() {
  while (myPort.available() > 0) {
    int inByte = myPort.read();
    print(inByte);
    if (inByte == 5) {
      player = minim.loadFile("C.mp3");
      player.rewind();
      player.play();
    }
    if (inByte == 4) {
      player = minim.loadFile("E.mp3");
      player.rewind();
      player.play();
    }
    if (inByte == 3) {
      player = minim.loadFile("G.mp3");
      player.rewind();
      player.play();
    }
    if (inByte == 2) {
      player = minim.loadFile("B.mp3");
      player.rewind();
      player.play();
    }
    if (inByte == 1) {
      player = minim.loadFile("CUp.mp3");
      player.rewind();
      player.play();
    }
    if (inByte == 0) {
      player = minim.loadFile("EUp.mp3");
      player.rewind();
      player.play();
    }
  }
}

void stop() {
  player.close(); // Close the player and release resources
  minim.stop();
  
  super.stop();
  myPort.stop(); // Ensure the serial port is closed properly
}
