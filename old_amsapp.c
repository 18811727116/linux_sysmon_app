/*
* Copyright (C) 2013 - 2016  Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or (b) that interact
* with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in this
* Software without prior written authorization from Xilinx.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <math.h>

#define RAW_DATA_LEN 		5
#define OFFSET_DATA_LEN 	6
#define SCALE_DATA_LEN 		11

static int Temp_LPD()
{

	int Temp_LPD[3] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},offset_buf[OFFSET_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	Temp_LPD[0] = open("/sys/bus/iio/devices/iio\:device0/in_temp0_ps_temp_raw", O_RDONLY);
	if(Temp_LPD[0] < 0)
	{
		printf("open in_temp0_ps_temp_raw failed \n");
		return -1;
	}
	Temp_LPD[1] = open("/sys/bus/iio/devices/iio\:device0/in_temp0_ps_temp_offset", O_RDONLY);
	if(Temp_LPD[1] < 0)
	{
		printf("open in_temp0_ps_temp_offset failed \n");
		close(Temp_LPD[0]);
		return -1;
	}
	Temp_LPD[2] = open("/sys/bus/iio/devices/iio\:device0/in_temp0_ps_temp_scale", O_RDONLY);
	if(Temp_LPD[2] < 0)
	{
		printf("open in_temp0_ps_temp_scale failed \n");
		close(Temp_LPD[0]);
		close(Temp_LPD[1]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(Temp_LPD[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else 
	printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;

	if(OFFSET_DATA_LEN==read(Temp_LPD[1],offset_buf,OFFSET_DATA_LEN))
	printf("\roffset value is :%s \n",offset_buf);
	else 
	printf("\roffset value read error!\n");
	offset_buf[OFFSET_DATA_LEN]=0;

	if(SCALE_DATA_LEN==read(Temp_LPD[2],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(Temp_LPD[0]);
	close(Temp_LPD[1]);
	close(Temp_LPD[2]);

	int raw_value = atoi(raw_buf);
	int offset_value = atoi(offset_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\roffset value is :%s \n", offset_buf);
	printf("\roffset value is :%d \n", offset_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = ((raw_value + offset_value) * scale_value) / 1000.0;
	printf("\rTemp_LPD is :%.2f\n", processed_value);
	if(processed_value > 60)
	printf("\rDangerous ! Temp_LPD is too high !\n");
	if(processed_value < 10)
	printf("\rDangerous ! Temp_LPD is too low !\n");

	return 0;
}

static int Temp_FPD()
{

	int Temp_FPD[3] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},offset_buf[OFFSET_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	Temp_FPD[0] = open("/sys/bus/iio/devices/iio\:device0/in_temp1_remote_temp_raw", O_RDONLY);
	if(Temp_FPD[0] < 0)
	{
		printf("open in_temp1_remote_temp_raw failed \n");
		return -1;
	}
	Temp_FPD[1] = open("/sys/bus/iio/devices/iio\:device0/in_temp1_remote_temp_offset", O_RDONLY);
	if(Temp_FPD[1] < 0)
	{
		printf("open in_temp1_remote_temp_offset failed \n");
		close(Temp_FPD[0]);
		return -1;
	}
	Temp_FPD[2] = open("/sys/bus/iio/devices/iio\:device0/in_temp1_remote_temp_scale", O_RDONLY);
	if(Temp_FPD[2] < 0)
	{
		printf("open in_temp1_remote_temp_scale failed \n");
		close(Temp_FPD[0]);
		close(Temp_FPD[1]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(Temp_FPD[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else 
	printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;

	if(OFFSET_DATA_LEN==read(Temp_FPD[1],offset_buf,OFFSET_DATA_LEN))
	printf("\roffset value is :%s \n",offset_buf);
	else 
	printf("\roffset value read error!\n");
	offset_buf[OFFSET_DATA_LEN]=0;

	if(SCALE_DATA_LEN==read(Temp_FPD[2],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(Temp_FPD[0]);
	close(Temp_FPD[1]);
	close(Temp_FPD[2]);

	int raw_value = atoi(raw_buf);
	int offset_value = atoi(offset_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\roffset value is :%s \n", offset_buf);
	printf("\roffset value is :%d \n", offset_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = ((raw_value + offset_value) * scale_value) / 1000.0;
	printf("\rTemp_FPD is :%.2f\n", processed_value);
	if(processed_value > 60)
	printf("\rDangerous ! Temp_FPD is too high !\n");
	if(processed_value < 10)
	printf("\rDangerous ! Temp_FPD is too low !\n");

	return 0;
}

static int Temp_PL()
{

	int Temp_PL[3] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},offset_buf[OFFSET_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	Temp_PL[0] = open("/sys/bus/iio/devices/iio\:device0/in_temp2_pl_temp_raw", O_RDONLY);
	if(Temp_PL[0] < 0)
	{
		printf("open in_temp2_pl_temp_raw failed \n");
		return -1;
	}
	Temp_PL[1] = open("/sys/bus/iio/devices/iio\:device0/in_temp2_pl_temp_offset", O_RDONLY);
	if(Temp_PL[1] < 0)
	{
		printf("open in_temp2_pl_temp_offset failed \n");
		close(Temp_PL[0]);
		return -1;
	}
	Temp_PL[2] = open("/sys/bus/iio/devices/iio\:device0/in_temp2_pl_temp_scale", O_RDONLY);
	if(Temp_PL[2] < 0)
	{
		printf("open in_temp2_pl_temp_scale failed \n");
		close(Temp_PL[0]);
		close(Temp_PL[1]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(Temp_PL[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else 
	printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;

	if(OFFSET_DATA_LEN==read(Temp_PL[1],offset_buf,OFFSET_DATA_LEN))
	printf("\roffset value is :%s \n",offset_buf);
	else 
	printf("\roffset value read error!\n");
	offset_buf[OFFSET_DATA_LEN]=0;

	if(SCALE_DATA_LEN==read(Temp_PL[2],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(Temp_PL[0]);
	close(Temp_PL[1]);
	close(Temp_PL[2]);

	int raw_value = atoi(raw_buf);
	int offset_value = atoi(offset_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\roffset value is :%s \n", offset_buf);
	printf("\roffset value is :%d \n", offset_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = ((raw_value + offset_value) * scale_value) / 1000.0;
	printf("\rTemp_PL is :%.2f\n", processed_value);
	if(processed_value > 60)
	printf("\rDangerous ! Temp_PL is too high !\n");
	if(processed_value < 10)
	printf("\rDangerous ! Temp_PL is too low !\n");

	return 0;
}

static int Voltage_VCCPSINTLP()
{

	int VCCPSINTLP[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPSINTLP[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage0_vccpsintlp_raw", O_RDONLY);
	if(VCCPSINTLP[0] < 0)
	{
		printf("open in_voltage0_vccpsintlp_raw failed \n");
		return -1;
	}
	VCCPSINTLP[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage0_vccpsintlp_scale", O_RDONLY);
	if(VCCPSINTLP[1] < 0)
	{
		printf("open in_voltage0_vccpsintlp_scale failed \n");
		close(VCCPSINTLP[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPSINTLP[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPSINTLP[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPSINTLP[0]);
	close(VCCPSINTLP[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPSINTLP is :%.2f\n", processed_value);
	if(processed_value > 0.86)
	printf("\rDangerous ! Voltage_VCCPSINTLP is too high !\n");
	if(processed_value < 0.84)
	printf("\rDangerous ! Voltage_VCCPSINTLP is too low !\n");

	return 0;
}

static int Voltage_VCCPSINTFP()
{

	int VCCPSINTFP[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPSINTFP[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage1_vccpsintfp_raw", O_RDONLY);
	if(VCCPSINTFP[0] < 0)
	{
		printf("open in_voltage0_vccpsintfp_raw failed \n");
		return -1;
	}
	VCCPSINTFP[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage1_vccpsintfp_scale", O_RDONLY);
	if(VCCPSINTFP[1] < 0)
	{
		printf("open in_voltage0_vccpsintfp_scale failed \n");
		close(VCCPSINTFP[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPSINTFP[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPSINTFP[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPSINTFP[0]);
	close(VCCPSINTFP[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPSINTFP is :%.2f\n", processed_value);
	if(processed_value > 0.86)
	printf("\rDangerous ! Voltage_VCCPSINTFP is too high !\n");
	if(processed_value < 0.84)
	printf("\rDangerous ! Voltage_VCCPSINTFP is too low !\n");

	return 0;
}

static int Voltage_VCCPSAUX()
{

	int VCCPSAUX[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPSAUX[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage2_vccpsaux_raw", O_RDONLY);
	if(VCCPSAUX[0] < 0)
	{
		printf("open in_voltage2_vccpsaux_raw failed \n");
		return -1;
	}
	VCCPSAUX[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage2_vccpsaux_scale", O_RDONLY);
	if(VCCPSAUX[1] < 0)
	{
		printf("open in_voltage2_vccpsaux_scale failed \n");
		close(VCCPSAUX[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPSAUX[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPSAUX[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPSAUX[0]);
	close(VCCPSAUX[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPSAUX is :%.2f\n", processed_value);
	if(processed_value > 1.82)
	printf("\rDangerous ! Voltage_VCCPSAUX is too high !\n");
	if(processed_value < 1.80)
	printf("\rDangerous ! Voltage_VCCPSAUX is too low !\n");

	return 0;
}

static int Voltage_VCCPSDDR()
{

	int VCCPSDDR[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPSDDR[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage3_vccpsddr_raw", O_RDONLY);
	if(VCCPSDDR[0] < 0)
	{
		printf("open in_voltage3_vccpsddr_raw failed \n");
		return -1;
	}
	VCCPSDDR[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage3_vccpsddr_scale", O_RDONLY);
	if(VCCPSDDR[1] < 0)
	{
		printf("open in_voltage3_vccpsddr_scale failed \n");
		close(VCCPSDDR[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPSDDR[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPSDDR[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPSDDR[0]);
	close(VCCPSDDR[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPSDDR is :%.2f\n", processed_value);
	if(processed_value > 1.20)
	printf("\rDangerous ! Voltage_VCCPSDDR is too high !\n");
	if(processed_value < 1.18)
	printf("\rDangerous ! Voltage_VCCPSDDR is too low !\n");

	return 0;
}

static int Voltage_VCCPSIO3()
{

	int VCCPSIO3[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPSIO3[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage4_vccpsio3_raw", O_RDONLY);
	if(VCCPSIO3[0] < 0)
	{
		printf("open in_voltage4_vccpsio3_raw failed \n");
		return -1;
	}
	VCCPSIO3[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage4_vccpsio3_scale", O_RDONLY);
	if(VCCPSIO3[1] < 0)
	{
		printf("open in_voltage4_vccpsio3_scale failed \n");
		close(VCCPSIO3[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPSIO3[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPSIO3[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPSIO3[0]);
	close(VCCPSIO3[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPSIO3 is :%.2f\n", processed_value);
	if(processed_value > 1.81)
	printf("\rDangerous ! Voltage_VCCPSIO3 is too high !\n");
	if(processed_value < 1.79)
	printf("\rDangerous ! Voltage_VCCPSIO3 is too low !\n");

	return 0;
}

static int Voltage_VCCPSIO0()
{

	int VCCPSIO0[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPSIO0[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage5_vccpsio0_raw", O_RDONLY);
	if(VCCPSIO0[0] < 0)
	{
		printf("open in_voltage5_vccpsio0_raw failed \n");
		return -1;
	}
	VCCPSIO0[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage5_vccpsio0_scale", O_RDONLY);
	if(VCCPSIO0[1] < 0)
	{
		printf("open in_voltage5_vccpsio0_scale failed \n");
		close(VCCPSIO0[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPSIO0[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPSIO0[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPSIO0[0]);
	close(VCCPSIO0[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPSIO0 is :%.2f\n", processed_value);
	if(processed_value > 1.81)
	printf("\rDangerous ! Voltage_VCCPSIO0 is too high !\n");
	if(processed_value < 1.79)
	printf("\rDangerous ! Voltage_VCCPSIO0 is too low !\n");

	return 0;
}

static int Voltage_VCCPSIO1()
{

	int VCCPSIO1[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPSIO1[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage6_vccpsio1_raw", O_RDONLY);
	if(VCCPSIO1[0] < 0)
	{
		printf("open in_voltage6_vccpsio1_raw failed \n");
		return -1;
	}
	VCCPSIO1[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage6_vccpsio1_scale", O_RDONLY);
	if(VCCPSIO1[1] < 0)
	{
		printf("open in_voltage6_vccpsio1_scale failed \n");
		close(VCCPSIO1[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPSIO1[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPSIO1[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPSIO1[0]);
	close(VCCPSIO1[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPSIO1 is :%.2f\n", processed_value);
	if(processed_value > 1.81)
	printf("\rDangerous ! Voltage_VCCPSIO1 is too high !\n");
	if(processed_value < 1.79)
	printf("\rDangerous ! Voltage_VCCPSIO1 is too low !\n");

	return 0;
}

static int Voltage_VCCPSIO2()
{

	int VCCPSIO2[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPSIO2[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage7_vccpsio2_raw", O_RDONLY);
	if(VCCPSIO2[0] < 0)
	{
		printf("open in_voltage7_vccpsio2_raw failed \n");
		return -1;
	}
	VCCPSIO2[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage7_vccpsio2_scale", O_RDONLY);
	if(VCCPSIO2[1] < 0)
	{
		printf("open in_voltage7_vccpsio2_scale failed \n");
		close(VCCPSIO2[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPSIO2[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPSIO2[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPSIO2[0]);
	close(VCCPSIO2[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPSIO2 is :%.2f\n", processed_value);
	if(processed_value > 1.81)
	printf("\rDangerous ! Voltage_VCCPSIO2 is too high !\n");
	if(processed_value < 1.79)
	printf("\rDangerous ! Voltage_VCCPSIO2 is too low !\n");

	return 0;
}

static int Voltage_PSMGTRAVCC()
{

	int PSMGTRAVCC[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	PSMGTRAVCC[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage8_psmgtravcc_raw", O_RDONLY);
	if(PSMGTRAVCC[0] < 0)
	{
		printf("open in_voltage8_psmgtravcc_raw failed \n");
		return -1;
	}
	PSMGTRAVCC[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage8_psmgtravcc_scale", O_RDONLY);
	if(PSMGTRAVCC[1] < 0)
	{
		printf("open in_voltage8_psmgtravcc_scale failed \n");
		close(PSMGTRAVCC[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(PSMGTRAVCC[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(PSMGTRAVCC[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(PSMGTRAVCC[0]);
	close(PSMGTRAVCC[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_PSMGTRAVCC is :%.2f\n", processed_value);
	if(processed_value > 0.86)
	printf("\rDangerous ! Voltage_PSMGTRAVCC is too high !\n");
	if(processed_value < 0.84)
	printf("\rDangerous ! Voltage_PSMGTRAVCC is too low !\n");

	return 0;
}

static int Voltage_PSMGTRAVTT()
{

	int PSMGTRAVTT[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	PSMGTRAVTT[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage9_psmgtravtt_raw", O_RDONLY);
	if(PSMGTRAVTT[0] < 0)
	{
		printf("open in_voltage8_psmgtravtt_raw failed \n");
		return -1;
	}
	PSMGTRAVTT[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage9_psmgtravtt_scale", O_RDONLY);
	if(PSMGTRAVTT[1] < 0)
	{
		printf("open in_voltage8_psmgtravtt_scale failed \n");
		close(PSMGTRAVTT[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(PSMGTRAVTT[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(PSMGTRAVTT[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(PSMGTRAVTT[0]);
	close(PSMGTRAVTT[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_PSMGTRAVTT is :%.2f\n", processed_value);
	if(processed_value > 1.83)
	printf("\rDangerous ! Voltage_PSMGTRAVTT is too high !\n");
	if(processed_value < 1.80)
	printf("\rDangerous ! Voltage_PSMGTRAVTT is too low !\n");

	return 0;
}

static int Voltage_VCCAMS()
{

	int VCCAMS[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCAMS[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage10_vccams_raw", O_RDONLY);
	if(VCCAMS[0] < 0)
	{
		printf("open in_voltage10_vccams_raw failed \n");
		return -1;
	}
	VCCAMS[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage10_vccams_scale", O_RDONLY);
	if(VCCAMS[1] < 0)
	{
		printf("open in_voltage10_vccams_scale failed \n");
		close(VCCAMS[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCAMS[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCAMS[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCAMS[0]);
	close(VCCAMS[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCAMS is :%.2f\n", processed_value);
	if(processed_value > 0.62)
	printf("\rDangerous ! Voltage_VCCAMS is too high !\n");
	if(processed_value < 0.58)
	printf("\rDangerous ! Voltage_VCCAMS is too low !\n");

	return 0;
}

static int Voltage_VCCINT()
{

	int VCCINT[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCINT[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage11_vccint_raw", O_RDONLY);
	if(VCCINT[0] < 0)
	{
		printf("open in_voltage11_vccint_raw failed \n");
		return -1;
	}
	VCCINT[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage11_vccint_scale", O_RDONLY);
	if(VCCINT[1] < 0)
	{
		printf("open in_voltage11_vccint_scale failed \n");
		close(VCCINT[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCINT[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCINT[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCINT[0]);
	close(VCCINT[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCINT is :%.2f\n", processed_value);
	if(processed_value > 0.86)
	printf("\rDangerous ! Voltage_VCCINT is too high !\n");
	if(processed_value < 0.84)
	printf("\rDangerous ! Voltage_VCCINT is too low !\n");

	return 0;
}

static int Voltage_VCCAUX()
{

	int VCCAUX[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCAUX[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage12_vccaux_raw", O_RDONLY);
	if(VCCAUX[0] < 0)
	{
		printf("open in_voltage12_vccaux_raw failed \n");
		return -1;
	}
	VCCAUX[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage12_vccaux_scale", O_RDONLY);
	if(VCCAUX[1] < 0)
	{
		printf("open in_voltage12_vccaux_scale failed \n");
		close(VCCAUX[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCAUX[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCAUX[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCAUX[0]);
	close(VCCAUX[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCAUX is :%.2f\n", processed_value);
	if(processed_value > 1.81)
	printf("\rDangerous ! Voltage_VCCAUX is too high !\n");
	if(processed_value < 1.80)
	printf("\rDangerous ! Voltage_VCCAUX is too low !\n");

	return 0;
}

static int Voltage_VCCVREFP()
{

	int VCCVREFP[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCVREFP[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage13_vccvrefp_raw", O_RDONLY);
	if(VCCVREFP[0] < 0)
	{
		printf("open in_voltage13_vccvrefp_raw failed \n");
		return -1;
	}
	VCCVREFP[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage13_vccvrefp_scale", O_RDONLY);
	if(VCCVREFP[1] < 0)
	{
		printf("open in_voltage13_vccvrefp_scale failed \n");
		close(VCCVREFP[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCVREFP[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCVREFP[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCVREFP[0]);
	close(VCCVREFP[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCVREFP is :%.2f\n", processed_value);
	if(processed_value > 0.45)
	printf("\rDangerous ! Voltage_VCCVREFP is too high !\n");
	if(processed_value < 0.40)
	printf("\rDangerous ! Voltage_VCCVREFP is too low !\n");

	return 0;
}

static int Voltage_VCCVREFN()
{

	int VCCVREFN[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCVREFN[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage14_vccvrefn_raw", O_RDONLY);
	if(VCCVREFN[0] < 0)
	{
		printf("open in_voltage14_vccvrefn_raw failed \n");
		return -1;
	}
	VCCVREFN[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage14_vccvrefn_scale", O_RDONLY);
	if(VCCVREFN[1] < 0)
	{
		printf("open in_voltage14_vccvrefn_scale failed \n");
		close(VCCVREFN[0]);
		return -1;
	}
	
	read(VCCVREFN[0],raw_buf,RAW_DATA_LEN);
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCVREFN[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCVREFN[0]);
	close(VCCVREFN[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCVREFN is :%.2f\n", processed_value);
	if((int)processed_value != 0)
	printf("\rDangerous ! Voltage_VCCVREFN is incorrect !\n");

	return 0;
}

static int Voltage_VCCBRAM()
{

	int VCCBRAM[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCBRAM[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage15_vccbram_raw", O_RDONLY);
	if(VCCBRAM[0] < 0)
	{
		printf("open in_voltage15_vccbram_raw failed \n");
		return -1;
	}
	VCCBRAM[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage15_vccbram_scale", O_RDONLY);
	if(VCCBRAM[1] < 0)
	{
		printf("open in_voltage15_vccbram_scale failed \n");
		close(VCCBRAM[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCBRAM[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCBRAM[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCBRAM[0]);
	close(VCCBRAM[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCBRAM is :%.2f\n", processed_value);
	if(processed_value > 0.86)
	printf("\rDangerous ! Voltage_VCCBRAM is too high !\n");
	if(processed_value < 0.84)
	printf("\rDangerous ! Voltage_VCCBRAM is too low !\n");

	return 0;
}

static int Voltage_VCCPLINTLP()
{

	int VCCPLINTLP[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPLINTLP[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage16_vccplintlp_raw", O_RDONLY);
	if(VCCPLINTLP[0] < 0)
	{
		printf("open in_voltage16_vccplintlp_raw failed \n");
		return -1;
	}
	VCCPLINTLP[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage16_vccplintlp_scale", O_RDONLY);
	if(VCCPLINTLP[1] < 0)
	{
		printf("open in_voltage16_vccplintlp_scale failed \n");
		close(VCCPLINTLP[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPLINTLP[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPLINTLP[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPLINTLP[0]);
	close(VCCPLINTLP[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPLINTLP is :%.2f\n", processed_value);
	if(processed_value > 0.86)
	printf("\rDangerous ! Voltage_VCCPLINTLP is too high !\n");
	if(processed_value < 0.84)
	printf("\rDangerous ! Voltage_VCCPLINTLP is too low !\n");

	return 0;
}

static int Voltage_VCCPLINTFP()
{

	int VCCPLINTFP[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPLINTFP[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage17_vccplintfp_raw", O_RDONLY);
	if(VCCPLINTFP[0] < 0)
	{
		printf("open in_voltage17_vccplintfp_raw failed \n");
		return -1;
	}
	VCCPLINTFP[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage17_vccplintfp_scale", O_RDONLY);
	if(VCCPLINTFP[1] < 0)
	{
		printf("open in_voltage17_vccplintfp_scale failed \n");
		close(VCCPLINTFP[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPLINTFP[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPLINTFP[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPLINTFP[0]);
	close(VCCPLINTFP[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPLINTFP is :%.2f\n", processed_value);
	if(processed_value > 0.86)
	printf("\rDangerous ! Voltage_VCCPLINTFP is too high !\n");
	if(processed_value < 0.84)
	printf("\rDangerous ! Voltage_VCCPLINTFP is too low !\n");

	return 0;
}

static int Voltage_VCCPLAUX()
{

	int VCCPLAUX[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCPLAUX[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage18_vccplaux_raw", O_RDONLY);
	if(VCCPLAUX[0] < 0)
	{
		printf("open in_voltage18_vccplaux_raw failed \n");
		return -1;
	}
	VCCPLAUX[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage18_vccplaux_scale", O_RDONLY);
	if(VCCPLAUX[1] < 0)
	{
		printf("open in_voltage18_vccplaux_scale failed \n");
		close(VCCPLAUX[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCPLAUX[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCPLAUX[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCPLAUX[0]);
	close(VCCPLAUX[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCPLAUX is :%.2f\n", processed_value);
	if(processed_value > 1.82)
	printf("\rDangerous ! Voltage_VCCPLAUX is too high !\n");
	if(processed_value < 1.80)
	printf("\rDangerous ! Voltage_VCCPLAUX is too low !\n");

	return 0;
}

static int Voltage_VCCAMS1()
{

	int VCCAMS1[2] = {0};
	char raw_buf[RAW_DATA_LEN+1]={0},scale_buf[SCALE_DATA_LEN+1]={0};

	VCCAMS1[0] = open("/sys/bus/iio/devices/iio\:device0/in_voltage19_vccams_raw", O_RDONLY);
	if(VCCAMS1[0] < 0)
	{
		printf("open in_voltage19_vccams_raw failed \n");
		return -1;
	}
	VCCAMS1[1] = open("/sys/bus/iio/devices/iio\:device0/in_voltage19_vccams_scale", O_RDONLY);
	if(VCCAMS1[1] < 0)
	{
		printf("open in_voltage19_vccams_scale failed \n");
		close(VCCAMS1[0]);
		return -1;
	}
	
	if(RAW_DATA_LEN==read(VCCAMS1[0],raw_buf,RAW_DATA_LEN))
	printf("\rraw value is :%s \n",raw_buf);
	else printf("\rraw value read error!\n");
	raw_buf[RAW_DATA_LEN]=0;



	if(SCALE_DATA_LEN==read(VCCAMS1[1],scale_buf,SCALE_DATA_LEN))
	printf("\rscale value is :%s \n",scale_buf);
	else 
	printf("\rscale value read error!\n");
	scale_buf[SCALE_DATA_LEN]=0;

	close(VCCAMS1[0]);
	close(VCCAMS1[1]);


	int raw_value = atoi(raw_buf);
	double scale_value = strtof(scale_buf,0);

	printf("\rTest value exchange:\n");
	printf("\rraw value is :%s \n", raw_buf);
	printf("\rraw value is :%d \n", raw_value);
	printf("\rscale value is :%s \n", scale_buf);
	printf("\rscale value is :%f \n", scale_value);

	double processed_value = (raw_value * scale_value) / 1000.0;
	printf("\rVoltage_VCCAMS1 is :%.2f\n", processed_value);
	if(processed_value > 0.65)
	printf("\rDangerous ! Voltage_VCCAMS1 is too high !\n");
	if(processed_value < 0.55)
	printf("\rDangerous ! Voltage_VCCAMS1 is too low !\n");

	return 0;
}
int main()
{
	printf("\rDo you like what you see?\n");
	printf("\rYes, test starting...\n");

	Temp_LPD();
	Temp_FPD();
	Temp_PL();
	Voltage_VCCPSINTLP();
	Voltage_VCCPSINTFP();
	Voltage_VCCPSAUX();
	Voltage_VCCPSDDR();
	Voltage_VCCPSIO3();
	Voltage_VCCPSIO0();
	Voltage_VCCPSIO1();
	Voltage_VCCPSIO2();
	Voltage_PSMGTRAVCC();
	Voltage_PSMGTRAVTT();
	Voltage_VCCAMS();
	Voltage_VCCINT();
	Voltage_VCCAUX();
	Voltage_VCCVREFP();
	Voltage_VCCVREFN();
	Voltage_VCCBRAM();
	Voltage_VCCPLINTLP();
	Voltage_VCCPLINTFP();
	Voltage_VCCPLAUX();
	Voltage_VCCAMS1();

	printf("\rOk! Test finished successfully\n");

	sleep(3);

	Temp_LPD();
	Temp_FPD();
	Temp_PL();
	Voltage_VCCPSINTLP();
	Voltage_VCCPSINTFP();
	Voltage_VCCPSAUX();
	Voltage_VCCPSDDR();
	Voltage_VCCPSIO3();
	Voltage_VCCPSIO0();
	Voltage_VCCPSIO1();
	Voltage_VCCPSIO2();
	Voltage_PSMGTRAVCC();
	Voltage_PSMGTRAVTT();
	Voltage_VCCAMS();
	Voltage_VCCINT();
	Voltage_VCCAUX();
	Voltage_VCCVREFP();
	Voltage_VCCVREFN();
	Voltage_VCCBRAM();
	Voltage_VCCPLINTLP();
	Voltage_VCCPLINTFP();
	Voltage_VCCPLAUX();
	Voltage_VCCAMS1();
	return 0;
}
