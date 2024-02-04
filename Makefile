# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 14:39:40 by aamhamdi          #+#    #+#              #
#    Updated: 2024/02/02 16:33:29 by aamhamdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = ircserv
BOT = bot

SRC_DIR = src/
CMD_DIR = src/commands/
BUILD_DIR = build/
BOT_DIR = src/bot/

CP = c++ -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address 

SRC_INC = Server.hpp Client.hpp Channel.hpp Connection.hpp ClientSource.hpp ChannelSource.hpp ChannelMode.hpp 
CMD_INC = ACommand.hpp Pass.hpp Nick.hpp User.hpp Join.hpp PrivMsg.hpp Part.hpp Kick.hpp Invite.hpp Mode.hpp Quit.hpp Topic.hpp 

SRC =  main.cpp Server.cpp Client.cpp Channel.cpp Connection.cpp ClientSource.cpp ChannelSource.cpp ChannelMode.cpp 
CMD =  ACommand.cpp Pass.cpp Nick.cpp User.cpp Join.cpp PrivMsg.cpp Part.cpp Kick.cpp Invite.cpp Mode.cpp Quit.cpp Topic.cpp 

B_SRC = bot_main.cpp Bot.cpp weather.cpp manual.cpp

SRCS = $(addprefix $(SRC_DIR), $(SRC))
CMDS = $(addprefix $(CMD_DIR), $(CMD))
B_SRCS = $(addprefix $(BOT_DIR), $(B_SRC))

SRC_INCS = $(addprefix $(SRC_DIR), $(SRC_INC))
CMD_INCS = $(addprefix $(CMD_DIR), $(CMD_INC))

OBJ = $(SRC:.cpp=.o) $(CMD:.cpp=.o) 
OBJS = $(addprefix $(BUILD_DIR), $(OBJ))

B_OBJ = $(B_SRC:.cpp=.o)
B_OBJS = $(addprefix $(BUILD_DIR), $(B_OBJ))

all : $(SERVER)

$(BUILD_DIR)%.o : $(SRC_DIR)%.cpp $(SRC_INCS)
	$(CP) -c $< -o $@

$(BUILD_DIR)%.o : $(CMD_DIR)%.cpp $(CMD_INCS)
	$(CP) -c $< -o $@
	
$(BUILD_DIR)%.o : $(BOT_DIR)%.cpp
	$(CP) -c $< -o $@

$(SERVER) : $(BUILD_DIR) $(OBJS)
	$(CP) $(OBJS) -o $@

$(BOT) : $(BUILD_DIR) $(B_OBJS)
	$(CP) $(B_OBJS) -lcurl -o $@

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

clean :
	rm -rf $(BUILD_DIR)

c : 
	rm -f leaks fds leaks1

fclean: clean
	rm -f $(SERVER)
	rm -f $(BOT)

re : fclean all bot



# SRC_DIRS = src src/commands
# INCLUDE_DIR = src
# OBJ_DIR = obj

# # Compiler and flags
# CC =  c++  -std=c++98 -fsanitize=address -g
# MLX_FLAGS = -lmlx -framework appkit -framework openGl -Ofast
# I = -I $(INCLUDE_DIR)
# CFLAGS = -Wall -Werror -Werror $(I)
# LDFLAGS =

# # Source files
# SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
# HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

# # Object files
# OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# # Target executable
# NAME = ircserv

# # NAMEs
# all: $(OBJ_DIR) $(NAME)

# $(OBJ_DIR):
# 	@echo "Create object direcotry"
# 	@mkdir -p $(OBJ_DIR)

# $(OBJ_DIR)/%.o: $(SRCS) $(HEADERS)
# 	$(CC) $(CFLAGS) -c $(filter %/$(notdir $*).cpp,$(SRCS)) -o $@

# $(NAME): $(OBJS)
# 	@echo "Linking"
# 	$(CC) $(CFLAGS) $(MLX_FLAGS) $^ -o $@


# clean:
# 	@echo "Clean"
# 	@rm -rf $(OBJ_DIR)

# fclean: clean
# 	@rm -rf $(NAME)

# re: fclean all