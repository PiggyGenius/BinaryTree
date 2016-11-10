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
PDF=$(LATEXSOURCE:.tex=.pdf)

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99 -lm -g

.PHONY: all doc binary report averagetest run

all: binary report doc 

$(BINDIR)/computeABROpt: computeABROpt.o averagedepth.o tree.o data_io.o
	@$(CC) $(CFLAGS) $(addprefix $(BINDIR)/, $^) -o $@

%.pdf: $(LATEXSOURCE)
	@$(LATEXC) -output-directory $(REPORTDIR) $^ 

$(DOCDIR)/index.html: $(SRCDIR)/Doxyfile $(CSOURCE) 
	@$(DOCC) $(SRCDIR)/Doxyfile

binary: $(BINDIR)/computeABROpt

report: $(PDF) 

doc: $(DOCDIR)/index.html

%.o: $(SRCDIR)/%.c
	@$(CC) -o $(BINDIR)/$@ -c $< $(CFLAGS)

# use it with : make run LENGTH=10 FILE_PATH=benchmarks/benchmark2.in
run: binary
	./$(BINDIR)/computeABROpt $(LENGTH) $(FILE_PATH)

clean:
	rm -rf $(DOCDIR) $(BINDIR)/* $(REPORTDIR)/*.aux $(REPORTDIR)/*.log  $(REPORTDIR)/rapport.pdf 


