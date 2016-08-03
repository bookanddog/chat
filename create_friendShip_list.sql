 create table "friendShip"
 (
 ucount text not null,
 fcount text not null,
 primary key(ucount, fcount),
 fgroup text not null default 'friends', --分组，默认在好友里面
 nowfriend boolean , --true/false,好友/等待添加,或者分出去另起一个表
 foreign key (ucount) references "user"(count),
 foreign key (fcount) references "user"(count)
 );
 create index uid on "friendShip"(ucount); --查找好友索引
 create index ugroup on "friendShip"(ucount, fgroup); --分组索引,联合索引