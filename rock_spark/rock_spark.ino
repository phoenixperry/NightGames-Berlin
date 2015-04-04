int led = D0;
int trigger_led = D3;
int z_axis = 0;
int z_axis_previous =0;
void lightup(){
int r_change =0;
int g_change = 0;
int b_change =0;

}

void setup(){

  Spark.variable("z_axis", &z_axis, INT);
  pinMode(A3, INPUT);
  pinMode(A5, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(trigger_led, OUTPUT);
}

void loop(){
  digitalWrite(led, HIGH);
  z_axis_previous = z_axis;
  z_axis = analogRead(A3);

  if(z_axis > z_axis_previous+10 || z_axis< z_axis_previous -10){
      digitalWrite(trigger_led, HIGH);
      delay(200);
      digitalWrite(trigger_led, LOW);
  }else{
    digitalWrite(trigger_led, LOW);
  }
}
