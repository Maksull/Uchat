CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -pthread -g

OBJDIR = obj
SRCDIR = db db/db_chat db/db_member db/db_message db/db_user handlers handlers/handlers_chat handlers/handlers_message handlers/handlers_user logger utils/json_utils utils/server_utils utils/user_utils utils/db_utils validation
UCHAT = ../uchat_server

SRC = main.c $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
OBJS = $(OBJDIR)/*.o

LIBMX_DIR = ../libraries/libmx
LIBMX_NAME = $(LIBMX_DIR)/libmx.a

CJSON_DIR = ../libraries/cjson
CJSON_NAME = $(CJSON_DIR)/libcjson.a

SSL_DIR = ../libraries/openssl
SSL_FILES:= ../libraries/libcrypto
SSL_INC_FILES:= $(SSL_DIR)

LIB_FLAGS = -lmx -lcjson -lsqlite3 -lssl -lcrypto \
	-L$(LIBMX_DIR) $(LIBMX_NAME) \
	-L$(CJSON_DIR) $(CJSON_NAME) \
	-L$(SSL_FILES) -I$(SSL_INC_FILES)

all: $(UCHAT)

$(UCHAT):
	mkdir $(OBJDIR)
	$(CC) $(CFLAGS) -c $(SRC)
	mv *.o $(OBJDIR)
	$(CC) $(CFLAGS) -o $(UCHAT) $(OBJS) $(LIB_FLAGS)

clean:
	rm -f $(OBJS)
	rm -df $(OBJDIR)

uninstall:
	make clean
	rm -f $(UCHAT)

reinstall:
	make uninstall
	make all
