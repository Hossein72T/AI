#ifndef _CLIKTS
/*****************************************
 *  File: RFM_driver
 *
 * Frequenza SPI 3.0 MHz
 *
 */
 
#include "RFM_driver.h"
#include "protocol_wireless.h"

//------------- Global var -------------
UINT8 op_status;


//Bank1 register initialization value

//In the array RegArrFSKAnalog,all the register value is the byte reversed!!!!!!!!!!!!!!!!!!!!!
const unsigned long Bank1_Reg0_13[]={       //latest config txt
    0xE2014B40,
    0x00004BC0,
    0x028CFCD0,
    0x41390099,
    0x1B8296d9,
    0xA67F0224,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00127300,
    0x46B48000,
};

const UINT8 Bank1_Reg14[]=
{
    0x41,0x20,0x08,0x04,0x81,0x20,0xCF,0xF7,0xFE,0xFF,0xFF
};

//Bank0 register initialization value
const UINT8 Bank0_Reg[][2]={
{0,0x0F},//reflect RX_DR\TX_DS\MAX_RT,Enable CRC ,2byte,POWER UP,PRX
{1,0x3F},//Enable auto acknowledgement data pipe5\4\3\2\1\0
{2,0x3F},//Enable RX Addresses pipe5\4\3\2\1\0
{3,0x03},//RX/TX address field width 5byte
{4,0xf7},//auto retransmission dalay (1500us),auto retransmission count(2)
{5,0x01},//default: 0x17=23 channel
{6,0x07},//air data rate-1M,out power 0dbm,setup LNA gain \bit4 must set up to 0
{7,0x07},//
{8,0x00},//
{9,0x00},
{12,0xc3},//only LSB Receive address data pipe 2, MSB bytes is equal to RX_ADDR_P1[39:8]
{13,0xc4},//only LSB Receive address data pipe 3, MSB bytes is equal to RX_ADDR_P1[39:8]
{14,0xc5},//only LSB Receive address data pipe 4, MSB bytes is equal to RX_ADDR_P1[39:8]
{15,0xc6},//only LSB Receive address data pipe 5, MSB bytes is equal to RX_ADDR_P1[39:8]
{17,0x20},//Number of bytes in RX payload in data pipe0(32 byte) 
{18,0x20},//Number of bytes in RX payload in data pipe1(32 byte)
{19,0x20},//Number of bytes in RX payload in data pipe2(32 byte)
{20,0x20},//Number of bytes in RX payload in data pipe3(32 byte)
{21,0x20},//Number of bytes in RX payload in data pipe4(32 byte)
{22,0x20},//Number of bytes in RX payload in data pipe5(32 byte)
{23,0x00},//fifo status
{28,0x3F},//Enable dynamic payload length data pipe5\4\3\2\1\0
{29,0x07}//Enables Dynamic Payload Length,Enables Payload with ACK,Enables the W_TX_PAYLOAD_NOACK command 
};


const UINT8 RX0_Address[]={0x34,0x43,0x10,0x10,0x01};//Receive address data pipe 0
const UINT8 RX1_Address[]={0x39,0x38,0x37,0x36,0xc2};//Receive address data pipe 1

extern UINT8 test_data;
extern UINT8 channel;
extern UINT8 power;
extern UINT8 data_rate;
extern UINT8 rx_buf[MAX_PACKET_LEN];

extern _PCA9500 PCA9500;

/**************************************************
 *  piccolo delay dopo il CSN
 ***************************************************/
void micro_delay() {
    for(char i=0; i <= 2; i++) asm("nop");
}


/**************************************************
  Function: init_port_RFM()

  Description:                                                
    Initialize the io to drive with Module RF
 **************************************************/  
void init_port_RFM()
{  
  // Inizializziamo le porte per pilotare il modulo RFM
  //TRISDbits.TRISD6 = 0;  // CE_RFM : output
  //CE_RFM(0);             // Disable TX & RX trasmission
  PCA9500.CE_RFM = 0;
  PCA9500_write( PCA9500 );
  
  //TRISDbits.TRISD1 = 0;  // CSN_RFM : output
  //CSN_RFM(0);
  CSN_RFM_Set();
  
  //TRISCbits.TRISC14 = 0;  // SCK_RFM : output
  //SCK_RFM(0);
  
  //TRISDbits.TRISD0  = 1; // input MISO
  //TRISDbits.TRISD11 = 1; // input IRQ_RFM
  
  //TRISCbits.TRISC13 = 0;  // MOSI_RFM : output
  //MOSI_RFM(0);

  //TRISDbits.TRISD5 = 0;  // TR_EN_RFM : output
  //TR_EN_RFM(0);
  PCA9500.TREN_RFM = 0;
  
  //TRISGbits.TRISG6 = 0;  // PA_EN_RFM : output
  //PA_EN_RFM(0);
  PCA9500.PAEN_RFM = 0;
  PCA9500_write( PCA9500 );
}  

