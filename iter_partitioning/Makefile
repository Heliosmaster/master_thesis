.SILENT:
all: createB local_view

local_view:
	(cd localview; make all)

createB:
	(cd utils; make createB)

clean:
	@echo "==Cleaning=="
	(cd localview; make clean)
	(cd utils; make clean)