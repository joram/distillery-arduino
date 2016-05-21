
int value_i = 0;

// a buffered history of values
const int max_poles = 20;
static const uint8_t pins[] = {A0, A1, A2, A3, A4, A5};
int values[sizeof(pins)][max_poles];
  
int average(int* array, int length){
  int avg = 0;
  for(int j=0; j<length; j++){
    avg += array[j];
  }
  return int(avg/length);
}

int safeAnalogRead(int pin)
{
  analogRead(pin);        // make an initial reading to set up the ADC
  delay(1);               // let the ADC stabilize
  return analogRead(pin); // toss the first reading and take one we will keep
}

void read_values(){
  if(value_i >= max_poles){
    value_i = 0;
  }
  for(int x=0; x<sizeof(pins); x++){
    values[x][value_i] = safeAnalogRead(pins[x]);
  }
  value_i++;
}

String json_array(int* array, int length){
  String s = "[";
  if(length>0){
    s += array[0];
    for(int x=1; x<length; x++){
      s += "," + String(array[x]);
    }
  }
  s += "]";
  return s;
}

void print_averages(){
  String s = "{";
  for(int j=0; j<sizeof(pins); j++){
    int avg = average(values[j], max_poles);
    s += "\"A"+String(j)+"\": "+String(avg);
    if (j != sizeof(pins)-1){
      s += ",";
    }
  }
  s += "}";
  Serial.println(s);
}

void print_values(){
  String s = "{";
  for(int j=0; j<sizeof(pins); j++){
    s += "\"A"+String(j)+"\": "+json_array(values[j], max_poles);
    if (j != sizeof(pins)-1){
      s += ",";
    }
  }
  s += "}";
  Serial.println(s);
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  read_values();

  if (Serial.available() > 0) {

    String s = Serial.readString();
    if(s == "ping"){
      Serial.println("pong");
    } 
    else if(s == "values"){
      print_values();
    } 
    else if(s == "averages"){
      print_averages();
    } 
    else {
      Serial.println("unknown command: '"+s+"', valid commands are: [values, averages]");
    }
  }
}


