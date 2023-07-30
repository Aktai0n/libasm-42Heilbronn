
# -------------------- config -------------------------

NAME := libasm.a
TESTER_NAME := tester

OS := $(shell uname -s)


# assembler config
AS = nasm
ASFLAGS = -wall -iinc

ifeq ($(OS), Darwin) # MacOS
ASFLAGS += -f macho64 -dMACOS=1
else ifeq ($(OS), Linux) # Linux
ASFLAGS += -f elf64 -dLINUX=1
else
$(error Unsupported operating system: $(OS))
endif


# linker config
LD = ld
LDFLAGS = 

# archive (library) config
AR = ar
ARFLAGS = rcs

# compiler config
CC = cc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion

ifneq ($(VERBOSE),)
CFLAGS += -DTEST_VERBOSE=1
endif

COMPILER := $(shell $(CC) --version)

# detect whether gcc or clang is being used
# because clang prefixes functions with an underscore
ifneq ($(or $(findstring GCC, $(COMPILER)), $(findstring gcc, $(COMPILER))),)
ASFLAGS += -dCOMPILER=gcc
else ifneq ($(or $(findstring CLANG, $(COMPILER)), $(findstring clang, $(COMPILER))),)
ASFLAGS += -dCOMPILER=clang
else
$(error Unsupported compiler: $(COMPILER))
endif

# utils config
RM = rm -rf
MKDIR = mkdir -p

# -------------------- dependencies ---------------------

SRC_BONUS = ft_atoi_base.asm \
            ft_list_push_front.asm \
            ft_list_remove_if.asm \
            ft_list_size.asm \
            ft_list_sort.asm
SDIR_BONUS = bonus

SRC = ft_write.asm \
      ft_read.asm \
      ft_strcmp.asm \
      ft_strcpy.asm \
      ft_strdup.asm \
      ft_strlen.asm \
      $(addprefix $(SDIR_BONUS)/, $(SRC_BONUS))
SDIR = src
SRC_FULL = $(addprefix $(SDIR)/, $(SRC))


IDIR = inc

ODIR = build
OBJ = $(patsubst $(SDIR)/%.asm, $(ODIR)/%.o, $(SRC_FULL))

TEST_DIR = test
TEST_SRC = $(shell find $(TEST_DIR) -type f -name "*.c")

# -------------------- public rules ---------------------

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)


all: $(NAME)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TESTER_NAME)

re: fclean test

bonus: all

test: all
	$(CC) $(CFLAGS) -I$(IDIR) $(TEST_SRC) $(NAME) -o $(TESTER_NAME)


.PHONY: all clean fclean re bonus test

# -------------------- util rules -----------------------

# copy the directory tree from $(SDIR) to $(ODIR)
$(ODIR):
	$(MKDIR) $(patsubst $(SDIR)/%, $(ODIR)/% , $(shell find $(SDIR)/ -type d))

$(ODIR)/%.o: $(SDIR)/%.asm | $(ODIR)
	$(AS) $(ASFLAGS) $< -o $@ -I $(IDIR)