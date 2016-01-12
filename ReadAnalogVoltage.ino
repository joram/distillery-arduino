int i = 0;
int d = 5;
const int max_poles = 5;
const int num_sensors = 6;
int values[num_sensors][max_poles];

int average(int* array, int length){
  int avg = 0;
  for(int j=0; j<length; j++){
    avg += array[j];
  }
  return int(avg/sizeof(array));
}


void read_values(){
  values[0][i] = analogRead(A0);
  values[1][i] = analogRead(A1);
  values[2][i] = analogRead(A2);
  values[3][i] = analogRead(A3);
  values[4][i] = analogRead(A4);
  values[5][i] = analogRead(A5);
  i++;
  delay(d);
}

String json_array(int* array, int length){
  String s = "[";
  if(length>0){
    s += String(array[0]);
    for(int x=1; x<length; x++){
      s += "," + String(array[x]);
    }
  }
  s += "]";
  return s;
}

void print_averages(){
  String s = "{";
  for(int j=0; j<num_sensors; j++){
    s += "'A"+String(j)+"': "+String(average(values[j], max_poles))+",";
  }
  s += "}";
  Serial.println(s);
}

void print_values(){
  String s = "{";
  for(int j=0; j<num_sensors; j++){
    s += "\"A"+String(j)+"\": "+json_array(values[j], max_poles);
    if (j != num_sensors-1){
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
  if(i >= max_poles){
    print_values();
    i = 0;
  }
  read_values();


  if (Serial.available() > 0) {

    String s = Serial.readString();
//    if(s == "ping"){
//      Serial.println("pong");
//    } else if(s == "values"){
//      print_values();
//    } else if(s == "averages"){
//      print_averages();
//    } else {
//      Serial.println("unknown command: '"+s+"', valid commands are: [values, averages]");
//    }
  }
}

