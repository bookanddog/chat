之前做的一个尝试。学一学网络编程。
程序是windows下的qt编写，运行时对数据库的访问需要加上几个库文件。
//**************************************************************
//**使用的数据库驱动程序,连接数据库注意集中几种情况：
//** 1，主要是版本问题，32位qt对于32位postgresql；
//** 2，.pro中加入包含和依赖目录;
//** 3,libeay32.dll,libpq.dll,ssleay32.dll,libintl.dll这几个文件放在编译好的exe或者可执行文件相同目录下
//*******************************************************************

初期想的太简单就直接边学边写，于是也导致目标与设计的不足。
利用qt写了图形界面，出于当初对能做出图形界面而不是一个黑框的崇拜与无知，对于后台实现也使用了简单图形界面。后悔莫及。

前台主要是对图形界面的相应与细节的把控，也没有做得很好，只是实现了对好友抽屉功能的比较好的相应，其他比较简单的功能实现也比较简单。

后台数据库使用了postgresql。发现数据库确实是一个值得研究的大问题。没有经验的情况下网上搜索实现方案，也不知道最终效率怎么样。对于好友之间多对多的关系该怎么设计没有好的想法，于是采用了一张大表存储，据传企业也是这样设计。对于高深的数据库理论没有多做使用，最多只是使用了索引内外键等。

对于多用户（客户端）连接，最初参考了网上的每次有接入便开辟一个新线程的处理方案，以免阻塞。单机开了几个客户端感觉还可以，沾沾自喜了一段时间。后来又才了解到epoll模型等高性能io模型，又听闻libevent等库，心向往之，准备重新实现的时候由于学校事务等至今没有重新启动。

对于网络通信，在局域网内畅通无阻，并且通信使用的是服务器中专的方式，想必在广域网也能成功。后来看到有关于tcp/udp穿透的技术，实现不难，但是准备加入的时候同上理由搁置。

总的来说学到了不少东西，但是长时间不用，其实也忘的差不多了。发现编程确实不是很难，主要是经验积累，查找文档还是能找到解决方法，难的是设计与规划。qt确实很不错，精致完备的本地文档帮助很大，信号与槽的机制确实好用。
