#include "CLInfoForm.h"

#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLAccessory.h"
#include "RDEeprom.h"
#include "CLTouch.h"
#include "CLImages.h"

#define	CLInfoForm_DeviceID_Caption_Point			4, 28
#define	CLInfoForm_DeviceID_Caption_Length			20
#define	CLInfoForm_DeviceID_Value_Point				165, 28
#define	CLInfoForm_DeviceID_Value_Length			18

#define	CLInfoForm_SerialNumber_Caption_Point		4, 42
#define	CLInfoForm_SerialNumber_Caption_Length		20
#define	CLInfoForm_SerialNumber_Value_Point			165, 42
#define	CLInfoForm_SerialNumber_Value_Length		18

#define	CLInfoForm_FirmwareVersion_Caption_Point	4, 56
#define	CLInfoForm_FirmwareVersion_Caption_Length	20
#define	CLInfoForm_FirmwareVersion_Value_Point		165, 56
#define	CLInfoForm_FirmwareVersion_Value_Length		18

#define	CLInfoForm_SoftwareVersionMB_Caption_Point	4, 70
#define	CLInfoForm_SoftwareVersionMB_Caption_Length	20
#define	CLInfoForm_SoftwareVersionMB_Value_Point	165, 70
#define	CLInfoForm_SoftwareVersionMB_Value_Length	18

#define	CLInfoForm_HardwareVersionMB_Caption_Point	4, 84
#define	CLInfoForm_HardwareVersionMB_Caption_Length	20
#define	CLInfoForm_HardwareVersionMB_Value_Point	165, 84
#define	CLInfoForm_HardwareVersionMB_Value_Length	18

#define	CLInfoForm_UnitType_Caption_Point			4, 98
#define	CLInfoForm_UnitType_Caption_Length			20
#define	CLInfoForm_UnitType_Value_Point				165, 98
#define	CLInfoForm_UnitType_Value_Length			18

#define	CLInfoForm_KTSFunctionality_Caption_Point	4, 112
#define	CLInfoForm_KTSFunctionality_Caption_Length	20
#define	CLInfoForm_KTSFunctionality_Value_Point		165, 112
#define	CLInfoForm_KTSFunctionality_Value_Length	18

#define	CLInfoForm_Counter_Caption_Point			4, 126
#define	CLInfoForm_Counter_Caption_Length			20
#define	CLInfoForm_Counter_Value_Point				165, 126
#define	CLInfoForm_Counter_Value_Length				18

#define	CLInfoForm_Probes_Caption_Point				4, 140
#define	CLInfoForm_Probes_Caption_Length			20
#define	CLInfoForm_Probes_Value_Point				165, 140
#define	CLInfoForm_Probes_Value_Length				18

//#define	CLInfoForm_Qr_Code_Rectangle		        85, 25, 235, 175
#define	CLInfoForm_Qr_Code_Rectangle		        85, 3, 260, 178
#define	CLInfoForm_Avensys_Rectangle		        10, 25, 80, 175

//const char* text1 = "Avensys SRL, KTS board ver2.35 , Rd ver 2.33";
const char* text1 = "FFFF|999900131211433001|232|235|040|1|FFFF|4|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|1666010602xFF1|1666010602xFF2|1666010602xFF3|1666010602xFF4|1666010602xFF5|1666010602xFF6|1666010602xFF7|1666010602xFF8|1666010602xFF9|1666010602xFF0|1666010602xFFA|1666010602xFF2|1666010602xFFB|1666010602xFFC|1666010602xFFD|1666010602xFFE|1666010602xFFF|1666010602xFFC|1666010602xFFD|1666010602xFFE|1666010602xFFF|";
//const char* text1 = "FFFF|999900131211433001|232|235|040|1|FFFF|4|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|FF|1666010602xFF1|1666010602xFF2|1666010602xFF3|1666010602xFF4|1666010602xFF5|1666010602xFF6|1666010602xFF7|1666010602xFF8|1666010602xFF9|1666010602xFF0|1666010602xFFA|1666010602xFF2|1666010602xFFB|1666010602xFFC|1666010602xFFD|1666010602xFFE|1666010602xFFF|1666010602x";
//char text1 [450];
char text2 [550];
basE91 Kts_Base;
char* Pointer1 = NULL;

