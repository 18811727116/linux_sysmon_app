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


static int Get_Temp(char *pdevicename,double *pouttemp)
{
    int rawfd = 0, offsetfd = 0, scalefd = 0;
    char raw_buf[RAW_DATA_LEN + 1] = {0},offset_buf[OFFSET_DATA_LEN + 1] = {0},scale_buf[SCALE_DATA_LEN + 1] = {0};
    char filename[256] = {0};
    char errorcode[256] = {0};

    sprintf(filename,"/sys/bus/iio/devices/iio\:device0/in_%s_temp_raw", pdevicename);//temp0_ps,temp1_remote,temp2_pl
    rawfd = open(filename, O_RDONLY);
    if(rawfd < 0)
    {
        sprintf(errorcode,"open in_%s_temp_raw failed!\n", pdevicename);
        printf("\r%s\n", errorcode);
        return -1;
    }

    sprintf(filename,"/sys/bus/iio/devices/iio\:device0/in_%s_temp_offset", pdevicename);
    offsetfd = open(filename, O_RDONLY);
    if(offsetfd < 0)
    {
        sprintf(errorcode,"open in_%s_temp_offset failed!\n", pdevicename);
        printf("\r%s\n", errorcode);
        close(rawfd);
        return -2;
    }

    sprintf(filename,"/sys/bus/iio/devices/iio\:device0/in_%s_temp_scale", pdevicename);
    scalefd = open(filename, O_RDONLY);
    if(scalefd < 0)
    {
        sprintf(errorcode,"open in_%s_temp_scale failed!\n", pdevicename);
        printf("\r%s\n", errorcode);
        close(rawfd);
        close(offsetfd);
        return -3;
    }

    if(RAW_DATA_LEN != read(rawfd, raw_buf, RAW_DATA_LEN))
    printf("\rraw value read error!\n");
    raw_buf[RAW_DATA_LEN] = 0;

    if(OFFSET_DATA_LEN != read(offsetfd, offset_buf, OFFSET_DATA_LEN))
    printf("\roffset value read error!\n");
    offset_buf[OFFSET_DATA_LEN] = 0;

    if(SCALE_DATA_LEN != read(scalefd, scale_buf, SCALE_DATA_LEN))
    printf("\rscale value read error!\n");
    scale_buf[SCALE_DATA_LEN] = 0;

    close(rawfd);
    close(offsetfd);
    close(scalefd);

    int raw_value = atoi(raw_buf);
    int offset_value = atoi(offset_buf);
    double scale_value = strtof(scale_buf, 0);
    printf("raw_value is : %d, offset_value is : %d, scale_value is : %.9f\n", raw_value, offset_value, scale_value);
    *pouttemp=((raw_value + offset_value) * scale_value) / 1000.0;
	if((int)*pouttemp > 60)
	{
		printf("dangerous ! %s is too high !", pdevicename);
	}
	if((int)*pouttemp < 10)
	{
		printf("dangerous ! %s is too low !", pdevicename);
	}

    return 0;
}

static int Get_Voltage(char *pdevicename,double *poutvol)
{
    int rawfd = 0,scalefd = 0;
    char raw_buf[RAW_DATA_LEN + 1] = {0}, scale_buf[SCALE_DATA_LEN + 1] = {0};
    char filename[256] = {0};
    char errorcode[256] = {0};

    sprintf(filename,"/sys/bus/iio/devices/iio\:device0/in_%s_raw", pdevicename);//voltage0_vccpsintlp,voltage1_vccpsintfp,...
    rawfd = open(filename, O_RDONLY);
    if(rawfd < 0)
    {
        sprintf(errorcode,"open in_%s_temp_raw failed!\n", pdevicename);
        printf("\r%s\n", errorcode);
        return -1;
    }
   
    sprintf(filename,"/sys/bus/iio/devices/iio\:device0/in_%s_scale", pdevicename);
    scalefd = open(filename, O_RDONLY);
    if(scalefd < 0)
    {
        sprintf(errorcode,"open in_%s_temp_scale failed!\n", pdevicename);
        printf("\r%s\n", errorcode);
        close(rawfd);
        return -2;
    }

    read(rawfd, raw_buf, RAW_DATA_LEN);
    raw_buf[RAW_DATA_LEN] = 0;

    read(scalefd, scale_buf, SCALE_DATA_LEN);
    scale_buf[SCALE_DATA_LEN] = 0;

    close(rawfd);
    close(scalefd);

    int raw_value = atoi(raw_buf);
    double scale_value = strtof(scale_buf, 0);
    printf("raw_value is : %d, scale_value is : %.9f\n", raw_value, scale_value);
    *poutvol=(raw_value * scale_value) / 1000.0;

    return 0;
}

