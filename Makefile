.SILENT:

all: mondriaan iter

iter:
	@echo == Building Iterative Partitioning ==
	(cd iter_partitioning; make all;)

mondriaan:
	@echo == Building Mondriaan ==
	(cd Mondriaan4RC; make all)

clean:
	@echo == Cleaning ==
	cd iter_partitioning; make clean;
	cd Mondriaan4RC; make veryclean;
