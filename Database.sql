DROP DATABASE POA_2020;
CREATE DATABASE POA_2020;

Use POA_2020;

CREATE TABLE tbl_Devices (
  Identifikationsnummer int AUTO_INCREMENT NOT NULL,
  Bezeichnung varchar(255) DEFAULT NULL,
  
  PRIMARY KEY (Identifikationsnummer)
);

CREATE TABLE tbl_User (
  Gelegenheitsunternehmensangestellteidentifikationsnummer int AUTO_INCREMENT NOT NULL,
  Vorname varchar(64) DEFAULT NULL,
  Nachname varchar(64) DEFAULT NULL,
  Pin varchar(255) DEFAULT NULL,
  CreatedAt timestamp NOT NULL DEFAULT current_timestamp(),
  
  PRIMARY KEY(Gelegenheitsunternehmensangestellteidentifikationsnummer)
);

CREATE TABLE tbl_ActivityLog (
  ID int AUTO_INCREMENT NOT NULL,
  UserID int NOT NULL,
  DeviceID_Login int NOT NULL,
  DeviceID_Logout int DEFAULT NULL,
  Time_Login timestamp DEFAULT current_timestamp(),
  Time_Logout timestamp DEFAULT '0000-00-00 00:00:00',
  
  PRIMARY KEY (ID),
  FOREIGN KEY (UserID) REFERENCES tbl_User(Gelegenheitsunternehmensangestellteidentifikationsnummer),
  FOREIGN KEY (DeviceID_Login) REFERENCES tbl_Devices(Identifikationsnummer),
  FOREIGN KEY (DeviceID_Logout) REFERENCES tbl_Devices(Identifikationsnummer)
);


INSERT INTO tbl_User (Vorname, Nachname, Pin) VALUES
('Enes ', 'Ünsal', '123A'),
('Nicklas', 'Gehlen', '4321'),
('Marvin', 'Höck', '6309');

INSERT INTO tbl_Devices (Bezeichnung) VALUES
('Der Geraet vong N1CK145'),
('Der Geraet von der Kanacke'),
('Hoeckeberry fin');