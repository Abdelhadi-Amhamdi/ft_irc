
SERVER = ircserv

SRC_DIR = src/
CMD_DIR = src/cmd/
BUILD_DIR = build/

CP = c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g

SRC =  main.cpp Server.cpp Client.cpp Channel.cpp
CMD =  ACommand.cpp Pass.cpp Nick.cpp

SRCS = $(addprefix $(SRC_DIR), $(SRC)) 
CMDS = $(addprefix $(CMD_DIR), $(CMD))

OBJ = $(SRC:.cpp=.o) $(CMD:.cpp=.o)
OBJS = $(addprefix $(BUILD_DIR), $(OBJ))

all : $(SERVER)

$(BUILD_DIR)%.o : $(SRC_DIR)%.cpp
	$(CP) -c $< -o $@

$(BUILD_DIR)%.o : $(CMD_DIR)%.cpp
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




