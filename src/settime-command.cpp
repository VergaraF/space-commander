#include "settime-command.h"
#include <string.h>
#include <cerrno>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SpaceString.h>
#include <shakespeare.h>
#include "commands.h"


void* SetTimeCommand::Execute(){
    struct timeval tv;
    char *result;
    result = (char*)malloc(sizeof(char) * 10);

    
    result[0] = SETTIME_CMD;
    tv.tv_sec = GetSeconds();   
    tv.tv_usec = 0;
    memcpy(result+2, &tv.tv_sec, sizeof(time_t)); 
    if (settimeofday(&tv, 0) != 0){
        perror ("Error! settimeofday()\n");
        result[1] = FAILURE_CMD;
        return (void*)result;        
    }
    result[1] = SUCCES_CMD;
    return (void*)result;
}
void* SetTimeCommand::ParseResult(const char *result)
{
    if(!result) {
        return (void*)0;
    }
    static struct InfoBytesSetTime info_bytes = {0};
    info_bytes.time_status = result[1];
    info_bytes.time_set = SpaceString::getTimet(result+2);

    FILE* logfile;
    logfile=Shakespeare::open_log("/var/log/job-template",PROCESS);
     // write to log via shakespeare
    int test = info_bytes.time_set;
    char buffer[80];
   
    if(info_bytes.time_status == '1')
       sprintf(buffer,"SetTime success. Time set to %d seconds since epoch",info_bytes.time_set);
    else
       sprintf(buffer,"SetTime failure. Time failed to set %d seconds since epoch",info_bytes.time_set);

   if(logfile!=NULL) {
        Shakespeare::log(logfile, Shakespeare::NOTICE, PROCESS, buffer);
        } 
   
    return (void*)&info_bytes;
}
