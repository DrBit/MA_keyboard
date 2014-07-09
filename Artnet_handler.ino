
/*
Chaned some things for Arduino 1.0

ARTNET SENDER

This SCRIPT allows you to use arduino with ethernet shield or wifi shield and send dmx artnet data. 
Up to you to use logics for channels as you want.

It works with Arduino 023 software

If you have implemented ameliorations to this sketch, please, contribute by sending back modifications, ameliorations, derivative sketch. 
It will be a pleasure to let them accessible to community

This sketch is part of white cat lighting board suite: /http://www.le-chat-noir-numerique.fr  
wich is sending data to many different types of devices, and includes a direct communication in serial also with arduino as devices
You may find whitecat interresting because its theatre based logic ( cuelist and automations) AND live oriented ( masters, midi, etc)

(c)Christoph Guillermet
http://www.le-chat-noir-numerique.fr
karistouf@yahoo.fr
*/

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>       // UDP library from: bjoern@cs.stanford.edu 12/30/2008

//MAC and IP of the ethernet shield
//MAC adress of the ethershield is stamped down the shield
//to translate it from hexa decimal to decimal, use: http://www.frankdevelopper.com/outils/convertisseur.php

//TO EDIT:
// the next two variables are set when a packet is received
byte destination_Ip[]= {   255,255,255,255 };        // the ip to send data, 255,255,255,255 is broadcast sending
// art net parameters
unsigned int localPort = 6454;      // artnet UDP port is by default 6454
// We set default to subnet 6 universe 4 (universe 100 in MA)
byte DMX_Subnet=6;//Subnet is from 0 to 15 (0 till F)
byte DMX_Universe=5;//universe is from 0 to 15 (0 till F)
unsigned int full_dmx_address = (DMX_Subnet*16)+DMX_Universe;   // Full address
const int number_of_channels=226; //512 for 512 channels, MAX=512

//HARDWARE
byte mac[] = {  144, 162, 218, 00, 17, 96  };//the mac adress of ethernet shield or uno shield board
byte ip[] = {   192,168,0,117 };// the IP adress of your device, that should be in same universe of the network you are using, here: 192.168.1.x

//ART-NET variables
char ArtNetHead[8]="Art-Net";
const int art_net_header_size=17;

// OpCodes
short OpOutput= 0x5000 ;//output

byte buffer_dmx[number_of_channels]; //buffer used for DMX data

EthernetUDP Udp;

//Artnet PACKET
byte  ArtDmxBuffer[(art_net_header_size+1)+512];


void setup_artnet() {

  //initialise artnet 
  Serial.println ("Init Artnet");
  clear_artnet_buffer ();
  construct_arnet_packet();
  // démarrage ethernet et serveur UDP
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
}

void loop_artnet() {
  
   construct_arnet_packet();
   
   Udp.beginPacket(destination_Ip, localPort);
   Udp.write(ArtDmxBuffer,(art_net_header_size+1+512)); // was Udp.sendPacket
   Udp.endPacket();

   //clear_artnet_buffer ();

   // delay (20);

}

void artnet_buffer_on(int dmx_channel)
{
  // Build arduino bufffer
  buffer_dmx[dmx_channel-1]=byte(255);
}

void artnet_buffer_off(int dmx_channel)
{
  // Build arduino bufffer
  buffer_dmx[dmx_channel-1]=byte(0);
}

void clear_artnet_buffer () {
  for (int t= 0;t<number_of_channels;t++)
  {
    buffer_dmx[t]=byte(0);    
  }
}

void construct_arnet_packet()
{
  //Field 1 - ID (Int8 array)[8]
  for (int i=0;i<7;i++)
  {
    ArtDmxBuffer[i]=ArtNetHead[i];
  }   

  //Field 2 - Opcode (int16)  
  ArtDmxBuffer[8]=OpOutput;
  ArtDmxBuffer[9]= OpOutput >> 8;

  //Field 3 - ProtVerHi (int8) 
  ArtDmxBuffer[10]=0;

  //Field 4 - ProtVerLow (int8)
  ArtDmxBuffer[11]=14;

  //Field 5 - Sequence (int8)
  ArtDmxBuffer[12]=0;
  /*The sequence number is used to ensure that ArtDmx packets are used in the correct order. When Art-Net 
  is carried over a medium such as the Internet, it is possible that ArtDmx packets will reach the receiver 
  out of order. 
  This field is incremented in the range 0x01 to 0xff to allow the receiving node to resequence packets. 
  The Sequence field is set to 0x00 to disable this feature. */
   
  //Field 6 - Physical (int8)
  ArtDmxBuffer[13] = 0;
  /*The physical input port from which DMX512 data was input. This field is for information only. Use Universe 
  for data routing.*/

  // Calulate final address based on subnet and universe.
  // Ex: subnet1 uni1 = address 17 (subnet 1 is the 0trough 15 universes after first 0-15 universes (subnet0))

  //Field 7 - SubUni (int8) 
  ArtDmxBuffer[14]= full_dmx_address;
  /*The low byte of the 15 bit Port-Address to which this packet is destined.*/

  //Filed 8 - NET (int8)
  ArtDmxBuffer[15]= full_dmx_address >> 8;
  /*The top 7 bits of the 15 bit Port-Address to which this packet is destined.*/

  //Filed 9 - LengthHi (int8)
  ArtDmxBuffer[16] = byte(512) >> 8;

  //Filed 10 - Length (int8)
  ArtDmxBuffer[17] = byte(512);

  //Filed 11 - Length (int8) [Length]
  for (int t=0;t<512;t++)
  {
    if (t<number_of_channels) {
      ArtDmxBuffer[t+art_net_header_size+1]=buffer_dmx[t];
    }else{
      ArtDmxBuffer[t+art_net_header_size+1]=byte(0);
    }
  }
  /*An variable length array of DMX512 lighting data.*/
}

void change_full_dmx_address (int new_fulladdress) {
  full_dmx_address = new_fulladdress;
}

void change_subnet (byte new_subnet) {
  DMX_Subnet = new_subnet;
  full_dmx_address = (DMX_Subnet*16)+DMX_Universe;    // Recalculate full address
}

void change_universe (byte new_universe) {
  DMX_Universe = new_universe;
  full_dmx_address = (DMX_Subnet*16)+DMX_Universe;    // Recalculate full address
}

byte get_DMX_subnet () {
  return DMX_Subnet;
}

byte get_DMX_universe () {
  return DMX_Universe;
}

int get_DMX_full_address () {
  return full_dmx_address;
}
