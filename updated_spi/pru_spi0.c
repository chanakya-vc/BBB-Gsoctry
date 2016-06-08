/*
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *All rights reserved (C)Vaibhav Choudhary
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include "resource_table_empty.h"
#include <pru_cfg.h>
#define   P8_11  15
#define   CLK  14
volatile register uint8_t __R30;
//volatile register uuint8_t32_t __R31
uint8_t CPOL=0,CPHA=0;
uint8_t i=0;


 void main()
{
	volatile uint8_t mosi ,miso;
	//Set the CFG Register to direct output
	CT_CFG.GPCFG0 = 0;
	//clear the r30 register
	__R30=0x0000;
	//setmosi to test data
	mosi=0X6;
	//shifting this data to the 15 place
	mosi<<=P8_11;
	CPOL=1;
	CPHA=2;
	//set value of the CLOCK_POL_PHA variable between 0 and 3
	uint8_t CLOCK_POL_PHA=(CPOL<<1)|CPHA;
	if (CLOCK_POL_PHA>=2)
	{
		//set the clock 1 to be in its idle state
		__R30^=(1<<CLK);
	}

	switch(CLOCK_POL_PHA){
		case 0:	

			for ( i=0;i<8;i++)
			{
				//set clk 1
				__R30^=(1<<CLK);
				//write data to it
				if ((mosi>>7-i)&0x1)
				{
					__R30|=(1<<P8_11);
				}
				//set clk 0
				__R30^=(1<<CLK);
				//Reset the register
				__R30=0x0000;
				//shift data in Mosi
				mosi<<=1;

		    }
		    break;
		case 1:
			for ( i=0;i<8;i++)
			{
				//set clk 1
				__R30^=(1<<CLK);
				//set clk 0
				__R30^=(1<<CLK);
				//write data on the falling edge
				if ((mosi>>7-i)&0x1111)
				{
					__R30|=(1<<P8_11);
				}
				//Reset the register
				__R30=0x0000;
				//shift data in Mosi
				mosi<<=1;

		    }
		    break;
			                  
		case 2:
			for ( i=0;i<8;i++)
			{
				//set clk 0 to set it in active state
				__R30^=(1<<CLK);
				//write data on the falling edge
				if ((mosi>>7-i)&0x1111)
				{
					__R30|=(1<<P8_11);
				}
				//set clk 1 to idle state
				__R30^=(1<<CLK);
				
				//Reset the data pin in the register to 0
				__R30&=(0<<P8_11);
				//shift data in Mosi
				mosi<<=1;

		    }
		    break;
		case 3:
			for ( i=0;i<8;i++)
			{
				//set clk 0 to set it in active state
				__R30^=(1<<CLK);
				//set clk 1 to idle state
				__R30^=(1<<CLK);
				//write data on the rising edge
				if ((mosi>>7-i)&0x1111)
				{
					__R30|=(1<<P8_11);
				}
				//Reset the data pin in the register to 0
				__R30&=(0<<P8_11);
				//shift data in Mosi
				mosi<<=1;

		    }

		    break;
 		default:
 			break;


 }

__halt();
}
