
SERVER = ircserv

SRC_DIR = src/
BUILD_DIR = build/

CP = c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address

SRC =  main.cpp Server.cpp Client.cpp Channel.cpp
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(BUILD_DIR), $(OBJ))

all : $(SERVER)

$(BUILD_DIR)%.o : $(SRC_DIR)%.cpp
	$(CP) -c $< -o $@

$(SERVER) : $(BUILD_DIR) $(OBJS)
	$(CP) $(OBJS) -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean :
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(SERVER)

re : fclean all




