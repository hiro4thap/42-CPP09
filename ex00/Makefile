NAME		= btc

COMPILE		= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98 -MMD

SRC_DIR 	= ./
OBJ_DIR 	= obj/

SRC			= main.cpp \
			  Log.cpp \
			  BitcoinExchange.cpp

OBJ			= $(SRC:.cpp=.o)

SRCS		= $(addprefix $(SRC_DIR), $(SRC))
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ))
DEPS		= $(OBJS:.o=.d)

all:$(NAME)

-include $(DEPS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(COMPILE) $(CFLAGS) -o $@ -c $<

$(NAME):$(OBJS)
	$(COMPILE) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(OBJ_DIR)

fclean:clean
	rm -rf $(NAME)

re:fclean all

.PHONY:all clean fclean re
