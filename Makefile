CC=cc
LATEXC=pdflatex
DOCC=doxygen
CFLAGS=-g -Wall 

REFDIR=.
SRCDIR=$(REFDIR)/src
BINDIR=$(REFDIR)/bin
DOCDIR=$(REFDIR)/doc
REPORTDIR=$(REFDIR)/rapport

LATEXSOURCE=$(wildcard $(REPORTDIR)/*.tex)
# CSOURCE=$(wildcard $(SRCDIR)/compileBST.c)
PDF=$(LATEXSOURCE:.tex=.pdf)

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99 -lm -g

.PHONY: all doc binary report averagetest run

all: binary report doc 

$(BINDIR)/computeABROpt: computeABROpt.o averagedepth.o tree.o datareader.o list.o
	$(CC) $(CFLAGS) $(addprefix $(BINDIR)/, $^) -o $@

%.pdf: $(LATEXSOURCE)
	$(LATEXC) -output-directory $(REPORTDIR) $^ 

$(DOCDIR)/index.html: $(SRCDIR)/Doxyfile $(CSOURCE) 
	$(DOCC) $(SRCDIR)/Doxyfile

binary: $(BINDIR)/computeABROpt

report: $(PDF) 

doc: $(DOCDIR)/index.html

averagetest: datareader.o averagedepth.o averagetest.o list.o tree.o
	$(CC) -o $(BINDIR)/$@ $(addprefix $(BINDIR)/, $^) && $(BINDIR)/$@ 

# tree_test: tree.o tree_test.o
# 	$(CC) -o $(BINDIR)/$@ $(addprefix $(BINDIR)/, $^) && $(BINDIR)/$@
#
# test_list: list.o test_list.o
# 	$(CC) -o $(BINDIR)/$@ $(addprefix $(BINDIR)/, $^) && $(BINDIR)/$@
#

%.o: $(SRCDIR)/%.c
	$(CC) -o $(BINDIR)/$@ -c $< $(CFLAGS)

# use it with : make run BENCHMARK=6
# if you want the 6th benchmark
run: binary
	./$(BINDIR)/computeABROpt 1 benchmarks/benchmark$(BENCHMARK).in


clean:
	rm -rf $(DOCDIR) $(BINDIR)/* $(REPORTDIR)/*.aux $(REPORTDIR)/*.log  $(REPORTDIR)/rapport.pdf 


