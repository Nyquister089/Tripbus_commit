CREATE TABLE IF NOT EXISTS `tripdb`.`rt` (
  `RevisioneRelativa` int unsigned NOT NULL,
  `TagliandoAssociato` int unsigned NOT NULL,
  PRIMARY KEY (`RevisioneRelativa`,`TagliandoAssociato`),
  KEY `rt_tagliando_idx` (`TagliandoAssociato`),
  KEY `rt_revisione` (`RevisioneRelativa`),
  CONSTRAINT `FK_rt_revisione` FOREIGN KEY (`RevisioneRelativa`) REFERENCES `revisione` (`IdRevisione`),
  CONSTRAINT `FK_rt_taglianto` FOREIGN KEY (`TagliandoAssociato`) REFERENCES `tagliando` (`IdTagliando`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
