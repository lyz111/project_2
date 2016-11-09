#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "make_log.h"

#include "cJSON.h"

void test_create_json(char *str_out)
{
	cJSON* root = NULL;
	root = cJSON_CreateObject();
	
	cJSON_AddStringToObject(root, "name", "lyz");
    //cJSON_AddItemToObject(root, "name", cJSON_CreateString("zhang3"));
    cJSON_AddNumberToObject(root, "age", 18);
    cJSON_AddNumberToObject(root, "id", 0001);
	
	cJSON* girls_array = NULL;
	girls_array = cJSON_CreateArray();
	cJSON_AddItemToArray(girls_array, cJSON_CreateString("marong"));
	cJSON_AddItemToArray(girls_array, cJSON_CreateString("wanger"));
	cJSON_AddItemToArray(girls_array, cJSON_CreateString("yiwei"));
	
	cJSON_AddItemToObject(root,"girls",girls_array);
	
	char* out = NULL;
	out =cJSON_Print(root);
    cJSON_Delete(root);
	
	strcpy(str_out,out);
   
}


void test_parse_json(char *str)
{
	cJSON* root = NULL;
	root = cJSON_Parse(str);
	
	cJSON* name = NULL;
	name = cJSON_GetObjectItem(root,"name");
	printf("%s:%s\n",name->string,name->valuestring);
	
	cJSON* age = NULL;
	age = cJSON_GetObjectItem(root,"age");
	printf("%s:%d\n",age->string,age->valueint);
	
	cJSON* id = NULL;
	id = cJSON_GetObjectItem(root,"id");
	printf("%s:%d\n",id->string,id->valueint);
	
	cJSON* girls_array = NULL;
	girls_array = cJSON_GetObjectItem(root,"girls");
	int num = cJSON_GetArraySize(girls_array);
	int i = 0;
	for(i = 0;i<num;i++)
	{
		cJSON *temp = cJSON_GetArrayItem(girls_array, i);
        printf("girls[%d]:%s\n",i, temp->valuestring);
	}
	cJSON_Delete(root);
}


int main(int argc,char* argv[])
{
	char str[4096] = {0};

    //创建一个json格式的数据
    test_create_json(str);

    printf("%s\n", str);

    
    printf("===================\n"); 
    //解析一个json格式的数据
    test_parse_json(str);
	
	return 0;
}