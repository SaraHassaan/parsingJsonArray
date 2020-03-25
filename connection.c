#include "inc.h"

int createSocket()
{
	int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	return sockfd;
}

int get(char *uri, char* bodyRes)
{
    int result = 0;
	char buffReq[SIZE_BUFFER_REQ] = {0};

	/*http get request*/
	strcat(buffReq, "GET /");
	strcat(buffReq, uri);
	strcat(buffReq, " HTTP/1.1\r\nHost: ");
	strcat(buffReq, URL);
	strcat(buffReq, ": ");
	strcat(buffReq, PORT);
	strcat(buffReq, "\r\nContent-Type: application/json");
	strcat(buffReq, "\r\nAccept: application/json");

	/*connect,send,recv */
	result = connectToServer(buffReq, bodyRes);
	if(result < 0)
	{
		return result;
	}

	return  1;
}

int post(char*data, char*endPoint, char*bodyRes)
{
	int result = 0;
    int lenData = 0;

	char buffReq[SIZE_BUFFER_REQ] = {0};
	char lenStr[10]={0};

	sprintf(lenStr, "%d", (int)strlen(data));

	strcat(buffReq,"POST /");
	strcat(buffReq,endPoint);
	strcat(buffReq," HTTP/1.1\r\nHost: ");
	strcat(buffReq,URL);
	strcat(buffReq,": ");
	strcat(buffReq, PORT);
	strcat(buffReq, "\r\nContent-Type: application/json");
	strcat(buffReq, "\r\nAccept: application/json");
	strcat(buffReq, "\r\nContent-Length: ");
	strcat(buffReq, lenStr);
	strcat(buffReq, "\r\n\r\n");
	strcat(buffReq, data);

	printf("REQ\n=========================\n");
	printf("%s\n", buffReq);

	/*connect,send,recv */
	result = connectToServer(buffReq, bodyRes);
	if(result < 0)
	{
		return result;
	}

	return  1;
}

int connectToServer(char*Req, char*Res)
{
	int result;
	int statusCode;
	int byteRecvN;
	int bodyBeginFlag = 0;
	int bodyPos;
	int i = 0, j = 0;
	int sockfd;
	char resRcevBuf[SIZE_BUFFER_REQ] = {0};

	struct sockaddr_in serverAdd;
	struct hostent *serverInfo;

	memset(&serverAdd, 0, sizeof(struct sockaddr_in));
	memset(&serverInfo, 0, sizeof(struct hostent));

	sockfd = createSocket();
	if(sockfd < 0)
	{
		printf("ERROR: opening socket");
		return -1;
	}

    serverInfo = gethostbyname(URL); /*get the ip of this url by storing it in serverInfo pointer to struct*/

    if(serverInfo == NULL)
	{
		printf("ERROR: no host");
		return -1;
    }

    memcpy((char *)&serverAdd.sin_addr.s_addr, (char *)serverInfo->h_addr, serverInfo->h_length);
	serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = htons(atoi(PORT));

	result = connect(sockfd, (const struct sockaddr*)&serverAdd, sizeof(struct sockaddr_in));
	if(result < 0)
	{
		printf("ERROR: connection failed");
		return result;
	}
	else
	{
	    printf("\nSUCCESS CONNECTION\n");
	}

	/* Send message to the server */
    result = write(sockfd, Req, strlen(Req)+1);
    if (result < 0)
    {
        printf("%d\n", result);
        printf("ERROR: send request failed");
        return -1;
    }

	if((byteRecvN=read(sockfd, resRcevBuf, 16)) > 0)
	{
	    printf("http status response code : %s\n", resRcevBuf);
		getSatusCode(resRcevBuf,&statusCode);
		if(statusCode != 200)
		{
		    printf("%d\n", statusCode);
			printf("request res failed");
            return -1;
		}
	}

    memset(resRcevBuf, 0, sizeof(resRcevBuf));

	while ((byteRecvN = read(sockfd, resRcevBuf, SIZE_BYTE_RECV)) > 0)
	{
		if(bodyBeginFlag == 0)
		{
			bodyPos = getTheBeginningBodyPos(resRcevBuf);
			if(bodyPos)
			{
				bodyBeginFlag = 1;
				i = bodyPos+1;
			}
			printf("the postion of the body = %d\n", bodyPos);
		}

		if(bodyBeginFlag == 1)
		{
			while(resRcevBuf[i] != '\0')
			{
				Res[j++] = resRcevBuf[i++];
			}
		}

	   memset(resRcevBuf, 0, sizeof(resRcevBuf));
	}

	if(byteRecvN < 0)
	{
		printf("recieving failed");
        return -1;
	}

	printf("BODY RES\n=================================\n");
	printf("%s\n", Res);

    close(sockfd);
    return 1;
}


/*
 * str (input) : (array of char)status code response..>e.g ..>HTTP/1.1 200 OK
 * statusCodePtr (output) : it is the code in the array str e.g..>200
 * */
void getSatusCode(const char*str, int *statusCodePtr)
{
	int j=0;
	int i=0;
	char code[4]={0};

	while(str[i] != '\0')
	{
		if( str[i] ==' ' && i == 8)        /*check for space in the first line*/
		{
			i++;
			code[j]=str[i];
			while(str[i+1] !=' ')          /*if j+1 is pointed to space that mean the number is stored in the word variable  */
			{
				i++;
				j++;
				code[j]=str[i];
		    }
		}

       i++;
   }
   *statusCodePtr = atoi(code);
}

int getTheBeginningBodyPos(const char*str)
{
	int pos=0;
	int i=0;
	while(str[i] !='\0')
	{
		if( str[i] =='\r' && str[i+1] =='\n' && str[i+2] =='\r' && str[i+3] =='\n')
		{
			pos = i+3;                        /*pos = the last index (i+1) that points to \n */
			break;
		}
	    i++;
	}

	return pos;
}
