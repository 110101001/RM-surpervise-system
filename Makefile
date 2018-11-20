ifneq ($(KERNELRELEASE),)
CC:= /opt/armhf-linux-2018.08/bin/arm-none-linux-gnueabi-gcc
MODULE_NAME := LED
#$(MODULE_NAME)-y :=modtest.o
obj-m := $(MODULE_NAME).o
else
#KDIR := /lib/modules/`uname -r`/build
KDIR := ~/share/linux/
PWD := $(shell pwd)
default:
	$(MAKE) ARCH=arm CROSS_COMPILE=/opt/armhf-linux-2018.08/bin/arm-none-linux-gnueabi- -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
endif
