# SmartHomeHub
Smart Home Hub built in C/C++ and controls the elements of the smart hub running on remote Pis  

g++ main.cpp settings.cpp -o main `pkg-config gtkmm-3.0 --cflags --libs`  

To mount a samba folder as a location: make sure the mounting point exists  
sudo mount -t cifs -o user=pi,iocharset=utf8,noperm //raspberrypi/garageshare ~/shares/garageshare  


## THIS CODE IS PROVIDED AS IS!!! THIS WILL MOST LIKELY NOT WORK OUT OF THE BOX ON YOUR MACHINE! A LOT OF SETUP IS REQUIRED

## ONLY A PROTOTYPE

### Devices, Programming Languages, & Programs Used
* 3 Raspberry Pi 3s running Raspbian
* A Raspberry Pi 2B running Raspbian
* C++ to delegate methods to the GUI
* C for the thermostat controller
* Python for most of the other controllers
* Glade to build the Gtkmm based GUI
* SSH to connect to the Pis
* Samba to be able to mount Pi directories locally
* A whole lot of good luck and the help of the brilliant @marymenges
