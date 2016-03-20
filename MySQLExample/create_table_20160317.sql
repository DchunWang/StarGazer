CREATE TABLE orders
(
o_num   INT(11) PRIMARY KEY NOT NULL UNIQUE AUTO_INCREMENT,
o_date  DATE,
o_id    INT(11),
CONSTRAINT orders_fk FOREIGN KEY(o_id) REFERENCES customers_info(c_num)
);