unsigned short Image_Qr_Code[ 22500 ];
enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level
//uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX]; //////////////////
//uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX]; ///////////////

uint8_t qrcode[1]; //////////////////
uint8_t tempBuffer[1]; ///////////////

/*CLImage	Qr_Code_MonoImage( CLImage::ImageType_16Bit_565,
	CLImage_Qr_Code_Width,
	CLImage_Qr_Code_Height,
	(const unsigned char*)Image_Qr_Code );*/

void printQr(const uint8_t qrcode[])
{
    int size = qrcodegen_getSize(qrcode);
	int border = 4;
    int Pixel_Ratio = (CLImage_Qr_Code_Width - 8) / size;
    int Pixel_Ratio_Remain = (CLImage_Qr_Code_Width - 8) % size;
    int Count_Pixel = 0;
    int y;
    int x;
    
    memset ( Image_Qr_Code, 0xFF, sizeof (Image_Qr_Code));
	for ( y = -border; y < size + border; y++) {
        if (( y < 0) || ( y >= size ))
            {
                for ( int z = 0; z < CLImage_Qr_Code_Width; z++ )
                    {
                        Image_Qr_Code[Count_Pixel] = 0xFFFF;
                        Count_Pixel++;
                    }
            }
        else
            {
                if ( y == 0)
                {
                    if ( (Pixel_Ratio_Remain / 2) != 0 )
                    {
                      for ( int z = 0; z < Pixel_Ratio_Remain / 2; z++ )
                        {
                            for ( int j = 0; j < CLImage_Qr_Code_Width; j++ )
                            {
                                Image_Qr_Code[Count_Pixel] = 0xFFFF;
                                Count_Pixel++;
                            }
                        }  
                    }
                }
                for (int h = 0; h < Pixel_Ratio; h++)
                {
                    for ( x = -border; x < size + border; x++)
                        {
                            if (( x < 0) || ( x >= size ))
                                {
                                    Image_Qr_Code[Count_Pixel] = 0xFFFF;
                                    Count_Pixel++;
                                }
                            else
                                {
                                    if ( x == 0)
                                    {
                                        if ( (Pixel_Ratio_Remain / 2) != 0 )
                                        {
                                          for ( int z = 0; z < Pixel_Ratio_Remain / 2; z++ )
                                            {
                                                Image_Qr_Code[Count_Pixel] = 0xFFFF;
                                                Count_Pixel++;
                                            }  
                                        }
                                    }
                                    for (int j = 0; j < Pixel_Ratio; j++)
                                    {
                                        if (qrcodegen_getModule(qrcode, x, y) == true)
                                            Image_Qr_Code[Count_Pixel] = 0;
                                        else
                                            Image_Qr_Code[Count_Pixel] = 0xFFFF;

                                        Count_Pixel++;
                                    }
                                    if ( x == (size - 1))
                                        {
                                            Count_Pixel = Count_Pixel + (Pixel_Ratio_Remain / 2) + (Pixel_Ratio_Remain % 2);
                                        }
                                }
                        }
                }
            }
	}
    
    border = 0;
}

CLFormResult CLInfoForm_Open()
{
	CLInfoForm	form;

	return form.Open();
}

