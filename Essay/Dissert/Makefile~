TEX_BIN_DIR = /usr/local/texlive/2010basic/bin/universal-darwin/
TEX = $(TEX_BIN_DIR)pdflatex
BIB = $(TEX_BIN_DIR)bibtex
PDF = $(TEX_BIN_DIR)dvipdft
TEXFLAGS = 
BIBFLAGS =
SOURCE = proposal
COUNTER = perl texWordCount.pl
REF_PDF_DIR = ../../../../../References/

all:
	$(TEX) $(SOURCE)
	$(BIB) $(SOURCE)
	$(TEX) $(SOURCE)
	$(TEX) $(SOURCE)
	open $(SOURCE).pdf

.PHONY: clean mrproper count

count:
	$(COUNTER) $(SOURCE).tex 

clean:
	rm $(SOURCE).aux $(SOURCE).bbl $(SOURCE).blg $(SOURCE).dvi $(SOURCE).log $(SOURCE).toc

npdfs:
	find $(REF_PDF_DIR) | grep "pdf" | wc -l

openrefs:
	open $(REF_PDF_DIR)

mrproper: clean
	rm $(SOURCE).pdf