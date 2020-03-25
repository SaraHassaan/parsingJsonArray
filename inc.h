/*
 * inc.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sara
 */

#ifndef _INC_H_
#define _INC_H_

unsigned char GetArrayObject(char*jsonArr, int obj_num, char*objOut);
unsigned char isEmptyStack(char *s);

#define URL "app.fakejson.com"
#define PORT  "80"
#define SIZE_BUFFER_REQ  2*512
#define SIZE_BUFFER_RES (3*1024)+1
#define SIZE_BYTE_RECV   1024

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include"connection.h"

#endif /* INC_H_ */
