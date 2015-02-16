int val = 0;
int isPressed(String val);
void setup() {
    Spark.variable("val", &val, INT);
    Spark.function("isPressed", isPressed);
}

void loop() {
    val = analogRead(A0);
    //val = 1;
}
int isPressed(String val)
{
    if(val > 0)
    {
       return 1;
    }
    else return 0;

}
