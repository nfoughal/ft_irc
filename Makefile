NAME = ircserv

FLAGS = -std=c++98 -Wall -Wextra -Werror

INCLUDE = -I ./include

HEADERS = include/Channel.hpp \
		include/Client.hpp \
		include/irc.hpp \
		include/IrcServer.hpp \
		include/Numerics.hpp \
		include/tools.hpp

SRC = src/Channel.cpp \
		src/Client.cpp \
		src/Command/bot.cpp \
		src/Command/invite.cpp \
		src/Command/join.cpp \
		src/Command/kick.cpp \
		src/Command/mode.cpp \
		src/Command/nick.cpp \
		src/Command/part.cpp \
		src/Command/pass.cpp \
		src/Command/privmsg.cpp \
		src/Command/topic.cpp \
		src/Command/user.cpp \
		src/Command/quit.cpp \
		src/IrcServer.cpp \
		src/main.cpp \
		Tools/Checks.cpp \
		Tools/communicate_tools.cpp \
		Tools/stringTools.cpp

OBG = $(SRC:.cpp=.o)

all : $(NAME)
		@printf "\e[1;31m	██╗██████╗  ██████╗    ███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗ \n"
		@printf "\e[1;31m	██║██╔══██╗██╔════╝    ██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗\n"
		@printf "\e[1;31m	██║██████╔╝██║         ███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝\n"
		@printf "\e[1;31m	██║██╔══██╗██║         ╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗\n"
		@printf "\e[1;31m	██║██║  ██║╚██████╗    ███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║\n"
		@printf "\e[1;31m	╚═╝╚═╝  ╚═╝ ╚═════╝    ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝\n"

$(NAME) : $(OBG)
	@c++ $(FLAGS) $(OBG) -o $(NAME)

%.o : %.cpp $(HEADERS)
	@c++ $(FLAGS) -I ./include -c $< -o $@
	@printf "\e[1;31m%s" $(info Compaling: $@)
	clear

run : all
	@clear; ./ircserv 6667 REDMEGA

clean :
	@rm -rf $(OBG)
	@make clean -C Bot

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C Bot

re : clean all

bot :
	@make -C Bot

re_bot : 
	@make re -C Bot

.PHONY : all clean fclean re bot re_bot
