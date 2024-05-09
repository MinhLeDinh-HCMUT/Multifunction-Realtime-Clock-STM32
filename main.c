/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "lcd_16x2.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
void MX_RTC_Init_New(int8_t hour,int8_t min,int8_t sec);
void giaima1(int8_t num1,int8_t num2);
void giaima2(int8_t num3,int8_t num4,int8_t num5,int8_t num6);
void end_timermode(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int8_t status=0, edit_state=0, status_tmr=0, pause_press=0, p_p_s=0, alarm_count=1, alarm_used=0, temp=0; 
int8_t c_h=0, c_m=0, c_s=0, t_h=0, t_m=0, t_s=0, p_h=0, p_m=0, p_s=0, trigger=0;
uint32_t alarm_time[50];
uint8_t ma7doan[11]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF};
void giaima1(int8_t num1,int8_t num2)
	{
		int8_t mahex1=ma7doan[num1];
		int8_t mahex2=ma7doan[num2];
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,0);
		for(int8_t iteration1=0;iteration1<=7;iteration1++)
		{
			mahex1=mahex1<<1;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,0);
			if((mahex1&0x80) == 0x80)	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,1);
			else if((mahex1&0x80) == 0) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,0);			
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,1);
		}
		
		for(int8_t iteration2=0;iteration2<=7;iteration2++)
		{
			mahex2=mahex2<<1;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,0);
			if((mahex2&0x80) == 0x80)	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,1);
			else if((mahex2&0x80) == 0) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,0);			
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,1);
		}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,1);
	}
void giaima2(int8_t num3,int8_t num4,int8_t num5,int8_t num6)
	{
		int8_t mahex3=ma7doan[num3];
		int8_t mahex4=ma7doan[num4];
		int8_t mahex5=ma7doan[num5];
		int8_t mahex6=ma7doan[num6];
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0);
		for(int8_t iteration3=0;iteration3<=7;iteration3++)
		{
			mahex3=mahex3<<1;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0);
			if((mahex3&0x80) == 0x80)	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1);
			else if((mahex3&0x80) == 0) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);			
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
		}
		
		for(int8_t iteration4=0;iteration4<=7;iteration4++)
		{
			mahex4=mahex4<<1;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0);
			if((mahex4&0x80) == 0x80)	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1);
			else if((mahex4&0x80) == 0) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);			
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
		}
		
			for(int8_t iteration5=0;iteration5<=7;iteration5++)
		{
			mahex5=mahex5<<1;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0);
			if((mahex5&0x80) == 0x80)	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1);
			else if((mahex5&0x80) == 0) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);			
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
		}
		
			for(int8_t iteration6=0;iteration6<=7;iteration6++)
		{
			mahex6=mahex6<<1;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0);
			if((mahex6&0x80) == 0x80)	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1);
			else if((mahex6&0x80) == 0) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);			
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
		}
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1);
	}
void end_timermode(void)
	{
		if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0) 
		{
			while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
			MX_RTC_Init_New(t_h,t_m,t_s);
			status=0;
			status_tmr=0;
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
			if (pause_press==1) pause_press=0;
			if (p_p_s==1)	p_p_s=0;
		}	
	}	
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	RTC_TimeTypeDef Ttime;
	RTC_DateTypeDef Tdate;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  char Lcd_data[100];
	Lcd_Init();
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if ((status==4) || (status==5)) //keep rtc while setting alarm
		{
			HAL_RTC_GetTime(&hrtc, &Ttime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &Tdate, RTC_FORMAT_BIN);
		}
		if (status==0) 
		{
			HAL_RTC_GetTime(&hrtc, &Ttime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &Tdate, RTC_FORMAT_BIN);
			giaima1(Ttime.Seconds%10,Ttime.Seconds/10);
			if ((status_tmr==0)||(Ttime.Hours>0)) giaima2(Ttime.Minutes%10,Ttime.Minutes/10,Ttime.Hours%10,Ttime.Hours/10);
			else if ((status_tmr==1)&&(Ttime.Hours<1)) giaima2(Ttime.Minutes%10,Ttime.Minutes/10,10,10);	//when hour=0 in timer mode disable hour leds
		}

