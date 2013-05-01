.SILENT:

all: iter

iter:
	@echo == Building Iterative Partitioning ==
	(cd iter_partitioning; make all;)

mondriaan:
	@echo == Building Mondriaan ==
	(cd Mondriaan3.11; make all)

clean:
	@echo == Cleaning ==
	cd iter_partitioning; make clean;
	cd Mondriaan3.11; make clean;