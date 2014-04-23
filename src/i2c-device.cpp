#include <stdio.h>
#include <sys/ioctl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/i2c-dev.h>

#include "i2c-device.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : I2CDevice
* 
* PURPOSE : Constructor for rd/wr to i2c devices
*
*-----------------------------------------------------------------------------*/
I2CDevice::I2CDevice(int i2c_bus)
{
    this->i2c_bus = i2c_bus;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : I2CRead
* 
* PURPOSE : Read the i2c-devices register values into a buffer
*
*-----------------------------------------------------------------------------*/

int I2CDevice::I2CRead(char* filename)
{
    int file = open(filename,O_RDONLY);
    char readBuff[100];
    if ( file < 0 )
        printf("Fopen failed and returned errno %s \n", strerror(errno));
    else
    {
	read(file,readBuff,1);
       // fgets(readBuff,10,file);
        close(file);
    }
    printf("The value read is %s",readBuff);
//    file = ioctl(file,I2C_SLAVE,answer); 
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : I2CWriteToRTC
* 
* PURPOSE : Write to the i2c-device register
*
*-----------------------------------------------------------------------------*/
int I2CDevice::I2CWriteToRTC(struct rtc_time rt)
{   
    char* fileHandler;
    sprintf(fileHandler,"/dev/rtc%d",i2c_bus);
    int file = open(fileHandler,O_RDWR);
    
    if (file < 0 )
    {
        printf("Open failed and returned errno %s \n", strerror(errno));

    }
    else
    {
        file = ioctl(file,RTC_SET_TIME,&rt);
        if ( file < 0 )
        {
            printf("Ioctl failed and returned errno %s \n", strerror(errno));
        }
        
    }
    close(file);            
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : I2CWrite
* 
* PURPOSE : Write to the i2c-device register
*
*-----------------------------------------------------------------------------*/
int I2CDevice::I2CWrite()
{
        


    

}
