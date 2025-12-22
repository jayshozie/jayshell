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

# default make is debug
all: debug

debug: CFLAGS += -g
debug: jayshell

release: CFLAGS += -O3
release: jayshell

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f jayshell
	rm -rf $(OBJDIR)

jayshell : $(OBJS)
	$(CC) $(CFLAGS) -o jayshell $(OBJS) $(LIBS)

# compile every source file with its dependencies
obj/%.o : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# cli options
.PHONY: all release debug clean

-include $(DEPS)
