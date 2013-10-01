/*  // MA Keyboard testing
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino Uno:  2, 3
     Arduino Due:  All pins, except 13 (LED)
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 2.0:   All pins, except 13 (LED)
     Teensy 2.0:   5, 6, 7, 8
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
*/



// Publicar a Drbit i vendre kits

   
#include <PS2Keyboard.h>

const int DataPin = 5;
const int IRQpin =  3;

PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("MA Keyboard Test");
  init_DBs ();
  Show_all_records();
  Serial.println("Press ` Key to access mapping functions");
}

void loop() {
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    unsigned int record_value = read_record(c);

	Serial.print(F("Ascii Key Pressed: ")); Serial.print(c,DEC); Serial.print(F(" = ")); Serial.write(c);  		// Add print of the ascii letter to verify
	Serial.print(F(" * Attached function: ")); Serial.println(record_value);

	if (c == 96) {
		//  Windows key pressed. Access mapping
		mapping_keys ();
	}else{
		// Execute function attached to S
		Send_DMX_Function (record_value);
	}
    /*
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {
      // otherwise, just print all normal characters
      Serial.print(c);
    }*/
  }
}

void mapping_keys () {
	// When mapping keys what we do is link an ascii key (wich mach the memory position) to a DMX function predefined
	// Procedure:

	// First type a key
	Serial.print(F("Type a key to remap_ "));
	while (!keyboard.available()) {
	}
	char key_index = keyboard.read();
	Serial.print(F(" Key pressed: "));
	Serial.write(key_index);
	Serial.println(F(" "));

	unsigned int record_value = read_record(key_index);
	if (record_value == 65535) {
		Serial.println(F("Mapping it's empty "));
	}else{
		Serial.print(F("Previous mapped function was: "));
		Serial.println (record_value);
	}
	// Assign a function
	Serial.print(F("Type new function number to map and press enter: "));
	unsigned int new_function = get_number_serial ();
	Serial.println(new_function);
	// Record new function into EEPROM memory
	write_record (key_index, new_function);
	Serial.print(F("Recorded! "));


}

//////////////////////// MA FUNCTIONS
void Send_DMX_Function (unsigned int function) {
	Debug (function);
	// Code to send DMX (function)
}



void Debug (unsigned int bufferContainer) {
	Serial.print ("Debug: ");
	Serial.println (bufferContainer);
}

