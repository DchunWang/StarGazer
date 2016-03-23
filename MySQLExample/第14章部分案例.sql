SELECT * FROM fivechapter.books INTO OUTFILE "F:\\MySQL\\bktestdir\\books_out.txt"
FIELDS
TERMINATED BY ','
ENCLOSED BY '\"'
LINES
STARTING BY '<'
TERMINATED BY '>\r\n';

-- 使用LOAD DATA INFILE语句导入数据到表中
LOAD DATA INFILE 'F:\\MySQL\\bktestdir\\test_out.txt' INTO TABLE fivechapter.dept
FIELDS
TERMINATED BY ','
ENCLOSED BY '<'
LINES
STARTING BY '<'
TERMINATED BY '>\r\n';

mysql -u root -p --html --execute="SELECT * FROM dept;" fivechapter>F:\MySQL\bktestdir\books_html.html




