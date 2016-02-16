#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/10 23:10:35 by jguyet            #+#    #+#              #
#    Updated: 2016/02/12 22:15:51 by jguyet           ###   ########.fr        #
#                                                                              #
#******************************************************************************#


.PHONY:			all, libft, clean, fclean, re

CC =			gcc

CFLAG =			-Wall -Wextra -Werror

NAME =			ft_select

SRC_PATH =		./src/

OBJ_PATH =		./obj/

LIBFT_PATH =	./libft/

INCLIBFT =		./includes/

INC_PATH =		./includes/

SRC_NAME =		main.c			term.c			list.c\
				key.c			tools.c			signal.c\
				sorting.c		print_lenght.c

OBJ_NAME =		$(SRC_NAME:.c=.o)

LIBFT_NAME =	libft.a

INC_NAME =		select.h

SRC =			$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ =			$(addprefix $(OBJ_PATH),$(OBJ_NAME))

LIBFT =			$(addprefix $(LIBFT_PATH),$(LIBFT_NAME))

INC =			$(addprefix $(INC_PATH),$(INC_NAME))

SELECT_FLAG =	-ltermcap

I = 0

LIBFT_FLAG =	-L$(LIBFT_PATH) -lft

all:			libft $(NAME)

$(NAME):		$(OBJ)
				@$(CC) $(LIBFT_FLAG) $(SELECT_FLAG) -o $@ $^
				@echo "\nCompiling" [ $(NAME) ] "\033[32mSUCCESS\033[00m"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c $(INC)
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAG) -I$(INC_PATH) -I$(INCLIBFT) -o $@ -c $<
				@echo "Loading   [\033[36m" $(notdir $(@:.o=.c)) "\033[00m]\033[A"

libft:			$(LIBFT)

$(LIBFT):		$(LIBFT_PATH)
				@make -C $(LIBFT_PATH)

clean:
				@make -C $(LIBFT_PATH) clean
				@rm -f $(OBJ)
				@echo "Cleaning " [ $(NAME) ] "..." "\033[35mOK\033[00m"

fclean:			clean
				@rm -f $(OBJ)

re:				fclean all
