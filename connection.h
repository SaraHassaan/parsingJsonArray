#ifndef _CONNECTION_H_
#define _CONNECTION_H_

int createSocket();
int get(char *uri, char* body);
int post(char*data, char*endPoint, char*bodyRes);
int connectToServer(char*Req, char*Res);
int getTheBeginningBodyPos(const char*str);
void getSatusCode(const char*str, int *statusCodePtr);

#endif
