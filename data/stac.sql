-- MySQL dump 10.13  Distrib 5.5.49, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: STACDB
-- ------------------------------------------------------
-- Server version	5.5.49-0ubuntu0.12.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Admins`
--

DROP TABLE IF EXISTS `Admins`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Admins` (
  `ID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `FName` varchar(20) NOT NULL,
  `LName` varchar(20) NOT NULL,
  `UName` varchar(20) NOT NULL,
  `Password` varchar(20) NOT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `ID_UNIQUE` (`ID`),
  UNIQUE KEY `UName_UNIQUE` (`UName`)
) ENGINE=InnoDB AUTO_INCREMENT=79 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Admins`
--

LOCK TABLES `Admins` WRITE;
/*!40000 ALTER TABLE `Admins` DISABLE KEYS */;
INSERT INTO `Admins` VALUES (1,'Mehrgan','Mostowfi','mmostowfi','lol'),(2,'Joshua','Sachs','sach0351','whatever'),(3,'David','Worth','wort9151','something'),(4,'New','Admin','na','mb'),(5,'New','Admin','mc','ha'),(7,'mac','chz','macaroni','1234'),(8,'first','Last','Tyler','a1'),(9,'New1','Admin','NewAdmin1','NewAdminPass1'),(12,'pink','ranger','pinkranger','zed3'),(13,'nuAdmin123','admin_right','admin_2014','admin1234'),(14,'Tyler','Smith','smit3928','smith39'),(15,'Erica','Garner','test3927','12345678'),(16,'Erica','Garner','test3928','12345678'),(24,'First Name','Last Name','username ','password'),(27,'Zach','Cervi','zach','test'),(36,'cam1','cam1','cam1','cam1'),(37,'cam2','cam2','cam2','cam2'),(38,'cam3','cam3','cam3','cam3'),(39,'test','test','testc','testc'),(40,'richard','williams','richard','richard1'),(41,'cristin','dicesare','cris2','cris2'),(42,'cam4','cam4','cam4','cam4'),(43,'cam5','cam5','cam5','cam5'),(44,'cam6','cam6','cam6','cam6'),(45,'cris1','cris1','cris1','cris1'),(46,'Connor','Rudolph','CR','password'),(47,'bob','ross','b.ross','abc123'),(48,'zach','cerviiii','U','P'),(49,'zachhh','cerrrviiii','zachCerv1','password'),(50,'john','smith','username123','password'),(51,'john','smith','username13421423','password'),(52,'jon','test','jon','test'),(53,'hippo','hippo','hippo','hippo'),(54,'fdgfdgdfgf','wfdfdsff','camiutuhirt','cam1'),(55,'Admin','Sutton','Sutt1001','Pass12'),(56,'Adammm\"','Suttonnn\"','adm1101','pass111\"_'),(57,'j','m','c','i'),(58,'jon','m','coding','isbad'),(59,'Tyler','Vier','joe_palisoul','Passw0rd'),(60,'Lord','Admin','admin111','pass1212'),(62,'add803','min803','admin803','pass803'),(63,'Sir Elton','John','ejohn','rocketman'),(64,'Eric','Melgarejo','eric100','1234'),(66,'Cesar','Espinosa','cesar','1234'),(67,'is','jeff','my','name'),(68,'Cesar','Espinosa','cesare','1234'),(69,'Billy','Joel','bjoel','pianoman'),(72,'Eric','Melgarejo','eric1000','1234'),(73,'Casey','Floyd','floynnnn','djdnjnjd'),(75,'Cesar','Espinosa','cesares','1234'),(77,'Cesar','Espinosa','cesarespi','1234'),(78,'o','p','m','n');
/*!40000 ALTER TABLE `Admins` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Attendance`
--

DROP TABLE IF EXISTS `Attendance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Attendance` (
  `ID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `UserID` int(11) unsigned NOT NULL,
  `ClassID` int(8) unsigned NOT NULL,
  `AttnTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ID`),
  KEY `FK_UserID_Users_ID_idx` (`UserID`),
  KEY `FK_Attendance_ClassID_Classes_ID_idx` (`ClassID`),
  CONSTRAINT `FK_Attendance_ClassID_Classes_ClassID` FOREIGN KEY (`ClassID`) REFERENCES `Classes` (`ClassID`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `FK_Attendance_UserID_Users_ID` FOREIGN KEY (`UserID`) REFERENCES `Users` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=70 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Attendance`
--

LOCK TABLES `Attendance` WRITE;
/*!40000 ALTER TABLE `Attendance` DISABLE KEYS */;
INSERT INTO `Attendance` VALUES (1,1,12234444,'2014-10-12 15:00:00'),(2,1,12234444,'2014-10-13 15:00:00'),(3,1,12234444,'2014-10-14 15:00:00'),(4,1,12234444,'2014-10-14 15:00:00'),(5,1,12234444,'2014-10-15 15:00:00'),(6,1,12234444,'2014-10-16 15:00:00'),(7,1,12234444,'2014-10-14 15:07:00'),(8,1,12234444,'2014-10-17 15:00:00'),(9,3,12234444,'2014-10-14 15:05:00'),(10,4,12234444,'2014-10-14 15:02:00'),(11,3,12234444,'2015-03-10 08:21:12'),(12,3,12234444,'2015-03-10 08:52:58'),(13,3,12234444,'2015-03-10 08:53:00'),(14,3,12234444,'2015-03-10 08:53:03'),(15,3,12234444,'2015-04-07 12:20:40'),(16,3,12527400,'2015-04-07 12:31:38'),(17,3,12234444,'2015-04-07 12:39:27'),(18,3,12234444,'2015-04-07 12:40:34'),(19,3,12527400,'2015-04-07 12:42:38'),(20,3,12527400,'2015-04-07 12:43:15'),(21,3,12234444,'2015-04-08 08:30:21'),(22,3,12234444,'2015-04-08 15:00:00'),(23,3,12234444,'2015-04-08 16:00:00'),(24,3,12234444,'2015-04-09 07:18:33'),(25,3,12234444,'2015-04-09 08:10:19'),(26,84,10155569,'2015-11-18 16:00:00'),(27,84,10155569,'2015-11-18 16:00:00'),(28,84,10155569,'2015-11-18 16:00:00'),(29,89,10155569,'2015-11-18 16:00:00'),(30,89,10155569,'2015-11-18 17:00:00'),(31,84,20151552,'2015-11-11 16:00:22'),(32,82,20151552,'2015-11-19 15:00:00'),(33,82,20151552,'2015-11-19 15:00:00'),(34,84,12234444,'2015-11-11 16:00:44'),(35,89,10155569,'2015-11-11 16:00:33'),(38,82,20151552,'2015-11-19 15:00:00'),(39,82,20151552,'2015-11-19 15:00:00'),(40,82,20151552,'2015-11-19 15:00:00'),(41,60,10155569,'2015-11-18 16:00:00'),(42,84,10155569,'2015-11-18 16:00:00'),(43,84,10155569,'2015-11-18 16:00:00'),(44,84,10155569,'2015-11-19 16:00:00'),(47,84,10155569,'2015-11-11 16:00:00'),(48,84,10155569,'2015-11-11 16:00:00'),(49,82,20157036,'2015-12-07 07:00:00'),(50,82,20157036,'2015-12-07 15:00:00'),(51,82,20157036,'2015-12-07 15:00:02'),(52,82,20153675,'2015-08-24 15:01:00'),(53,82,20153675,'2015-08-31 15:01:00'),(54,82,20153675,'2015-09-07 15:03:00'),(55,82,20153675,'2015-09-29 15:03:02'),(56,82,20153675,'2015-10-06 15:03:02'),(57,82,20153675,'2015-10-05 15:03:02'),(58,82,20153675,'2015-10-07 15:03:02'),(59,101,20156865,'2015-12-08 23:44:37'),(60,101,20156865,'2015-12-08 23:58:03'),(61,101,20158216,'2015-12-09 00:43:37'),(62,103,20153756,'2015-12-09 00:50:24'),(63,103,20153756,'2015-12-09 00:53:16'),(64,103,20153756,'2015-12-09 00:59:20'),(65,84,10155569,'2015-12-10 19:00:00'),(66,84,10155569,'2015-12-10 19:00:00'),(67,103,20159999,'2015-12-11 00:46:44'),(68,7,10155569,'2015-12-11 19:00:00'),(69,101,20158216,'2015-12-11 16:21:38');
/*!40000 ALTER TABLE `Attendance` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Classes`
--

DROP TABLE IF EXISTS `Classes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Classes` (
  `ClassID` int(8) unsigned NOT NULL,
  `ClassName` varchar(50) NOT NULL,
  `AdminID` int(11) unsigned NOT NULL,
  `Institution` varchar(50) DEFAULT NULL,
  `MeetTimes` varchar(100) NOT NULL,
  `StartDate` date NOT NULL,
  `EndDate` date NOT NULL,
  `PublicIPAddress` varchar(15) NOT NULL,
  PRIMARY KEY (`ClassID`),
  KEY `FK_Admins_ID_idx` (`AdminID`),
  CONSTRAINT `FK_Classes_AdminID_Admins_ID` FOREIGN KEY (`AdminID`) REFERENCES `Admins` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Classes`
--

LOCK TABLES `Classes` WRITE;
/*!40000 ALTER TABLE `Classes` DISABLE KEYS */;
INSERT INTO `Classes` VALUES (20166,'TestClass',63,'UNC-2','M1030-1130','0000-00-00','0000-00-00','127.0.0.1'),(1015449,'boom',38,'UNC','','2015-11-11','2015-12-12','0.0.0.0'),(1656300,'Anatomy',2,'UNC','W11:00-12:00','2014-01-04','2014-05-25','0.0.0.0'),(4819233,'newClass',15,'inst','W11:00-12:00','2015-08-24','2015-12-11','127.0.0.0'),(10152285,'boom',38,'UNC','','2015-11-11','2015-12-12','0.0.0.0'),(10155569,'math',36,'UNC','M11:00-12:00','2015-11-11','2015-12-12','0.0.0.0'),(10158827,'math',37,'UNC','','2015-11-11','2015-12-12','0.0.0.0'),(10519642,'Physiology',2,'UNC','M09:00-10:00','2014-01-04','2014-05-25','0.0.0.0'),(10865052,'tag',2,'UNC','W08:00-10:00','2014-01-04','2014-05-25','0.0.0.0'),(11850126,'Chemistry',2,'UNC','W11:00-12:00','2014-01-04','2014-05-25','0.0.0.0'),(12234444,'Biology',2,'UNC','M09:00-10:00','2014-01-04','2014-05-25','138.86.122.233'),(12510038,'Chemistry 101',2,'UNC','W11:00-13:00','2015-08-24','2015-12-11','138.86.122.233'),(12527400,'Krafting',7,'UNC','M13:00-15:00,T13:00-15:00,W13:00-15:00','2015-08-24','2015-12-11','138.86.122.233'),(12992015,'House, M.D.',2,'Madeup TV','M(13:00-14:30),W(13:00-14:30),R(17:00-17:30)','2015-08-24','2015-12-11','138.86.122.233'),(13088471,'MakingKidsShows',12,'UNC','M08:00-10:00','2015-08-24','2015-12-11','138.86.122.233'),(14145090,'Spanish',2,'UNC','M08:00-09:33,T13:45-14:00','2015-08-24','2015-12-11','138.86.47.202'),(15033520,'Ecology',2,'UNC','M08:00-10:00,W09:00-10:00','2015-08-24','2015-12-11','138.86.47.202'),(15242965,'Spanish',2,'UNC','M08:00-09:33,T13:45-14:00','2015-08-24','2015-12-11','138.86.47.202'),(15588290,'b',8,'a','M10:12-11:11','2015-08-24','2015-12-11','138.86.47.202'),(16772014,'Software Engineering - Fall 2014',1,'Univ. of N. Colorado - NHS - MathSci','T(08:00-09:15),R(08:00-09:15)','2015-08-24','2015-12-11','138.86.47.202'),(20150237,'BACS 101',27,'UNC','M09:00-10:00,W09:00-10:00,F09:00-10:00','2015-01-01','2016-01-01','0.0.0.0'),(20151552,'math',36,'UNC','W12:00-13:00','2015-11-11','2015-12-12','4.4.4.4'),(20151641,'Final',27,'UNC','F09:10-11:00,S10:10-11','2015-12-10','2016-01-01','0.0.0.0'),(20151790,'math4',36,'UNC','M02:00-03:00,W02:00-03:3:00,F02:00-03:00','2015-05-05','2015-06-06','4.4.4.4'),(20152042,'Apple',27,'UNCO','M12:05-18:09,T18:55-19:55','2015-12-10','2015-10-10','0.0.0.0'),(20152257,'CS 350',27,'UNC','M08:00-09:00,W09:00-10:00','2015-02-02','2016-02-02','0.0.0.0'),(20152289,'science',45,'unc','W11:00-12:00','2015-11-11','2015-12-12','7.7.7.7'),(20152563,'Hippos',53,'HippoU','T12:00-13:00','2015-12-08','2016-12-08','0.0.0.0'),(20152859,'Final',36,'CS350','F08:10-10:00','2015-12-11','2015-12-12','0.0.0.0'),(20152906,'Testing',52,'Classes','M12:23-14:00','2015-12-08','2016-04-08','0.0.0.0'),(20153019,'HotDogs',40,'Heinz','W12:00-14:00,S14:00-15:00','2000-01-01','2000-01-07','0.0.0.0'),(20153207,'CS 350',27,'UNC','M05:00-07:00 F08:00-11:00','2015-02-02','2016-02-02','0.0.0.0'),(20153318,'Final',27,'UNC','F09:10-11:00,S10:10-11','2015-12-10','2016-01-01','0.0.0.0'),(20153675,'THE BEST CLASS EVAR',27,'UNC','M09:00-09:50','2015-08-23','2015-12-15','0.0.0.0'),(20153756,'Test',40,'CS350','T17:35-18:00','2015-12-08','2015-12-09','0.0.0.0'),(20154170,'Math2',36,'UNC','R02:00-03:00','2015-09-09','2015-10-10','2.2.2.2'),(20154210,'CS 250',27,'UNC','M08:00-09:00,W09:00-10:00','2015-02-02','2016-02-02','0.0.0.0'),(20154335,'CS',40,'UNCO','M11:00-14:00,M15:00-16:00','2000-01-01','2000-01-02','0.0.0.0'),(20154348,'math123',41,'UNC','M10:00-11:00','2015-11-11','2015-12-12','0.0.0.0'),(20155122,'Science',40,'Bill Nye College','T11:00-13:00,R13:00-14:00,Riuhui','2000-01-01','2000-01-06','0.0.0.0'),(20155266,'math',36,'UNC','W12:00-13:00','2015-08-24','2015-12-11','4.4.4.4'),(20155427,'Demo',27,'UNC','S08:10-11:00,U08:10-11','2015-12-10','2016-01-01','0.0.0.0'),(20156391,'Test Class',27,'UNC','M012:00-23:00, F08:00-11:00','2015-12-02','2016-01-02','0.0.0.0'),(20156865,'math',36,'UNC','T12:00-19:00','2015-12-01','2015-12-20','4.4.4.4.4'),(20156911,'science',44,'unc','M11:00-12:00','2015-11-11','2015-12-12','7.7.7.7'),(20157036,'CS 350',27,'UNC','M08:00-09:00,W09:00-10:00','2015-02-02','2016-02-02','0.0.0.0'),(20157139,'CS760',27,'UNC','M08:00-09:00,W09:00-10:00','2015-02-02','2016-02-02','0.0.0.0'),(20157536,'Math3',36,'UNC','F10:00-11:00','2015-07-07','2015-08-08','3.3.3.3'),(20157913,'Demo',27,'UNC','F08:10-11:00 S08:10-11','2015-12-10','2016-01-01','0.0.0.0'),(20158146,'Final',27,'UNC','F08:10-11:00,S08:10-11','2015-12-10','2016-01-01','0.0.0.0'),(20158216,'math',36,'UNC','T12:00-19:00,F07:00-12:00','2015-12-01','2015-12-20','6.6.6.6.6'),(20158238,'art',42,'UNC','F12:00-13:00','2015-07-07','2015-08-08','7.7.7.7'),(20159474,'CS 350',27,'UNC','R17:00-07:00 F08:00-11:00','2015-12-02','2016-01-02','0.0.0.0'),(20159571,'Final',27,'UNC','S08:10-11:00,U08:10-11','2015-12-10','2016-01-01','0.0.0.0'),(20159871,'CS 350',27,'UNC','M05:00-07:00 F08:00-11:00','2015-12-02','2016-01-02','0.0.0.0'),(20159999,'Test Class',27,'UNC','M012:00-23:00, R17:00-23:00','2015-12-02','2016-01-02','0.0.0.0'),(2016026232,'The White Album',63,'UNC-2','F1030-1130','2016-08-09','2016-12-07','127.0.0.1'),(2016058357,'Test Class',63,'UNC-2','M1030-1130','2016-08-09','2016-12-07','1.1.1.1'),(2016061156,'The White Album',63,'UNC-2','F1030-1130','2016-08-09','2016-12-07','127.0.0.1'),(2016094330,'Soft',66,'UNC','W0525-1930;','2016-08-09','2016-12-07','192.168.1.149'),(2016138703,'The White Album',63,'UNC-2','F1030-1130','2016-08-09','2016-12-07','127.0.0.1'),(2016174094,'jlk',1,'unc','tr','2016-02-02','2016-03-03','127.0.0.1'),(2016276540,'Test Class',63,'UNC-2','M1030-1130','0000-00-00','0000-00-00','1.1.1.1'),(2016884798,'Van Halen School of Rock',63,'UNC-2','W1030-1130','2016-08-09','2016-12-07','1.2.3.4');
/*!40000 ALTER TABLE `Classes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Enrollment`
--

DROP TABLE IF EXISTS `Enrollment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Enrollment` (
  `ClassID` int(8) unsigned NOT NULL,
  `UserID` int(11) unsigned NOT NULL,
  `DeviceID` varchar(17) DEFAULT NULL,
  `DeviceChangeFlag` varchar(1) NOT NULL DEFAULT 'Y',
  PRIMARY KEY (`ClassID`,`UserID`),
  KEY `FK_Enrollment_ClassID_Classes_idx` (`ClassID`),
  CONSTRAINT `FK_Enrollment_ClassID_Classes` FOREIGN KEY (`ClassID`) REFERENCES `Classes` (`ClassID`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Enrollment`
--

LOCK TABLES `Enrollment` WRITE;
/*!40000 ALTER TABLE `Enrollment` DISABLE KEYS */;
INSERT INTO `Enrollment` VALUES (1656300,3,NULL,'0'),(4819233,3,NULL,'0'),(4819233,69,NULL,'0'),(10155569,7,'3463538','Y'),(10155569,60,'4534735','Y'),(10155569,62,'55767453','Y'),(10155569,84,'235365','Y'),(10155569,89,NULL,'Y'),(10155569,101,'00:50:56:C0:00:08','Y'),(10158827,82,'MAC','Y'),(10519642,1,NULL,'0'),(11850126,68,NULL,'0'),(12234444,1,NULL,'0'),(12234444,3,'11:22:33:44:55:66','0'),(12234444,68,NULL,'0'),(12234444,84,'34598722','Y'),(12510038,1,NULL,'0'),(12527400,1,NULL,'0'),(20151552,82,'a','Y'),(20151641,101,'00:50:56:C0:00:08','Y'),(20152257,103,'00:50:56:C0:00:08','Y'),(20152563,103,'00:50:56:C0:00:08','Y'),(20152859,101,'00:50:56:C0:00:08','Y'),(20152859,103,'00:50:56:C0:00:08','Y'),(20152859,105,'00:50:56:C0:00:08','Y'),(20153675,82,'0.0.0.0','Y'),(20153756,103,'00:50:56:C0:00:08','Y'),(20154210,82,'MAC','Y'),(20156865,101,'00:50:56:C0:00:08','Y'),(20157036,82,'0.0.0.0','Y'),(20158216,101,'00:50:56:C0:00:08','Y'),(20159999,103,'00:50:56:C0:00:08','Y');
/*!40000 ALTER TABLE `Enrollment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Users`
--

DROP TABLE IF EXISTS `Users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Users` (
  `ID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `FName` varchar(20) NOT NULL,
  `LName` varchar(20) NOT NULL,
  `UName` varchar(20) NOT NULL,
  `Password` varchar(20) NOT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `ID_UNIQUE` (`ID`),
  UNIQUE KEY `UName_UNIQUE` (`UName`)
) ENGINE=InnoDB AUTO_INCREMENT=132 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Users`
--

LOCK TABLES `Users` WRITE;
/*!40000 ALTER TABLE `Users` DISABLE KEYS */;
INSERT INTO `Users` VALUES (1,'Becker','Andrew','beck4113','1234'),(2,'Brooks','Zachary','broo5501','asdf123'),(3,'Garner','Erica','garn3925','qwerty'),(4,'Gregory','House','g.house','zxcvb'),(5,'James','Wilson','james.wilson','987654'),(6,'Remy','Hadley','thirteen','13'),(7,'Sarah ','Linden','sarah','11111'),(8,'Stephen ','Holder','holder','66666'),(54,'john','brown','johnny','54321'),(55,'New Test','User','newtest','newpass'),(56,'New','Admin','NewAdmin','NewAdminPass'),(57,'herbie','joe','herbie3','2345'),(58,'herbert','hoover','herbie6','2345'),(59,'zach','b','hcaz1444','12345'),(60,'q','a','hcaz','123'),(61,'q','a','hcaz1','123'),(62,'robert','kraft','taft','1234'),(63,'hot','sauce','tabasco','1234'),(68,'Gregory','Peck','gregpeck','1234'),(69,'bdylan','why','bob','dylan123'),(71,'Andrew','Becker','beck4116','apple2'),(72,'zach','b','zach123','test123'),(73,'outkast1','andre123','andre','3000'),(75,'Erica','Garner','test3926','12345678'),(76,'Erica','Garner','test3927','12345678'),(77,'Erica','Garner','test3928','12345678'),(78,'M','N','MeNa','123123'),(79,'pass','name','','sdkfjalsdkfjasldfkj'),(82,'Zach','Cervi','zach','test'),(83,'cristin1','cristin1','cristin1','cristin1'),(84,'cris1','cris1','cris1','cris1'),(85,'zach','cervi','zach1','zach1'),(86,'cam','peterson','cam10','cam10'),(87,'cam','peterson','cam11','cam11'),(88,'camryn','peterson','camster','cam111'),(89,'cris2','cris2','cris2','cris2'),(90,'Ryun','Valdez','rvaldez','password'),(91,'Connor','Rudolph','CR','password'),(92,'Jane','Smith','jsmith','abc123'),(93,'tester','tester','hello','there'),(94,'connor','rudolph','connor','test'),(95,'zach','cerviiiii','U','P'),(96,'zach','cervi','usernamedoesne','¡??¬…?'),(97,'zachhh','cerrrviiii','zachCerv1','password'),(98,'zachhh','cerrrviiii','zacrv1','password'),(99,'zachhh','cerrrviiii','jakfds;','password'),(100,'zachhh','cerrrviiii','zachCerdafasfasv1','password'),(101,'Ryun','Valdez','rvaldez24','password'),(102,'Ryun','Valdez','rva','rva'),(103,'Ryun','Valdez','rval','rval'),(104,'Ryun','Valdez','rvald','rvald'),(105,'Ryun','Valdez','ryun12','ryun12'),(106,'Adam','Sutton','Sutt1000','Pass1'),(110,'Elton','John','ejohn','rocketman'),(111,'Sally','Solomon','ssolomon','donlover4ever'),(112,'Dick','Solomon','rsolomon','highcommander'),(113,'matt','wallace','wall','123'),(114,'Test','McSignup','testmc','asdfasdf'),(116,'SELECT','SELECT','SELECT','SELECT'),(117,'john','117','MasterChief','arbiter'),(118,'Saul','Goodman','CallSaul','kjhfkfg'),(119,'Barack','Obama','Gobama','BarackUrworld123'),(120,'Charmayne','Cullom','CCDawg','MCBRULEZ'),(121,'joe','fancy','joe','spaceace4455'),(122,'The Phreshizt','User','thephreshizthimself','asdfasdf'),(123,'Jay','Lightfoot','JLightfoot','xyz123'),(124,'Bill','Cosby','BCosby','hai123'),(125,'NewUser','UserUser','thenewuser','asdfasdf'),(127,'Test','Four','asldkjdlkj','sdlkjdldksj'),(130,'Bradley','Rangel','Bradley123','Rangel123'),(131,'Asdf','Asdf','asdf','asdf');
/*!40000 ALTER TABLE `Users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-11-06 18:24:11
