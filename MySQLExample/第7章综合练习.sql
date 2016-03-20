
-- 第7章

-- 创建表dept
CREATE TABLE dept
(
d_no  INT(11) PRIMARY KEY NOT NULL UNIQUE AUTO_INCREMENT,
d_name  VARCHAR(50) NOT NULL,
d_location  VARCHAR(100)
);

--创建表employee
CREATE TABLE employee
(
	e_no  INT(11) PRIMARY KEY NOT NULL UNIQUE,
	e_name  VARCHAR(50) NOT NULL, 
	e_gender  CHAR(2),
	dept_no  INT(11) NOT NULL,
	e_job  	VARCHAR(50) NOT NULL,
	e_salary  INT(11) NOT NULL,
	hireDate  DATE NOT NULL,
	CONSTRAINT dno_fk FOREIGN KEY(dept_no) REFERENCES dept(d_no)
);


-- 将指定的记录分别插入两个表中

INSERT INTO dept VALUES
(10, 'ACCOUNTING', 'ShangHai'),
(20, 'RESEARCH', 'BeiJing'),
(30, 'SALES', 'ShenZhen'),
(40, 'OPERATIONS', 'FuJian');

INSERT INTO employee VALUES
(1001, 'SMITH', 'm', 20, 'CLERK', 800, '2005-11-12'),
(1002, 'ALLEN', 'f', 30, 'SALESMAN', 1600, '2003-05-12'),
(1003, 'WARD', 'f', 30, 'SALESMAN', 1250, '2003-05-12'),
(1004, 'JONES', 'm', 20, 'MANAGER', 2975, '1998-05-18'),
(1005, 'MARTIN', 'm', 30, 'SALESMAN', 1250, '2001-06-12'),
(1006, 'BLAKE', 'f', 30, 'MANAGER', 2850, '1997-02-15'),
(1007, 'CLARK', 'm', 10, 'MANAGER', 2450, '2002-09-12'),
(1008, 'SCOTT', 'm', 20, 'ANALYST', 3000, '2003-05-12'),
(1009, 'KING', 'f', 10, 'PRESIDENT', 5000, '1995-01-01'),
(1010, 'TURNER', 'f', 30, 'SALESMAN', 1500, '1997-10-12'),
(1011, 'ADAMS', 'm', 20, 'CLERK', 1100, '1999-10-05'),
(1012, 'JAMES', 'f', 30, 'CLERK', 950, '2008-06-15');



-- 在employee表中，查询所有记录的e_no, e_name和e_salary字段值

SELECT e_no, e_name, e_salary FROM employee;


/*在employee表中，查询dept_no等于10和20的所有记录*/
SELECT * FROM employee WHERE dept_no IN(10, 20);


-- 在employee表中，查询工资范围在800~2500之间的员工信息
SELECT e_no, e_name, e_salary, hireDate FROM employee
WHERE e_salary BETWEEN 800 AND 2500;


-- 在employee表中，查询部门编号为20的部门中的员工信息

SELECT * FROM employee WHERE dept_no <=> 20;


-- 在employee表中，查询每个部门最高工资的员工信息
SELECT e_name,dept_no, MAX(e_salary) FROM employee GROUP BY dept_no;

-- 查询员工BLAKE所在部门和部门所在地
SELECT d_name, d_location FROM dept
WHERE d_no =
(SELECT dept_no FROM employee WHERE e_name = 'BLAKE');

-- 使用连接查询，查询所有员工的部门和部门信息
SELECT e_no, e_name, dept_no, d_name, d_location 
FROM dept, employee
WHERE employee.dept_no = dept.d_no;

-- 在employee表中，计算每个部门各有多少名员工
SELECT dept_no,COUNT(*) AS eNum
FROM employee
GROUP BY dept_no;

-- 在employee表中，计算不同类型职工的总工资数
SELECT e_job, SUM(e_salary) FROM employee
GROUP BY e_job;


-- 在employee表中，计算不同部门的平均工资
SELECT dept_no, AVG(e_salary) FROM employee
GROUP BY dept_no;

-- 在employee表中，查询工资低于1500的员工信息
SELECT e_name, dept_no, e_job, e_salary FROM employee
WHERE e_salary <= 1500;


-- 在employee表中，将查询记录先按部门编号由高到低排列，再按员工工资由高到低排列

SELECT e_name,dept_no, e_salary FROM employee ORDER BY dept_no DESC, e_salary DESC;


-- 在employee表中，查询员工姓名以字母A或S开头的员工的信息

SELECT e_name, e_job FROM employee
WHERE e_name REGEXP '^[as]';


-- 在employee表中，查询到目前为止，工龄大于等于10年的员工信息

SELECT * FROM employee WHERE (YEAR(NOW()) - YEAR(hireDate)) >= 15;

-- 在employee表中，计算所有女员工的工龄
SELECT e_name, e_gender,YEAR(NOW()) - YEAR(hireDate) AS gongling 
FROM employee
WHERE e_gender = 'f';


-- 使用LIMIT查询从第3条记录开始到第6条记录

SELECT * FROM employee
LIMIT 2, 4;

-- 查询销售人员(SALSEMAN)的最低工资
SELECT e_name, e_job, MIN(e_salary) 
FROM employee
WHERE e_job = 'SALESMAN';


-- 查询名字以字母N或者S结尾的记录
SELECT e_name FROM employee
WHERE e_name REGEXP '[ns]$';


-- 查询在BeiJing工作的员工的姓名和职务
SELECT dept_no,e_name, e_job FROM employee
WHERE dept_no = 
(SELECT d_no FROM dept WHERE d_location = 'BeiJing');


-- 使用左连接方式查询employee和dept表
SELECT * FROM employee LEFT OUTER JOIN dept 
ON employee.dept_no = dept.d_no;


-- 查询所有2001~2005年入职的员工的信息，查询部门编号为
-- 20和30的员工信息并使用UNION合并两个查询结果

SELECT e_name, dept_no, e_job, hireDate
FROM employee
WHERE YEAR(hireDate) BETWEEN 2001 AND 2005
UNION ALL
SELECT e_name, dept_no, e_job, hireDate
FROM employee
WHERE dept_no IN(20, 30);


-- 使用LIKE查询员工姓名中包含字母a的记录
SELECT e_name FROM employee
WHERE e_name LIKE '%a%';


-- 使用REGEXP查询员工姓名中包含T、C或者M这3个字母中任意一个的记录

SELECT e_name FROM employee
WHERE e_name REGEXP '.*[tcm].*';

















