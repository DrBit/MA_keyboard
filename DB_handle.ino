#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include <EEPROM.h>
#include <DB.h>
#include <string.h>

DB db;

// Starting position of the table. Each value in structure must be count
// byte counts as 1, int as 2 etc....
#define KEYS_TBL_START 0
#define number_of_keys_to_store 1000


struct MA_KEY {
// Containig
  byte Key_function;
} DB_keys;

// When changing the structure data in the eeprom needs to be rewritten


void init_DBs () {
	db.create(KEYS_TBL_START,sizeof(DB_keys),number_of_keys_to_store);
	Serial.println ("Init DB");
}

void Show_all_records() {
	db.open(KEYS_TBL_START);
	Serial.print(F("Number of records in DB: "));Serial.println(db.nRecs(),DEC);
	if (db.nRecs()) Serial.println(F("\nDATA RECORDED IN INTERNAL MEMORY:"));
	int itemsXrow = 0;
	for (int i = 1; i <= db.nRecs(); i++) {
		db.read(i, DB_REC DB_keys);
		Serial.print(F(" | Key: ")); Serial.print(i); 
		Serial.print(F(" * MA func: ")); Serial.print(DB_keys.Key_function);
		itemsXrow ++;
		if (itemsXrow == 5) {
			itemsXrow = 0;
			Serial.println ("");
		}
	} 
	Serial.println(F("-----"));
}


unsigned int read_record (unsigned long recordNum) {
	db.open(KEYS_TBL_START);
	db.read(recordNum, DB_REC DB_keys);
	return DB_keys.Key_function;
}

void write_record (unsigned long recordNum, unsigned int value) {
	db.open(KEYS_TBL_START);
	DB_keys.Key_function = value;
	db.write(recordNum, DB_REC DB_keys);
}