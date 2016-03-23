-- 视图的应用

-- 创建stu表，并插入相应的数据
CREATE TABLE stu
(
s_id   INT(11) PRIMARY KEY NOT NULL UNIQUE,
s_name VARCHAR(20) NOT NULL,
addr   VARCHAR(50) NOT NULL,
tel    VARCHAR(50) NOT NULL
);

INSERT INTO stu VALUES
(1, 'XiaoWang', 'Henan', '0371-12345678'),
(2, 'XiaoLi', 'Hebei', '13889072345'),
(3, 'ZhengGu', 'Henan', '0371-12345670');

-- 创建表sign表，并插入相应数据
CREATE TABLE vsign
(
s_id  		INT(11) PRIMARY KEY NOT NULL UNIQUE,
s_name  	VARCHAR(20) NOT NULL,
s_sch  		VARCHAR(50) NOT NULL,
s_sign_sch  VARCHAR(50) NOT NULL
);


INSERT INTO vsign VALUES
(1, 'XiaoWang', 'Middle School1', 'Peking University'),
(2, 'XiaoLi', 'Middle School2', 'Tsinghua University'),
(3, 'XiaoTian', 'Middle School3', 'Tsinghua University');

--创建stu_mark表，并插入相应的数据
CREATE TABLE stu_mark
(
s_id  	INT(11) PRIMARY KEY NOT NULL UNIQUE,
s_name 	VARCHAR(20) NOT NULL,
mark  	INT(11) NOT NULL
);

INSERT INTO stu_mark VALUES
(1, 'XiaoWang', 80),
(2, 'XiaoLi', 71),
(3, 'XiaoTian', 70);


-- 创建考上Peking University的学生的视图
CREATE VIEW beida(id, name, mark, sch)
AS SELECT stu_mark.s_id, stu_mark.s_name, stu_mark.mark, vsign.s_sign_sch
FROM stu_mark, vsign
WHERE stu_mark.s_id = vsign.s_id AND stu_mark.mark >= 41 AND vsign.s_sign_sch = 'Peking University';


-- 创建考上Tsinghua University的学生的视图
CREATE VIEW qinghua(id, name, mark, sch)
AS SELECT stu_mark.s_id, stu_mark.s_name,stu_mark.mark,vsign.s_sign_sch
FROM stu_mark,vsign
WHERE stu_mark.s_id = vsign.s_id AND stu_mark.mark >= 40 AND vsign.s_sign_sch = 'Tsinghua University';



-- 对录入的成绩进行更正
UPDATE stu_mark SET mark = mark-50 WHERE stu_mark.s_name = 'XiaoTian';

-- 查看视图的创建信息
SELECT * FROM information_schema.views\G

-- 删除创建的视图
DROP VIEW beida;


-- 创建一个业务统计表persons
CREATE TABLE persons
(
name  VARCHAR(40) NOT NULL,
num   INT(11) NOT NULL
);

-- 创建一个销售额表sales
CREATE TABLE sales
(
name  VARCHAR(40) NOT NULL,
ssum  INT(11) NOT NULL
);

-- 创建一个触发器
CREATE TRIGGER num_sum AFTER INSERT ON persons
FOR EACH ROW INSERT INTO sales VALUES(NEW.name, 7*NEW.num);


-- 向persons表中插入记录
INSERT INTO persons VALUES('xiaoxiao',20),('xiaohua',69);


-- 查看触发器的信息
SELECT * FROM INFORMATION_SCHEMA.TRIGGERS WHERE TRIGGER_NAME = 'num_sum'\G

-- 创建INSERT事件的触发器
CREATE TRIGGER insertevent BEFORE INSERT ON persons
FOR EACH ROW INSERT INTO sales VALUES('test', 10);


INSERT INTO persons VALUES('wangdch', 80);

-- 创建新账户
GRANT SELECT, UPDATE(b_id, b_name,price)
ON fivechapter.books
To 'newAdmin'@'localhost' IDENTIFIED BY 'pwl'
WITH MAX_CONNECTIONS_PER_HOUR 30;


-- 用户账户创建完成后，账户信息保存在user表，权限信息则分别保存在tables_priv和column_priv表中

SELECT host, user, select_priv,update_priv FROM user WHERE user = 'newAdmin';

SELECT host, db, user, table_name, column_name, column_priv
FROM columns_priv WHERE user = 'newAdmin';

SELECT host, db, user, table_name, table_priv, column_priv
FROM tables_priv WHERE user = 'newAdmin';


-- 使用SHOW GRANT语句查看newAdmin的权限信息
SHOW GRANTS FOR 'newAdmin'@'localhost'\G

-- 使用newAdmin用户登录MySQL


-- 使用newAdmin用户查看数据库中的表数据
SELECT * FROM fivechapter.books;

SELECT * FROM fivechapter.books LIMIT 3;

-- 使用newAdmin用户向表中插入一条新记录
INSERT INTO fivechapter.books VALUES(250, 'WANG','DE',25,'2016-03-23','CHUN',10);


-- 收回newAdmin账户的权限
REVOKE SELECT, UPDATE ON fivechapter.books FROM 'newAdmin'@'localhost';

-- 删除指定账户
DROP USER 'newAdmin'@'localhost';



-- 创建数据库
CREATE DATABASE Team;
use Team;
CREATE TABLE player
(
playid  	INT PRIMARY KEY,
playname  	VARCHAR(30) NOT NULL,
teamnum  	INT NOT NULL UNIQUE,
info  		VARCHAR(50)
);

-- 创建一个新账户，授权该用户对Team数据库中player表的SELECT和INSERT权限，并且授权该用户对player表的info字段的UPDATE权限

GRANT SELECT, INSERT ON Team.player
To 'account1'@'localhost'
IDENTIFIED BY 'oldpwd1';

-- 更改account1账户的密码为newpwd2
SET PASSWORD = PASSWORD('newpwd2');

























