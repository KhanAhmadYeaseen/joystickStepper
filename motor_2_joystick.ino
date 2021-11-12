

#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12


#define STEPPER1_PIN_1 2
#define STEPPER1_PIN_2 3
#define STEPPER1_PIN_3 4
#define STEPPER1_PIN_4 5

// Arduino pin numbers
#define X_pin 0// analog pin connected to X output
#define Y_pin 1 // analog pin connected to Y output

int step_number = 0;
int step_number1 = 0;
int delay_time = 2;
int x_val = 511 ;
int y_val = 511 ;


void OneStep(bool dir)
{
    if (dir)
    {
        switch (step_number)
        {
        case 0:
            digitalWrite(STEPPER_PIN_1, HIGH);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 1:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, HIGH);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, HIGH);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, HIGH);
            break;
        }
    }
    else
    {
        switch (step_number)
        {
        case 0:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, HIGH);
            break;
        case 1:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, HIGH);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, HIGH);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(STEPPER_PIN_1, HIGH);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
        }
    }
    step_number++;
    if (step_number > 3)
    {
        step_number = 0;
    }
}




void OneStep1(bool dir)
{
    if (dir)
    {
        switch (step_number1)
        {
        case 0:
            digitalWrite(STEPPER1_PIN_1, HIGH);
            digitalWrite(STEPPER1_PIN_2, LOW);
            digitalWrite(STEPPER1_PIN_3, LOW);
            digitalWrite(STEPPER1_PIN_4, LOW);
            break;
        case 1:
            digitalWrite(STEPPER1_PIN_1, LOW);
            digitalWrite(STEPPER1_PIN_2, HIGH);
            digitalWrite(STEPPER1_PIN_3, LOW);
            digitalWrite(STEPPER1_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(STEPPER1_PIN_1, LOW);
            digitalWrite(STEPPER1_PIN_2, LOW);
            digitalWrite(STEPPER1_PIN_3, HIGH);
            digitalWrite(STEPPER1_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(STEPPER1_PIN_1, LOW);
            digitalWrite(STEPPER1_PIN_2, LOW);
            digitalWrite(STEPPER1_PIN_3, LOW);
            digitalWrite(STEPPER1_PIN_4, HIGH);
            break;
        }
    }
    else
    {
        switch (step_number1)
        {
        case 0:
            digitalWrite(STEPPER1_PIN_1, LOW);
            digitalWrite(STEPPER1_PIN_2, LOW);
            digitalWrite(STEPPER1_PIN_3, LOW);
            digitalWrite(STEPPER1_PIN_4, HIGH);
            break;
        case 1:
            digitalWrite(STEPPER1_PIN_1, LOW);
            digitalWrite(STEPPER1_PIN_2, LOW);
            digitalWrite(STEPPER1_PIN_3, HIGH);
            digitalWrite(STEPPER1_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(STEPPER1_PIN_1, LOW);
            digitalWrite(STEPPER1_PIN_2, HIGH);
            digitalWrite(STEPPER1_PIN_3, LOW);
            digitalWrite(STEPPER1_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(STEPPER1_PIN_1, HIGH);
            digitalWrite(STEPPER1_PIN_2, LOW);
            digitalWrite(STEPPER1_PIN_3, LOW);
            digitalWrite(STEPPER1_PIN_4, LOW);
        }
    }


    step_number1++;
    if (step_number1 > 3)
    {
        step_number1 = 0;
    }
}




void rotate_step(int num, bool dir)
{
    for (int i = 0 ; i < num ; )
    {
        OneStep(dir) ;
        delay(2)  ;
        i++ ;
    }
}


void rotate_step1(int num, bool dir)
{
    for (int i = 0 ; i < num ; )
    {
        OneStep1(dir) ;
        delay(2);
        i++ ;
    }
}


void rotate_both(int num, bool dir, bool dir1)
{
    for( int i =0 ; i < num ; i++ )
    {
        OneStep(dir) ;
        OneStep1(dir1) ;
        delay(2) ;
    }
}


void setup()
{
    pinMode(STEPPER_PIN_1, OUTPUT);
    pinMode(STEPPER_PIN_2, OUTPUT);
    pinMode(STEPPER_PIN_3, OUTPUT);
    pinMode(STEPPER_PIN_4, OUTPUT);

    pinMode(STEPPER1_PIN_1, OUTPUT);
    pinMode(STEPPER1_PIN_2, OUTPUT);
    pinMode(STEPPER1_PIN_3, OUTPUT);
    pinMode(STEPPER1_PIN_4, OUTPUT);

    Serial.begin(9600);

}

bool is_low(int a)
{
    if(a >=0 && a <= 255)
        return true ;
    else
        return false;
}


bool is_high(int a)
{
    if(a >=766 && a <= 1034)
        return true ;
    else
        return false;
}

bool is_stable(int a)
{
    if(a > 255 && a < 766)
        return true;
    else
        return false ;
}


void loop()
{
    // put your main code here, to run repeatedly:
    x_val = analogRead(X_pin) ;
    y_val = analogRead(Y_pin) ;



    int com ;

    if(is_low(x_val) && is_stable(y_val))
    {
        rotate_step(4, false) ;
    }
    else if(is_low(x_val) && is_low(y_val))
    {
        rotate_both(4, false, false) ;
    }
    else if(is_stable(x_val) && is_low(y_val))
    {
        rotate_step1(4 , false) ;
    }
    else if(is_low(y_val) && is_high(x_val))
    {
        rotate_both(4, true, false) ;
    }
    else if(is_stable(y_val) && is_high(x_val))
    {
        rotate_step(4, true) ;
    }
    else if(is_high(x_val) && is_high(y_val))
    {
        rotate_both(4, true, true) ;
    }
    else if(is_stable(x_val) && is_high(y_val))
    {
        rotate_step1(4, true) ;
    }
    else if(is_high(y_val) && is_low(x_val))
    {
        rotate_both(4, false, true) ;
    }

//  if(x_val >= 0 && x_val <= 255){
//    rotate_step(4 , false) ;
//  }
//
//  if(x_val >= 766 && x_val <= 1034) {
//    rotate_step(4 , true) ;
//  }
//
//  if(y_val >= 0 && y_val <= 255){
//    rotate_step1(4 , false) ;
//  }
//
//  if(y_val >= 766 && y_val <= 1034) {
//    rotate_step1(4 , true) ;
//  }

}
