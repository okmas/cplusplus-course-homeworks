CXXFLAGS=-g -O0 -Werror -pedantic -ansi -Wall -Wextra


TARGETS_nanecisto = \
 nanecisto_bind_last_1 \
 nanecisto_bind_last_2 \
 nanecisto_bind_last_3 \
 nanecisto_bind_last_4 \
 nanecisto_bind_last_5 \
 nanecisto_bind_last_2_complex \
 nanecisto_filter_view_integrity \
 nanecisto_filter_view_load \
 nanecisto_filter_view_traverse

TARGETS = $(TARGETS_nanecisto)

all: nanecisto run

nanecisto: $(TARGETS_nanecisto)

clean:
	rm -rf ${TARGETS}

run:
	@for i in `ls ${TARGETS} 2> /dev/null` ; do echo -n -e $${i}":\t\a" ; if ./$${i} ; then echo " [ OK ]" ; else echo " [FAIL]" ; fi ; done


