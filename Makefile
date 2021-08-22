

TAGET := snake

CC = gcc

OPT = \
-g \
-m32 \

DEFINE = \
# -DDEBUG \

C_FILES := main.c \
control.c \
gui_port.c \
snake.c \

LIBS = \
-lcurses \

INCLUDES := \
 -I/usr/include/x86_64-linux-gnu \
#  -I/usr/include/newlib/sys \
#  -I/usr/include/newlib \
#  -I/usr/src/linux-headers-5.3.0-46/arch/mips/include/asm/dec \
#  -I/usr/include/x86_64-linux-gnu/sys \

$(TAGET):$(C_FILES)
	$(CC) $(INCLUDES) $(DEFINE) $(LIBS) $(OPT) $^ -o $@

clean:
	rm $(TAGET)