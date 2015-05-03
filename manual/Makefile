#
# This Makefile produces the JPetManual in either PDF of HTML format
# from the markdown source file
# inserting the current document production date just below the title
#

PROCESSOR = pandoc
OPTS = -t markdown

SOURCE = JPetManual.md JPetScopeReaderManula.md
SOURCE_UPDATED_DATE = $(SOURCE:.md=.md.updated)
PDF =  $(SOURCE:.md=.pdf)
HTML = $(SOURCE:.md=.html)

DATE = `date +"%d.%m.%Y"`

%.updated: %
	@sed "s/produced on: [0-9]\{2\}.[0-9]\{2\}.[0-9]\{4\}/produced on: $(DATE)/g" $< > $@
	@echo "$(DATE)"

pdf: $(SOURCE_UPDATED_DATE)
	$(PROCESSOR) -o $(PDF) $(SOURCE_UPDATED_DATE)
	rm $(SOURCE_UPDATED_DATE)

html: $(SOURCE_UPDATED_DATE)
	$(PROCESSOR) -o $(HTML) $(SOURCE_UPDATED_DATE)
	rm $(SOURCE_UPDATED_DATE)


clean:
	rm $(PDF) $(HTML) *.log