//timer step 2 (stop timer after started & end timer)
		if (status_tmr==1)
		{
			if ((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) && pause_press==0) //pause button pressed 1st time
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
					status=3; //stop time in timer		
					p_h=Ttime.Hours;
					p_m=Ttime.Minutes;
					p_s=Ttime.Seconds;
					giaima1(Ttime.Seconds%10,Ttime.Seconds/10);
					if (Ttime.Hours<1) giaima2(Ttime.Minutes%10,Ttime.Minutes/10,10,10);
					else if (Ttime.Hours>0) giaima2(Ttime.Minutes%10,Ttime.Minutes/10,Ttime.Hours%10,Ttime.Hours/10);
					pause_press=1; 
					p_p_s=1;	// when pause and stop happen at same time, skip the stop button pressed 1st time 
			}
			if ((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) && pause_press==1) //pause button pressed 2nd time
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
					status=0; //stop time in timer status		
					MX_RTC_Init_New(p_h,p_m,p_s);
					pause_press=0;
			}
			if ((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0) && pause_press==0) //stop button pressed 1st time
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){}
					status=3; //stop time in timer status		
					giaima1(Ttime.Seconds%10,Ttime.Seconds/10);
					if (Ttime.Hours<1) giaima2(Ttime.Minutes%10,Ttime.Minutes/10,10,10);
					else if (Ttime.Hours>0) giaima2(Ttime.Minutes%10,Ttime.Minutes/10,Ttime.Hours%10,Ttime.Hours/10);
					status_tmr=2; 
			}
			end_timermode();
		}
		
//timer step 2 (reset timer for the next run & end timer)
		if ((status_tmr==2) || p_p_s==1)	//activated when stop button has been pressed 1 time or stop during pause
		{
			if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0)	//stop button pressed  2nd time
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){}	
				MX_RTC_Init_New(0,0,0);
				giaima1(0,0);
				giaima2(0,0,10,10);
				status=2;
				status_tmr=0;
				p_p_s=0;
			}
			end_timermode();
		}

//edit mode with rtc stopped
		if (status==1) 
		{			
			while (edit_state==0) //edit hour 
				{
					giaima1(c_s%10,c_s/10);
					giaima2(c_m%10,c_m/10,10,10);
					HAL_Delay(80);
					giaima2(c_m%10,c_m/10,c_h%10,c_h/10);
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
						c_h=c_h+1;
						if(c_h==24) c_h=0;
					}	
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
						c_h=c_h-1;
						if(c_h==-1) c_h=23;
					}
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){}
						edit_state = 1;	//initialize edit minute  
						giaima2(c_m%10,c_m/10,c_h%10,c_h/10);
					}
					HAL_Delay(80);
				}
			while (edit_state==1)	//edit minute
				{
					giaima1(c_s%10,c_s/10);
					giaima2(10,10,c_h%10,c_h/10);
					HAL_Delay(80);
					giaima2(c_m%10,c_m/10,c_h%10,c_h/10);
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
						c_m=c_m+1;
						if(c_m==60) c_m=0;
					}	
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
						c_m=c_m-1;
						if(c_m==-1) c_m=59;
					}
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){}
						edit_state = 2;	//initialize edit second 
						giaima2(c_m%10,c_m/10,c_h%10,c_h/10);
					}
					HAL_Delay(80);
				}				
			while (edit_state==2)	//edit second
				{
					giaima1(10,10);
					giaima2(c_m%10,c_m/10,c_h%10,c_h/10);
					HAL_Delay(80);
					giaima1(c_s%10,c_s/10);
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
						c_s=c_s+1;
						if(c_s==60) c_s=0;
					}	
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
						c_s=c_s-1;
						if(c_s==-1) c_s=59;
					}
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){}
						edit_state = 3;	//initialize finish edit  
						giaima1(c_s%10,c_s/10);
					}
					HAL_Delay(80);
				}				
			if(edit_state==3)	//finish edit
			{
				edit_state=0;
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,1);
				MX_RTC_Init_New(c_h,c_m,c_s);	//continue rtc with editted value
				status=0;
			}		
		}