void print_list_of_functions () {
// Available functions

	Serial.println (F("RESERVED - 1"));
	Serial.println (F("EXEC  - 2"));
	Serial.println (F("EXEC_FADER - 3"));
	Serial.println (F("PAGE_CHANNEL_UP - 4"));
	Serial.println (F("PAGE_CHANNEL_DOWN - 5"));
	Serial.println (F("PAGE_FADER_UP - 6"));
	Serial.println (F("PAGE_FADER_DOWN - 7"));
	Serial.println (F("PAGE_BUTTON_UP - 8"));
	Serial.println (F("PAGE_BUTTON_DOWN - 9"));
	Serial.println (F("DEF_PAUSE - 10"));
	Serial.println (F("DEF_GO_MINUS - 11"));
	Serial.println (F("DEF_GO_PLUS - 12"));
	Serial.println (F("X1 - 13"));
	Serial.println (F("X2 - 14"));
	Serial.println (F("X3 - 15"));
	Serial.println (F("X4 - 16"));
	Serial.println (F("X5 - 17"));
	Serial.println (F("X6 - 18"));
	Serial.println (F("X7 - 19"));
	Serial.println (F("X8 - 20"));
	Serial.println (F("X9 - 21"));
	Serial.println (F("X10 - 22"));
	Serial.println (F("X11 - 23"));
	Serial.println (F("X12 - 24"));
	Serial.println (F("X13 - 25"));
	Serial.println (F("X14 - 26"));
	Serial.println (F("X15 - 27"));
	Serial.println (F("X16 - 28"));
	Serial.println (F("X17 - 29"));
	Serial.println (F("X18 - 30"));
	Serial.println (F("X19 - 31"));
	Serial.println (F("X20 - 32"));
	Serial.println (F("PRINT  - 33"));
	Serial.println (F("USER1 - 34"));
	Serial.println (F("USER2 - 35"));
	Serial.println (F("BACKGROUND - 36"));
	Serial.println (F("U1  - 37"));
	Serial.println (F("U2  - 38"));
	Serial.println (F("U3  - 39"));
	Serial.println (F("U4 - 40"));
	Serial.println (F("ENCODER - 41"));
	Serial.println (F("FIX - 42"));
	Serial.println (F("SELECT - 43"));
	Serial.println (F("OFF  - 44"));
	Serial.println (F("TEMP - 45"));
	Serial.println (F("TOP - 46"));
	Serial.println (F("ON  - 47"));
	Serial.println (F("GOM_FAST - 48"));
	Serial.println (F("LEARN - 49"));
	Serial.println (F("GOP_FAST - 50"));
	Serial.println (F("GO_MINUS - 51"));
	Serial.println (F("PAUSE  - 52"));
	Serial.println (F("GO_PLUS  - 53"));
	Serial.println (F("OOPS - 54"));
	Serial.println (F("ESC  - 55"));
	Serial.println (F("EDIT - 56"));
	Serial.println (F("GOTO - 57"));
	Serial.println (F("UPDATE  - 58"));
	Serial.println (F("TIME - 59"));
	Serial.println (F("STORE  - 60"));
	Serial.println (F("BLIND  - 61"));
	Serial.println (F("FREEZE  - 62"));
	Serial.println (F("PREVIEW  - 63"));
	Serial.println (F("ASSIGN  - 64"));
	Serial.println (F("ALIGN  - 65"));
	Serial.println (F("BLACKOUT  - 66"));
	Serial.println (F("VIEW  - 67"));
	Serial.println (F("EFFECT  - 68"));
	Serial.println (F("MA  - 69"));
	Serial.println (F("DELETE  - 70"));
	Serial.println (F("PAGE  - 71"));
	Serial.println (F("MACRO  - 72"));
	Serial.println (F("PRESET  - 73"));
	Serial.println (F("COPY  - 74"));
	Serial.println (F("SEQU  - 75"));
	Serial.println (F("CUE  - 76"));
	Serial.println (F("EXECUTOR  - 77"));
	Serial.println (F("EXECUTOR0 - 78"));
	Serial.println (F("EXECUTOR1 - 79"));
	Serial.println (F("EXECUTOR2 - 80"));
	Serial.println (F("EXECUTOR3 - 81"));
	Serial.println (F("FADER  - 82"));
	Serial.println (F("CHANNEL  - 83"));
	Serial.println (F("FIXTURE - 84"));
	Serial.println (F("GROUP  - 85"));
	Serial.println (F("MOVE  - 86"));
	Serial.println (F("number_0 - 87"));
	Serial.println (F("number_1 - 88"));
	Serial.println (F("number_2 - 89"));
	Serial.println (F("number_3 - 90"));
	Serial.println (F("number_4 - 91"));
	Serial.println (F("number_5 - 92"));
	Serial.println (F("number_6 - 93"));
	Serial.println (F("number_7 - 94"));
	Serial.println (F("number_8 - 95"));
	Serial.println (F("number_9 - 96"));
	Serial.println (F("PLUS  - 97"));
	Serial.println (F("MINUS  - 98"));
	Serial.println (F("PUNKT  - 99"));
	Serial.println (F("FULL  - 100"));
	Serial.println (F("HIGH  - 101"));
	Serial.println (F("SOLO  - 102"));
	Serial.println (F("THRU  - 103"));
	Serial.println (F("IF  - 104"));
	Serial.println (F("AT  - 105"));
	Serial.println (F("CLEAR  - 106"));
	Serial.println (F("ENTER  - 107"));
	Serial.println (F("UP  - 108"));
	Serial.println (F("SET  - 109"));
	Serial.println (F("PREV  - 110"));
	Serial.println (F("NEXT  - 111"));
	Serial.println (F("DOWN  - 112"));
	Serial.println (F("MOUSE  - 113"));
	Serial.println (F("LBTN  - 114"));
	Serial.println (F("MBTN  - 115"));
	Serial.println (F("RBTN  - 116"));
	Serial.println (F("HELP  - 117"));
	Serial.println (F("BACKUP  - 118"));
	Serial.println (F("SETUP  - 119"));
	Serial.println (F("TOOLS  - 120"));
	Serial.println (F("V1 - 121"));
	Serial.println (F("V2 - 122"));
	Serial.println (F("V3 - 123"));
	Serial.println (F("V4 - 124"));
	Serial.println (F("V5 - 125"));
	Serial.println (F("V6 - 126"));
	Serial.println (F("V7 - 127"));
	Serial.println (F("V8 - 128"));
	Serial.println (F("V9 - 129"));
	Serial.println (F("V10 - 130"));
}