int main()
{
	double Temp_LPD = 0, Temp_FPD = 0,Temp_PL = 0;

	if(Get_Temp("temp0_ps", &Temp_LPD) == 0)printf("Temp_LPD : %.2f\n", Temp_LPD);
	else printf("error while read Temp_LPD !\n");

	if(Get_Temp("temp1_remote", &Temp_FPD) == 0)printf("Temp_FPD : %.2f\n", Temp_FPD);
	else printf("error while read Temp_FPD !\n");

	if(Get_Temp("temp2_pl", &Temp_PL) == 0)printf("Temp_PL : %.2f\n", Temp_PL);
	else printf("error while read Temp_PL !\n");

	double VCCPSINTLP, VCCPSINTFP, VCCPSAUX, VCCPSDDR, VCCPSIO3, VCCPSIO0, VCCPSIO1, VCCPSIO2, PSMGTRAVCC, PSMGTRAVTT, VCCAMS0;

	if(Get_Voltage("voltage0_vccpsintlp", &VCCPSINTLP) == 0)printf("VCCPSINTLP : %.2f\n", VCCPSINTLP);
	else printf("error while read VCCPSINTLP !\n");

	if(Get_Voltage("voltage1_vccpsintfp", &VCCPSINTFP) == 0)printf("VCCPSINTFP : %.2f\n", VCCPSINTFP);
	else printf("error while read VCCPSINTFP !\n");

	if(Get_Voltage("voltage2_vccpsaux", &VCCPSAUX) == 0)printf("VCCPSAUX : %.2f\n", VCCPSAUX);
	else printf("error while read VCCPSAUX !\n");

	if(Get_Voltage("voltage3_vccpsddr", &VCCPSDDR) == 0)printf("VCCPSDDR : %.2f\n", VCCPSDDR);
	else printf("error while read VCCPSDDR !\n");

	if(Get_Voltage("voltage4_vccpsio3", &VCCPSIO3) == 0)printf("VCCPSIO3 : %.2f\n", VCCPSIO3);
	else printf("error while read VCCPSIO3 !\n");

	if(Get_Voltage("voltage5_vccpsio0", &VCCPSIO0) == 0)printf("VCCPSIO0 : %.2f\n", VCCPSIO0);
	else printf("error while read VCCPSIO0 !\n");

	if(Get_Voltage("voltage6_vccpsio1", &VCCPSIO1) == 0)printf("VCCPSIO1 : %.2f\n", VCCPSIO1);
	else printf("error while read VCCPSIO1 !\n");

	if(Get_Voltage("voltage7_vccpsio2", &VCCPSIO2) == 0)printf("VCCPSIO2 : %.2f\n", VCCPSIO2);
	else printf("error while read VCCPSIO2 !\n");

	if(Get_Voltage("voltage8_psmgtravcc", &PSMGTRAVCC) == 0)printf("PSMGTRAVCC : %.2f\n", PSMGTRAVCC);
	else printf("error while read PSMGTRAVCC !\n");

	if(Get_Voltage("voltage9_psmgtravtt", &PSMGTRAVTT) == 0)printf("PSMGTRAVTT : %.2f\n", PSMGTRAVTT);
	else printf("error while read PSMGTRAVTT !\n");

	if(Get_Voltage("voltage10_vccams", &VCCAMS0) == 0)printf("VCCAMS0 : %.2f\n", VCCAMS0);
	else printf("error while read VCCAMS0 !\n");

	double VCCINT, VCCAUX, VCCVREFP, VCCVREFN, VCCBRAM, VCCPLINTLP, VCCPLINTFP, VCCPLAUX, VCCAMS1;

	if(Get_Voltage("voltage11_vccint", &VCCINT) == 0)printf("VCCINT : %.2f\n", VCCINT);
	else printf("error while read VCCINT !\n");

	if(Get_Voltage("voltage12_vccaux", &VCCAUX) == 0)printf("VCCAUX : %.2f\n", VCCAUX);
	else printf("error while read VCCAUX !\n");

	if(Get_Voltage("voltage13_vccvrefp", &VCCVREFP) == 0)printf("VCCVREFP : %.2f\n", VCCVREFP);
	else printf("error while read VCCVREFP !\n");

	if(Get_Voltage("voltage14_vccvrefn", &VCCVREFN) == 0)printf("VCCVREFN : %.2f\n", VCCVREFN);
	else printf("error while read VCCVREFN !\n");

	if(Get_Voltage("voltage15_vccbram", &VCCBRAM) == 0)printf("VCCBRAM : %.2f\n", VCCBRAM);
	else printf("error while read VCCBRAM !\n");

	if(Get_Voltage("voltage16_vccplintlp", &VCCPLINTLP) == 0)printf("VCCPLINTLP : %.2f\n", VCCPLINTLP);
	else printf("error while read VCCPLINTLP !\n");

	if(Get_Voltage("voltage17_vccplintfp", &VCCPLINTFP) == 0)printf("VCCPLINTFP : %.2f\n", VCCPLINTFP);
	else printf("error while read VCCPLINTFP !\n");

	if(Get_Voltage("voltage18_vccplaux", &VCCPLAUX) == 0)printf("VCCPLAUX : %.2f\n", VCCPLAUX);
	else printf("error while read VCCPLAUX !\n");

	if(Get_Voltage("voltage19_vccams", &VCCAMS1) == 0)printf("VCCAMS1 : %.2f\n", VCCAMS1);
	else printf("error while read VCCAMS1 !\n");
}
