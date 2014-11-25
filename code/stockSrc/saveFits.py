#! /usr/bin/env python
# -*- coding: utf-8 -*-

# /!\ TODO: À TESTER /!\

""" saveFits
	Sauve au format `fits` la base de données des sources. Sauve uniquement les données sur les sources de SDSS et du Stack (DC-2013) d'une région donnée du ciel.
"""

from config import *

import os, sys

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

## Récupération des données de la base de données MySQL
db = MYSQLdb.connect( host   = DB_HOST   ,
                      user   = DB_USER   ,
                      passwd = DB_PASSWD ,
                      db     = DB_NAME    )
c = db.cursor()

### STACK ##############################################################	

c.execute("""SELECT id,ra,dec,mag FROM srcSTACK WHERE
    ra  BETWEEN """ + ra_min  + """ AND """ + ra_max  + """
AND dec BETWEEN """ + dec_min + """ AND """ + dec_max + """ """)

## Création de la table des données du Stack (projet LSST)
l_id  = np.array()
l_ra  = np.array()
l_dec = np.array()
l_mag = np.array()

for row in cur.fetchall() :
	np.append( l_id  , row[0] )
	np.append( l_ra  , row[1] )
	np.append( l_dec , row[2] )
	np.append( l_mag , row[3] )

## Création de l'objet HDU correspondant (table binaire avec les données)
l_cols  = pyfits.ColDefs([ pyfits.Column( name='id'    , format='I' , array=l_id  ) ,
                           pyfits.Column( name='ra'    , format='D' , array=l_ra  ) ,
                           pyfits.Column( name='dec'   , format='D' , array=l_dec ) ,
                           pyfits.Column( name='ABmag' , format='D' , array=l_mag ) ])

lsst_hdu = pyfits.BinTableHDU.from_columns( l_cols )



### SDSS ###############################################################

c.execute("""SELECT id, ra, dec, u, g, r, i, z FROM srcSDSS WHERE
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

for row in cur.fetchall() :
	np.append( s_id  , row[0] )
	np.append( s_ra  , row[1] )
	np.append( s_dec , row[2] )
	np.append( s_u   , row[3] )
	np.append( s_g   , row[4] )
	np.append( s_r   , row[5] )
	np.append( s_i   , row[6] )
	np.append( s_z   , row[7] )

## Création de l'objet HDU correspondant (table binaire avec les données)
s_cols  = pyfits.ColDefs([ pyfits.Column( name='id'      , format='I' , array=s_id  ) ,
                           pyfits.Column( name='ra'      , format='D' , array=s_ra  ) ,
                           pyfits.Column( name='dec'     , format='D' , array=s_dec ) ,
                           pyfits.Column( name='ABmag_u' , format='D' , array=s_u   )
                           pyfits.Column( name='ABmag_g' , format='D' , array=s_g   )
                           pyfits.Column( name='ABmag_r' , format='D' , array=s_r   )
                           pyfits.Column( name='ABmag_i' , format='D' , array=s_i   )
                           pyfits.Column( name='ABmag_z' , format='D' , array=s_z   ) ])

sdss_hdu = pyfits.BinTableHDU.from_columns( s_cols )



### Fichier Fits #######################################################

## Création du header
head = pyfits.Header()
head['AUTHOR']  = 'Josselin Massot'
head['CONTACT'] = 'josselin.massot@gmail.com'
head['TUTOR']   = 'Bogdan Vulpescu (vulpescu@clermont.in2p3.fr)'
head['COMMENT'] = 'Saving of SDSS and Stack sources of one sky region of Stripe 82'
head['REGION']  = '( ' + ra_min + ' ; ' + dec_min + ' ) to ( ' + ra_max + ' ; ' + dec_max + ' )'


hdulist = pyfits.HDUList([ head , lsst_hdu , sdss_hdu ])
hdulist.writeto( 's82-' + ra_min + ':' + dec_min + '-' ra_max + ':' + dec_max + '.fits' )