////// Copy
// Mapping of the function on the grand MA
// This numbers will be sent in form of DMX channel wich at the same time are being mapped in the DMX input of the grandMA

//#define **** 		1  ## reserved
#define EXEC 		2
#define EXEC_FADER		3
#define PAGE_CHANNEL_UP		4
#define PAGE_CHANNEL_DOWN		5
#define PAGE_FADER_UP		6
#define PAGE_FADER_DOWN		7
#define PAGE_BUTTON_UP		8
#define PAGE_BUTTON_DOWN		9
#define DEF_PAUSE		10
#define DEF_GO_MINUS		11
#define DEF_GO_PLUS		12
#define X1		13
#define X2		14
#define X3		15
#define X4		16
#define X5		17
#define X6		18
#define X7		19
#define X8		20
#define X9		21
#define X10		22
#define X11		23
#define X12		24
#define X13		25
#define X14		26
#define X15		27
#define X16		28
#define X17		29
#define X18		30
#define X19		31
#define X20		32
#define PRINT 		33
#define USER1		34
#define USER2		35
#define BACKGROUND		36
#define U1 		37
#define U2 		38
#define U3 		39
#define U4		40
#define ENCODER		41
#define FIX		42
#define SELECT		43
#define OFF 		44
#define TEMP		45
#define TOP		46
#define ON 		47
#define GOM_FAST		48
#define LEARN		49
#define GOP_FAST		50
#define GO_MINUS		51
#define PAUSE 		52
#define GO_PLUS 		53
#define OOPS		54
#define ESC 		55
#define EDIT		56
#define GOTO		57
#define UPDATE 		58
#define TIME		59
#define STORE 		60
#define BLIND 		61
#define FREEZE 		62
#define PREVIEW 		63
#define ASSIGN 		64
#define ALIGN 		65
#define BLACKOUT 		66
#define VIEW 		67
#define EFFECT 		68
#define MA 		69
#define DELETE 		70
#define PAGE 		71
#define MACRO 		72
#define PRESET 		73
#define COPY 		74
#define SEQU 		75
#define CUE 		76
#define EXECUTOR 		77
#define EXECUTOR0		78
#define EXECUTOR1		79
#define EXECUTOR2		80
#define EXECUTOR3		81
#define FADER 		82
#define CHANNEL 		83
#define FIXTURE		84
#define GROUP 		85
#define MOVE 		86
#define number_0		87
#define number_1		88
#define number_2		89
#define number_3		90
#define number_4		91
#define number_5		92
#define number_6		93
#define number_7		94
#define number_8		95
#define number_9		96
#define PLUS 		97
#define MINUS 		98
#define PUNKT 		99
#define FULL 		100
#define HIGH 		101
#define SOLO 		102
#define THRU 		103
#define IF 		104
#define AT 		105
#define CLEAR 		106
#define ENTER 		107
#define UP 		108
#define SET 		109
#define PREV 		110
#define NEXT 		111
#define DOWN 		112
#define MOUSE 		113
#define LBTN 		114
#define MBTN 		115
#define RBTN 		116
#define HELP 		117
#define BACKUP 		118
#define SETUP 		119
#define TOOLS 		120
#define V1		121
#define V2		122
#define V3		123
#define V4		124
#define V5		125
#define V6		126
#define V7		127
#define V8		128
#define V9		129
#define V10		130



unsigned int get_number_serial () {
	Serial.flush ();
	const int buf = 6;
	char serial_data[buf];
	recevie_data (serial_data,buf);
	char * thisChar = serial_data;
	// Serial.println (atoi(thisChar));
	return atoi(thisChar);
}

boolean recevie_data (char* parameter_container,int buffer) {
	// first clean data
	int len = buffer;
	for (int c = 0; c < len; c++) {
		parameter_container[c] = 0;
	}

	while (true) {
		while (Serial.available()) {
			char c = (char) Serial.read();
			//Serial.print (Serial.read()); // JUST for debug
			if ((c == 13) || (c == 10)) { 	// begining or end of command
				//end
				if (strlen(parameter_container) > 0) {	// We have to receive something first
					parameter_container[strlen(parameter_container)] = '\0';
					return true;
				}
			}else{
					if (strlen(parameter_container) == buffer ) {
					// Serial.println (" Reached the data max lengh, we reset the tag" );
					// Error!! buffer overload
					return false;
				}else{
					// DATA comes here
					// Serial.print (c);
					parameter_container[strlen(parameter_container)]=c;
					// DEBUG IP
				}
			}
		}
	}
}