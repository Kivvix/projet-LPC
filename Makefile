### Nom du projet  #####################################################
PROJET  = projet-LPC

MODULES = $(shell find -mindepth 2 -name [Mm]akefile | sed 's/^..//'  )
DIRS = $(dir $(MODULES))

EDITOR = geany

echo = /bin/echo


### Règles de compilation ##############################################
all : $(PROJET)
	@ $(echo) -e "\t Compilation des différentes parties effectuée"

# ~~ $(PROJET) ~~ compile toutes les parties du projet
$(PROJET) :
	@for i in $(DIRS); do \
		$(echo) -e "\033[31m===\033[0m \033[33m $$(echo $$i | sed s'/.$$//') \033[0m \033[31m===\033[0m" ; \
		$(MAKE) -C $$i; \
	done;
# avec un foreach ça marche pas hyper bien (affichage une fois le make fini)	
#	$(foreach dir,$(DIRS),$(shell make -C $(dir)))

# ~~ open ~~ ouvre tous les fichiers du projet en l'appelant dans les sous-makefiles
open :
	$(foreach dir,$(DIRS),$(shell make open -C $(dir)))


# ~~ branch ~~ change l'indication de la branche de git avec le contenu de $(MAKECMDGOALS)
BRANCH = master
branch :
	@B1="BRANCH = $(BRANCH)" ; B2="BRANCH = $(filter-out $@,$(MAKECMDGOALS))" ; \
	sed -i "s/$${B1}.*/$${B2}/" Makefile
	#@git checkout $(BRANCH)

# ~~ git ~~ crée un commit et push le commit, le nom du commit est dans $(MAKECMDGOALS)
git :
	@git checkout $(BRANCH)
	@git commit -a -m "$(filter-out $@,$(MAKECMDGOALS))"
	@git push origin master
