/*

 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sara Hassaan
 */
#include "inc.h"

int main()
{
    int result;
	char bodyRes[5*SIZE_BUFFER_RES] = {0};
	char objOut[1000] = {0};
	char data[1000] = "{\"token\": \"8Nr7U50Yid4hGqID5HipOw\",\"data\": {\"id\": \"personNickname\",\"email\": \"internetEmail\",\"gender\": \"personGender\",\"_repeat\": 5}}";

	/*post method of HTTP protocol*/
	post(data, "q", bodyRes);/*q(endpoint), access the end point q using post method*/

	/*body response is an array of objects , get the object number 4 in this array*/
	result = GetArrayObject(bodyRes, 4, objOut);

	if(result)
	{
	    printf("\nthe object %s\n", objOut);
	}

    return 0;
}
