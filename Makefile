
CC=gcc
CPPFLAGS= -I./include  
CFLAGS=-Wall 
LIBS=-lpthread -lhiredis

#找到当前目录下所有的.c文件
src = $(wildcard *.c)

#将当前目录下所有的.c  转换成.o给obj
obj = $(patsubst %.c, %.o, $(src))


test_fdfs_client = ./test/fdfs_client_test
main = main_test
test_redis = ./test/test_redis

target=$(test_fdfs_client)  $(main)  $(test_redis)


ALL:$(target)


#生成所有的.o文件
$(obj):%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) 


#fdfs_client_test程序
$(test_fdfs_client):./test/fdfs_client_test.o  make_log.o
	$(CC) $^ -o $@ $(LIBS)

#main程序
$(main):main.o make_log.o
	$(CC) $^ -o $@ $(LIBS)

#test_redis程序
$(test_redis):./test/test_redis.o make_log.o redis_op.o
	$(CC) $^ -o $@ $(LIBS)

#clean指令

clean:
	-rm -rf $(obj) $(target) ./test/*.o

distclean:
	-rm -rf $(obj) $(target) ./test/*.o

#将clean目标 改成一个虚拟符号
.PHONY: clean ALL distclean
