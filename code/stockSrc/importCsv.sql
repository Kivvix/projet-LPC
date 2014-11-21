/* ------------------------------------------------------------------ *
 * IMPORTATION DES DONNÉES                                            *
 *                                                                    *
 * Base de données : STAGE2014                                        *
 * Tables          :                                                  *
 *           srcSDSS      : liste des sources identifiées par SDSS    *
 *           srcSTACK     : liste des sources identifiées par Stack   *
 * Fichiers        :                                                  *
 *           src_sdss.csv : fichier csv des sources SDSS              *
 *           src_stack    : fichier csv des sources Stack             *
 *                                                                    *
 * ------------------------------------------------------------------ */

USE STAGE2014;

/* --- importation des sources SDSS --------------------------------- */
LOAD DATA LOCAL INFILE '/tmp/src_sdss.csv'
INTO TABLE srcSDSS
	FIELDS TERMINATED BY ','
	LINES TERMINATED BY '\n'
	IGNORE 1 LINES /* première ligne est l'indication des colonnes */
( 
	`id` ,
	`run` , `col` , `field` ,
	`ra`  , `dec` ,
	`u` , `g` , `r` , `i` , `z` ,
)


/* --- importation des sources Stack -------------------------------- */
LOAD DATA LOCAL INFILE '/tmp/src_stack.csv'
INTO TABLE srcSTACK
	FIELDS TERMINATED BY ','
	LINES TERMINATED BY '\n'
	IGNORE 1 LINES /* première ligne est l'indication des colonnes */
( 
	`id` ,
	`run` , `col` , `field` , `filter` ,
	`ra`  , `dec` ,
	`mag` ,
)

