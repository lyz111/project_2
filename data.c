#include "fcgi_config.h"
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "fcgi_stdio.h"
#include "util_cgi.h"
#include "redis_op.h"
#include "cJSON.h"

#define FDFS_LOG_MODULE       "Data"
#define FDFS_LOG_PROC         "Data_test"
#define FILE_ID_LEN   4096 

int main ()
{
	int ret = 0;
	//char fileid_arr[FIELD_ID_SIZE] = {0};
	RVALUES values = NULL;
	
	while (FCGI_Accept() >= 0) 
	{
       	printf("Content-type: text/html\r\n"
               "\r\n");
		
		redisContext *conn = NULL;
		conn = rop_connectdb_nopwd("127.0.0.1", "6379");
		if(conn == NULL)
		{
			LOG(FDFS_LOG_MODULE,FDFS_LOG_PROC,"----rop_range_list-----error");
		}
		//get list
	    //RVALUES values = &fileid_arr;
		int count =2;
		values = malloc(count* VALUES_ID_SIZE);
		int get_num = 0;
		ret = rop_range_list(conn,"FILE_INFO_LIST",1,2,values,&get_num);
		
		if(ret != 0)
		{
			LOG(FDFS_LOG_MODULE,FDFS_LOG_PROC,"----rop_range_list-----error");
		}
		
		
				
		//组json
		cJSON* root = NULL;
		root = cJSON_CreateObject();
		
		cJSON* games_arr = NULL;
		games_arr = cJSON_CreateArray();
		
		
		int i = 0;
		LOG(FDFS_LOG_MODULE,FDFS_LOG_PROC,"get_num:%d",get_num);
		for (i = 0;i <get_num;i++)
		{
			cJSON* game1 = NULL;
			game1 = cJSON_CreateObject();
			char name_value[100] = {0};
		
			ret = rop_hash_get(conn,"fileid_name_hash",values[i],name_value);
			LOG(FDFS_LOG_MODULE,FDFS_LOG_PROC,"name:%s",name_value);
			if(ret != 0)
			{
				LOG(FDFS_LOG_MODULE,FDFS_LOG_PROC,"----rop_hash_get-----error");
			}

			cJSON_AddStringToObject(game1, "id", values[i]);
			cJSON_AddNumberToObject(game1, "kind", 2);
			cJSON_AddStringToObject(game1, "title_m", name_value);
			cJSON_AddStringToObject(game1, "title_s", "title_s");
			cJSON_AddStringToObject(game1, "descrip", "2016-08-09 11:06:09");
			
			cJSON_AddStringToObject(game1, "picurl_m", "group1/M00/aa.jpg");
			cJSON_AddStringToObject(game1, "picurl_m", "http://192.168.2.108/group1/M00/00/00/wKgCbFepSKeARhoLAAXsKfNoK_k046.jpg");
			cJSON_AddNumberToObject(game1, "pv", 0);
			cJSON_AddNumberToObject(game1, "hot", 0);
			cJSON_AddItemToArray(games_arr,game1);
		}
		
		cJSON_AddItemToObject(root,"games",games_arr);
		
		free(values);
		char* out = NULL;
		out =cJSON_Print(root);
	    cJSON_Delete(root);
		printf("%s\n",out);
			        
	}

    return 0;
}
