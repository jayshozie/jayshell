.DEFAULT_GOAL := release
# TODO: will automate the compiler at some point too
CC = gcc
# needed compiler flags. will change this so that it works with clang too.
CFLAGS = -Wall -Wextra -I./include/ -I./builtins/ -I./src/
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
TARGET = ./jayshell

BK   := \033[30m
R     := \033[31m
G   := \033[32m
Y  := \033[33m
B    := \033[34m
M := \033[35m
C    := \033[36m
W   := \033[37m
BO    := \033[1m
RS   := \033[0m

run: run-release

run-debug: debug
	$(TARGET)
debug: CFLAGS += -g
debug: jayshell

run-release: release
	$(TARGET)
release: CFLAGS += -O3
release: jayshell

check:
	@echo -e "$(B)$(BO)=== Syntax Check via GCC ===$(RS)"
	$(CC) -fsyntax-only $(CFLAGS) $(SRCS)
	@echo -e "$(B)$(BO)=== Clang-Tidy ===$(RS)"
	@if command -v clang-tidy > /dev/null; then \
		clang-tidy $(CLANG_TIDY_FLAGS) $(SRCS) -- $(CFLAGS) \
			&& echo -e "$(G)$(BO)[PASS] Check cleared.$(RS)"; \
	else \
		echo -e "$(R)$(BO)[ERROR] clang-tidy not found.$(RS)"; \
	fi

expand:
	@echo 'Expanding macros to intermediate (*.i) files...'
	@rm -rf debug_preproc
	@mkdir -p debug_preproc
	@$(foreach FILE, $(SRCS), \
		$(CC) -E -P $(CFLAGS) $(FILE) -o debug_preproc/$(notdir $(FILE:.c=.i));)
	@echo 'Expansion complete. Check debug_preproc/.'

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f jayshell jayshell.hex
	rm -rf $(OBJDIR)
	rm -rf debug_preproc/

help:
	@echo
	@echo -e "$(Y)=====================================================================$(RS)"
	@echo -e "$(Y)|                        $(R)$(BO)Jayshell's Makefile$(RS)                        $(Y)|$(RS)"
	@echo -e "$(Y)=====================================================================$(RS)"
	@echo -e "$(Y)| $(M)$(BO)Usage:$(RS)                                                            $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make run$(RS)            $(B)$(BO)Alias for release-run$(RS)                      $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make run-release$(RS)    $(B)$(BO)Build jayshell for release and run it$(RS)      $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make run-debug$(RS)      $(B)$(BO)Build jayshell for debug and run it$(RS)        $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make release$(RS)        $(B)$(BO)Build jayshell for release$(RS)                 $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make debug$(RS)          $(B)$(BO)Build jayshell with debugging information$(RS)  $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make check$(RS)          $(B)$(BO)Check for syntax errors$(RS)                    $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make expand$(RS)         $(B)$(BO)Only expansion, no compilation$(RS)             $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make clean$(RS)          $(B)$(BO)Clean object/intermediary/executable files$(RS) $(Y)|$(RS)"
	@echo -e "$(Y)|    $(C)$(BO)make help$(RS)           $(B)$(BO)Print this message$(RS)                         $(Y)|$(RS)"
	@echo -e "$(Y)=====================================================================$(RS)"
	@echo

# jayshell: CFLAGS += -MMD
jayshell: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# compile every source file with its dependencies
obj/%.o : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# cli options
.PHONY: release debug check expand clean help run run-release run-debug

-include $(DEPS)
