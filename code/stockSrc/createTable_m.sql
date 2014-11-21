/* ------------------------------------------------------------------ *
 * CRÉATION DES TABLES                                                *
 *                                                                    *
 * Base de données : STAGE2014                                        *
 * Tables          :                                                  *
 *           srcSDSS    : liste des sources identifiées par SDSS      *
 *           srcSTACK   : liste des sources identifiées par Stack     *
 *           algorithms : liste des algorithmes de matching           *
 *           matching   : différents matching entre SDSS et Stack     *
 *                                                                    *
 * Ce modèle est un modèle à colonnes variables, à 3 tables           *
 * ------------------------------------------------------------------ */

USE STAGE2014;

/* --- Creation des tables ------------------------------------------ */
CREATE TABLE IF NOT EXISTS srcSDSS_m (
/* table srcSDSS_m sources plus matching
		#id         : identifiant de chaque ligne (celui de SDSS)
		run         : run de la photo identifiant la source SDSS
		col         : colonne du capteur (1 à 6)
		field       : numéro du champ de la run
		ra          : coordonnées en RA de la source
		dec         : coordonnées en Dec de la source
		u,g,r,i,z   : magnitude dans les différents filtres
		_algo1      : id de la source SDSS associé par algo1
*/
	`id` BIGINT NOT NULL AUTO_INCREMENT,

/* donnees camera */
	`run`   INT(6) NOT NULL,
	`col`   INT(1) NOT NULL, /* camcol dans SDSS */
	`field` INT(4) NOT NULL,

/* donnees astrometriques */
	`ra`    FLOAT(16,10) NOT NULL,
	`dec`   FLOAT(16,10) NOT NULL,

/* donnees photometriques */
	`u`     FLOAT(5,3),
	`g`     FLOAT(5,3),
	`r`     FLOAT(5,3),
	`i`     FLOAT(5,3),
	`z`     FLOAT(5,3),

/* donnees du matching */
	`algo1` BIGINT,

/* contraintes */
	PRIMARY KEY(`id`),
	CONSTRAINT c_col CHECK ( `col` > 0 AND `col` < 7 )
	CONSTRAINT fk_algo1  FOREIGN KEY(`algo1`)  REFERENCES srcSTACK(`id`),
);

CREATE TABLE IF NOT EXISTS srcSTACK_m (
/* table srcSTACK_m sources plus matching
		#id         : identifiant de chaque ligne (celui du Stack)
		run         : run de la photo identifiant la source SDSS
		col         : colonne du capteur (1 à 6)
		field       : numéro du champ de la run
		filter      : filtre utilisé (u,g,r,i,z)
		ra          : coordonnées en RA de la source
		dec         : coordonnées en Dec de la source
		mag         : magnitude dans le filtre précisé
		_algo1      : id de la source Stack associé par algo1
*/
	`id` BIGINT NOT NULL AUTO_INCREMENT,

/* donnee camera */
	`run`    INT (6) NOT NULL,
	`col`    INT (1) NOT NULL,
	`field`  INT (4) NOT NULL,
	`filter` CHAR(1) NOT NULL,

/* donnees astrometriques */	
	`ra`     FLOAT(16,10) NOT NULL,
	`dec`    FLOAT(16,10) NOT NULL,

/* donnees photometriques */
	`mag`    FLOAT(5,3),	

/* donnees du matching */
	`algo1` BIGINT,
	
/* contraintes */	
	PRIMARY KEY(`id`),
	CONSTRAINT c_filter CHECK ( `filter` IN ('u','g','r','i','z') ),
	CONSTRAINT c_col    CHECK ( `col` > 0 AND `col` < 7 )
	CONSTRAINT fk_algo1  FOREIGN KEY(`algo1`)  REFERENCES srcSDSS(`id`),
);

CREATE TABLE IF NOT EXISTS algorithms_m (
/* table algorithms_m :
		#id         : identifiant de chaque ligne
		author      : auteur de l'algorithme de matching
		date        : date du matching ou du développement de l'algorithme
		url         : adresse à laquelle on peut trouver l'algorithme de matching
		description : description courte (max 512 caractères) de l'algorithme
		tag         : nom de la colonne faisant référence à l'algorithme
*/
	`id` INT NOT NULL AUTO_INCREMENT,
	
	`author`      VARCHAR(255),
	`date`        TIMESTAMP NOT NULL,
	`url`         VARCHAR(255),
	`description` MEDIUMTEXT,
	`tag`         VARCHAR(10),
	
	PRIMARY KEY(`id`)
);
