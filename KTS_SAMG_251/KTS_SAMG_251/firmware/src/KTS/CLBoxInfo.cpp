#include "CLBoxInfo.h"
#include "CLKTS.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLFonts.h"
#include "CLLocalitation.h"
#include "CLAlarm.h"
#include "CLAccessory.h"
#include "CLLCDCommon.h"
#include "CLBypass.h"
#include "CLImages.h"

const unsigned long BoxInfo_RefreshMilliseconds = 4000;

extern uint8_t CO2_1_Accuracy;
extern uint8_t CO2_2_Accuracy;

#define	CLAccurracy_Rectangle1  9, 171, 16, 183
#define	CLAccurracy_Rectangle2  18, 171, 25, 183
#define	CLAccurracy_Rectangle3  27, 171, 34, 183

#define	CLAccurracy1_Rectangle1  150, 171, 157, 183
#define	CLAccurracy1_Rectangle2  159, 171, 166, 183
#define	CLAccurracy1_Rectangle3  168, 171, 175, 183

#define	CLAccurracynull_Rectangle1  9, 171, 34, 183
#define	CLAccurracy1null_Rectangle1  150, 171, 175, 183

// =============================================================================
// CLBoxInfo [class]
// -----------------------------------------------------------------------------
CLBoxInfo::CLBoxInfo()
{
	m_CurrentShowInfoId	= CLShowInfoId_LASTITEM;
	m_Refresh_Timer		= millis();
	
    m_AccuracyRectangle1.Set( CLAccurracy_Rectangle1 );
    m_AccuracyRectangle2.Set( CLAccurracy_Rectangle2 );
    m_AccuracyRectangle3.Set( CLAccurracy_Rectangle3 );
    
    m_Accuracy1Rectangle1.Set( CLAccurracy1_Rectangle1 );
    m_Accuracy1Rectangle2.Set( CLAccurracy1_Rectangle2 );
    m_Accuracy1Rectangle3.Set( CLAccurracy1_Rectangle3 );
    
    m_AccuracynullRectangle1.Set( CLAccurracynull_Rectangle1 );
    m_Accuracy1nullRectangle1.Set( CLAccurracy1null_Rectangle1 );
    
	//if ( gKTSEeprom.GetDesktopBoxInfo() == 0)
		//m_CurrentShowInfoId = 0;
}

