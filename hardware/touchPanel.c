void writePair(char* xValue, char * yValue);

// Touch Panel module connections
sbit DriveX_Left at GPIOB_ODR.B1;
sbit DriveX_Right at GPIOB_ODR.B8;
sbit DriveY_Up at GPIOB_ODR.B9;
sbit DriveY_Down at GPIOB_ODR.B0;

void main() {
  char textValueX[20];
  char textValueY[20];
  unsigned long valueX;
  unsigned long valueY;

  //Set PORTD and PORTC as output
  GPIO_Digital_Output(&GPIOD_ODR, _GPIO_PINMASK_LOW);
  GPIO_Digital_Output(&GPIOC_ODR, _GPIO_PINMASK_LOW);
  GPIOD_ODR = 0;
  //Setup four buttons for input
  GPIO_Digital_Input(&GPIOD_IDR, _GPIO_PINMASK_0);

  // Choose ADC channel
  ADC1_Init();
  TP_TFT_Init(320, 240, 8, 9);
  ADC_Set_Input_Channel(_ADC_CHANNEL_8 | _ADC_CHANNEL_9 );
  
  // Initialize UART module at 56000 bps
  UART1_Init(56000);
  UART1_Write_Text("Start\r\n");
  Delay_ms(100);
  
  while (1) {
      //Read values for UART
      valueX = ADC1_Get_Sample(8);
      valueY = ADC1_Get_Sample(9);

      IntToStr(valueX, textValueX);
      IntToStr(valueY, textValueY);

      writePair(textValueX, textValueY);
      Delay_ms(500);
  }
}

void writePair(char* xValue, char * yValue) {
    char bufferOrderPair[] = "(";
    strcat(bufferOrderPair, xValue);
    strcat(bufferOrderPair, ",");
    strcat(bufferOrderPair, yValue);
    strcat(bufferOrderPair, " )\r\n");
    UART1_Write_Text(bufferOrderPair);
}