///////////////////////////////////////////////////////////////////////////////
//                  SPI access                                               //
///////////////////////////////////////////////////////////////////////////////

/**************************************************         
Function: SPI_RW();                                         
                                                            
Description:                                                
	Writes one UINT8 to RFM73, and return the UINT8 read 
 **************************************************/        
UINT8 SPI_RW(UINT8 value)                                    
{                                                           
    UINT8 bit_ctr, temp, bit_in;
    
    FLEXCOM2_SPI_Write( &value, 1 );
    
   /* for(bit_ctr=0; bit_ctr<8; bit_ctr++)   // output 8-bit
    {
        
        if(value & 0x80)
            MOSI_RFM(1);
        else
            MOSI_RFM(0);
	
        	
        SCK_RFM(1);			// Set SCK high..		
	value = (value << 1);           // shift next bit into MSB.
        
        asm("nop");
        
        
	value |= MISO_RFM;              // capture current MISO bit
	SCK_RFM(0);                     // ..then set SCK low again
        
    }*/

    return(value);           		// return read UINT8
}                                                           
                                                              
/**************************************************         
Function: SPI_Write_Reg();                                  
                                                            
Description:                                                
	Writes value 'value' to register 'reg'              
/**************************************************/        
void SPI_Write_Reg(UINT8 reg, UINT8 value)                 
{
    /*CSN_RFM(0);               // CSN low, init SPI transaction
    
    micro_delay();
    
    op_status = SPI_RW(reg);    // select register
    SPI_RW(value);              // ..and write value to it..
    
    CSN_RFM(1);              // CSN high again*/
    
    CSN_RFM_Clear();
    micro_delay();
    
    op_status = SPI_RW(reg);    // select register
    RFM73_Ready();
    SPI_RW(value);              // ..and write value to it..
    RFM73_Ready();
    
    CSN_RFM_Set();
}                                                         
        
                                                            
/**************************************************         
Function: SPI_Read_Reg();                                   
                                                            
Description:                                                
	Read one UINT8 from BK2421 register, 'reg'           
/**************************************************/        
UINT8 SPI_Read_Reg(UINT8 reg)                               
{                                                           
    UINT8 value=0;
    
    /*CSN_RFM(0);           // CSN low, initialize SPI communication...
    
    micro_delay();
    
    op_status=SPI_RW(reg);  // Select register to read from..
    value = SPI_RW(0);      // ..then read register value
    CSN_RFM(1);          // CSN high, terminate SPI communication*/
    
    CSN_RFM_Clear();
    micro_delay();
    
    op_status = SPI_RW(reg);    // select register
    RFM73_Ready();
    FLEXCOM2_SPI_Read( &value, 1 );              // ..and write value to it..
    RFM73_Ready();
    
    CSN_RFM_Set();
    
    return(value);          // return register value
}                                                           
    
                                                            
/**************************************************         
Function: SPI_Read_Buf();                                   
                                                            
Description:                                                
	Reads 'length' #of length from register 'reg'         
/**************************************************/        
void SPI_Read_Buf(UINT8 reg, UINT8 *pBuf, UINT8 length)     
{                                                           
    UINT8 status_reg, byte_ctr;
    UINT8 value;
                                                            
    /*CSN_RFM(0);               // Set CSN l
    
    micro_delay();
    
    status_reg = SPI_RW(reg);       // Select register to write, and read status UINT8
                                                            
    for(byte_ctr=0;byte_ctr<length;byte_ctr++)
        pBuf[byte_ctr] = SPI_RW(0);    // Perform SPI_RW to read UINT8 from RFM73
                                                            
    CSN_RFM(1);              // Set CSN high again*/
    
    CSN_RFM_Clear();
    micro_delay();
    
    status_reg = SPI_RW(reg);       // Select register to write, and read status UINT8
    RFM73_Ready();
    
    for(byte_ctr=0;byte_ctr<length;byte_ctr++)
    {
        FLEXCOM2_SPI_Read( &value, 1 );
        RFM73_Ready();
        pBuf[byte_ctr] = value;    // Perform SPI_RW to read UINT8 from RFM73
    }
    
    CSN_RFM_Set();
}
       
                                                            
/**************************************************         
Function: SPI_Write_Buf();                                  
                                                            
Description:                                                
	Writes contents of buffer '*pBuf' to RFM73         
/**************************************************/        
void SPI_Write_Buf(UINT8 reg, UINT8 *pBuf, UINT8 length)    
{                                                           
    UINT8 byte_ctr, value;
                                                            
    /*CSN_RFM(0);                     // Set CSN low, init SPI transaction
  
    micro_delay();
    
    op_status = SPI_RW(reg);        // Select register to write to and read status UINT8

    for(byte_ctr=0; byte_ctr<length; byte_ctr++) // then write all UINT8 in buffer(*pBuf)
        SPI_RW(*pBuf++);

    CSN_RFM(1);                 // Set CSN high again*/
    
    CSN_RFM_Clear();
    micro_delay();
    
    op_status = SPI_RW(reg);       // Select register to write, and read status UINT8
    RFM73_Ready();
    
    for(byte_ctr=0;byte_ctr<length;byte_ctr++)
    {
        value = *pBuf;
        FLEXCOM2_SPI_Write( &value, 1 );
        RFM73_Ready();
        pBuf++;
    }
    
    CSN_RFM_Set();
    
}
/**************************************************
Function: SwitchToRxMode();
Description:
	switch to Rx mode
/**************************************************/
void SwitchToRxMode()
{
    UINT8 value;

   /* TR_EN_RFM(0);
    PA_EN_RFM(1);

    micro_delay();
    micro_delay();

    CE_RFM(0);                                // Set CSN low, init SPI tranaction
    
    SPI_Write_Reg(FLUSH_RX,0);                  //flush Rx

    value=SPI_Read_Reg(REG_STATUS);             // read register STATUS's value
    SPI_Write_Reg(WRITE_REG|REG_STATUS,value);  // clear RX_DR or TX_DS or MAX_RT interrupt flag

    value=SPI_Read_Reg(CONFIG);	// read register CONFIG's value
	
//PRX
    value=0x0F;                                 //set bit 1
    SPI_Write_Reg(WRITE_REG | CONFIG, value);   // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled..
   
    CE_RFM(1);*/
    
  PCA9500.TREN_RFM = 0;
  PCA9500.PAEN_RFM = 1;
  PCA9500_write( PCA9500 );
  
  micro_delay();
  micro_delay();
  
  PCA9500.CE_RFM = 0;
  PCA9500_write( PCA9500 );
  
  SPI_Write_Reg(FLUSH_RX,0);                  //flush Rx

  value=SPI_Read_Reg(REG_STATUS);             // read register STATUS's value
  SPI_Write_Reg(WRITE_REG|REG_STATUS,value);  // clear RX_DR or TX_DS or MAX_RT interrupt flag

  value=SPI_Read_Reg(CONFIG);	// read register CONFIG's value
	
//PRX
  value=0x0F;                                 //set bit 1
  SPI_Write_Reg(WRITE_REG | CONFIG, value);   // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled..
  
  PCA9500.CE_RFM = 1;
  PCA9500_write( PCA9500 );
}

