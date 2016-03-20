CREATE TABLE employee
(
	empployeeNumber	 INT(11) NOT NULL PRIMARY KEY AUTO_INCREMENT,
	lastName		 VARCHAR(50) NOT NULL,
	firstName		 VARCHAR(50) NOT NULL,
	mobile			 VARCHAR(25) NOT NULL,
	officeCode	   	 INT(10) NOT NULL,
	jobTitle		 VARCHAR(50) NOT NULL,
	birth			 DATETIME NOT NULL,
	note			 VARCHAR(255) NOT NULL,
	sex				 VARCHAR(5) NOT NULL,
	CONSTRAINT office_fk FOREIGN KEY(officeCode) REFERENCES offices(officeCode)
);

