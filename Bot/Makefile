NAME = ../irc_bot

FLAGS = -std=c++98 -Wall -Wextra -Werror

INCLUDE = -I ./include

HEADERS = include/Bot.hpp \
	include/Numerics.hpp \
	include/BotToken.hpp \
	include/tools.hpp

SRC = src/Bot.cpp \
	src/main.cpp \
	Tools/Checks.cpp \
	Tools/communicate_tools.cpp \
	Tools/stringTools.cpp

OBG = $(SRC:.cpp=.o)

all : $(NAME)
		@printf "\e[0;31m	██████╗  ██████╗ ████████\n"
		@printf "\e[0;31m	██╔══██╗██╔═══██╗╚══██╔══\n"
		@printf "\e[0;31m	██████╔╝██║   ██║   ██║\n"
		@printf "\e[0;31m	██╔══██╗██║   ██║   ██║\n"
		@printf "\e[0;31m	██████╔╝╚██████╔╝   ██║\n"
		@printf "\e[0;31m	╚═════╝  ╚═════╝    ╚═╝\n"

$(NAME) : $(OBG)
	@c++ $(FLAGS) $(OBG) -o $(NAME)

%.o : %.cpp $(HEADERS)
	@c++ $(FLAGS) -I ./include -c $< -o $@
	@echo $(info Compaling: $@)
	clear

clean :
	@rm -rf $(OBG)

fclean : clean
	@rm -rf $(NAME) 

re : clean all

.PHONY : all clean fclean re
