#include "CLAccessoryManagerForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLTouch.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"

#define	CLAccessoryManagerForm_BackButtonRectangle			10, 190, 80, 229

//#define	CLAccessoryManagerForm_Accessory1ButtonRectangle	10, 35, 99, 66
//#define	CLAccessoryManagerForm_Accessory2ButtonRectangle	115, 35, 204, 66
//#define	CLAccessoryManagerForm_Accessory3ButtonRectangle	220, 35, 309, 66
//#define	CLAccessoryManagerForm_Accessory4ButtonRectangle	10, 85, 99, 116
//#define	CLAccessoryManagerForm_Accessory5ButtonRectangle	115, 85, 204, 116
//#define	CLAccessoryManagerForm_Accessory6ButtonRectangle	220, 85, 309, 116
//#define	CLAccessoryManagerForm_Accessory7ButtonRectangle	10, 134, 99, 165
//#define	CLAccessoryManagerForm_Accessory8ButtonRectangle	115, 134, 204, 165
//#define	CLAccessoryManagerForm_Accessory9ButtonRectangle	220, 134, 309, 165

#define	CLAccessoryManagerForm_Accessory1ButtonRectangle	6, 35, 103, 66
#define	CLAccessoryManagerForm_Accessory2ButtonRectangle	111, 35, 208, 66
#define	CLAccessoryManagerForm_Accessory3ButtonRectangle	216, 35, 313, 66
#define	CLAccessoryManagerForm_Accessory4ButtonRectangle	6, 85, 103, 116
#define	CLAccessoryManagerForm_Accessory5ButtonRectangle	111, 85, 208, 116
#define	CLAccessoryManagerForm_Accessory6ButtonRectangle	216, 85, 313, 116
#define	CLAccessoryManagerForm_Accessory7ButtonRectangle	6, 134, 103, 165
#define	CLAccessoryManagerForm_Accessory8ButtonRectangle	111, 134, 208, 165
#define	CLAccessoryManagerForm_Accessory9ButtonRectangle	216, 134, 313, 165
#define CLAccessoryManagerForm_Disconect_All_ButtonRectangle    60, 65, 260, 135

CLFormResult CLAccessoryManagerForm_Open( unsigned short options )
{
	CLAccessoryManagerForm	form;

	return form.Open( options );
}

// =============================================================================
// CLAccessoryManagerForm [class]
// -----------------------------------------------------------------------------
CLAccessoryManagerForm::CLAccessoryManagerForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( CLAccessoryManagerForm_BackButtonRectangle );
	m_PreviousButtonRectangle.Set( ViewForm_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( ViewForm_NextButtonRectangle );

	m_DisplayedAccessoryButtonRectangles[ 0 ].Set( CLAccessoryManagerForm_Accessory1ButtonRectangle );
	m_DisplayedAccessoryButtonRectangles[ 1 ].Set( CLAccessoryManagerForm_Accessory2ButtonRectangle );
	m_DisplayedAccessoryButtonRectangles[ 2 ].Set( CLAccessoryManagerForm_Accessory3ButtonRectangle );
	m_DisplayedAccessoryButtonRectangles[ 3 ].Set( CLAccessoryManagerForm_Accessory4ButtonRectangle );
	m_DisplayedAccessoryButtonRectangles[ 4 ].Set( CLAccessoryManagerForm_Accessory5ButtonRectangle );
	m_DisplayedAccessoryButtonRectangles[ 5 ].Set( CLAccessoryManagerForm_Accessory6ButtonRectangle );
	m_DisplayedAccessoryButtonRectangles[ 6 ].Set( CLAccessoryManagerForm_Accessory7ButtonRectangle );
	m_DisplayedAccessoryButtonRectangles[ 7 ].Set( CLAccessoryManagerForm_Accessory8ButtonRectangle );
	m_DisplayedAccessoryButtonRectangles[ 8 ].Set( CLAccessoryManagerForm_Accessory9ButtonRectangle );
        m_Disconect_All_ButtonRectangle.Set( CLAccessoryManagerForm_Disconect_All_ButtonRectangle );
}

