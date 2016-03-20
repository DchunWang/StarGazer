SELECT LENGTH('Hello World!') AS leng1,
LENGTH('University') AS leng2,
SUBSTRING('Nice to meet you!', 9, 4) AS sub,
REPEAT('Cheer!', 3) AS rep,
REVERSE('voodoo') AS rev;


SELECT CONCAT(ELT(1,'MySQL', 'not', 'is', 'great'), 
ELT(3, 'MySQL', 'not', 'is', 'great'),
ELT(4, 'MySQL', 'not', 'is', 'great')) AS xin;

SELECT WEEK(CURDATE()) AS tweek,
DAYNAME(CURDATE()) AS tgong,
DAYOFWEEK(CURDATE()) AS twei,
YEAR(CURDATE()) - YEAR('1929-02-14') AS t3,
DATE_FORMAT(CURDATE(), '%y %b %D %W') AS t4,
SECOND(now()) AS t5;


SELECT ENCODE('mysql', '123') AS mi1,
DECODE(ENCODE('mysql','123'), 'bbb') AS mi2;


SELECT ENCODE('mysql', 'bbb') AS mi1,
DECODE(mil, 'bbb') AS mi2;



SELECT CONV(100, 10, 16) AS W3;

SELECT FORMAT(5.1584, 3) AS W4;

SELECT CHARSET('new string') AS w6,
CHARSET(CONVERT('new string' USING gb2312)) as w5;