//timer step 1 (waiting for start button pressed & end timer)		
		if (status==2) 
		{
			giaima1(0,0);
			giaima2(0,0,10,10);
			if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0) //start button 
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){}
				MX_RTC_Init_New(0,0,0);
				status=0;
				status_tmr=1; 
				}
			end_timermode();
		}		

//alarm step 1 (input number of alarm)
		if (status==4) 
		{
			if (alarm_count<10) giaima1(alarm_count,10);
			else giaima1(alarm_count%10,alarm_count/10);
			giaima2(10,10,10,10);
			if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0) 
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
				alarm_count=alarm_count+1;
				if(alarm_count==50) alarm_count=49;
			}	
			if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) 
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
				alarm_count=alarm_count-1;
				if(alarm_count==0) alarm_count=1;
			}
			if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0)
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0){}
				status=5;	//alarm
			}		
		}	

//alarm step 2 (select time for each alarm)
		if (status==5) 
		{			
			for(int8_t iteration7=0;iteration7<alarm_count;iteration7++)
			{
				if (alarm_count<10) giaima1(iteration7+1,10);
				else giaima1((iteration7+1)%10,(iteration7+1)/10);
				giaima2(10,10,10,10);
				HAL_Delay(850);	//display the alarm number 
				while (edit_state==0) //alarm hour 
				{
					giaima1(t_s%10,t_s/10);
					giaima2(t_m%10,t_m/10,10,10);
					HAL_Delay(80);
					giaima2(t_m%10,t_m/10,t_h%10,t_h/10);
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
						t_h=t_h+1;
						if(t_h==24) t_h=0;
					}	
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
						t_h=t_h-1;
						if(t_h==-1) t_h=23;
					}
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0){}
						edit_state = 1;	//initialize alarm minute  
						giaima2(t_m%10,t_m/10,t_h%10,t_h/10);
					}
					HAL_Delay(80);
				}
				while (edit_state==1)	//alarm minute
				{
					giaima1(t_s%10,t_s/10);
					giaima2(10,10,t_h%10,t_h/10);
					HAL_Delay(80);
					giaima2(t_m%10,t_m/10,t_h%10,t_h/10);
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
						t_m=t_m+1;
						if(t_m==60) t_m=0;
					}	
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
						t_m=t_m-1;
						if(t_m==-1) t_m=59;
					}
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0){}
						edit_state = 2;	//initialize alarm second 
						giaima2(t_m%10,t_m/10,t_h%10,t_h/10);
					}
					HAL_Delay(80);
				}				
				while (edit_state==2)	//alarm second
				{
					giaima1(10,10);
					giaima2(t_m%10,t_m/10,t_h%10,t_h/10);
					HAL_Delay(80);
					giaima1(t_s%10,t_s/10);
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
						t_s=t_s+1;
						if(t_s==60) t_s=0;
					}	
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){}
						t_s=t_s-1;
						if(t_s==-1) t_s=59;
					}
					if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0) 
					{
						while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0){}
						edit_state = 0;	//initialize finish alarm  
						alarm_time[iteration7]=t_h*3600+t_m*60+t_s;
						giaima1(t_s%10,t_s/10);
							for(int8_t iteration8=0;iteration8<4;iteration8++)
							{
								HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);	//alarm cofirmation
								HAL_Delay(90);
							}
						}
					HAL_Delay(80);
					}		
				}