CLAccessoryManagerForm::CLAccessory* CLAccessoryManagerForm::GetAccessory( _NUMBER_ACCESSORY_EEP rdAccessoryIndex )
{
	for (int accessoriesCounter = 0; accessoriesCounter < m_AccessoryCount; accessoriesCounter++)
	{
		if (m_Accessories[ accessoriesCounter ].RDIndex == rdAccessoryIndex)
			return &m_Accessories[ accessoriesCounter ];
	}
	return NULL;
}

CLFormResult CLAccessoryManagerForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Initializza le properties
	RefreshData( true );

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RefreshData( true );
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Home Button
			if (m_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// Back Button
			if (m_BackButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_BackButtonRectangle );
				formResult	= CLFormResult_Back;
				break;
			}
			else
                // Next Button
                if (m_NextButtonRectangle.Contains( touchX, touchY ))
                {
                    CLLCDCommon::WaitButton( m_NextButtonRectangle );

                    if (m_Page.GoNext())
                        RenderPage();
                }
                else
                    // Previous Button
                    if (m_PreviousButtonRectangle.Contains( touchX, touchY ))
                    {
                        CLLCDCommon::WaitButton( m_PreviousButtonRectangle );

                        if (m_Page.GoPrevious())
                            RenderPage();
                    }
                    else
                    {
                        if ( m_Page.GetValue() < ( m_Page.GetPageCount() - 1) )
                        {
                        short	pressedAccessoryIndex	= -1;

                        for (int displayedAccessoriesCounter = 0; displayedAccessoriesCounter < m_DisplayedAccessoryCount; displayedAccessoriesCounter++)
                        {
                            if (m_DisplayedAccessoryButtonRectangles[ displayedAccessoriesCounter ].Contains( touchX, touchY ))
                            {
                                pressedAccessoryIndex	= m_DisplayedAccessoryStartIndex + displayedAccessoriesCounter;
                                break;
                            }
                        }

                        if (pressedAccessoryIndex != -1 && m_Accessories[ pressedAccessoryIndex ].Present)
                        {
                            if (CLMessageBoxForm::Open( CLMessageBoxButtons_YesNo, CLMessageBoxGravity_Question,
                                CLLocalitation::GetText( CLTextId_REMOVE_ACCESSORY ), CLLocalitation::GetText( CLTextId_CONFIRM_REMOVE ) ) == CLMessageBoxResult_Yes)
                            {
                                RemoveAccessory( options, pressedAccessoryIndex );
                            }
                            RefreshData( true );
                        }
                        else
                            WaitForTouchRelease();
                        }

                        else
                        {
                            if (m_Disconect_All_ButtonRectangle.Contains( touchX, touchY ))
                                {
                                         if (CLMessageBoxForm::Open( CLMessageBoxButtons_YesNo, CLMessageBoxGravity_Question,
                                                "", " ETES VOUS SURE ?" ) == CLMessageBoxResult_Yes)
                                            {
                                                RemoveAccessory( options, 1);
                                            }
                                            RefreshData( true );
                                }
                        }
                    }
		}
    }


	return formResult;
}

void CLAccessoryManagerForm::RemoveAccessory( unsigned short options, short accessoryIndexToRemove )
{
	ComQueue_Status	writeEeprom_Status;
	byte			accessoryHW[ 4 ];
    byte			accessoryHW1[ 4 ];

	if (accessoryIndexToRemove < 0 || accessoryIndexToRemove >= m_AccessoryCount)
		return;

	// Visualizza il messaggio di scrittura in corso   Affiche le message d'écriture en cours
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente lo stato degli accessory  Enregistrer temporairement l'état des accessoires
	memcpy( accessoryHW, gRDEeprom.AccessoyHW, sizeof(gRDEeprom.AccessoyHW) );
        
        if ( m_Page.GetValue() < ( m_Page.GetPageCount() - 1) )
          {
        	// Rimuove l'accessorio dalla eeprom,  Supprime l'accessoire de l'eeprom
        	Accessory_Set( m_Accessories[ accessoryIndexToRemove ].RDIndex, false );
          }
        else
          {
            accessoryHW1[0] = 0x40;
            accessoryHW1[1] = 0x1C;
            accessoryHW1[2] = 0x00; // accessoryHW1[2] = 0x00
            accessoryHW1[3] = 0x00; // accessoryHW1[3] = 0x00
            memcpy( gRDEeprom.AccessoyHW, accessoryHW1, sizeof(gRDEeprom.AccessoyHW) );
          }  

	// Accoda la richiesta di WriteEeprom   Mettre en file d'attente la requête WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, AccessoyHW ),
		sizeof(gRDEeprom.AccessoyHW),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta   Attendez que votre demande soit traitée
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home  Si ça n'a pas marché, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente  Restaurer la valeur précédente
		memcpy( gRDEeprom.AccessoyHW, accessoryHW, sizeof(gRDEeprom.AccessoyHW) );

		// Visualizza il messaggio di errore   Affiche le message d'erreur
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError();
	}
	else
	{
		// Visualizza il messaggio di ok  Affiche un message ok
		if (CLFormOption_CanShowWriteMessage_Success( options ))
			CLLCDCommon::WriteDataPanel_DisplaySuccess();
	}
}

