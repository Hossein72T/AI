/*******************************************************************
 * file: CLCommunication_Driver.ccp
 *
 * Author/Date: Maurizio Colmone dic.2013
 *
 * Description: Il file gestisce il traffico sulla seriale 1, tramite
 *              il protocollo ser1.
 *
 ******************************************************************/

#include "RDProtocol.h"
#include "CLSerialDriver.h"
#include "protocol_wireless.h"
#include "RFM_driver.h"
#include "definitions.h"

//--------------- Var Global -----------------------------
byte wait_to_analayzer_message = 0;
byte num_pkt_received          = 0; 
char tx_buf_pkt[32];
byte  count_Rx_wi = 0;
byte  count_Tx_wi = 0;

unsigned long tmr_mills_polling_func_rfm = 0;

DEF_DATA_WIRELESS sdata_wi;  // struttura dati wireless
byte flag_Rx_message_wireless = 0;

byte rx_buf_tail = 0;
byte sRxBuffer[ MAX_SERIAL_BUFFER_LENGHT ];

extern volatile uint32_t nBytesRead;
extern uint8_t rxBuffer[256];
extern volatile bool txThresholdEventReceived;

/**************************************************
Function: Send_Packet
Description:
	fill FIFO to send a packet
Parameter:
	type: WR_TX_PLOAD or  W_TX_PAYLOAD_NOACK_CMD
	pbuf: a buffer pointer
	len: packet length
Return:
	None
**************************************************/
void Send_Packet(UINT8 type, char *pbuf, UINT8 len)
{
    byte fifo_sta;
	

    fifo_sta=SPI_Read_Reg(FIFO_STATUS);	  // read register FIFO_STATUS's value
    if((fifo_sta&FIFO_STATUS_TX_FULL)==0) // if not full, send data (write buff)
    { 
        SPI_Write_Buf(type, (UINT8 *)pbuf, len);   // Writes data to buffer
    }	  	 	
}

/************************************************************************
 * RecivePacket:
 *
 * Verifica se Ã¨ arrivato un messaggio.
 ************************************************************************/
