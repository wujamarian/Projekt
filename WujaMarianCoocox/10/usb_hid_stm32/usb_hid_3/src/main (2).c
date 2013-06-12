#include "main.h"
#include "pdm_filter.h"

#define Przerywanie_od_MP45DT02          SPI2_IRQHandler

long int iter=0;

int c1s=sizeof(c1)/2;
int cis1s=sizeof(cis1)/2;

int d1s=sizeof(d1)/2;
int dis1s=sizeof(dis1)/2;

int e1s=sizeof(e1)/2;

int f1s=sizeof(f1)/2;
int fis1s=sizeof(fis1)/2;

int g1s=sizeof(g1)/2;
int gis1s=sizeof(gis1)/2;

int a1s=sizeof(a1)/2;
int ais1s=sizeof(ais1)/2;

int h1s=sizeof(h1)/2;

int c2s=sizeof(c2)/2;

int button=0;

int music1s=sizeof(music1)/2;
int music2s=sizeof(music2)/2;
int music3s=sizeof(music3)/2;
int music4s=sizeof(music4)/2;

void przerywanie_zewn()
{

	NVIC_InitTypeDef NVIC_InitStructure;
	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);


	// wybór numeru aktualnie konfigurowanej linii przerwañ
	EXTI_InitStructure.EXTI_Line = GPIO_Pin_0;
	// wybór trybu - przerwanie b¹dŸ zdarzenie
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	// wybór zbocza, na które zareaguje przerwanie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	// uruchom dan¹ liniê przerwañ
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	// zapisz strukturê konfiguracyjn¹ przerwañ zewnêtrznych do rejestrów
	EXTI_Init(&EXTI_InitStructure);

	// pod³¹czenie danego pinu portu do kontrolera przerwañ
	SYSCFG_EXTILineConfig(GPIOA, GPIO_Pin_0);

}

//Zewnêtrzne przerywaanie:
void EXTI0_IRQHandler(void)
{
		if(EXTI_GetITStatus(EXTI_Line0) != RESET)
		{

		TIM_Cmd ( TIM2 , ENABLE ) ;

		// miejsce na kod wywo³ywany w momencie wyst¹pienia przerwania
		// wyzerowanie flagi wyzwolonego przerwania
		EXTI_ClearITPendingBit(EXTI_Line0);
		}
}

void timer()
{
	if(TIM_GetCounter(TIM2)==99)
	{
		if(  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1  )
		{

			button++;		if(button>17)button=0;

			iter=0;
			sampleCounter=0;

			TIM_SetCounter(TIM2,0);
			TIM_Cmd ( TIM2 , DISABLE ) ;
		}
	}
}


void tim2()
{
	RCC_APB1PeriphClockCmd ( RCC_APB1Periph_TIM2 , ENABLE ) ; // uruchomienie zegara dla Timera 2

	// taktow ani e FCLK=72MHz/7200=10kHz
		TIM_TimeBaseStructure . TIM_Prescaler = 8400;
		// p r z e p e l n i e n i e l i c z n i k a 10000 taktów = 1 s
		TIM_TimeBaseStructure . TIM_Period = 100;
		// z l i c z a n i e w gore
		TIM_TimeBaseStructure . TIM_CounterMode = TIM_CounterMode_Up ;
		// l i c z n i k powtorzen
		TIM_TimeBaseStructure . TIM_RepetitionCounter = 0 ;
		// i n i c j a l i z a c j a l i c z n i k a 2
		TIM_TimeBaseInit ( TIM2 , &TIM_TimeBaseStructure ) ;
}

void gpio_inicjacja()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//Button
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


int main(void)
{
	SystemInit();

	gpio_inicjacja();
	tim2();
	przerywanie_zewn();

	codec_init();
	codec_ctrl_init();

	I2S_Cmd(CODEC_I2S, ENABLE);


while(1)
    {

timer();


	   if(button==1)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=c1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == c1s)sampleCounter = 0;
        }

	   if(button==2)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=cis1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == cis1s)sampleCounter = 0;
        }

	   if(button==3)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=d1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == d1s)sampleCounter = 0;
        }

	   if(button==4)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=dis1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == dis1s)sampleCounter = 0;
        }

	   if(button==5)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=e1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == e1s)sampleCounter = 0;
        }

	   if(button==6)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=f1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == f1s)sampleCounter = 0;
        }

	   if(button==7)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=fis1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == fis1s)sampleCounter = 0;
        }

	   if(button==8)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=g1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == g1s)sampleCounter = 0;
        }

	   if(button==9)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=gis1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == gis1s)sampleCounter = 0;
        }

	   if(button==10)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=a1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == a1s)sampleCounter = 0;
        }

	   if(button==11)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=ais1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == ais1s)sampleCounter = 0;
        }

	   if(button==12)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=h1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;

     		}
        if (sampleCounter == h1s)sampleCounter = 0;
        }

	   if(button==13)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=c2[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == c2s)sampleCounter = 0;
        }


///////////////SAMPLE
	   if(button==14)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=music1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == music1s)sampleCounter = 0;
        }

	   if(button==15)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=music2[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == music2s)sampleCounter = 0;
        }

	   if(button==16)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=music3[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == music3s)sampleCounter = 0;
        }

	   if(button==17)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=music4[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == music4s)sampleCounter = 0;
        }


    }


}

