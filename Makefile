SUBDIRS=client server

all: compile


compile:
	for subdir in $(SUBDIRS); do  make -C $$subdir ; done



clean:
	find . -name '*~' | xargs rm -f
	find . -name '*.swp' | xargs rm -f
	for subdir in $(SUBDIRS); do  make -C $$subdir clean ; done
