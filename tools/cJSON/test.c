#include <stdio.h>
#include "cJSON.h"

int main(int argc, char *argv[])
{
	cJSON * Array = cJSON_CreateArray();
	cJSON_AddItemToArray(Array, cJSON_CreateString("哈"));
	cJSON_AddItemToArray(Array, cJSON_CreateString("哈尔"));
	cJSON_AddItemToArray(Array, cJSON_CreateString("哈尔滨"));
	printf("%s\n", cJSON_Print(Array));

	cJSON_Delete(Array);
	return 0;
}