/**************************************************
Function: SwitchToTxMode();
Description:
	switch to Tx mode
/**************************************************/
void SwitchToTxMode()
{
    UINT8 value;

    /*TR_EN_RFM(1);
    PA_EN_RFM(1);

    CE_RFM(0);                     // Set CSN low, init SPI tranaction
    
    micro_delay();
    micro_delay();

    SPI_Write_Reg(FLUSH_TX,0);      // flush Tx
                   
    value=SPI_Read_Reg(CONFIG);     // read register CONFIG's value
    //PTX
    value=value&0xfe;//set bit 0
    SPI_Write_Reg(WRITE_REG | CONFIG, value); // Set PWR_UP bit, enable CRC(2 length) & Prim:PTX. RX_DR enabled.
	
    CE_RFM(1);*/
    
  PCA9500.TREN_RFM = 1;
  PCA9500.PAEN_RFM = 1;
  PCA9500.CE_RFM = 0;
  PCA9500_write( PCA9500 );
  
  micro_delay();
  micro_delay();
  
  SPI_Write_Reg(FLUSH_TX,0);      // flush Tx
                   
  value=SPI_Read_Reg(CONFIG);     // read register CONFIG's value
  //PTX
  value=value&0xfe;//set bit 0
  SPI_Write_Reg(WRITE_REG | CONFIG, value); // Set PWR_UP bit, enable CRC(2 length) & Prim:PTX. RX_DR enabled.
    
  PCA9500.CE_RFM = 1;
  PCA9500_write( PCA9500 );
 
}


