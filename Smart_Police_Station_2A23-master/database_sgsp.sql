--------------------------------------------------------
--  Fichier crÈÈ - mercredi-mars-31-2021   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table VEHICULE
--------------------------------------------------------

  CREATE TABLE "VEHICULE" 
   (	"ID_VEHICULE" VARCHAR2(20 BYTE), 
	"TYPE_VEHICULE" NUMBER, 
	"DATE_SORTIE" DATE, 
	"DATE_ENTREE" DATE, 
	"HEURE_ENTREE" DATE, 
	"NB_VEHICULE" NUMBER, 
	"ETAT" NUMBER, 
	"HEURE_SORTIE" DATE
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table TEMOIGNAGE
--------------------------------------------------------

  CREATE TABLE "TEMOIGNAGE" 
   (	"ID_T" VARCHAR2(20 BYTE), 
	"NOM_T" VARCHAR2(20 BYTE), 
	"CONTENU" VARCHAR2(20 BYTE), 
	"ID_CITOYEN" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table TACHE
--------------------------------------------------------

  CREATE TABLE "TACHE" 
   (	"ID" VARCHAR2(20 BYTE), 
	"LIBELLE" VARCHAR2(255 BYTE), 
	"DEBUT" DATE, 
	"FIN" DATE, 
	"EXECUTEUR" VARCHAR2(30 BYTE), 
	"ETAT" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table SUSPECT
--------------------------------------------------------

  CREATE TABLE "SUSPECT" 
   (	"ID_ENQUETTE" VARCHAR2(20 BYTE), 
	"ID_CITOYEN" VARCHAR2(20 BYTE), 
	"DESCRIPTION" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table PV
--------------------------------------------------------

  CREATE TABLE "PV" 
   (	"ID_PV" VARCHAR2(20 BYTE), 
	"LIBELLE" VARCHAR2(20 BYTE), 
	"INFRACTION" VARCHAR2(20 BYTE), 
	"TYPE_INFRACTION" VARCHAR2(20 BYTE), 
	"ID_CITOYEN" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table PLAINTE
--------------------------------------------------------

  CREATE TABLE "PLAINTE" 
   (	"ID_PLAINTE" VARCHAR2(20 BYTE), 
	"INTITULE" VARCHAR2(20 BYTE), 
	"NOM_PLAINTE" VARCHAR2(20 BYTE), 
	"PRIX_AMENDE" NUMBER, 
	"TYPE_PLAINTE" NUMBER, 
	"DATE_PLAINTE" DATE, 
	"ID_CITOYEN" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table OBJET_RETROUVE
--------------------------------------------------------

  CREATE TABLE "OBJET_RETROUVE" 
   (	"ID_OBJET" VARCHAR2(20 BYTE), 
	"TYPE_OBJET" VARCHAR2(20 BYTE), 
	"DESCRIPTION" VARCHAR2(100 BYTE), 
	"IMAGE" VARCHAR2(50 BYTE), 
	"CARACTERISTIQUE" VARCHAR2(20 BYTE), 
	"DISPONIBILITE" VARCHAR2(20 BYTE), 
	"ID_CITOYEN" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table MSG_LUES_ETNONLUES
--------------------------------------------------------

  CREATE TABLE "MSG_LUES_ETNONLUES" 
   (	"ID_MSG" VARCHAR2(20 BYTE), 
	"LOGIN_AGENT" VARCHAR2(30 BYTE), 
	"CONSULTER" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table MESSAGE
--------------------------------------------------------

  CREATE TABLE "MESSAGE" 
   (	"ID_MSG" VARCHAR2(30 BYTE), 
	"CONTENT" VARCHAR2(1000 BYTE), 
	"LOGIN_AGENT" VARCHAR2(30 BYTE), 
	"DATE_ENVOIE" TIMESTAMP (6), 
	"CONTEXT" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table AGENT
--------------------------------------------------------

  CREATE TABLE "AGENT" 
   (	"MATRICULE" VARCHAR2(30 BYTE), 
	"LOGIN" VARCHAR2(30 BYTE), 
	"PASSWORD" VARCHAR2(30 BYTE), 
	"NOM" VARCHAR2(30 BYTE), 
	"PRENOM" VARCHAR2(30 BYTE), 
	"DATENAISS" DATE, 
	"MAIL" VARCHAR2(30 BYTE), 
	"TYPE" NUMBER, 
	"POSTE" VARCHAR2(30 BYTE), 
	"NOMPERE" VARCHAR2(30 BYTE), 
	"NOMMERE" VARCHAR2(30 BYTE), 
	"VILLE" VARCHAR2(30 BYTE), 
	"IMAGE" VARCHAR2(30 BYTE), 
	"GRADE" VARCHAR2(30 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table ARME
--------------------------------------------------------

  CREATE TABLE "ARME" 
   (	"ID_ARME" VARCHAR2(20 BYTE), 
	"TYPE_ARME" NUMBER, 
	"DATE_STOCK" DATE, 
	"NB_ARME" NUMBER, 
	"DATE_SORTIE" DATE, 
	"ETAT" NUMBER, 
	"HEURE_SORTIE" DATE, 
	"HEURE_ENTREE" DATE, 
	"DATE_ENTREE" DATE
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table CITOYEN
--------------------------------------------------------

  CREATE TABLE "CITOYEN" 
   (	"ID_CITOYEN" VARCHAR2(20 BYTE), 
	"NOM_CITOYEN" VARCHAR2(20 BYTE), 
	"PRENOM_CITOYEN" VARCHAR2(20 BYTE), 
	"DATE_NAISSANCE" DATE, 
	"HEURE_NAISSANCE" DATE, 
	"PAYS_NAISSANCE" VARCHAR2(20 BYTE), 
	"VILLE" VARCHAR2(20 BYTE), 
	"NOM_PERE" VARCHAR2(20 BYTE), 
	"NOM_MERE" VARCHAR2(20 BYTE), 
	"NUMERO_TEL" VARCHAR2(20 BYTE), 
	"MAIL" VARCHAR2(20 BYTE), 
	"IMAGE" VARCHAR2(50 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table DECLARATION
--------------------------------------------------------

  CREATE TABLE "DECLARATION" 
   (	"ID_DECL" VARCHAR2(20 BYTE), 
	"DATE_DECL" VARCHAR2(20 BYTE), 
	"OBJET" VARCHAR2(20 BYTE), 
	"IMAGE" VARCHAR2(50 BYTE), 
	"ID_CITOYEN" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table DOCUMENT
--------------------------------------------------------

  CREATE TABLE "DOCUMENT" 
   (	"ID_DOC" VARCHAR2(20 BYTE), 
	"TYPE_DOC" VARCHAR2(20 BYTE), 
	"DATE_DELIVRE" DATE, 
	"ETAT_TRAIT" NUMBER, 
	"ID_CITOYEN" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table ENQUETTE
--------------------------------------------------------

  CREATE TABLE "ENQUETTE" 
   (	"ID_ENQUETTE" VARCHAR2(20 BYTE), 
	"SUJET" VARCHAR2(20 BYTE), 
	"DATE_DEBUT" DATE, 
	"TYPE_ENQUETTE" VARCHAR2(20 BYTE), 
	"INDICE" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
REM INSERTING into VEHICULE
SET DEFINE OFF;
REM INSERTING into TEMOIGNAGE
SET DEFINE OFF;
REM INSERTING into TACHE
SET DEFINE OFF;
Insert into TACHE (ID,LIBELLE,DEBUT,FIN,EXECUTEUR,ETAT) values ('tache001','Depot de dossier',to_date('30/03/21','DD/MM/RR'),to_date('31/03/21','DD/MM/RR'),'Mohammed','0');
REM INSERTING into SUSPECT
SET DEFINE OFF;
REM INSERTING into PV
SET DEFINE OFF;
REM INSERTING into PLAINTE
SET DEFINE OFF;
REM INSERTING into OBJET_RETROUVE
SET DEFINE OFF;
REM INSERTING into MSG_LUES_ETNONLUES
SET DEFINE OFF;
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('23564318032021','codPro','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('23554118032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('23554218032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('23564418032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('1618318032021','Lionardo','0');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('1619418032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('1621818032021','Lionardo','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('17161418032021','codPro','0');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('19013018032021','codPro','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('19013118032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('23154018032021','Lionardo','0');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('21374620032021','Lionardo','0');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('21394720032021','Lionardo','0');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('21555420032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('21555520032021','codPro','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('17531618032021','codPro','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('17561718032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('17561818032021','codPro','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('17561918032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('17562018032021','codPro','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('17582118032021','leProder','0');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('18282218032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('1542018032021','Lionardo','0');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('1544118032021','Lionardo','0');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('18292318032021','Lionardo','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('18292418032021','Lionardo','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('18302518032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('18302618032021','admin','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('18312718032021','Lionardo','1');
Insert into MSG_LUES_ETNONLUES (ID_MSG,LOGIN_AGENT,CONSULTER) values ('18312818032021','admin','1');
REM INSERTING into MESSAGE
SET DEFINE OFF;
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('23564318032021','pourquoi t''as supprimer ahhhh :)','admin',to_timestamp('18/03/21 23:56:33','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('23564418032021','bye bye','codPro',to_timestamp('18/03/21 23:56:59','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('23554118032021','c''est d√©goutant','codPro',to_timestamp('18/03/21 23:55:36','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('23554218032021','<em style = "color: gray;"> ^^message supprimer par : codPro^^</em>','codPro',to_timestamp('18/03/21 23:55:40','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1609218032021','eeeh oo la famille','admin',to_timestamp('18/03/21 16:09:08','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1618318032021','lionardo o√π est tu??','admin',to_timestamp('18/03/21 16:18:13','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1619418032021','stop tes connerie','Lionardo',to_timestamp('18/03/21 16:19:13','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1620518032021','fgdfgdfg','Lionardo',to_timestamp('18/03/21 16:20:19','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1620618032021','dgdfgdfgdfg','Lionardo',to_timestamp('18/03/21 16:20:27','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1621718032021','dfgdfgdf','admin',to_timestamp('18/03/21 16:21:22','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1621818032021','dfgdfgfd','admin',to_timestamp('18/03/21 16:21:30','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1622918032021','dfgdfgdfg','admin',to_timestamp('18/03/21 16:22:21','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('16221018032021','dfgdfg','admin',to_timestamp('18/03/21 16:22:23','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('16221118032021','dfgdf','admin',to_timestamp('18/03/21 16:22:25','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('16231218032021','qdqsd','admin',to_timestamp('18/03/21 16:23:44','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('16251318032021','OOOOOOOOOOOOOOOOOOOO','admin',to_timestamp('18/03/21 16:25:37','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('17161418032021','bonjour codPro','admin',to_timestamp('18/03/21 17:16:17','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19012918032021','bonosdfsf','admin',to_timestamp('18/03/21 19:01:15','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19013018032021','et alors qu''est ce qu''on dit','admin',to_timestamp('18/03/21 19:01:45','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19013118032021','bah rien j''suis l√†','codPro',to_timestamp('18/03/21 19:01:57','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19043218032021','fgdfdf','codPro',to_timestamp('18/03/21 19:04:08','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19043318032021','dfsgsg','admin',to_timestamp('18/03/21 19:04:15','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19043418032021','dsgdfgdsg','codPro',to_timestamp('18/03/21 19:04:27','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19043518032021','dgdsgdg','admin',to_timestamp('18/03/21 19:04:33','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19093618032021','bsgjpojkljqfds','admin',to_timestamp('18/03/21 19:09:04','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19093718032021','gfdsdfgsdfg','codPro',to_timestamp('18/03/21 19:09:10','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('19093818032021','dgsdg','codPro',to_timestamp('18/03/21 19:09:15','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('22543918032021','bonjour non non bonsoir :)','admin',to_timestamp('18/03/21 22:54:35','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('23154018032021','ehooo Lionardo','admin',to_timestamp('18/03/21 23:15:06','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21394720032021','Oups ;:)','admin',to_timestamp('20/03/21 21:39:15','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21374520032021','Salut tout le monde, je suis le nouveau administrateur.','baldrog',to_timestamp('20/03/21 21:37:32','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21374620032021','Salut Baldrog','admin',to_timestamp('20/03/21 21:37:57','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21394820032021','Salut Balrog','admin',to_timestamp('20/03/21 21:39:29','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21394920032021','eeuh Baldrog','admin',to_timestamp('20/03/21 21:39:43','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21395020032021','dsl','admin',to_timestamp('20/03/21 21:39:48','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21405120032021','Tkt salut','baldrog',to_timestamp('20/03/21 21:40:00','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21405220032021','petite rectification, tu n''ais pas le NOUVEAU mais le 2eme administrateur','admin',to_timestamp('20/03/21 21:40:51','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21415320032021','aaaaah autant pour moi ;)','baldrog',to_timestamp('20/03/21 21:41:27','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21555420032021','bonjour mon petit','codPro',to_timestamp('20/03/21 21:55:02','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('21555520032021','ok mon bon petit','admin',to_timestamp('20/03/21 21:55:17','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('17531518032021','bonjour','codPro',to_timestamp('18/03/21 17:53:03','DD/MM/RR HH24:MI:SS'),'0');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('17531618032021','est-ce qu''on peut parler seull?','admin',to_timestamp('18/03/21 17:53:40','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('17561718032021','salut!','codPro',to_timestamp('18/03/21 17:56:10','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('17561818032021','salut toi!!','admin',to_timestamp('18/03/21 17:56:25','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('17561918032021','comment tu vas??','codPro',to_timestamp('18/03/21 17:56:36','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('17562018032021','bien et toi??','admin',to_timestamp('18/03/21 17:56:49','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('17582118032021','salut leProder','admin',to_timestamp('18/03/21 17:58:11','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('18282218032021','bonjour administritourr','Lionardo',to_timestamp('18/03/21 18:28:32','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1542018032021','dsfsdfs','admin',to_timestamp('18/03/21 15:42:18','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('1544118032021','<em style = "color: gray;"> ^^message supprimer par : admin</em>','admin',to_timestamp('18/03/21 15:44:11','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('18292318032021','ahoola','admin',to_timestamp('18/03/21 18:29:09','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('18292418032021','eeeh oh','admin',to_timestamp('18/03/21 18:29:48','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('18302518032021','bieenne','Lionardo',to_timestamp('18/03/21 18:30:03','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('18302618032021','wattt','codPro',to_timestamp('18/03/21 18:30:31','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('18312718032021','ok bienne','admin',to_timestamp('18/03/21 18:31:01','DD/MM/RR HH24:MI:SS'),'1');
Insert into MESSAGE (ID_MSG,CONTENT,LOGIN_AGENT,DATE_ENVOIE,CONTEXT) values ('18312818032021','eeeey stay calm','Lionardo',to_timestamp('18/03/21 18:31:37','DD/MM/RR HH24:MI:SS'),'1');
REM INSERTING into AGENT
SET DEFINE OFF;
Insert into AGENT (MATRICULE,LOGIN,PASSWORD,NOM,PRENOM,DATENAISS,MAIL,TYPE,POSTE,NOMPERE,NOMMERE,VILLE,IMAGE,GRADE) values ('00074Zfe','codPro','14sansmele','Leuvril','Cortez',to_date('01/01/00','DD/MM/RR'),null,'0','grodo',null,null,'Tunis',null,'sanstos');
Insert into AGENT (MATRICULE,LOGIN,PASSWORD,NOM,PRENOM,DATENAISS,MAIL,TYPE,POSTE,NOMPERE,NOMMERE,VILLE,IMAGE,GRADE) values ('2100LFK','baldrog','option','Moham''','Chokiril',to_date('14/04/95','DD/MM/RR'),null,'1','Baldozer','Hambo','Bannil','Bizerte',null,'Adjuvant');
Insert into AGENT (MATRICULE,LOGIN,PASSWORD,NOM,PRENOM,DATENAISS,MAIL,TYPE,POSTE,NOMPERE,NOMMERE,VILLE,IMAGE,GRADE) values ('00k4ooi','leProder','loohiu','ouliou','pronon',to_date('14/10/15','DD/MM/RR'),'sdf@gmail.com','0','sdf','sdf','sdf','Nabeul',null,'sdf');
Insert into AGENT (MATRICULE,LOGIN,PASSWORD,NOM,PRENOM,DATENAISS,MAIL,TYPE,POSTE,NOMPERE,NOMMERE,VILLE,IMAGE,GRADE) values ('ak0047','Lionardo','mohamed','Ali','boustros',to_date('30/07/00','DD/MM/RR'),null,'0',null,null,null,null,null,null);
Insert into AGENT (MATRICULE,LOGIN,PASSWORD,NOM,PRENOM,DATENAISS,MAIL,TYPE,POSTE,NOMPERE,NOMMERE,VILLE,IMAGE,GRADE) values ('00054MP','admin','admin',null,null,null,null,'1',null,null,null,null,null,null);
Insert into AGENT (MATRICULE,LOGIN,PASSWORD,NOM,PRENOM,DATENAISS,MAIL,TYPE,POSTE,NOMPERE,NOMMERE,VILLE,IMAGE,GRADE) values ('45fui','Lacrim','dsfgd','oboso',null,to_date('01/01/00','DD/MM/RR'),null,'0','dg',null,null,'dsf',null,'dfg');
REM INSERTING into ARME
SET DEFINE OFF;
REM INSERTING into CITOYEN
SET DEFINE OFF;
REM INSERTING into DECLARATION
SET DEFINE OFF;
REM INSERTING into DOCUMENT
SET DEFINE OFF;
REM INSERTING into ENQUETTE
SET DEFINE OFF;
--------------------------------------------------------
--  DDL for Index VEHICULE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "VEHICULE_PK" ON "VEHICULE" ("ID_VEHICULE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index TEMOIGNAGE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "TEMOIGNAGE_PK" ON "TEMOIGNAGE" ("ID_T") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index TABLE1_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "TABLE1_PK" ON "TACHE" ("ID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index SUSPECT_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "SUSPECT_PK" ON "SUSPECT" ("ID_ENQUETTE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PV_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "PV_PK" ON "PV" ("ID_PV") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PLAINTE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "PLAINTE_PK" ON "PLAINTE" ("ID_PLAINTE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index OBJET_RETROUVE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "OBJET_RETROUVE_PK" ON "OBJET_RETROUVE" ("ID_OBJET") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index MESSAGE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "MESSAGE_PK" ON "MESSAGE" ("ID_MSG") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index COMPTE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "COMPTE_PK" ON "AGENT" ("MATRICULE", "LOGIN") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index ARME_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "ARME_PK" ON "ARME" ("ID_ARME") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CITOYEN_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "CITOYEN_PK" ON "CITOYEN" ("ID_CITOYEN") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index DECLARATION_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DECLARATION_PK" ON "DECLARATION" ("ID_DECL") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index DOCUMENT_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DOCUMENT_PK" ON "DOCUMENT" ("ID_DOC") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index ENQUETTE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "ENQUETTE_PK" ON "ENQUETTE" ("ID_ENQUETTE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  Constraints for Table VEHICULE
--------------------------------------------------------

  ALTER TABLE "VEHICULE" MODIFY ("ID_VEHICULE" NOT NULL ENABLE);
  ALTER TABLE "VEHICULE" ADD CONSTRAINT "VEHICULE_PK" PRIMARY KEY ("ID_VEHICULE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table TEMOIGNAGE
--------------------------------------------------------

  ALTER TABLE "TEMOIGNAGE" ADD CONSTRAINT "TEMOIGNAGE_PK" PRIMARY KEY ("ID_T")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
  ALTER TABLE "TEMOIGNAGE" MODIFY ("ID_T" NOT NULL ENABLE);
--------------------------------------------------------
--  Constraints for Table TACHE
--------------------------------------------------------

  ALTER TABLE "TACHE" MODIFY ("ID" NOT NULL ENABLE);
  ALTER TABLE "TACHE" ADD CONSTRAINT "TABLE1_PK" PRIMARY KEY ("ID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table SUSPECT
--------------------------------------------------------

  ALTER TABLE "SUSPECT" MODIFY ("ID_ENQUETTE" NOT NULL ENABLE);
  ALTER TABLE "SUSPECT" ADD CONSTRAINT "SUSPECT_PK" PRIMARY KEY ("ID_ENQUETTE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table PV
--------------------------------------------------------

  ALTER TABLE "PV" MODIFY ("ID_PV" NOT NULL ENABLE);
  ALTER TABLE "PV" ADD CONSTRAINT "PV_PK" PRIMARY KEY ("ID_PV")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table PLAINTE
--------------------------------------------------------

  ALTER TABLE "PLAINTE" MODIFY ("ID_PLAINTE" NOT NULL ENABLE);
  ALTER TABLE "PLAINTE" ADD CONSTRAINT "PLAINTE_PK" PRIMARY KEY ("ID_PLAINTE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table OBJET_RETROUVE
--------------------------------------------------------

  ALTER TABLE "OBJET_RETROUVE" MODIFY ("ID_OBJET" NOT NULL ENABLE);
  ALTER TABLE "OBJET_RETROUVE" ADD CONSTRAINT "OBJET_RETROUVE_PK" PRIMARY KEY ("ID_OBJET")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table MESSAGE
--------------------------------------------------------

  ALTER TABLE "MESSAGE" MODIFY ("ID_MSG" NOT NULL ENABLE);
  ALTER TABLE "MESSAGE" ADD CONSTRAINT "MESSAGE_PK" PRIMARY KEY ("ID_MSG")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table AGENT
--------------------------------------------------------

  ALTER TABLE "AGENT" MODIFY ("MATRICULE" NOT NULL ENABLE);
  ALTER TABLE "AGENT" ADD CONSTRAINT "COMPTE_PK" PRIMARY KEY ("MATRICULE", "LOGIN")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS"  ENABLE;
  ALTER TABLE "AGENT" MODIFY ("LOGIN" NOT NULL ENABLE);
  ALTER TABLE "AGENT" MODIFY ("PASSWORD" NOT NULL ENABLE);
  ALTER TABLE "AGENT" MODIFY ("TYPE" NOT NULL ENABLE);
--------------------------------------------------------
--  Constraints for Table ARME
--------------------------------------------------------

  ALTER TABLE "ARME" MODIFY ("ID_ARME" NOT NULL ENABLE);
  ALTER TABLE "ARME" ADD CONSTRAINT "ARME_PK" PRIMARY KEY ("ID_ARME")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table CITOYEN
--------------------------------------------------------

  ALTER TABLE "CITOYEN" MODIFY ("ID_CITOYEN" NOT NULL ENABLE);
  ALTER TABLE "CITOYEN" ADD CONSTRAINT "CITOYEN_PK" PRIMARY KEY ("ID_CITOYEN")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table DECLARATION
--------------------------------------------------------

  ALTER TABLE "DECLARATION" MODIFY ("ID_CITOYEN" NOT NULL ENABLE);
  ALTER TABLE "DECLARATION" MODIFY ("ID_DECL" NOT NULL ENABLE);
  ALTER TABLE "DECLARATION" ADD CONSTRAINT "DECLARATION_PK" PRIMARY KEY ("ID_DECL")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table DOCUMENT
--------------------------------------------------------

  ALTER TABLE "DOCUMENT" MODIFY ("ID_DOC" NOT NULL ENABLE);
  ALTER TABLE "DOCUMENT" ADD CONSTRAINT "DOCUMENT_PK" PRIMARY KEY ("ID_DOC")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table ENQUETTE
--------------------------------------------------------

  ALTER TABLE "ENQUETTE" MODIFY ("ID_ENQUETTE" NOT NULL ENABLE);
  ALTER TABLE "ENQUETTE" ADD CONSTRAINT "ENQUETTE_PK" PRIMARY KEY ("ID_ENQUETTE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table TEMOIGNAGE
--------------------------------------------------------

  ALTER TABLE "TEMOIGNAGE" ADD CONSTRAINT "TEMOIGNAGE_FK1" FOREIGN KEY ("ID_CITOYEN")
	  REFERENCES "CITOYEN" ("ID_CITOYEN") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table SUSPECT
--------------------------------------------------------

  ALTER TABLE "SUSPECT" ADD CONSTRAINT "SUSPECT_FK1" FOREIGN KEY ("ID_CITOYEN")
	  REFERENCES "CITOYEN" ("ID_CITOYEN") ENABLE;
  ALTER TABLE "SUSPECT" ADD CONSTRAINT "SUSPECT_FK2" FOREIGN KEY ("ID_ENQUETTE")
	  REFERENCES "ENQUETTE" ("ID_ENQUETTE") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table PV
--------------------------------------------------------

  ALTER TABLE "PV" ADD CONSTRAINT "PV_FK1" FOREIGN KEY ("ID_CITOYEN")
	  REFERENCES "CITOYEN" ("ID_CITOYEN") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table PLAINTE
--------------------------------------------------------

  ALTER TABLE "PLAINTE" ADD CONSTRAINT "PLAINTE_FK1" FOREIGN KEY ("ID_CITOYEN")
	  REFERENCES "CITOYEN" ("ID_CITOYEN") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table OBJET_RETROUVE
--------------------------------------------------------

  ALTER TABLE "OBJET_RETROUVE" ADD CONSTRAINT "OBJET_RETROUVE_FK1" FOREIGN KEY ("ID_CITOYEN")
	  REFERENCES "CITOYEN" ("ID_CITOYEN") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table MSG_LUES_ETNONLUES
--------------------------------------------------------

  ALTER TABLE "MSG_LUES_ETNONLUES" ADD CONSTRAINT "MSG_LUES_ETNONLUES_FK1" FOREIGN KEY ("ID_MSG")
	  REFERENCES "MESSAGE" ("ID_MSG") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table DECLARATION
--------------------------------------------------------

  ALTER TABLE "DECLARATION" ADD CONSTRAINT "DECLARATION_FK1" FOREIGN KEY ("ID_CITOYEN")
	  REFERENCES "CITOYEN" ("ID_CITOYEN") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table DOCUMENT
--------------------------------------------------------

  ALTER TABLE "DOCUMENT" ADD CONSTRAINT "DOCUMENT_FK1" FOREIGN KEY ("ID_CITOYEN")
	  REFERENCES "CITOYEN" ("ID_CITOYEN") ENABLE;
