//KEY-VALUE-STRUCT TO ASSIGN THE RIGHT CHARS, PIXELS AND ROWS TO THE RFID TAGS
struct KeyValue{
  KeyValue(String k, String v, int id, int l, Adafruit_NeoPixel *r){
    key = k;
    value = v;
    id_stripe = id;
    length = l;
    row = r;
  }
  String key;
  String value;
  int id_stripe;
  int length;
  Adafruit_NeoPixel *row;
};

KeyValue* rfidTags[30] = {
  //EMPTY IS FOR READER READING NOTHING
  new KeyValue("", "EMPTY", -2, -2, nullptr),
  new KeyValue("70 199 167 131","A", 28, 2, &board::stripBoard_R0),
  new KeyValue("107 48 140 195", "B", 25, 2, &board::stripBoard_R0),
  new KeyValue("151 179 167 131", "C", 23, 2, &board::stripBoard_R0),
  new KeyValue("29 208 214 115", "D", 21, 2, &board::stripBoard_R0),
  new KeyValue("68 197 208 131", "E", 19, 2, &board::stripBoard_R0),
  new KeyValue("89 154 209 131", "F", 17, 2, &board::stripBoard_R0),
  new KeyValue("139 110 212 131", "G", 15, 2, &board::stripBoard_R0),
  new KeyValue("208 97 210 131", "H", 13, 2, &board::stripBoard_R0),
  new KeyValue("34 102 208 131", "I", 11, 2, &board::stripBoard_R0),
  new KeyValue("68 67 131 195", "J", 9, 2, &board::stripBoard_R0),
  new KeyValue("84 140 164 131", "K", 7, 2, &board::stripBoard_R0),
  new KeyValue("135 213 163 131", "L", 5, 2, &board::stripBoard_R0),
  new KeyValue("183 43 242 195", "M", 2, 3, &board::stripBoard_R0),
  new KeyValue("65 202 164 131", "N", 0, 2, &board::stripBoard_R0),
  new KeyValue("198 221 167 131", "O", 25, 2, &board::stripBoard_R1),
  new KeyValue("167 242 209 131", "P", 23, 1, &board::stripBoard_R1),
  new KeyValue("227 154 131 195", "Q", 21, 1, &board::stripBoard_R1),
  new KeyValue("110 185 129 195", "R", 18, 2, &board::stripBoard_R1),
  new KeyValue("205 117 131 195", "S", 16, 2, &board::stripBoard_R1),
  new KeyValue("77 245 130 195", "T", 14, 2, &board::stripBoard_R1),
  new KeyValue("189 181 209 131", "U", 12, 2, &board::stripBoard_R1),
  new KeyValue("61 59 209 131", "V", 10, 2, &board::stripBoard_R1),
  new KeyValue("156 184 209 131", "W", 7, 3, &board::stripBoard_R1),
  new KeyValue("171 253 130 195", "X", 5, 1, &board::stripBoard_R1),
  new KeyValue("212 74 209 131", "Y", 2, 2, &board::stripBoard_R1),
  new KeyValue("010 161 227 115", "Z", 0, 2, &board::stripBoard_R1),
  new KeyValue("09 159 201 115", "1", 0, 8, &board::stripBoard_R4),//YES
  new KeyValue("41 014 165 131", "2", 0, 26, &board::stripBoard_R3),//STERN
  new KeyValue("102 212 201 115", "4", 0, 21, &board::stripBoard_R2)//GOOD
  //new KeyValue("185 246 138 195", "3", 0, 21, &board::stripBoard_R2)//BYE
};

//Methods for accessing the different params of the map

//RETURNS NAME
String GetValue(String key){
  for(auto i = 0; i< 30; i++){
    if(rfidTags[i]->key.equals(key)){
      return rfidTags[i]->value;
    }
  }
return "";
}

String GetKey(byte v){
  for(auto i = 0; i< 30; i++){
    if(rfidTags[i]->value[0] == v){
      return rfidTags[i]->key;
    }
  }
return "";
}

//RETURNS ID of first pixel of character
int GetID(String key){
  for(auto i = 0; i< 30; i++){
    if(rfidTags[i]->key.equals(key)){
      return rfidTags[i]->id_stripe;
    }
  }
return -1;
}

//RETURNS length of pixels that are mapped to one character
int GetLength(String key){
  for(auto i = 0; i< 30; i++){
    if(rfidTags[i]->key.equals(key)){
      return rfidTags[i]->length;
    }
  }
return -1;
}

//RETURNS number of led row in which key is located
Adafruit_NeoPixel *GetRow(String key){
  for(auto i = 0; i< 30; i++){
    if(rfidTags[i]->key.equals(key)){
      return rfidTags[i]->row;
    }
  }
return nullptr;
}
