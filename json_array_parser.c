#include"inc.h"


/*
 * using stack concept to get a specific object from the array
 * jsonArr(input): array of json objects e.g[{"":"",..},{},{}...]
 */


unsigned char GetArrayObject(char*jsonArr, int obj_num, char*objOut)
{
	int i = 0;
	unsigned char isArray = 0;
	int count_obj = 0;
	int k = 0;
	char stack[1000] = {0};
	int top = -1;

	while(jsonArr[i] != '\0')
	{
		isArray = 1;
		i++;
		if(isArray || jsonArr[i] == '[') /*check if it is array*/
		{
			if(jsonArr[i] == '{' && top == -1)  /*it is a new object (an element) in the array*/
			{
				stack[++top] = '{';              /*push in the stack*/
				count_obj++;                    /*increase the order of the object*/
			}
			else if(jsonArr[i] == '{')         /*it is an object in the element of array(nested object)*/
			{
				stack[++top] = '{';           /*push in stack*/
			}
			else if(jsonArr[i] == '}')         /*the end of the object*/
			{
				stack[top--] = '\0';          /*pop from the stack*/
			}

			if(count_obj == obj_num) /*it is the wanted object in the array*/
			{
				objOut[k++] = jsonArr[i++];

				while(top != -1 && jsonArr[i] != '\0') /* when top = -1 that means the end of the new object (an element of the array)*/
				{
					if(jsonArr[i] == '{')
					{
						stack[++top] = '{';
					}
					else if(jsonArr[i] == '}')
					{
						stack[top--] = '\0';
					}
					objOut[k++] = jsonArr[i++];     /*copy the object you want in objOut*/
				}
				break;
			}
		}
	}

	if(obj_num > count_obj)
	{
		printf("the wanted object(%d)is greater than the number of elements(%d)in the array\n", obj_num, count_obj);
		return 0;
	}

	if(!isEmptyStack(stack) || !isArray) /*error : NO BALANCE BRACKETS or the string is not an array*/
	{
		return 0;
	}

	return 1;
}

unsigned char isEmptyStack(char *s)
{
	if(s[0] == '\0') /*empty stack*/
	{
		return 1;
	}

	return 0;
}