//				MX_RTC_Init_New(c_h,c_m,c_s);  //unlock if no need to keep rtc when on alarm setting mode
				status=0;
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
				alarm_used=1;	//alarm has been used
				for (int8_t iteration9=0;iteration9<alarm_count;iteration9++) //rearrange alarm time array in increasing order
				{     
					for (int8_t iteration10=iteration9+1;iteration10<alarm_count;iteration10++) 
					{     
						if(alarm_time[iteration9] > alarm_time[iteration10]) 
						{    
							temp = alarm_time[iteration9];    
              alarm_time[iteration9] = alarm_time[iteration10];    
              alarm_time[iteration10] = temp;    
						}     
					}     
				}  									
		}	

//alarm step 3( alarm is used and detect if the current time is same as the alarm set)
		if (alarm_used==1)
		{
			if ((alarm_count==1)&&((Ttime.Hours*3600+Ttime.Minutes*60+Ttime.Seconds)>alarm_time[0])) trigger=1;	
			for (int8_t iteration11=0;iteration11<alarm_count;iteration11++) 
			{     
				if (((Ttime.Hours*3600+Ttime.Minutes*60+Ttime.Seconds) == alarm_time[iteration11]))
				{
					trigger=1;
				}
			}
			if (trigger==1) 
			{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);	//turn on alarm led
			}
			if ((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0) && (trigger==1))
			{
				while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0){}
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1); 
				trigger=0; //turn off alarm led		
				if(Ttime.Hours*3600+Ttime.Minutes*60+Ttime.Seconds>alarm_time[alarm_count-1])	//if the real time> than the largest alarm then reset alarm
				{
					alarm_used=0;
					alarm_count=1;
				}
			}					
		} 
	
//edit mode		
		if ((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0) && (status_tmr==0))
		{
			while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){}
			status=1;	//edit
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,0);
			c_h=Ttime.Hours;	 
			c_m=Ttime.Minutes;
			c_s=Ttime.Seconds;
		}	

//timer mode		
		if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0)
		{
			while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){}
			status=2;	//timer
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);
			t_h=Ttime.Hours;	//stored time before enter timer mode
			t_m=Ttime.Minutes;
			t_s=Ttime.Seconds;
		}

//alarm mode		
		if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0 && alarm_used==0)
		{
			while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0){}
			status=4;	//alarm
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
			t_h=Ttime.Hours;	//stored time before enter alarm mode
			t_m=Ttime.Minutes;
			t_s=Ttime.Seconds;
//			c_h=Ttime.Hours;	 //unlock if no need to keep rtc when on alarm setting mode
//			c_m=Ttime.Minutes;
//			c_s=Ttime.Seconds;
		}			
		
		Lcd_gotoxy(0,0);	//print rtc to lcd (connect lcd first)
		Lcd_write_string("Real-time clock");
		sprintf(Lcd_data,"%d:%02d:%02d",Ttime.Hours,Ttime.Minutes,Ttime.Seconds);
		Lcd_gotoxy(0,1);
		Lcd_write_string(Lcd_data); 
/*		if (Tdate.Month >9) Tdate.Month=Tdate.Month-6; // unlock if working on date/month/year
		sprintf(Lcd_data, "Date: %02d:%02d:%02d",Tdate.Date,Tdate.Month,Tdate.Year);
			Lcd_gotoxy(0,1);
			Lcd_write_string(Lcd_data);*/		
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 10;
  sTime.Minutes = 20;
  sTime.Seconds = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_SATURDAY;
  DateToUpdate.Month = RTC_MONTH_AUGUST;
  DateToUpdate.Date = 26;
  DateToUpdate.Year = 23;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void MX_RTC_Init_New(int8_t hour, int8_t min, int8_t sec)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = hour;
  sTime.Minutes = min;
  sTime.Seconds = sec;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_SATURDAY;
  DateToUpdate.Month = RTC_MONTH_AUGUST;
  DateToUpdate.Date = 26;
  DateToUpdate.Year = 23;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
