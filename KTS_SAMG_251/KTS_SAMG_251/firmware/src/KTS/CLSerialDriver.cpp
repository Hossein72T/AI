#ifndef _CLIKTS
/*******************************************************************
 * file: CLSerialDriver.ccp
 *
 * Author/Date: Maurizio Colmone dic.2013
 *
 * Description: Il file gestisce il traffico sulla seriale 1, tramite
 *              il protocollo ser1.
 *
 ******************************************************************/

#include "CLSerialDriver.h"
#include "RDProtocol.h"
#include "CLKTS.h"

//--------------- Var Global -----------------------------
#ifdef EXCLUDED
byte rx_buf_tail = 0;
byte sRxBuffer[ MAX_SERIAL_BUFFER_LENGHT ];
unsigned long gSer1ReceiveResponse_PreviousReceiveMilliseconds = 0;
#endif

//---------------------------------------------------------
// Disabilita la Trasmissione
//--------------------------------------------------------
void DisablePinTX()
{
   //U1STAbits.UTXEN = 0;         // Diabilita il Pin TX1
   //mPORTDSetPinsDigitalIn(BIT_3);
   
   FLEXCOM0_USART_Disable_TX( );
}  

//---------------------------------------------------------
// Abilita la Trasmissione
//--------------------------------------------------------
void EnablePinTX()
{
   //U1STAbits.UTXEN = 1; // abilita il Pin TX1
   
   FLEXCOM0_USART_Enable_TX( );
} 

#ifdef EXCLUDED
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

//---------------------------------------------------------
// Manda un messaggio sulla seriale 1. 
//---------------------------------------------------------
void Write_Message_Ser1(byte *buff)
{
	word Cksum16, len, nByte_available;
	int i;
	
	// testa del messaggio
	buff[IHM1_START_MSG_0] = PROTO_START_MSG_0;
	buff[IHM1_START_MSG_1] = PROTO_START_MSG_1;
   
	// lunghezza del messaggio
	len = buff[IHM1_POS_CRC_LO] + 2; 
	len &= 0x7F; // max 127 byte. 
    
	// calcola il cksum
	Cksum16 = calc_cksum_16( buff,  buff[ IHM1_POS_CRC_LO ] );
   
	buff[ buff[ IHM1_POS_CRC_LO ] ]     = lowByte(Cksum16);
	buff[ buff[ IHM1_POS_CRC_LO ] + 1 ] = highByte(Cksum16);

	// scarico il buffer 
	while(Serial0.available())
		Serial0.read();
	
	Serial0.write(buff, len); 

#if KTS_DEBUG == 1
	gKTSGlobal.KTSDebug_MessageTXCount++;
#endif
}


/*******************************************************************                                                                 
                                                                 
  Name:  Read_Message_Ser1                                          
   
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
int Read_Message_Ser1()
{  
	word Cksum16, Cksum16_calc;
	int  Byte_aval = 0;
	int  i, len;
	int	crcLoIndex;
  
	Byte_aval	= Serial0.available();

	// se abbiamo ricevuto dei caratteri, attendiamo la fine del messaggio prima di andare a scaricarlo.
	if (Byte_aval)
	{
		//unsigned long	currentMillis	= millis();

		//// Se non ha superato il tempo di attesa di 6 ms tra un carattere ricevuto e l'altro, esce
		//if (currentMillis > gSer1ReceiveResponse_PreviousReceiveMilliseconds &&
		//	(currentMillis - gSer1ReceiveResponse_PreviousReceiveMilliseconds) < 6)
		//{
		//	return RUN_DOWNLOAD;
		//}

		//gSer1ReceiveResponse_PreviousReceiveMilliseconds	= currentMillis;

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
   
   len = (rx_buf_tail % RX_BUFFER_SIZE);
   rx_buf_tail = 0;
   
   // scarichiamo il messaggio
   for(i=0; i < len; i++) 
		sRxBuffer[i] = Serial0.read(); 
      
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

#endif
#endif

