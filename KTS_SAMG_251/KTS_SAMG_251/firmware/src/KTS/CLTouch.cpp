#ifndef _CLIKTS

#include "CLTouch.h"
#include "CLKTS.h"
#include "CLScreenSaver.h"

int Y_Offset = 720;
int Y_Max = 3602;
int X_Offset = 416;
int X_Max = 3698;

// global variable X and Y, the coordinates of the point pressed
int X_GLOBAL;
int Y_GLOBAL;

#define SAMPLE 8

int ReadX()
{
    ReadXY();
    return X_GLOBAL;
}

int ReadY()
{
    return Y_GLOBAL;
}

int ReadXY()
{
    //int XY_coord[2];

    int Y[SAMPLE];
    int Y_med;
    int Y_vmin;
    int Y_vmax;

    int X[SAMPLE];
    int X_med;
    int X_vmin;
    int X_vmax;

    int i;
    int kx;
    int ky;

    int X_Medium = ((X_Max-X_Offset)/2) + X_Offset ;  // value in the middle of x coordinate
    int Y_Medium = ((Y_Max-Y_Offset)/2) + Y_Offset ;  // value in the middle of y coordinate


    Y_med = 0;
    X_med = 0;

    Y_vmin = Y_Max;
    Y_vmax = Y_Offset;
    X_vmin = X_Max;
    X_vmax = X_Offset;

    kx=0;
    ky=0;

    for(int i = 0; i <SAMPLE;i++)
    {


     // if(!Touched_opt())
       // break;

        //-----------------------  leggo Y
        //-----------------------  leggo Y
        //-----------------------  leggo Y


         // -------  imposto Y come ingressi analogici
        
        Y_P_YU_InputEnable();
        Y_P_YD_InputEnable();
        
        Y_P_YU_Clear();
        Y_P_YD_Clear();
        
        // -------  imposto X come una supply
        Y_P_XL_OutputEnable();
        Y_P_XR_OutputEnable();

        if(bitRead(i,0) == 0)
        {
          Y_P_XR_Set();
          Y_P_XL_Clear();
        }
        else
        {
          Y_P_XR_Clear();
          Y_P_XL_Set();
        }

        SYSTICK_DelayMs ( 2 );
        ADC_ChannelsEnable( ADC_CH2_MASK );
        ADC_ConversionStart( );
        while ( !ADC_ChannelResultIsReady( ADC_CH2 )) {};
        Y[i] = ADC_ChannelResultGet( ADC_CH2 );
        ADC_ChannelsDisable( ADC_CH2_MASK );

        if(bitRead(i,0) == 1)
           Y[i]  = Y[i] - 2*(Y[i]-Y_Medium);

        SYSTICK_DelayUs ( 500 );

        if(!Touched())
        {
          X_GLOBAL= 0;
          Y_GLOBAL= 0;
          return 0;
          break;
        }

        if(Y[i] >= Y_Offset &&  Y[i] <= Y_Max)
        {
          Y_med += Y[i];
          ky++;
          if (Y[i]< Y_vmin)
            Y_vmin = Y[i];
          if (Y[i] > Y_vmax)
            Y_vmax = Y[i];
        }

        //-----------------------  leggo X
        //-----------------------  leggo X
        //-----------------------  leggo X

          // -------  imposto X come ingressi analogici
          Y_P_XR_InputEnable();
          Y_P_XL_InputEnable();

          Y_P_XR_Clear();
          Y_P_XL_Clear();

          // -------  imposto Y come una supply
          Y_P_YU_OutputEnable();
          Y_P_YD_OutputEnable();

          if(bitRead(i,0) == 0)
          {
            Y_P_YU_Set();
            Y_P_YD_Clear();
          }
          else
          {
            Y_P_YU_Clear();
            Y_P_YD_Set();
          }

          SYSTICK_DelayMs ( 2 );
  
          ADC_ChannelsEnable( ADC_CH1_MASK );
          ADC_ConversionStart( );
          while ( !ADC_ChannelResultIsReady( ADC_CH1 )) {};
          X[i] = ADC_ChannelResultGet( ADC_CH1 );
          ADC_ChannelsDisable( ADC_CH1_MASK );

          if(bitRead(i,0) == 1)
           X[i]  = X[i] - 2*(X[i]-X_Medium);

          SYSTICK_DelayUs ( 500 );

         if(!Touched())
        {
          X_GLOBAL= 0;
          Y_GLOBAL= 0;
          return 0;
          break;
        }

        if(X[i] >= X_Offset &&  X[i] <= X_Max)
        {
          X_med += X[i];
          kx++;
          if (X[i]< X_vmin)
            X_vmin = X[i];
          if (X[i] > X_vmax)
            X_vmax = X[i];
        }

    }

    if(ky >4)
    {
      Y_med = Y_med - Y_vmin - Y_vmax;
      Y_med = Y_med/(ky-2);;
      Y_GLOBAL = (int)((((long)(Y_med - Y_Offset)) *gLCD.getMaxY())/(Y_Max -Y_Offset));
      Y_GLOBAL = constrain(Y_GLOBAL,gLCD.getMinY(), gLCD.getMaxY());
    }
    else{
      Y_GLOBAL= 0;
      return 0;
    }

    if(kx >4)
    {
      X_med = X_med - X_vmin - X_vmax;
      X_med = X_med/(kx-2);;
      X_GLOBAL = (int)((((long)(X_med - X_Offset)) *gLCD.getMaxX())/(X_Max -X_Offset));
      X_GLOBAL = constrain(X_GLOBAL,gLCD.getMinX(), gLCD.getMaxX());
    }
    else{
      X_GLOBAL= 0;
      return 0;
    }

    return 1;
}

//---------------------------------------------------------------------------------
//----------------  Touched optimized -------------------------------------
//---------------------------------------------------------------------------------
int Touched()
{
    static int YD_t;
    
    // Imposto YU come HIgh impedance  
    Y_P_YU_InputEnable();
    Y_P_YU_Clear();
    
    // Imposto YD come ingresso analogico
    Y_P_YD_InputEnable();
    Y_P_YD_Clear();
    
    // Imposto XL a GND
    Y_P_XL_OutputEnable();
    Y_P_XL_Clear();
    
    Y_P_XR_InputEnable();
    Y_P_XR_Clear();
    
    SYSTICK_DelayUs ( 320 );
    
    ADC_ChannelsEnable( ADC_CH2_MASK );
    
    // Verifica se il touch è stato premuto
    ADC_ConversionStart( );
    while ( !ADC_ChannelResultIsReady( ADC_CH2 )) {};
    YD_t = ADC_ChannelResultGet( ADC_CH2 );
    
    ADC_ChannelsDisable( ADC_CH2_MASK );
    
    if (YD_t < 2001)
	{
		gKTSGlobal.LastTouchedMilliseconds				= millis();
		gKTSGlobal.ScreenSaver_LastTouchedMilliseconds	= millis();
		return 1;
	}
            
	return 0;
}

//---------------------------------------------------------------------------------
//  Aspetto che venga rilasciato il tasto
//  @Maury: la funzione viene modificata per permettere di leggere la seriale mentre
//          sto facendo una impostazione
//---------------------------------------------------------------------------------
void WaitForTouchRelease()
{
  while(Touched()!=0)
   {
	   SYSTICK_DelayMs ( 4 );
	   CLKTS::Process();
	   CLKTS::Pir_Process();
   }
}

#endif