void ReceivePacket(void)
{
    byte len=0,i,sta=0,fifo_sta, chksum;
    byte num_pkt, tot_pkt;
    byte rx_buf[MAX_PACKET_LEN+1];

    sta=SPI_Read_Reg(REG_STATUS);	// read register STATUS's value
    
	//if (sdata_wi.status == TX_WIRELESS_IN_PROGRESS)
	//{
	//   //clear flag status
 //      SPI_Write_Reg(WRITE_REG|REG_STATUS, (sta & ~0x40) );
	//   return;
	//}

    // if receive data ready (RX_DR) interrupt
    if((STATUS_RX_DR & sta) == 0x40)
    {   
      
        // piccolo tempo di attesa, neccesario per permettere al moduloRFM di stabilizzarsi. 
#ifdef _CLIKTS
		for(i=0; i < 50; i++) __asm { nop };
#else
        for(i=0; i < 50; i++) asm("nop");
#endif
        
        do
        {           
            // read len message
            len=SPI_Read_Reg(R_RX_PL_WID_CMD);

            if(len<=MAX_PACKET_LEN)
            {
                SPI_Read_Buf(RD_RX_PLOAD, rx_buf, len);// read receive payload from RX_FIFO buffer
            }
            else
            {
                SPI_Write_Reg(FLUSH_RX,0);  // flush Rx
            }

            fifo_sta = SPI_Read_Reg(FIFO_STATUS);	// read register FIFO_STATUS's value

        }while((fifo_sta & FIFO_STATUS_RX_EMPTY)==0);   // while not empty

        // Verifichiamo il contenuto del messaggio, ricordiamoci che ogni pacchetto Ã¨ spedito
        // 2 volte per inrobustire la comunicazione

		chksum = 0;
        for(i=0; i <(len-1); i++)
            chksum += rx_buf[i];
            
	
        if((chksum == rx_buf[IHMW_CKSUM_8]) && (len==32))
        {
            num_pkt = rx_buf[IHMW_PACKET] & 0x0F;
            tot_pkt = rx_buf[IHMW_PACKET] >> 4;
    
            if(num_pkt != sdata_wi.num_packet) 
            {

               num_pkt_received++;
               sdata_wi.tot_packet = tot_pkt;
               sdata_wi.num_packet = num_pkt;

               // se la sequenza dei pacchetti non Ã¨ rispettata, azzeriamo tutto
               if(num_pkt_received != num_pkt){
                  sdata_wi.status = BUFF_WIRELESS_EMPY;
                  sdata_wi.len = 0;
                  sdata_wi.pos_data_tx = 0;
                  sdata_wi.num_packet  = 0;
                  num_pkt_received     = 0;
   

#ifdef DEBUG_WI  //-----------------------------------------------x_dbg  
                  count_Err_Pkt++; 
#endif  //--------------------------------------------------------x_dbg                   
               
                }else {

                  for(i=0; i < rx_buf[IHMW_LEN_DATA]; i++)
                     sdata_wi.data[sdata_wi.len++] = rx_buf[IHMW_START_DATA + i];

                  if(num_pkt == tot_pkt)                    
				  {
                    sdata_wi.status = RX_WIRELESS_END;  // analizziamo il messaggio
					wait_to_analayzer_message = 3;
					sdata_wi.receivedDeviceId = ((unsigned int) (rx_buf[IHMW_ID_DEVICE_HI] << 8)) | rx_buf[IHMW_ID_DEVICE_LO];
				  }
                  else 
                    sdata_wi.status = RX_WIRELESS_IN_PROGRESS;
                
                }                 
           }
      }
#ifdef DEBUG_WI  //-----------------------------------------------x_dbg      
      else {
        
           count_Err_Cks++;         
      }  
#endif  //--------------------------------------------------------x_dbg       
      
       //clear flag status
       SPI_Write_Reg(WRITE_REG|REG_STATUS,sta);
    }
 
}

//---------------------------------------------------------
//  Configura i registri per la trasmissione Wireless ,
//  e componi il messaggio. 
//---------------------------------------------------------
void send_by_wireless(byte *buff, byte len)
{
	//ReceivePacket();
    SwitchToTxMode();              // switch to tx mode
         
    for(int i=0; i < len; i++)
       sdata_wi.data[i] = buff[i];  
    
    sdata_wi.status = TX_WIRELESS_IN_PROGRESS;
   
    wait_to_analayzer_message = 4;    //  ritardo di ~40ms

    sdata_wi.pos_data_tx   = 0;
    sdata_wi.num_packet    = 1;
    sdata_wi.len           = len;
    sdata_wi.tot_packet    = (len + (NUM_BYTE_PACKET- 1))/ NUM_BYTE_PACKET;
    sdata_wi.num_repeat_tx = 0;
}  


//---------------------------------------------------------
// Funzione che Calcola il Cksum su 16 bit e ritorna il 
// complemento a 1 della somma.
//---------------------------------------------------------
word calc_cksum_16(byte * buffer, int lenght)
{
    word cksum16_temp = 0;
  
    for(int i=0; i < lenght; i++)
      cksum16_temp += buffer[i];
  
    return (~cksum16_temp) & 0x0000ffff;
}


