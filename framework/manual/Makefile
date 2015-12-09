#
# This Makefile produces the JPetManual in either PDF of HTML format
# from the markdown source file
# inserting the current document production date just below the title
#

PROCESSOR = pandoc
OPTS = -t markdown

SOURCE = JPetManual.md JPetScopeReaderManual.md
SOURCE_UPDATED_DATE = $(SOURCE:.md=.md.updated)
PDF =  $(SOURCE:.md=.pdf)
HTML = $(SOURCE:.md=.html)

DATE = `date +"%d.%m.%Y"`

%.md.updated: %.md
	@sed "s/produced on: [0-9]\{2\}.[0-9]\{2\}.[0-9]\{4\}/produced on: $(DATE)/g" $< > $@

all: pdf html

pdf: $(PDF)

html: $(HTML)

%.pdf: %.md.updated
	$(PROCESSOR) -o $@ $^

%.html: %.md.updated
	$(PROCESSOR) -o $@ $^

clean:
	rm $(PDF) $(HTML)

