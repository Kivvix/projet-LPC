SRC = main
#REP= ./sources_gnuplot

DEBUG_MODE ?= N
LATEX = pdflatex --shell-escape

ifeq ($(DEBUG_MODE), Y)
#LATEX += -interaction=nonstopmode
else
LATEX += -interaction=batchmode
endif

BIBTEX = bibtex -terse
RERUN = ‘(There were undefined references|Rerun to get (cross-references|the bars) right)’
UNDEFINED = ‘((Reference|Citation).*undefined)|(Label.*multiply defined)’

ECHO = /bin/echo -e

.PHONY:all $(REP)

#all: $(REP) ${SRC}.pdf
all: complet

$(REP):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

clean: $(REP)
	@$(ECHO) "suppression des fichiers de compilation"
	@# fichiers de compilation latex
	@rm -f *.log *.aux *.dvi *.toc *.lot *.lof *.loa *.lol *.out *.idx
	@# fichiers de bibtex
	@rm -f *.bbl *.blg

DEB=$(shell date -d now +%s)

complet:
	@$(ECHO) "\033[31mCompilation complète\033[0m"
	@date +%H:%M:%S
	@notify-send --expire-time=27000 -i /usr/share/icons/gnome/32x32/emblems/emblem-new.png "Début de compilation" "À : $$(date +%H:%M:%S)"
	@$(ECHO) "\033[32m\t Compilation n°1\033[0m"
	@${LATEX} ${SRC}
	@date +%H:%M:%S
	@notify-send -i /usr/share/icons/gnome/32x32/emblems/emblem-default.png "Compilation n°1" "Check : $$(date +%H:%M:%S)"
	@if [ -e ${SRC}.bbl ]; then $(ECHO) "\033[36m\t Bibliographie\033[0m"; ${BIBTEX} ${SRC} ; notify-send -i /usr/share/icons/gnome/32x32/emblems/emblem-documents.png "Bibliographie" "Check : $$(date +%H:%M:%S)"; fi
	@$(ECHO) "\033[32m\t Compilation n°2\033[0m"
	@${LATEX} ${SRC}
	@date +%H:%M:%S
	@notify-send -i /usr/share/icons/gnome/32x32/emblems/emblem-default.png "Compilation n°2" "Check : $$(date +%H:%M:%S)"
	@$(ECHO) "\033[32m\t Compilation n°3\033[0m"
	@${LATEX} ${SRC}
	@date +%H:%M:%S
	@notify-send -i /usr/share/icons/gnome/32x32/emblems/emblem-generic.png "Compilation n°3" "Check : $$(date +%H:%M:%S)"
	@$(ECHO) "\033[33mTemps de compilation : $$(( $$(date -d now +%s) - $(DEB) )) s\033[0m"
	@notify-send -i /usr/share/icons/gnome/32x32/actions/document-open-recent.png "Temps de compilation" "$$(( $$(date -d now +%s) - $(DEB) )) s"

initial: propre
	@$(ECHO) „suppression des fichiers cibles“
	@rm -f ${SRC}.ps ${SRC}.pdf

bib:
	bibtex ${SRC}

%.pdf : %.tex
	@$(ECHO) „compilation du tex“
	${LATEX} $<
	@if [ -e ${SRC}.bbl ]; then ${BIBTEX} $* ; fi
	@if egrep -q $(RERUN) $*.log ; then $(ECHO) «passe LaTeX» \
	&& $(LATEX) $<; fi
	@if egrep -q $(RERUN) $*.log ; then $(ECHO) «passe LaTeX» \
	&& $(LATEX) $<; fi
	@$(ECHO) “Citations ou références indéfinies:»
	@egrep -i $(UNDEFINED) $*.log || echo «Aucune»

open:
	@geany $(SRC).tex part/*.tex &
