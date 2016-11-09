#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "make_log.h"

#include "redis_op.h"

int main(int argc,char* argv[])
{
	int ret = 0;
	char* value = NULL;
	redisContext *conn = NULL;
	conn = rop_connectdb_nopwd("127.0.0.1", "6379");
	
	ret = rop_set_string(conn, "lol", "amm");
	if(ret != 0)
	{
		LOG("test_redis","rop_set_string","---------error");
	}
	printf("---set---ok---\n");
	
	ret = rop_get_string(conn,"lol",&value);
	if(ret != 0)
	{
		LOG("test_redis","rop_get_string","---------error");
	}
	if(value == NULL)
	{
		printf("没有匹配该key的value值\n");
	}
	else
	{
		printf("---get---value:%s---\n",value);
	}
	
	if(value != NULL)
	{
		free(value);
	}
	
	return 0;
}