/**************************************************
Function: SwitchCFG();
                                                            
Description:
	 access switch between Bank1 and Bank0 

Parameter:
	_cfg      1:register bank1
	          0:register bank0
Return:
     None
/**************************************************/
void SwitchCFG(char _cfg)//1:Bank1 0:Bank0
{
    UINT8 Tmp;

    Tmp=SPI_Read_Reg(7);
    Tmp=Tmp&0x80;

    if( ( (Tmp)&&(_cfg==0) )
	||( ((Tmp)==0)&&(_cfg) ) )
    {
	SPI_Write_Reg(ACTIVATE_CMD,0x53);
    }
}

/**************************************************
 Function: SetChannelNum

 Description:
   Set new channel number
   @Maury: Cambiando canale dobbiamo, reinserire i
           dati di Setup etc..
/**************************************************/
void SetChannelNum(UINT8 ch)
{

    SPI_Write_Reg(FLUSH_TX,0);  // flush Tx

	sdata_wi.channel_old = sdata_wi.channel;
	sdata_wi.channel = ch;

    //CE_RFM(0);                  // Disable TX & RX
    PCA9500.CE_RFM = 0;
    PCA9500_write( PCA9500 );
    
    micro_delay();

    for(int i=0; i <= 4; i++)
        SPI_Write_Reg((WRITE_REG|Bank0_Reg[i][0]),Bank0_Reg[i][1]);

    SPI_Write_Reg((UINT8)(WRITE_REG|RF_CH),(UINT8)(ch));

    SPI_Write_Reg((WRITE_REG|RF_SETUP), sdata_wi.rf_setup); //massima potenza del segnale

    //delay(25);
    SYSTICK_DelayMs ( 25 );
    //CE_RFM(1);                  // Enable TX & RX
    PCA9500.CE_RFM = 1;
    PCA9500_write( PCA9500 );
}





