# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/28 12:54:53 by jbert             #+#    #+#              #
#    Updated: 2015/06/05 14:08:07 by jbert            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		=	serveur
CLIENT		=	client

DEBUG		= no
ifeq ($(DEBUG),no)
	FLAGS	= -Wall -Werror -Wextra
else
	FLAGS	= -g3
endif

SRC_SV	=	serv.c serv2.c serv3.c all.c all2.c
SRC_CL	=	client.c client2.c all.c all2.c

OBJ_SV	=	$(SRC_SV:.c=.o)
OBJ_CL	=	$(SRC_CL:.c=.o)

INC 		= 
LIBFLAGS 	= -L./libftprintf/ -lftprintf
SRCDIR_SV	= ./
SRCDIR_CL	= ./
OBJDIR  	= ./obj/
INCDIRLIB	= 
INCDIR		= ./
SRCS_SV		= $(addprefix $(SRCDIR_SV), $(SRC_SV))
OBJS_SV		= $(addprefix $(OBJDIR), $(OBJ_SV))
SRCS_CL		= $(addprefix $(SRCDIR_CL), $(SRC_CL))
OBJS_CL		= $(addprefix $(OBJDIR), $(OBJ_CL))

.SILENT:

all : serveur client

$(SERVER) :
ifeq ($(DEBUG),yes)
		echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
		echo "\\033[1;31mCompilation of server with -Wall -Wextra -Werror...\\033[0;39m"
endif
		echo "\\033[1;34mGenerating server's objects... Please wait.\\033[0;39m"
		Make -C libftprintf/
			gcc $(FLAGS) -c $(SRCS_SV)
			echo "compiling $(SERVER)..."
			mkdir -p $(OBJDIR)
			mv $(OBJ_SV) $(OBJDIR)
			gcc $(FLAGS) -o $(SERVER) $(OBJS_SV) $(LIBFLAGS)
			echo "$(SERVER) has been created !"

$(CLIENT) :
ifeq ($(DEBUG),yes)
		echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
		echo "\\033[1;31mCompilation of client with -Wall -Wextra -Werror...\\033[0;39m"
endif
		echo "\\033[1;34mGenerating client's objects... Please wait.\\033[0;39m"
		Make -C libftprintf/
			gcc $(FLAGS) -c $(SRCS_CL)
			echo "compiling $(CLIENT)..."
			mkdir -p $(OBJDIR)
			mv $(OBJ_CL) $(OBJDIR)
			gcc $(FLAGS) -o $(CLIENT) $(OBJS_CL) $(LIBFLAGS)
			echo "$(CLIENT) has been created !"

toto :
	echo "done"

.PHONY: 	all serveur client clean fclean re

clean : 
			Make -C ./libftprintf/ clean
			rm -rf $(OBJS_SV)
			rm -rf $(OBJS_CL)
			rm -rf $(OBJDIR)
			echo "objects files has been removed !"

fclean :	clean
			Make -C ./libftprintf/ fclean
			rm -rf $(SERVER)
			rm -rf $(CLIENT)
			echo "$(SERVER) has been removed !"
			echo "$(CLIENT) has been removed !"

re		: 	fclean all

git :
			git add .
			echo "Enter Your Commit : "
			read root_path ; git commit -m "$$root_path"
			git push