void CLAccessoryManagerForm::RenderPage()
{
	int		accessoryIndex	= m_Page.GetValue() * AccessoryPerPage;

	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( m_HomeButtonRectangle.GetX1(), m_HomeButtonRectangle.GetY1() );

	// Display Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Tasto Previous
	CLLCDCommon::DrawPreviousButton( m_PreviousButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Tasto Next
	CLLCDCommon::DrawNextButton( m_NextButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_DISCONNECT_ACCESSORY ),
		&m_Page );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );
        
        if ( m_Page.GetValue() < ( m_Page.GetPageCount() - 1) )
        {
        	// Display Accessories
        	m_DisplayedAccessoryCount		= 0;
        	m_DisplayedAccessoryStartIndex	= accessoryIndex;
        	for (int displayedAccessoriesCounter = 0; displayedAccessoriesCounter < AccessoryPerPage && accessoryIndex < m_AccessoryCount; displayedAccessoriesCounter++, accessoryIndex++)
        	{
        		// Visualizza l'accessory button
        		CLLCDCommon::DrawGenericButton( m_DisplayedAccessoryButtonRectangles[ displayedAccessoriesCounter ],
        			(m_Accessories[ m_DisplayedAccessoryStartIndex + displayedAccessoriesCounter ].Present ? GenericButtonStyle_Normal_BigFont : GenericButtonStyle_Disabled_BigFont),
        			AccessoryNames[ m_Accessories[ m_DisplayedAccessoryStartIndex + displayedAccessoriesCounter ].RDIndex ] );
        
        		m_DisplayedAccessoryCount++;
        	}
        }
        
        else
        {
          CLLCDCommon::DrawGenericButton( m_Disconect_All_ButtonRectangle, GenericButtonStyle_Normal_BigFont_Multiline,"DECONNECTER TOUT");
        }
}

void CLAccessoryManagerForm::RefreshData( bool render )
{
	byte	currentPage	= m_Page.GetValue();
	
	m_AccessoryCount	= 0;
	for (int accessoriesCounter = 0; accessoriesCounter < AccessoryCount; accessoriesCounter++)
	{
#if CUSTOMERID == CUSTOMERID_FA
		if (accessoriesCounter == ACC_EEP_AWP ||
			accessoriesCounter == ACC_EEP_PCAP ||
			accessoriesCounter == ACC_EEP_PCAF)
			continue;
#endif

		if (AccessoryNames[ accessoriesCounter ] &&
			accessoriesCounter != ACC_EEP_INP &&
			accessoriesCounter != ACC_EEP_OUT &&
			accessoriesCounter != ACC_EEP_BPD &&
			accessoriesCounter != ACC_EEP_MBUS &&
			accessoriesCounter != ACC_EEP_RFM)
		{
			m_Accessories[ m_AccessoryCount ].RDIndex	= accessoriesCounter;
			m_Accessories[ m_AccessoryCount ].Present	= Accessory_IsPresent( accessoriesCounter );
			m_AccessoryCount++;
		}
	}
	m_Page.SetPageCount( m_AccessoryCount / AccessoryPerPage + (m_AccessoryCount % AccessoryPerPage > 0 ? 1 : 0) );
        m_Page.SetPageCount ( m_Page.GetPageCount() + 1);
	m_Page.Go( currentPage >= m_Page.GetPageCount() ? 0 : currentPage );

	if (render)
		RenderPage();
}
// -----------------------------------------------------------------------------
// CLAccessoryManagerForm [class]
// =============================================================================

