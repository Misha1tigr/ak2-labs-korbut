ccflags-y := -I$(PWD)/inc

KDIR ?= /home/io23kmy/repos/linux-stable

# Модулі

obj-m := hello1.o hello2.o

# Джерела для кожного модуля

hello1-objs := src/hello1.o

hello2-objs := src/hello2.o

# Збирання

all:
	make -C $(KDIR) M=$(PWD) modules

# Очищення

clean:
	make -C $(KDIR) M=$(PWD) clean