bool CLBoxInfo::RenderInfo( CLShowInfoId showInfoId )
{
	char	text[ 50 ];

	if (m_Rectangle.GetHeight() == 0 || m_Rectangle.GetWidth() == 0)
		return false;

	switch (showInfoId)
	{
		case CLShowInfoId_Fire:
		{
			if (!IsFireAlarm())
				return false;

			if (Alarm_IsActive( ALM_SMOKE_VENT_OFF ))
				CLLCDCommon::RenderFireConfiguration( m_DataRectangle, INP_12V_ALM_FIRE_UNIT_STOP );
			else
			if (Alarm_IsActive( ALM_SMOKE_VENT_MAX ))
				CLLCDCommon::RenderFireConfiguration( m_DataRectangle, INP_12V_ALM_FIRE_VENT_MAX );
			else
			if (Alarm_IsActive( ALM_SMOKE_ONLY_EXT ))
				CLLCDCommon::RenderFireConfiguration( m_DataRectangle, INP_12V_ALM_FIRE_ONLY_EXTRACT );
			else
			if (Alarm_IsActive( ALM_SMOKE_ONLY_SUP ))
				CLLCDCommon::RenderFireConfiguration( m_DataRectangle, INP_12V_ALM_FIRE_ONLY_SUPPLY );

			return true;
		}

		case CLShowInfoId_Boost:
		{
			int	partyMinuteRemaining;

			// Se siamo in modalità boost, visualizza le informazioni di party
			if (!gKTSGlobal.Party_IsEnabled)
				return false;

			partyMinuteRemaining	= (unsigned long) gRDEeprom.Set_TimeBoost - ((CLDateTime::GetNow().GetTotalSeconds() - gKTSGlobal.Party_StartDateTime.GetTotalSeconds()) / 60);

			if (partyMinuteRemaining > 0)
				sprintf( text, "%s\r%d %s", CLLocalitation::GetText( CLTextId_PARTY_MODE ), partyMinuteRemaining, CLLocalitation::GetText( CLTextId_MINUTE_ABBR ) );
			else
				strcpy( text, CLLocalitation::GetText( CLTextId_PARTY_MODE ) );

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;
		}

		case CLShowInfoId_Temperatures_TFresh:
		{
			if (!IsEnabled( CLBoxInfo_InfoId_TFresh ))
				return false;
		
			if (Alarm_IsActive( ALM_PTFRESH_KO ) || gKTSData.Measure_Temp[ I_PROBE_FRESH ] < -40 || gKTSData.Measure_Temp[ I_PROBE_FRESH ] > 70)
			{
				sprintf( text, "%s\r...",
					CLLocalitation::GetText( CLTextId_TFRESH ) );
			}
			else
			{
				sprintf( text, "%s\r%d %cC",
					CLLocalitation::GetText( CLTextId_TFRESH ),
					(short) gKTSData.Measure_Temp[ I_PROBE_FRESH ], FONT_SYMBOL_DEGREES );
			}
			
			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;
		}

		case CLShowInfoId_Temperatures_TReturn:
		{
			if (!IsEnabled( CLBoxInfo_InfoId_TReturn ))
				return false;
		
			if (Alarm_IsActive( ALM_PTRET_KO ) || gKTSData.Measure_Temp[ I_PROBE_RETURN ] < -40 || gKTSData.Measure_Temp[ I_PROBE_RETURN ] > 70)
			{
				sprintf( text, "%s\r...",
					CLLocalitation::GetText( CLTextId_TRETURN ) );
			}
			else
			{
				sprintf( text, "%s\r%d %cC",
					CLLocalitation::GetText( CLTextId_TRETURN ),
					(short) gKTSData.Measure_Temp[ I_PROBE_RETURN ], FONT_SYMBOL_DEGREES );
			}
			
			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;
		}

		case CLShowInfoId_Filters_DPS:

			if (!IsEnabled( CLBoxInfo_InfoId_Filters ))
				return false;

			if (!Function_IsEnabled( ENAB_CTRL_FILTER ))
			{
				sprintf( text, "%s\r%s",
					CLLocalitation::GetText( CLTextId_FILTERS ),
					CLLocalitation::GetText( CLTextId_DISABLE ) );
			}
			else
			{
				long	dayFilterRunning	= (gRDEeprom.hour_runnig - gRDEeprom.time_lastCloggedFilers < 0 ? 0 : (gRDEeprom.hour_runnig - gRDEeprom.time_lastCloggedFilers) / 24);
				long	weekFilterRemaining	= (gRDEeprom.gg_manut_Filter - dayFilterRunning < 0 ? 0 : (gRDEeprom.gg_manut_Filter - dayFilterRunning) / 7);
				
				sprintf( text, "%s\r%d %s",
					CLLocalitation::GetText( CLTextId_FILTERS ),
					weekFilterRemaining,
					CLLocalitation::GetText( CLTextId_WEEK ) );
			}

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;

		case CLShowInfoId_Accessory_PEHD_PHWD:
		{
			char	accessoryName[ 5 ];

			// +-----------+
			// | PEHD:OFF  |
			// |  In ALARM |
			// +-----------+
			if (!IsEnabled( CLBoxInfo_InfoId_Accessories ) ||
				!AccessoryClimaStatus_IsConnected( gKTSDebugData.PreHeater_Status ))
				return false;

			strcpy( accessoryName, (AccessoryClimaStatus_IsAir( gKTSDebugData.PreHeater_Status ) ? AccessoryNames[ ACC_EEP_PEHD ] : AccessoryNames[ ACC_EEP_PHWD ]) );

			// E' spento?
			if (!AccessoryClimaStatus_IsOn( gKTSDebugData.PreHeater_Status ))
			{
				sprintf( text, "%s:OFF", accessoryName );
			}
			// Non e' in allarme?
			else
			if (!AccessoryClimaStatus_InAlarm( gKTSDebugData.PreHeater_Status ))
			{
				sprintf( text, "%s:ON", accessoryName );
			}
			// Ok, e' in allarme
			else
			{
				sprintf( text, "%s:ON\r%s",
					accessoryName,
					CLLocalitation::GetText( CLTextId_IN_ALARM ) );
			}

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;
		}

		case CLShowInfoId_Accessory_HWD_EHD:
		{
			char	accessoryName[ 5 ];

			// +-----------+
			// | EHD: OFF  |
			// |  In ALARM |
			// +-----------+
			if (!IsEnabled( CLBoxInfo_InfoId_Accessories ) ||
				!AccessoryClimaStatus_IsConnected( gKTSDebugData.Heater_Status ))
				return false;

			strcpy( accessoryName, (AccessoryClimaStatus_IsAir( gKTSDebugData.Heater_Status ) ? "EHD" : "HWD") );

			// E' spento?
			if (!AccessoryClimaStatus_IsOn( gKTSDebugData.Heater_Status ))
			{
				sprintf( text, "%s:OFF", accessoryName );
			}
			// Non e' in allarme?
			else
			if (!AccessoryClimaStatus_InAlarm( gKTSDebugData.Heater_Status ))
			{
				sprintf( text, "%s:ON", accessoryName );
			}
			// Ok, e' in allarme
			else
			{
				sprintf( text, "%s:ON\r%s",
					accessoryName,
					CLLocalitation::GetText( CLTextId_IN_ALARM ) );
			}

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;
		}

		case CLShowInfoId_Accessory_CWD:
			// +-----------+
			// | CWD: OFF  |
			// |  In ALARM |
			// +-----------+

			if (!IsEnabled( CLBoxInfo_InfoId_Accessories ) ||
				!AccessoryClimaStatus_IsConnected( gKTSDebugData.Cooler_Status ))
				return false;

			// E' spento?
			if (!AccessoryClimaStatus_IsOn( gKTSDebugData.Cooler_Status ))
			{
				strcpy( text, "CWD:OFF" );
			}
			// Non e' in allarme?
			else
			if (!AccessoryClimaStatus_InAlarm( gKTSDebugData.Cooler_Status ))
			{
				strcpy( text, "CWD:ON" );
			}
			// Ok, e' in allarme
			else
			{
				sprintf( text, "CWD:ON\r%s",
					CLLocalitation::GetText( CLTextId_IN_ALARM ) );
			}

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;

		case CLShowInfoId_Defrost:

			if (!IsEnabled( CLBoxInfo_InfoId_Defrost ))
				return false;

			if (Function_IsEnabled( ENAB_DEFROST ))
			{
				sprintf( text, "%s\r%s",
					CLLocalitation::GetText( CLTextId_DEFROST ),
					(CLKTS::IsRunningDefrost() ? CLFixedText_ON : CLFixedText_OFF) );
			}
			else
			{
				sprintf( text, "%s\r%s",
					CLLocalitation::GetText( CLTextId_DEFROST ),
					CLLocalitation::GetText( CLTextId_DISABLE) );
			}

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;

		case CLShowInfoId_Bypass:
		{
			char	bypassStatusText[ 20 ];

			if (!IsEnabled( CLBoxInfo_InfoId_Bypass ))
				return false;

			switch (gRDEeprom.Config_Bypass)
			{
				case BPD_MANUAL_CLOSE:
					strcpy( bypassStatusText, CLLocalitation::GetText( CLTextId_MANUAL_OFF ) );
					break;

				case BPD_MANUAL_OPEN:
					strcpy( bypassStatusText, CLLocalitation::GetText( CLTextId_MANUAL_ON ) );
					break;
				
				default:
					strcpy( bypassStatusText, (Bypass_GetStatus() == CLBypassStatus_Close ? CLLocalitation::GetText( CLTextId_AUT_OFF ) : CLLocalitation::GetText( CLTextId_AUT_ON ) ) );
					break;
			}

			sprintf( text, "%s\r%s",
				CLLocalitation::GetText( CLTextId_BYPASS ),
				bypassStatusText );

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;
		}

		case CLShowInfoId_Probes_RH:

			if (!IsEnabled( CLBoxInfo_InfoId_Probes ))
				return false;

			if (gRDEeprom.SetPoint_RH == 0 ||
				(gRDEeprom.Type_func != CLKTSType_EXTRA && gRDEeprom.Type_func != CLKTSType_DEMO) ||
				(!Accessory_IsPresent( ACC_EEP_P1RH ) && !Accessory_IsPresent( ACC_EEP_P2RH )))
			{
				return false;
			}

			if (gKTSData.Measure_RH_max <= 0 || gKTSData.Measure_RH_max > 100)
			{
				sprintf( text, "%s\r...",
					CLFixedText_RH );
			}
			else
			{
				sprintf( text, "%s\r%d%%", CLFixedText_RH,
					gKTSData.Measure_RH_max );
			}

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );
            
            if(Accessory_IsPresent( ACC_EEP_P1CO2 )) // AIR SENSOR1 CONNECTED
            {
                switch (CO2_1_Accuracy)
                {
                    case 0:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracynullRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevide0Image );
                        break;
                        
                    case 1:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                    
                    case 2:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                        
                    case 3:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        break;    
                }
            }
            
            if(Accessory_IsPresent( ACC_EEP_P2CO2 )) // AIR SENSOR2 CONNECTED
            {
                switch (CO2_2_Accuracy)
                {
                    case 0:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1nullRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevide0Image );
                        break;
                        
                    case 1:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                    
                    case 2:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                        
                    case 3:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        break;    
                }
            }
            
			return true;

		case CLShowInfoId_Probes_CO2:
		{
			CLRectangle	rectangle( m_DataRectangle );

			if (!IsEnabled( CLBoxInfo_InfoId_Probes ))
				return false;

			if (gRDEeprom.SetPoint_CO2 == 0 ||
				(gRDEeprom.Type_func != CLKTSType_EXTRA && gRDEeprom.Type_func != CLKTSType_DEMO) ||
				(!Accessory_IsPresent( ACC_EEP_P1CO2 ) && !Accessory_IsPresent( ACC_EEP_P2CO2 )))
			{
				return false;
			}

			rectangle.SetSize( rectangle.GetWidth(), rectangle.GetHeight() / 2 );
			CLGraphics::DrawBoxWithText( rectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Bottom | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				CLFixedText_CO2 );

			if (gKTSData.Measure_CO2_max < 0 || gKTSData.Measure_CO2_max > 4000)
				strcpy( text, "..." );
			else
			{
				sprintf( text, "%d %s", gKTSData.Measure_CO2_max,
					CLFixedText_PPM );
			}

			rectangle.MoveOffset( 0, rectangle.GetHeight() + 1 );
			CLGraphics::DrawBoxWithText( rectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Top | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, (gKTSData.Measure_CO2_max <= 1000 ? RGBColor_Green : gKTSData.Measure_CO2_max <= 1400 ? 0xff6600 : RGBColor_Red),
				text );
            
            if(Accessory_IsPresent( ACC_EEP_P1CO2 )) // AIR SENSOR1 CONNECTED
            {
                switch (CO2_1_Accuracy)
                {
                    case 0:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracynullRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevide0Image );
                        break;
                        
                    case 1:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                    
                    case 2:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                        
                    case 3:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        break;    
                }
            }
            
            if(Accessory_IsPresent( ACC_EEP_P2CO2 )) // AIR SENSOR2 CONNECTED
            {
                switch (CO2_2_Accuracy)
                {
                    case 0:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1nullRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevide0Image );
                        break;
                        
                    case 1:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                    
                    case 2:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                        
                    case 3:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        break;    
                }
            }
            
			return true;
		}

		case CLShowInfoId_Probes_VOC:

			if (!IsEnabled( CLBoxInfo_InfoId_Probes ))
				return false;

			if (gRDEeprom.SetPoint_VOC == 0 ||
				(gRDEeprom.Type_func != CLKTSType_EXTRA && gRDEeprom.Type_func != CLKTSType_DEMO) ||
				(!Accessory_IsPresent( ACC_EEP_P1VOC )))
			{
				return false;
			}

			if (gKTSData.Measure_VOC_max < 0 || gKTSData.Measure_VOC_max > CLKTS::VOC_GetMax())
			{
				sprintf( text, "%s\r...",
					CLFixedText_VOC );
			}
			else
			{
				sprintf( text, "%s\r%d %s",
					CLFixedText_VOC,
					gKTSData.Measure_VOC_max,
					CLFixedText_PPM );
			}

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );
            
            if(Accessory_IsPresent( ACC_EEP_P1CO2 )) // AIR SENSOR1 CONNECTED
            {
                switch (CO2_1_Accuracy)
                {
                    case 0:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracynullRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevide0Image );
                        break;
                        
                    case 1:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                    
                    case 2:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                        
                    case 3:
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_AccuracyRectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        break;    
                }
            }
            
            if(Accessory_IsPresent( ACC_EEP_P2CO2 )) // AIR SENSOR2 CONNECTED
            {
                switch (CO2_2_Accuracy)
                {
                    case 0:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1nullRectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevide0Image );
                        break;
                        
                    case 1:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                    
                    case 2:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrevideImage );
                        break;
                        
                    case 3:
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle1, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle2, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        CLGraphics::DrawBoxWithDrawer( m_Accuracy1Rectangle3, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &datacarrepleinImage );
                        break;    
                }
            }
            
			return true;

		case CLShowInfoId_Probes_AWP:

			if (!IsEnabled( CLBoxInfo_InfoId_Probes ))
				return false;

			if ((gRDEeprom.Type_func != CLKTSType_EXTRA && gRDEeprom.Type_func != CLKTSType_DEMO) ||
				(!Accessory_IsPresent( ACC_EEP_AWP )))
			{
				return false;
			}

			if (gKTSData.Measure_Temp_AWP < 0)
			{
				sprintf( text, "%s\r...",
					CLFixedText_AWP );
			}
			else
			{
				sprintf( text, "%s\r%-4.1f %c",
					CLFixedText_AWP,
					gKTSData.Measure_Temp_AWP,
					FONT_SYMBOL_DEGREES );
			}

			CLGraphics::DrawBoxWithText( m_DataRectangle, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				text );

			return true;

	}

	return false;
}

