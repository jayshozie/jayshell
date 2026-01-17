# TODO: will automate the compiler at some point too
CC = gcc

# needed compiler flags. will change this so that it works with clang too.
CFLAGS = -MMD -Wall -Wextra -I./include/ -I./builtins/ -I./src/

# required libraries
LIBS = -lreadline

# automatation of source files
SRCS_DIR = src builtins
SRCS = $(wildcard $(addsuffix /*.c, $(SRCS_DIR)))

# automation of object files
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

# automation of dependencies
DEPS = $(OBJS:.o=.d)
vpath %.c src builtins

debug: CFLAGS += -g
debug: jayshell

release: CFLAGS += -O3
release: jayshell

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f jayshell
	rm -rf $(OBJDIR)

GREEN  := $(shell tput -Txterm setaf 2)
RESET  := $(shell tput -Txterm sgr0)

help:
	@echo ''
	@echo 'Usage:'
	@echo '  ${GREEN}make release${RESET}   Build the base Docker image'
	@echo '  ${GREEN}make debug${RESET}     Run the container with your local dotfiles mounted'
	@echo '  ${GREEN}make clean${RESET}     Remove the Docker image'
	@echo '  ${GREEN}make help${RESET}      Remove the Docker image'
	@echo ''

jayshell : $(OBJS)
	$(CC) $(CFLAGS) -o jayshell $(OBJS) $(LIBS)

# compile every source file with its dependencies
obj/%.o : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# cli options
.PHONY: release debug clean help

-include $(DEPS)
