 create table "user"
 (
 count text primary key,
 pwd text not null,
 nickname text not null, --以后加密，不能是明文
 qq text,
 email text,
 phone text,
 ip text,
 port text,
 sex smallint default ((0)), --0,1,2,未知，男，女
 birthday date,
 state smallint default ((0)),  --0,1,2,断线重连，下线，在线
 registertime date not null,
 motto text
 );