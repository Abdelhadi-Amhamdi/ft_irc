
SERVER = ircserv

SRC_DIR = src/
CMD_DIR = src/commands/
BUILD_DIR = build/

CP = c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g

SRC =  main.cpp Server.cpp Client.cpp Channel.cpp Connection.cpp ClientSource.cpp ChannelSource.cpp ChannelMode.cpp
CMD =  ACommand.cpp Pass.cpp Nick.cpp User.cpp Join.cpp PrivMsg.cpp Part.cpp Kick.cpp Invite.cpp Mode.cpp Quit.cpp Topic.cpp

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
	@mkdir $(BUILD_DIR)

clean :
	@echo cleaning... 
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(SERVER)

re : fclean all



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