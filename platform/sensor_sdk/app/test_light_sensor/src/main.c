// ****************************************************************************
// Copyright SoC Design Research Group, All rights reserved.    
// Electronics and Telecommunications Research Institute (ETRI)
//
// THESE DOCUMENTS CONTAIN CONFIDENTIAL INFORMATION AND KNOWLEDGE 
// WHICH IS THE PROPERTY OF ETRI. NO PART OF THIS PUBLICATION IS 
// TO BE USED FOR ANY OTHER PURPOSE, AND THESE ARE NOT TO BE 
// REPRODUCED, COPIED, DISCLOSED, TRANSMITTED, STORED IN A RETRIEVAL 
// SYSTEM OR TRANSLATED INTO ANY OTHER HUMAN OR COMPUTER LANGUAGE, 
// IN ANY FORM, BY ANY MEANS, IN WHOLE OR IN PART, WITHOUT THE 
// COMPLETE PRIOR WRITTEN PERMISSION OF ETRI.
// ****************************************************************************
// 13.Apr.2017 
// Sukho Lee (shle99@etri.re.kr)
// ****************************************************************************
#include "ervp_core_id.h"
#include "ervp_printf.h"
#include "ervp_external_peri_group_api.h"
#include "light_sensor.h"
#include "pressure_sensor.h"
#include "ervp_delay.h"

#define ENABLE_LIGHT_SENSOR 1
#define ENABLE_PRESSURE_SENSOR 0

const int NUM_TRY = 20;

int main() {
	if(EXCLUSIVE_ID==0)
	{
		configure_light_sensor();
		configure_pressure_sensor();
		for (int i=0; i<NUM_TRY; i++)
		{
			unsigned int result0, result1;
			printf("=========================\n");
			printf("index:%d\n", i);

			if(ENABLE_LIGHT_SENSOR==1)
			{
				
				result0 = read_light_sensor_value();
				printf("Light Level : %d / 255 \n", result0);
			}

			if(ENABLE_PRESSURE_SENSOR==1)
			{
				result1 = read_pressure_sensor_value();
				printf("Pressure Diff : %d/4095 \n", result1);
			}
			delay_ms(1000);
		}
	}
	return 0;
}