//-------------------------------------------------------------
// Manda un messaggio all'unitÃ . 
// viene passato la stringa da mandare, e l'uscita da utilizzare
//   type_output : BY_WIRELESS
//                 BY_SERIAL_0
//-------------------------------------------------------------
void Write_Message(byte *buff, char type_output)
{
    word Cksum16, len, i;

    // testa del messaggio
    buff[IHM1_START_MSG_0] = PROTO_START_MSG_0;
    buff[IHM1_START_MSG_1] = PROTO_START_MSG_1;
   
    // lunghezza del messaggio
    len = buff[IHM1_POS_CRC_LO] + 2; 
    len &= 0x7F; // max 127 byte. 
    
    // calcola il cksum
    Cksum16 = calc_cksum_16(buff,  buff[IHM1_POS_CRC_LO]);
   
    i = buff[ IHM1_POS_CRC_LO ]; 
    buff[i]     = lowByte(Cksum16);
    buff[i + 1] = highByte(Cksum16);

    if(type_output == BY_WIRELESS) {
        send_by_wireless(buff, len);
    }else {
        // Spedisci il messaggio tramite Seriale 0
        sdata_wi.status = WIRELESS_DISABLE;
        // scarico prima il buffer , I unload the buffer first
        //while(Serial0.available())
	    //Serial0.read();
	//Serial0.write(buff, len);
        
        if ( nBytesRead != 0)
        {
           nBytesRead = 0;
           memset ( rxBuffer, 0, sizeof (rxBuffer));
        }
        
        FLEXCOM0_USART_Write( buff, len);
        while (txThresholdEventReceived == false);
        txThresholdEventReceived = false;
    }             
}

int gMWIEntryCounter = 0;

void management_message_wi(unsigned long tmr_mills)
{
    byte cksum_8;    
    int len;
	static char text[ 512 ];
    
    if (((tmr_mills - tmr_mills_polling_func_rfm  ) >= 9) 
       ||(tmr_mills_polling_func_rfm  > tmr_mills)) 
    {         
        tmr_mills_polling_func_rfm  = tmr_mills; 

        // per la lettura del buffer in ricezione andiamo al massimo 9ms,
        // mentre per la scrittura raddopiamo il tempo di attesa
        if(wait_to_analayzer_message)
            wait_to_analayzer_message--;
        gMWIEntryCounter++;
             
        switch(sdata_wi.status)
        {
            case WIRELESS_DISABLE:
            default:
               // in caso che si utilizza la seriale non serve monitorare il modulo Wireless
               num_pkt_received         = 0; 
               flag_Rx_message_wireless = 0;     
               sdata_wi.status = WIRELESS_DISABLE;
            break;
      
            case BUFF_WIRELESS_EMPY:
            case RX_WIRELESS_IN_PROGRESS:       
               ReceivePacket();
            break;

            case RX_WIRELESS_END:
               ReceivePacket(); // scarichiamo il buffer da eventuali eco

               // analizziamo il messaggio di rispsota dello Slave
               for(int i=0; i < sdata_wi.len; i++) 
                  sRxBuffer[i] = sdata_wi.data[i];

               num_pkt_received = 0;

               flag_Rx_message_wireless  = 2;
     
               count_Rx_wi++;      // contatore messaggi ricevuti buoni

            break;

            case TX_WIRELESS_IN_PROGRESS:

               if(sdata_wi.num_packet <= sdata_wi.tot_packet) 
               {
                  wait_to_analayzer_message = 2; // ogni 18ms inviamo un messaggio
                  
                  if(sdata_wi.num_repeat_tx == 0) 
                  {
                      
                      sdata_wi.num_repeat_tx = 1;
                      
                      for(int i=3; i < 32; i++)
                          tx_buf_pkt[i] = 0;
    
                      tx_buf_pkt[IHMW_ID_DEVICE_LO] = sdata_wi.deviceId & 0xFF;
                      tx_buf_pkt[IHMW_ID_DEVICE_HI] = (sdata_wi.deviceId >> 8) & 0xFF;
                      //bit[7..4]-> Totale Pachetti, bit[3..0]-> Numero pacchetto del messaggio.
                      tx_buf_pkt[IHMW_PACKET]    = ((sdata_wi.tot_packet << 4) & 0xF0);
                      tx_buf_pkt[IHMW_PACKET]   |= (sdata_wi.num_packet & 0x0F);
    
                      if(sdata_wi.len > NUM_BYTE_PACKET)
                          tx_buf_pkt[IHMW_LEN_DATA]  = NUM_BYTE_PACKET;
                      else
                          tx_buf_pkt[IHMW_LEN_DATA]  = (sdata_wi.len % NUM_BYTE_PACKET);
    
                      cksum_8 += tx_buf_pkt[IHMW_ID_DEVICE_LO];
                      cksum_8 += tx_buf_pkt[IHMW_ID_DEVICE_HI];
                      cksum_8 += tx_buf_pkt[IHMW_PACKET];
                      cksum_8 += tx_buf_pkt[IHMW_LEN_DATA];
    
                      for(int i=0; i < tx_buf_pkt[IHMW_LEN_DATA]; i++) {
                          tx_buf_pkt[i + IHMW_START_DATA] = sdata_wi.data[sdata_wi.pos_data_tx++];
                          cksum_8 += tx_buf_pkt[i + IHMW_START_DATA];
                      }
    
                      tx_buf_pkt[IHMW_CKSUM_8] = cksum_8;  // il 32 Byte
    
                      Send_Packet(W_TX_PAYLOAD_NOACK_CMD, tx_buf_pkt, 32);

                  }else {
                      // Secondo invio. Migliora il livello di comunicazione.                     
                      Send_Packet(W_TX_PAYLOAD_NOACK_CMD, tx_buf_pkt, 32);
                      
					  sdata_wi.num_packet++;
                      sdata_wi.len -= tx_buf_pkt[IHMW_LEN_DATA];
                      sdata_wi.num_repeat_tx    = 0;
                  }
            
               }else {
                  SwitchToRxMode();  //switch to rx mode
 
                  sdata_wi.status = BUFF_WIRELESS_EMPY;
                  sdata_wi.len = 0;
                  sdata_wi.pos_data_tx = 0;
                  
                  wait_to_analayzer_message = 1;  
                  
                  if (count_Tx_wi >= 4) {
                     sdata_wi.level_signal = count_Rx_wi;
                     count_Rx_wi = 0;
                     count_Tx_wi = 1;
                  }else                    
                     count_Tx_wi++;
              }  
           break;        
        } 
    }
}

