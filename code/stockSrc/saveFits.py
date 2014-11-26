#! /usr/bin/env python
# -*- coding: utf-8 -*-

"""
	module   : stockSrc
	language : Python 2.7
	auteur   : Josselin Massot (josselin.massot@gmail.com)
	date     : 2014-11-26

Script permettant d'effectuer une requête sur la base de données des
sources du Stack (DC-2013) et de SDSS sur une région du ciel, et de
sauvegarder au format `fits`.
"""


# /!\ TODO: À TESTER /!\


from config import *

import os, sys
import time

import MYSQLdb

import pyfits
import numpy as np


## Récupération des coordonnées de la région

if ( len(sys.argv) >= 4 ) :
	ra_min  = sys.argv[1]
	dec_min = sys.argv[2]
	ra_max  = sys.argv[3]
	dec_max = sys.argv[4]
else :
	print """ Usage : \n""" + sys.argv[0] + """ ra_min dec_min ra_max dec_max """


## Connexion à la base de données

db = MYSQLdb.connect( host   = DB_HOST   ,
                      user   = DB_USER   ,
                      passwd = DB_PASSWD ,
                      db     = DB_NAME    )
c = db.cursor()


########################################################################
### STACK ##############################################################	
########################################################################

c.execute("""SELECT id,ra,dec,mag,run,col,filter,field FROM srcSTACK WHERE
    ra  BETWEEN """ + ra_min  + """ AND """ + ra_max  + """
AND dec BETWEEN """ + dec_min + """ AND """ + dec_max + """ """)

## Création de la table des données du Stack (projet LSST)

l_id  = np.array()
l_ra  = np.array()
l_dec = np.array()
l_mag = np.array()
l_r   = np.array() # run
l_c   = np.array() # column
l_v   = np.array() # filter
l_f   = np.array() # field

# parcours des résultats de la requête et remplissage des tableaux

for row in cur.fetchall() :
	np.append( l_id  , row[0] )
	np.append( l_ra  , row[1] )
	np.append( l_dec , row[2] )
	np.append( l_mag , row[3] )
	np.append( l_r   , row[4] )
	np.append( l_c   , row[5] )
	np.append( l_v   , row[6] )
	np.append( l_f   , row[7] )


## Création de l'objet HDU correspondant (table binaire avec les données)

l_cols  = pyfits.ColDefs([ pyfits.Column( name='id'     , format='I'  , array=l_id  ) ,
                           pyfits.Column( name='ra'     , format='D'  , array=l_ra  ) ,
                           pyfits.Column( name='dec'    , format='D'  , array=l_dec ) ,
                           pyfits.Column( name='ABmag'  , format='D'  , array=l_mag ) ,
                           pyfits.Column( name='run'    , format='A6' , array=l_r   ) ,
                           pyfits.Column( name='col'    , format='A1' , array=l_c   ) ,
                           pyfits.Column( name='filter' , format='A1' , array=l_v   ) ,
                           pyfits.Column( name='field'  , format='A4' , array=l_f   ) ])

lsst_hdu = pyfits.BinTableHDU.from_columns( l_cols )


########################################################################
### SDSS ###############################################################
########################################################################

c.execute("""SELECT id, ra, dec, u, g, r, i, z, run, col, field FROM srcSDSS WHERE
    ra  BETWEEN """ + ra_min  + """ AND """ + ra_max  + """
AND dec BETWEEN """ + dec_min + """ AND """ + dec_max + """ """)

## Création de la table des données de SDSS

s_id  = np.array()
s_ra  = np.array()
s_dec = np.array()
s_u   = np.array()
s_g   = np.array()
s_r   = np.array()
s_i   = np.array()
s_z   = np.array()
s_r   = np.array() # run
s_c   = np.array() # col
s_f   = np.array() # field

# parcours des résultats de la requête et remplissage des tableaux

for row in cur.fetchall() :
	np.append( s_id  , row[0] )
	np.append( s_ra  , row[1] )
	np.append( s_dec , row[2] )
	np.append( s_u   , row[3] )
	np.append( s_g   , row[4] )
	np.append( s_r   , row[5] )
	np.append( s_i   , row[6] )
	np.append( s_z   , row[7] )
	np.append( s_r   , row[7] )
	np.append( s_c   , row[7] )
	np.append( s_f   , row[7] )

## Création de l'objet HDU correspondant (table binaire avec les données)

s_cols  = pyfits.ColDefs([ pyfits.Column( name='id'      , format='I'  , array=s_id  ) ,
                           pyfits.Column( name='ra'      , format='D'  , array=s_ra  ) ,
                           pyfits.Column( name='dec'     , format='D'  , array=s_dec ) ,
                           pyfits.Column( name='ABmag_u' , format='D'  , array=s_u   ) ,
                           pyfits.Column( name='ABmag_g' , format='D'  , array=s_g   ) ,
                           pyfits.Column( name='ABmag_r' , format='D'  , array=s_r   ) ,
                           pyfits.Column( name='ABmag_i' , format='D'  , array=s_i   ) ,
                           pyfits.Column( name='ABmag_z' , format='D'  , array=s_z   ) ,
                           pyfits.Column( name='run'     , format='A6' , array=s_r   ) ,
                           pyfits.Column( name='col'     , format='A1' , array=s_c   ) ,
                           pyfits.Column( name='field'   , format='A4' , array=s_f   ) ])

sdss_hdu = pyfits.BinTableHDU.from_columns( s_cols )



########################################################################
### Fichier Fits #######################################################
########################################################################


## Création du header

head = pyfits.Header()
head['author']  = 'Josselin Massot'
head['contact'] = 'josselin.massot@gmail.com'
head['tutor']   = 'Bogdan Vulpescu (vulpescu@clermont.in2p3.fr)'
head['date']    = 'Create at: ' + time.strftime('%Y-%m-%d :: %H:%M:%S',time.localtime())
head['comment'] = 'Saving of SDSS and Stack sources of one sky region of Stripe 82'
head['region']  = '( ' + ra_min + ' ; ' + dec_min + ' ) to ( ' + ra_max + ' ; ' + dec_max + ' )'


## Sauvegarde du fichier `fits`

hdulist = pyfits.HDUList([ head , lsst_hdu , sdss_hdu ])
hdulist.writeto( 's82-' + ra_min + ':' + dec_min + '-' ra_max + ':' + dec_max + '.fits' )