///////////////////////////////////////////////////////////////////////////////
//                  RFM73 initialization                                     //
///////////////////////////////////////////////////////////////////////////////
/**************************************************
Function: RFM73_Initialize();

Description:
	register initialization
 Input:
    RF_chanel : 2.400 GHz,  ....
    power  : -10dbm, -5dbm, 0 dbm, +5 dbm
  data_rate:  1 Mbit, 2 Mbit
/**************************************************/
void RFM73_Initialize(UINT8 RF_ch, UINT8 power, UINT8 data_rate)
{
    UINT8 i,j,temp;
    UINT8 WriteArr[12];

    //delay(150);
    SYSTICK_DelayMs ( 150 );

    SwitchCFG(0);


    //********************Write Bank0 register******************
    for(i=0;i<5;i++)
    {
        SPI_Write_Reg((WRITE_REG|Bank0_Reg[i][0]),Bank0_Reg[i][1]);
    }


    //********************select channel*************************
    //F0 = 2400Mhz + RF_ch (MHZ)
    SPI_Write_Reg(WRITE_REG|5, RF_ch);
	sdata_wi.channel_old = RF_ch;
	sdata_wi.channel = RF_ch;
	
    // REG: RF_SETUP
    // 5.RF_DR_LOW, 3.RF_DR_HIGH
    //           0, 0     â€“ 1Mbps
    //           0, 1     â€“ 2Mbps(default)
    //           1, 0     â€“ 250Kbps
    //           1, 1     â€“ 2Mbps
    if(data_rate == DATA_RATE_2MBPS)
        temp = 0x28;     //data rate 2M
    else if(data_rate == DATA_RATE_250KBPS)
        temp = 0x20;	 //data rate 250K
    else
	temp = 0x00;	 //data rate 1M

    switch(power)
    {
        case POWER_NEG_5DBM:
            temp |= 0x02; // b2:0, b1:1
        break;

        case POWER_POS_0DBM:
            temp |= 0x04; // b2:1, b1:0
        break;

        case POWER_POS_5DBM:
            temp |= 0x06; // b2:1, b1:1
        break;

        default: break;
    }

    temp |= 0x01; // HIGH GAIN LNA
    
    sdata_wi.rf_setup = temp;

    SPI_Write_Reg((WRITE_REG|6), sdata_wi.rf_setup); //max power TX

    for(i=7;i<21;i++)
    {
        SPI_Write_Reg((WRITE_REG|Bank0_Reg[i][0]),Bank0_Reg[i][1]);
    }

    //reg 10 - Rx0 addr
    for(j=0;j<5;j++)
    {
        WriteArr[j]=RX0_Address[j];
    }
    SPI_Write_Buf((WRITE_REG|10),&(WriteArr[0]),5);

    //REG 11 - Rx1 addr
    for(j=0;j<5;j++)
    {
        WriteArr[j]=RX1_Address[j];
    }
    SPI_Write_Buf((WRITE_REG|11),&(WriteArr[0]),5);

    //REG 16 - TX addr
    for(j=0;j<5;j++)
    {
        WriteArr[j]=RX0_Address[j];
    }
    SPI_Write_Buf((WRITE_REG|16),&(WriteArr[0]),5);


    i=SPI_Read_Reg(29);//read Feature Register

    //SPI_Write_Reg((WRITE_REG|29),(i|0x04)); //Enable
    if(i==0) // i!=0 showed that chip has been actived.so do not active again.
        SPI_Write_Reg(ACTIVATE_CMD,0x73);// Active

    for(i=22;i>=21;i--)
    {
        //Enable Dynamic Payload length ,Enables the W_TX_PAYLOAD_NOACK command
        SPI_Write_Reg((WRITE_REG|Bank0_Reg[i][0]),Bank0_Reg[i][1]);
    }

    //********************Write Bank1 register******************
    SwitchCFG(1);

    for(i=0;i<=8;i++)//reverse
    {
        for(j=0;j<4;j++)
            WriteArr[j]=(Bank1_Reg0_13[i]>>(8*(j) ) )&0xff;

        SPI_Write_Buf((WRITE_REG|i),&(WriteArr[0]),4);
    }

    for(i=9;i<=13;i++)
    {
        for(j=0;j<4;j++)
            WriteArr[j]=(Bank1_Reg0_13[i]>>(8*(3-j) ) )&0xff;

        SPI_Write_Buf((WRITE_REG|i),&(WriteArr[0]),4);
    }

    //SPI_Write_Buf((WRITE_REG|14),&(Bank1_Reg14[0]),11);
    for(j=0;j<11;j++)
    {
        WriteArr[j]=Bank1_Reg14[j];
    }
    SPI_Write_Buf((WRITE_REG|14),&(WriteArr[0]),11);

    //toggle REG4<25,26>
    for(j=0;j<4;j++)
        WriteArr[j]=(Bank1_Reg0_13[4]>>(8*(j) ) )&0xff;

    WriteArr[0]=WriteArr[0]|0x06;
    SPI_Write_Buf((WRITE_REG|4),&(WriteArr[0]),4);

    WriteArr[0]=WriteArr[0]&0xf9;
    SPI_Write_Buf((WRITE_REG|4),&(WriteArr[0]),4);

    //delay(100);
    SYSTICK_DelayMs ( 100 );

    //********************switch back to Bank0 register access******************
    SwitchCFG(0);
    SwitchToRxMode();//switch to RX mode
    
    //delay(25);
    SYSTICK_DelayMs ( 25 );
    
    sdata_wi.install_rfm  = check_install_rfm(); // install_rfm = 0 -> modulo non installato sul KTS.
    sdata_wi.level_signal = 0;

    //CE_RFM(1);
    PCA9500.CE_RFM = 1;
    PCA9500_write( PCA9500 );
}


//-----------------------------------------------------------
// Func: check_install_rfm
//
// Descipt:
//   Dopo l'inizializzazione andiamo a leggere alcuni registri,
//   Se le cose tornano, allora il modulo Ã¨ inserito.
//
// return: 1  modulo presente
//         0  molulo non presente
//-----------------------------------------------------------
int check_install_rfm()
{
    byte val_reg[2] = {0,0};
    
    //CE_RFM(0);
    PCA9500.CE_RFM = 0;
    PCA9500_write( PCA9500 );
    
    val_reg[0] = SPI_Read_Reg(CONFIG);     // 0x00: 0x0F
    //delay(1);
    SYSTICK_DelayMs ( 1 );
    val_reg[1] = SPI_Read_Reg(SETUP_AW);   // 0x03: 0x03    
    //CE_RFM(1);
    PCA9500.CE_RFM = 1;
    PCA9500_write( PCA9500 );
    
    if((val_reg[0] == Bank0_Reg[CONFIG][1]) && (val_reg[1] == Bank0_Reg[SETUP_AW][1]))
      return 1;
    else
      return 0;  // mudulo RF non presente  

}  

#endif