//-------------------------------------------------
// La funzione gestisce il traffico dei messaggi in 
// wireless, Ã¨ temporizzata (sample= 9ms)
//-------------------------------------------------
//void management_message_wi_ori(unsigned long tmr_mills)
//{
//    byte cksum_8;    
//    int len;
//    
//    if (((tmr_mills - tmr_mills_polling_func_rfm  ) >= 9) 
//       ||(tmr_mills_polling_func_rfm  > tmr_mills)) 
//    {         
//        tmr_mills_polling_func_rfm  = tmr_mills; 
//        
//        // per la lettura del buffer in ricezione andiamo al massimo 9ms,
//        // mentre per la scrittura raddopiamo il tempo di attesa
//        if(wait_to_analayzer_message)
//            wait_to_analayzer_message--;
//             
//        switch(sdata_wi.status)
//        {
//            case WIRELESS_DISABLE:
//            default:
//               // in caso che si utilizza la seriale non serve monitorare il modulo Wireless
//               num_pkt_received         = 0; 
//               flag_Rx_message_wireless = 0;     
//               sdata_wi.status = WIRELESS_DISABLE;
//            break;
//      
//            case BUFF_WIRELESS_EMPY:
//            case RX_WIRELESS_IN_PROGRESS:       
//               ReceivePacket();
//            break;
//
//            case RX_WIRELESS_END:
//               ReceivePacket(); // scarichiamo il buffer da eventuali eco
//
//               // analizziamo il messaggio di rispsota dello Slave
//               for(int i=0; i < sdata_wi.len; i++) 
//                  sRxBuffer[i] = sdata_wi.data[i];
//                           
//               num_pkt_received = 0;              
//
//               flag_Rx_message_wireless  = 2;
//			   wait_to_analayzer_message = 2;
//     
//               count_Rx_wi++;      // contatore messaggi ricevuti buoni
//
//            break;
//
//            case TX_WIRELESS_IN_PROGRESS: 
//               if(sdata_wi.num_packet <= sdata_wi.tot_packet) 
//               {
//                  wait_to_analayzer_message = 2; // ogni 18ms inviamo un messaggio
//                  
//                  if(sdata_wi.num_repeat_tx == 0) 
//                  {
//                      
//                      sdata_wi.num_repeat_tx = 1;
//                      
//                      for(int i=3; i < 32; i++)
//                          tx_buf_pkt[i] = 0;
//    
//                      tx_buf_pkt[IHMW_START_MSG] = 's';
//                      tx_buf_pkt[IHMW_ID_DEVICE] = 0x01;
//                      //bit[7..4]-> Totale Pachetti, bit[3..0]-> Numero pacchetto del messaggio.
//                      tx_buf_pkt[IHMW_PACKET]    = ((sdata_wi.tot_packet << 4) & 0xF0);
//                      tx_buf_pkt[IHMW_PACKET]   |= (sdata_wi.num_packet & 0x0F);
//    
//                      if(sdata_wi.len > NUM_BYTE_PACKET)
//                          tx_buf_pkt[IHMW_LEN_DATA]  = NUM_BYTE_PACKET;
//                      else
//                          tx_buf_pkt[IHMW_LEN_DATA]  = (sdata_wi.len % NUM_BYTE_PACKET);
//    
//                      cksum_8  = tx_buf_pkt[IHMW_START_MSG];
//                      cksum_8 += tx_buf_pkt[IHMW_ID_DEVICE];
//                      cksum_8 += tx_buf_pkt[IHMW_PACKET];
//                      cksum_8 += tx_buf_pkt[IHMW_LEN_DATA];
//    
//                      for(int i=0; i < tx_buf_pkt[IHMW_LEN_DATA]; i++) {
//                          tx_buf_pkt[i + IHMW_START_DATA] = sdata_wi.data[sdata_wi.pos_data_tx++];
//                          cksum_8 += tx_buf_pkt[i + IHMW_START_DATA];
//                      }
//    
//                      tx_buf_pkt[IHMW_CKSUM_8] = cksum_8;  // il 32 Byte
//    
//                      Send_Packet(W_TX_PAYLOAD_NOACK_CMD, tx_buf_pkt, 32);
//                     
//                  }else {
//                      // Secondo invio. Migliora il livello di comunicazione.                     
//                      Send_Packet(W_TX_PAYLOAD_NOACK_CMD, tx_buf_pkt, 32);
//                      
//                      sdata_wi.num_packet++;
//                      sdata_wi.len -= tx_buf_pkt[IHMW_LEN_DATA];
//                      sdata_wi.num_repeat_tx    = 0;
//                  }
//            
//               }else {
//                  SwitchToRxMode();  //switch to rx mode
// 
//                  sdata_wi.status = BUFF_WIRELESS_EMPY;
//                  sdata_wi.len = 0;
//                  sdata_wi.pos_data_tx = 0;
//                  
//                  wait_to_analayzer_message = 1;  
//                  
//                  if(count_Tx_wi >= 4) {
//                     sdata_wi.level_signal = count_Rx_wi;
//                     count_Rx_wi = 0;
//                     count_Tx_wi = 1;
//                  }else                    
//                     count_Tx_wi++;
//              }  
//           break;        
//        } 
//    }
//}