void CLBoxInfo::Process()
{
	byte	initialShowInfoId	= m_CurrentShowInfoId;

	// Se non è passato tempo di refresh, esce
	// Si le temps de rafraîchissement n'est pas écoulé, il quitte
	if (!(millis() - m_Refresh_Timer >= BoxInfo_RefreshMilliseconds ||
		millis() < m_Refresh_Timer))
		return;

	m_Refresh_Timer	= millis();

	while (true)
	{
		bool	showedInfo;

		// Se siamo in allarme incendio, forzo l'info da visualizzare incendio
		// Si on est en alarme incendie, je force l'info à afficher feu
		if (IsFireAlarm())
		{
			if (m_CurrentShowInfoId != CLShowInfoId_Fire)
			{
				ClearBox();
				m_CurrentShowInfoId	= CLShowInfoId_Fire;
			}
			RenderInfo( CLShowInfoId_Fire );
			break;
		}
		else
		// Se siamo in boost, forzo l'info da visualizzare in boost (party),
		// Si on est en boost, je force les infos à s'afficher en boost (fête),
		if (CLKTS::IsRunningBoost())
		{
			if (m_CurrentShowInfoId != CLShowInfoId_Boost)
			{
				ClearBox();
				m_CurrentShowInfoId	= CLShowInfoId_Boost;
			}
			RenderInfo( CLShowInfoId_Boost );
			break;
		}

		showedInfo	= RenderInfo( (CLShowInfoId) m_CurrentShowInfoId );

		// Incrementa l'info corrente da visualizzare
		// Incrémenter les informations actuelles à afficher
		if (++m_CurrentShowInfoId > CLShowInfoId_LASTITEM)
			m_CurrentShowInfoId	= 0;

		// Se la info è stata visualizzata o nessuna informazione da visualizzare , esce
		// Si l'info a été affichée ou pas d'information à afficher, il quitte
		if (m_CurrentShowInfoId == initialShowInfoId || showedInfo)
			{
				break;
			}
	}

}

void CLBoxInfo::ForceRefresh()
{
	m_Refresh_Timer	= m_Refresh_Timer - BoxInfo_RefreshMilliseconds;
}

void CLBoxInfo::ClearBox()
{
	if (m_Rectangle.GetHeight() == 0 || m_Rectangle.GetWidth() == 0)
		return;

	// Clear Box Info Data Panel
	CLGraphics::DrawBox( m_Rectangle, GenericForm_Group_Style );
}

void CLBoxInfo::SetRectangle( short x1, short y1, short x2, short y2 )
{
	m_Rectangle.Set( x1, y1, x2, y2 );
	m_DataRectangle.Set( m_Rectangle );
	m_DataRectangle.Inflate( -1, -1 );
}

CLRectangle& CLBoxInfo::GetRectangle()
{
	return m_Rectangle;
}

bool CLBoxInfo::IsEnabled( CLBoxInfo_InfoId infoId )
{
	return (gKTSEeprom.GetDesktopBoxInfo() & infoId ? true : false);
}

bool CLBoxInfo::Write( byte value )
{
	gKTSEeprom.SetDesktopBoxInfo( value );

	return true;
}
// -----------------------------------------------------------------------------
// CLBoxInfo [class]
// =============================================================================

