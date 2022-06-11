CREATE TABLE IF NOT EXISTS `tripdb`.`r-t` (
  `RevisioneRelativa` int unsigned NOT NULL,
  `TagliandoAssociato` int unsigned NOT NULL,
  PRIMARY KEY (`RevisioneRelativa`,`TagliandoAssociato`),
  KEY `FK_tagliando_idx` (`TagliandoAssociato`),
  CONSTRAINT `FK_revisione` FOREIGN KEY (`RevisioneRelativa`) REFERENCES `revisione` (`IdRevisione`),
  CONSTRAINT `FK_tagliando` FOREIGN KEY (`TagliandoAssociato`) REFERENCES `tagliando` (`IdTagliando`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
