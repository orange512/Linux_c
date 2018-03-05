OBJ = api_redis.o cJSON.o ./lucky_money.o ./api_mysql.o
###########################################

all:$(OBJ)
	gcc $(OBJ) -g -o luckymoney  -lpthread -Wall  -I /usr/include/mysql -L /usr/lib/mysql -l mysqlclient -lz -lm -lhiredis `pkg-config --cflags --libs glib-2.0`
%.o:%.c
	gcc -c $< -o $@ -I   -Wall
clean:
	rm -rf $(OBJ)
