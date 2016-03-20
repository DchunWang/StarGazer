-- 第八章

--创建数据表
CREATE TABLE books
(
	b_id  	INT(11) PRIMARY KEY NOT NULL UNIQUE AUTO_INCREMENT,
	b_name  VARCHAR(50) NOT NULL,
	authors VARCHAR(100) NOT NULL,
	price   FLOAT NOT NULL,
	pubdate YEAR NOT NULL,
	note  	VARCHAR(100),
	num 	INT(11) NOT NULL
);


-- 指定所有字段名称插入记录
INSERT INTO books 
(b_id, b_name,authors, price, pubdate, note, num)
VALUES(1, 'Tale of AAA', 'Dickes', 23, '1995', 'novel', 11);


-- 不指定字段名称插入记录
INSERT INTO books VALUES
(2, 'EmmaT', 'Jane lura', 35, '1993', 'joke', 22);

-- 同时插入多条记录
INSERT INTO books VALUES
(3, 'Story of Jane', 'Jane Tim', 40, '2001', 'novel', 0),
(4, 'Lovey Day', 'George Byron', 20, '2005', 'novel', 30),
(5, 'Old Land', 'Honore Blade', 30, '2010', 'law', 0),
(6, 'The Battle', 'Upton Sara', 30, '1999', 'medicine', 40),
(7, 'Rose Hood', 'Richard Haggard', 28, '2008', 'cartoon', 28);

-- 将小说类型（novel)的书的价格都增加5
UPDATE books SET price = price + 5 WHERE note = 'novel';

SELECT b_id, b_name, price FROM books WHERE note = 'novel';


-- 将名称EmmaT的书的价格改为40，并将说明改为drama
UPDATE books SET price = 40, note = 'drama' WHERE b_name = 'EmmaT';

SELECT b_name, price, note FROM books
WHERE b_name = 'EmmaT';

-- 删除库存为0的记录
DELETE FROM books WHERE num = 0;

SELECT b_id, num FROM books;


-- 创建数据表pet
CREATE TABLE pet
(
	name    VARCHAR(20) NOT NULL,
	owner   VARCHAR(20),
	species VARCHAR(20) NOT NULL,
	sex    CHAR(1) NOT NULL,
	birth  YEAR NOT NULL,
	death  YEAR
);

-- 使用不同方法将数据插入其中
INSERT INTO pet
(name, owner, species, sex, birth, death)
VALUES
('Fluffy', 'Harold', 'cat', 'f', '2003', '2010');

INSERT INTO pet
VALUES
('Claws', 'Gwen', 'cat', 'm', '2004', NULL);


INSERT INTO pet
VALUES
('Buffy', NULL, 'dog', 'f', '2009', NULL),
('Fang', 'Benny', 'dog', 'm', '2000', NULL),
('Bowser', 'Diane', 'dog', 'm', '2003', '2009'),
('Chirpy', NULL, 'bird', 'f', '2008', NULL);

-- 使用UPDATE语句将名称为Fang的狗的主人改为Kevin
UPDATE pet SET owner = 'Kevin' WHERE name = 'Fang';

SELECT * FROM pet WHERE name = 'Fang';


-- 将没有主人的宠物的owner字段值都改为Duck
UPDATE pet SET owner = 'Duck' WHERE owner <=> NULL;

SELECT * FROM pet WHERE owner <=> 'Duck';


-- 删除已经死亡的宠物记录
DELETE FROM pet WHERE death IS NOT NULL;


-- 删除表中所哟记录
DELETE FROM pet;



























