
#include "main.h"
#include "usbd_hid_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"


#define ADC1_CDR_Address    ((uint32_t)0x40012308)


#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment = 4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;
  
__IO uint8_t UserButtonPressed = 0x00;
uint8_t InBuffer[64], OutBuffer[63];


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

int ciszas=sizeof(cisza)/2;
int cisza_iter=0;


int main(void)
{

	  USBD_Init(&USB_OTG_dev,
	#ifdef USE_USB_OTG_HS
	  USB_OTG_HS_CORE_ID,
	#else
	  USB_OTG_FS_CORE_ID,
	#endif
	  &USR_desc,&USBD_HID_cb,&USR_cb);

	SystemInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	codec_init();
	codec_ctrl_init();

	I2S_Cmd(CODEC_I2S, ENABLE);

while(1)
    {

	   if(OutBuffer[0]==1)
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


	   if( OutBuffer[0]==2)
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

	   if( OutBuffer[0]==3)
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

	   if(OutBuffer[0]==4)
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

	   if( OutBuffer[0]==5)
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

	   if( OutBuffer[0]==6)
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

	   if( OutBuffer[0]==7)
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

	   if( OutBuffer[0]==8)
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

	   if( OutBuffer[0]==9)
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

	   if( OutBuffer[0]==10)
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

	   if( OutBuffer[0]==11)
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

	   if( OutBuffer[0]==12)
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

	   if(OutBuffer[0]==13)
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
	   if(OutBuffer[0]==26)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=music1[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == music1s){sampleCounter = 0;Delay(0x100000);}
        }

	   if( OutBuffer[0]==27)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=music2[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == music2s){sampleCounter = 0;Delay(0x100000);}
        }

	   if(OutBuffer[0]==28)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=music3[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == music3s){sampleCounter = 0;Delay(0x100000);}
        }

	   if(OutBuffer[0]==29)
        {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=music4[sampleCounter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		if(iter%2==1)
       		sampleCounter++;
       		iter++;
     		}
        if (sampleCounter == music4s){sampleCounter = 0;Delay(0x100000);}
        }

	   if(OutBuffer[0]==0)
	   {
		   if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		   {
       		sample=cisza[cisza_iter];

       		SPI_I2S_SendData(CODEC_I2S, sample);

       		cisza_iter++;
            if (cisza_iter == ciszas){cisza_iter = 0;}
		   }

		   sampleCounter=0;
		   iter=0;
	   }
    }
}

void Delay(__IO uint32_t nTime)
{
  if (nTime != 0x00)
  { 
    nTime--;
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {}
}
#endif