// =============================================================================
// CLInfoForm [class]
// -----------------------------------------------------------------------------
CLInfoForm::CLInfoForm()
	: m_Page( 3 )
{
	m_HomeButtonRectangle.Set( ::Form_HomeButtonRectangle );
	m_PreviousButtonRectangle.Set( ViewForm_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( ViewForm_NextButtonRectangle );
    m_Qr_Code_Rectangle.Set( CLInfoForm_Qr_Code_Rectangle );
    m_Avensys_Rectangle.Set(CLInfoForm_Avensys_Rectangle);
}

CLFormResult CLInfoForm::Open()
{
	int				touchX, touchY;
	CLFormResult	formResult;
	short			accessoryCount	= 0;

	for (int accessoriesCounter = 0; accessoriesCounter < 32; accessoriesCounter++)
	{
		if (Accessory_IsPresent( accessoriesCounter ))
		{
			if ((accessoryCount % CLInfoForm_AccessoryPerPage) == 0)
				m_AccessoryPageStartIndexes[ accessoryCount / CLInfoForm_AccessoryPerPage ]	= accessoriesCounter;
			accessoryCount++;
		}
	}

	m_Page.SetPageCount( 2 + (accessoryCount / CLInfoForm_AccessoryPerPage) +
		(accessoryCount % CLInfoForm_AccessoryPerPage > 0 ? 1 : 0) );

	RenderPage();

	while (true)
	{
		// Processa le funzionalitÃ  del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
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
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLInfoForm::RenderPage()
{
	char	text[ 40 ];
	char*	pageTitle	= NULL;

	// Clear screen
	gLCD.clrScr();

	// Draw Data Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Tasto Previous
    CLLCDCommon::DrawPreviousButton( m_PreviousButtonRectangle, GenericButtonStyle_Normal_BigFont );

	// Tasto Next
    CLLCDCommon::DrawNextButton( m_NextButtonRectangle, GenericButtonStyle_Normal_BigFont );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );
	gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );

	switch (m_Page.GetValue())
	{
		case 0:
		{
			// Imposta il titolo della pagina
			pageTitle	= (char*) CLLocalitation::GetText( CLTextId_INFO );

			// DeviceID
			strcpy( text, "DEVICE ID" );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_DeviceID_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_DeviceID_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			sprintf( text, "%u", gKTSEeprom.GetDeviceID() );
			CLGraphics::DrawText( CLInfoForm_DeviceID_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text, CLInfoForm_DeviceID_Value_Length );

			// Serial number
			strcpy( text, CLLocalitation::GetText( CLTextId_SERIAL_ID ) );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_SerialNumber_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_SerialNumber_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			strncpy( text, (char*) gRDEeprom.SerialString, sizeof(gRDEeprom.SerialString) );
			text[ sizeof(gRDEeprom.SerialString) ]	= '\0';
			CLGraphics::DrawText( CLInfoForm_SerialNumber_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text, CLInfoForm_SerialNumber_Value_Length );

			// Firmware Version
			strcpy( text, CLLocalitation::GetText( CLTextId_FIRMWARE_VERSION ) );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_FirmwareVersion_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_FirmwareVersion_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			CLGraphics::DrawText( CLInfoForm_FirmwareVersion_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				FirmwareVersion, CLInfoForm_FirmwareVersion_Value_Length );
			
			// SOFTWARE VERSION MB
			strcpy( text, CLLocalitation::GetText( CLTextId_MB_SOFTWARE_VERSION ) );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_SoftwareVersionMB_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_SoftwareVersionMB_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			CLKTS::SWVers_GetText( text );
			CLGraphics::DrawText( CLInfoForm_SoftwareVersionMB_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text, CLInfoForm_SoftwareVersionMB_Value_Length );

			// HARDWARE VERSION MB
			strcpy( text, CLLocalitation::GetText( CLTextId_MB_HARDWARE_VERSION ) );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_HardwareVersionMB_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_HardwareVersionMB_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			CLKTS::HWVers_GetText( text );
			CLGraphics::DrawText( CLInfoForm_HardwareVersionMB_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text, CLInfoForm_HardwareVersionMB_Value_Length );

			// Tipo unita'
			strcpy( text, CLLocalitation::GetText( CLTextId_UNIT_TYPE ) );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_UnitType_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_UnitType_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			CLKTS::UnitType_GetText( text );
			CLGraphics::DrawText( CLInfoForm_UnitType_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text, CLInfoForm_UnitType_Value_Length );

			// KTS Type
			strcpy( text, "KTS" );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_KTSFunctionality_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_KTSFunctionality_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			CLKTS::TypeFunc_GetText( text );
			CLGraphics::DrawText( CLInfoForm_KTSFunctionality_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text, CLInfoForm_KTSFunctionality_Value_Length );

			// Conta Ore
			strcpy( text, CLLocalitation::GetText( CLTextId_COUNTER ) );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_Counter_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_Counter_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			sprintf( text, "%d", gRDEeprom.hour_runnig );
			CLGraphics::DrawText( CLInfoForm_Counter_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text, CLInfoForm_Counter_Value_Length );

			// Num Sonde
			strcpy( text, CLLocalitation::GetText( CLTextId_PROBES ) );
			CLCommon::String_AppendCharacters( text, '.', CLInfoForm_Probes_Caption_Length );
			CLGraphics::DrawText( CLInfoForm_Probes_Caption_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text );

			sprintf( text, "%d", gRDEeprom.numNTC );
			CLGraphics::DrawText( CLInfoForm_Probes_Value_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_BorderRound_No,
				RGBColor_Black, RGBColor_White,
				text, CLInfoForm_Probes_Value_Length );

			break;
		}

		// Page 1 ... n : Accessories
		default:
		{
			int	currentX			= 20;
			int	currentY			= 40;
			int accessoryRowCounter	= 0;
			int	accessoryIndex		= m_AccessoryPageStartIndexes[ m_Page.GetValue() - 2 ]; // -1
			int	accessoryPageCount	= 0;

			// Imposta il titolo della pagina
			pageTitle	= (char*) CLLocalitation::GetText( CLTextId_ACCESSORY );

			// Visualizza gli accessori
			while (accessoryIndex < AccessoryCount && accessoryPageCount < CLInfoForm_AccessoryPerPage)
			{
				if (Accessory_IsPresent( accessoryIndex ))
				{
					gLCD.print( AccessoryNames[ accessoryIndex ], currentX, currentY );
					accessoryRowCounter++;

					if (accessoryRowCounter == 3)
					{
						accessoryRowCounter	= 0;
						currentY			+= 16;
						currentX			= 20;
					}
					else
						currentX	+= 100;

					accessoryPageCount++;
				}
				accessoryIndex++;
			}
			break;
		}
        
        case 1: // QR  code
        {
          // Imposta il titolo della pagina
			//pageTitle	= (char*) CLLocalitation::GetText( CLTextId_QR_CODE );
            
            //memset ( text1, 0, sizeof ( text1));
            memset ( text2, 0, sizeof ( text2));
            memset ( text, 0, sizeof ( text));
            /*sprintf( text, "%u", gKTSEeprom.GetDeviceID() );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // DEVICE_ID
            memset ( text, 0, sizeof ( text));
            strcat ( text1, (char*) gRDEeprom.SerialString );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // SERIAL_ID
            strcat ( text1, (char*) FirmwareVersion );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // FIRMWARE_VERSION
            CLKTS::SWVers_GetText( text );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // SOFTWARE_VERSION
            memset ( text, 0, sizeof ( text));
            CLKTS::HWVers_GetText( text );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // HARDWARE_VERSION
            memset ( text, 0, sizeof ( text));
            CLKTS::TypeFunc_GetText( text );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // KTS
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%d", gRDEeprom.hour_runnig );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // COUNTER
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%d", gRDEeprom.numNTC );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // PROBES
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gRDEeprom.AccessoyHW[0] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // AccessoyHW[0]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gRDEeprom.AccessoyHW[1] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // AccessoyHW[1]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gRDEeprom.AccessoyHW[2] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // AccessoyHW[1]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gRDEeprom.AccessoyHW[3] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // AccessoyHW[1]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%d", gRDEeprom.depotMotors );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // AccessoyHW[1]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[0] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[0]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[1] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[1]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[2] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[2]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[3] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[3]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[4] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[4]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[5] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[5]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[6] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[6]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[7] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[7]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[8] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[8]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[9] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[9]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[10] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[10]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[11] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[11]
            memset ( text, 0, sizeof ( text));
            sprintf( text, "%02X", gKTSData.Events[12] );
            strcat ( text1 , text ); strcat ( text1 , "|" ); // Alarm[12]*/
            
            /*basE91_init(&Kts_Base);
            basE91_encode(&Kts_Base, &text1[0], strlen(text1), &text2[0]);
            Pointer1 = &text2[0];
            Pointer1 += strlen ( text2 );
            basE91_encode_end(&Kts_Base, Pointer1);*/
            
            /*bool ok = qrcodegen_encodeText(text1, tempBuffer, qrcode, errCorLvl, qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
            if ( ok )
              printQr( qrcode );*/
            
            CLGraphics::DrawBoxWithDrawer( m_Qr_Code_Rectangle, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &Qr_Code_MonoImage ); // Qr_Code_MonoImage
            CLGraphics::DrawBoxWithDrawer( m_Avensys_Rectangle, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &Avensys_Image );
            
          break;  
        }
	}

	// Display Title
	//RenderFormTitle( pageTitle, &m_Page ); //////
}

// -----------------------------------------------------------------------------
// CLInfoForm [class]
// =============================================================================


