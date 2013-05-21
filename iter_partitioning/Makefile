include ./init.mk

all: lw hr ut

hr:
	cd hot_restart; make all

lw:
	cd localview; make all

ut:
	cd utils; make all

clean:
	cd hot_restart; make clean
	cd localview; make clean
	cd utils; make clean
