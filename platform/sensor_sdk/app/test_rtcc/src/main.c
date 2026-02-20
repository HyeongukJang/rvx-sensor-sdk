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
// ****************************************************************************

#include "ervp_printf.h"
#include "ervp_core_id.h"
#include "ervp_external_peri_group_api.h"
#include "ervp_platform_controller_api.h"
#include "orvp_rtcc_module.h"
#include "ervp_delay.h"
#include "virtual_i2c.h"

const int NUM_TRY = 10;

int main() {
	if(EXCLUSIVE_ID==0)
	{
		if(is_sim())
		{
			test_virutal_i2c(I2C_INDEX_FOR_READYMADE);
		}
		else
		{
      printf("RTCC TEST\n");
			unsigned int sec, min, hour, day, date, month, year;
			configure_i2c_for_rtcc_module();
			sec = 0;	min = 50; hour = 20; day = SATURDAY; date = 17; month = 6; year = 21;
			configure_rtcc_module(sec, min, hour, day, date, month, year);
			for (int i=0; i<NUM_TRY; i++) {
				read_time(&sec, &min, &hour, &day, &date, &month, &year);
				printf("-------------------------\n");
				printf("Real-Time Clock, Calendar\n");
				printf("%d:%d:%d, %d/%d/%d\n",
					hour, min, sec, year, month, date);
				printf("-------------------------\n");
				delay_ms(1000);
			}
		}
	}

	return 0;
}
