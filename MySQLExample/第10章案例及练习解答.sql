-- 创建一个存储函数用来统计sch中的记录数
CREATE FUNCTION count_sch()
RETURNS INT 
RETURN (SELECT COUNT(*) FROM sch);


-- 创建一个存储过程，通过调用存储函数的方法来获取表sch中的记录数和sch表中的id的和

DELIMITER// 
CREATE PROCEDURE add_id(out count INT)
BEGIN
DECLARE itmp INT;
DECLARE cur_id CURSOR FOR SELECT id FROM sch;
DECLARE EXIT HANDLER FOR NOT FOUND CLOSE cur_id;
SELECT count_sch() INTO count;
SET @sum = 0;
OPEN cur_id;
REPEAT
FETCH cur_id INTO itmp;
IF itmp < 10
THEN SET @sum = @sum + itmp;
END IF;
UNTIL 0 END REPEAT;
CLOSE cur_id;
END//
DELIMITER ; 
































































