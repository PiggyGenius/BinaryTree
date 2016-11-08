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
CSOURCE=$(wildcard $(SRCDIR)/compileBST.c)
PDF=$(LATEXSOURCE:.tex=.pdf)

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99 -lm -g

all: binary report doc 


$(BINDIR)/compileBST: $(CSOURCE)
	$(CC) $(CFLAGS)  $^ -o $@

%.pdf: $(LATEXSOURCE)
	$(LATEXC) -output-directory $(REPORTDIR) $^ 

$(DOCDIR)/index.html: $(SRCDIR)/Doxyfile $(CSOURCE) 
	$(DOCC) $(SRCDIR)/Doxyfile

binary: $(BINDIR)/compileBST

report: $(PDF) 

doc: $(DOCDIR)/index.html

averagetest: datareader.o averagedepth.o averagetest.o list.o tree.o
	$(CC) -o $(BINDIR)/$@ $(addprefix $(BINDIR)/, $^) && $(BINDIR)/$@ 

tree_test: tree.o tree_test.o
	$(CC) -o $(BINDIR)/$@ $(addprefix $(BINDIR)/, $^) && $(BINDIR)/$@

test_list: list.o test_list.o
	$(CC) -o $(BINDIR)/$@ $(addprefix $(BINDIR)/, $^) && $(BINDIR)/$@


%.o: $(SRCDIR)/%.c
	$(CC) -o $(BINDIR)/$@ -c $< $(CFLAGS)

clean:
	rm -rf $(DOCDIR) $(BINDIR)/* $(REPORTDIR)/*.aux $(REPORTDIR)/*.log  $(REPORTDIR)/rapport.pdf 


.PHONY: all doc binary report averagetest tree_test test_list
