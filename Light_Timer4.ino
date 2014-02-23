#include <Servo.h>

//pinNo
#define SERVOPIN	9
#define LED 		13
#define BUTTON      8

//servo angle
#define ON      	130
#define DEFO    	100
#define OFF     	70

//millisec
#define HOUR    	3600000
#define MINUTE  	60000
#define SEC     	1000


Servo g_servo;



void setup() { 
	Serial.begin(9600);
	pinMode(LED, OUTPUT);
	g_servo.attach(SERVOPIN);
	Serial.print("setup OK!\n");
} 


void loop() { 
	//set val
	static unsigned long time = 0;
    static unsigned long myTime = 0;
	static int i = 1;
	static int loopCount = 1;

	//指定時間をミリ秒でセット
	if (loopCount == 1){
		alert1(); //myTime入力開始アラート
		myTime = HOUR * setTime();

		Serial.print("myTime of ");
		Serial.print(myTime);
		Serial.print("\n");

	}

	//Arduinoが起動してから現在までの時間(ms)
	time = millis();
	
	Serial.print(time);
	Serial.print("\n");

	if (time > myTime && i==1){
		on();
		i++;
	}

	
	loopCount++;
	delay(1000);
} 




int setTime(){
	//set val
	int buttonCount = 0;
	long loopCount = 0;
	int lastButtonStatus = LOW;
	int bottonStatus = LOW;

	//15sec loop
	while(1){
		int bottonStatus = digitalRead(BUTTON);  
		delay(50);


		if(lastButtonStatus == LOW && bottonStatus == HIGH){
		    buttonCount++;

		    digitalWrite(LED, HIGH); 
			delay(30);
			digitalWrite(LED, LOW);

			Serial.print("\nbuttonCount ");
	        Serial.print(buttonCount);
	        Serial.print("\n");
		}



		if(loopCount >= 300){	//15秒たったら
		    disp_count(buttonCount);
		    loopCount = 0;
	        Serial.print("Now 15 Sec\n");
	        break;
		}

		lastButtonStatus = bottonStatus;
		loopCount++;
	}
	

	return buttonCount;




}


void disp_count(int buttonCount){
    Serial.print("disp_count\n");
	led_flash(buttonCount);
}

//number回LEDを点滅
void led_flash(int number){
    Serial.print("number\n");
    Serial.print(number);
    Serial.print("\n");

    alert2(); //myTime表示開始アラート

	for(int i=1; i<=number; i++){
	    digitalWrite(LED, HIGH); 
		delay(500);
		digitalWrite(LED, LOW);
		delay(500);
		Serial.print(i);
		Serial.print("\n");
	}

	alert2(); //myTime表示終了アラート
}


//servo　motion
void on(){
	Serial.print("on!\n");

	int i;
	for (i=DEFO; i<=ON; i++){
		g_servo.write(i);
	} 
	delay(1000);
	g_servo.write(DEFO);
	Serial.print("on! end\n");
}

void off(){
	int i;
	for (i=DEFO; i>=OFF; i--){
		g_servo.write(i);
	} 
	delay(1000);
	g_servo.write(DEFO);
}

void defo(){
	g_servo.write(DEFO);
}



//LED alert
void alert1(){
	Serial.print("alert1\n");
	delay(1000);
	for(int i=1; i<=5; i++){
	    digitalWrite(LED, HIGH); 
	    delay(100);
	    digitalWrite(LED, LOW);
	    delay(100);
	}
  delay(1000);
}

void alert2(){
	Serial.print("alert2\n");
	delay(1000);
	for(int i=1; i<=5; i++){
	    digitalWrite(LED, HIGH); 
	    delay(50);
	    digitalWrite(LED, LOW);
	    delay(50);
	}
	delay(1000);
}