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

-- 
GRANT SELECT, UPDATE(id, name, age)
ON test_db.person_old
To 'new Admin'@'localhost' IDENTIFIED BY 'pwl'
WITH MAX_CONNECTIONS_PER_HOUR 30;


















































