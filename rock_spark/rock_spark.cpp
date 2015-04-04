
int z_axis = 0;

void setup(){

  Spark.variable("z_axis", &z_axis, INT);
  pinMode(A0, INPUT);
}

void loop(){

  z = analogRead(A0);
}
