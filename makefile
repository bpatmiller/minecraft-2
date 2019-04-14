default: build

.PHONY: build
build:
	-[[ -d build ]] || mkdir build
	cd build; cmake ..;  make -j8

.PHONY: clean
clean:
	rm -rf build/

run:
	build/bin/minecraft