/*******************************************************************                                                                 
                                                                 
  Name:  Read_Message                                         
   
  Description:
    Analizza se vi sono messaggi in ricezione.
    Tempo di ricezione di 1 byte ÃƒÂ¨ circa 1,05ms.
        
                                                                      
  Return:
    Value statusRX |            Description
   ----------------+-----------------------------------------
         > 1           Ricezione OK , Lunghezza del Messaggio
          1            RUN_DOWNLOAD
          0            BUFFER EMPY nessun messaggio.
         -1            ERROR_HEAD_MESSAGE
         -2            ERROR_LEN_MESSAGE
         -3            ERROR_CKSUM_16
         
 *******************************************************************/          
int Read_Message()
{  
    word Cksum16, Cksum16_calc;
    int  Byte_aval = 0;
    int  i, len;
    int  crcLoIndex;

    if(flag_Rx_message_wireless) {
       // Ã¨ arrivato un messaggio tramite wireless, andiamo ad analizzarlo.
       flag_Rx_message_wireless = 0;
	   sdata_wi.status  = BUFF_WIRELESS_EMPY;

       return (int)sdata_wi.len; 
    }  
  
    //Byte_aval	= Serial0.available();
    Byte_aval	= nBytesRead;

    // se abbiamo ricevuto dei caratteri, attendiamo la fine del messaggio prima di andare a scaricarlo.
    if (Byte_aval)
    {
		

        if (Byte_aval != rx_buf_tail)
	{
	    // finchÃƒÂ¨ il numero di caratteri aumenta aspetta ad andare a scaricare
	    // il messaggio.
	    rx_buf_tail = Byte_aval;
	    return RUN_DOWNLOAD; // aquisizione del messaggio in corso, aspettiamo di che finisca.
	}            
    }
    else
    { 
	 if (rx_buf_tail == 0)
	    return BUFFER_RX_EMPY; // BUFFER EMPY     
    }  
   
    //--------------------------------------------------------------------
    // Abbiamo ricevuto un messaggio, andiamo a verificare se ÃƒÂ¨ corretto
    //---------------------------------------------------------------------
   
    //len = (rx_buf_tail % RX_BUFFER_SIZE); FLEXCOM0_USART_ReadBufferSizeGet(void)
    len = (rx_buf_tail % FLEXCOM0_USART_ReadBufferSizeGet( ));
    rx_buf_tail = 0;
   
    // scarichiamo il messaggio
    for(i=0; i < len; i++) 
      //sRxBuffer[i] = Serial0.read();
        sRxBuffer[i] = rxBuffer[i];
    
    nBytesRead = 0;
    memset ( rxBuffer, 0, sizeof (rxBuffer));
    
    // 1. Verifichiamo L'intestazione del messaggio.
    if((sRxBuffer[IHM1_START_MSG_0] != PROTO_START_MSG_0) || (sRxBuffer[IHM1_START_MSG_1] != PROTO_START_MSG_1))
    {
#if KTS_DEBUG == 1
        gKTSGlobal.KTSDebug_MessageErrorHeadCount++;
#endif
	return ERROR_HEAD_MESSAGE;
    }
     
    // 2. Verifichaimo la lunghezza del messaggio.
    crcLoIndex	= sRxBuffer[ IHM1_POS_CRC_LO ];
    if ((crcLoIndex + 2 != len) || (len <= IHM1_START_DATA))
    {
#if KTS_DEBUG == 1
	gKTSGlobal.KTSDebug_MessageErrorLenCount++;
#endif
	return  ERROR_LEN_MESSAGE;
    }
   
    // 3. Verifichiamo il cksum_16 del messaggio
    Cksum16 = (word) ((word) sRxBuffer[ crcLoIndex + 1 ] << 8) | sRxBuffer[ crcLoIndex ];
    Cksum16_calc = calc_cksum_16( sRxBuffer, crcLoIndex );

     // ÃƒÂ¨ arrivata la richiesta di inviare i dati di debug
    if (Cksum16 != Cksum16_calc)  
    {
#if KTS_DEBUG == 1
	gKTSGlobal.KTSDebug_MessageErrorCRCCount++;
#endif
	return  ERROR_CKSUM_16;
    }
    
#if KTS_DEBUG == 1
    gKTSGlobal.KTSDebug_MessageRXCount++;
#endif
    return len;
 
 }

/**************
 *   E O F
 *************/
 
 
 
 


