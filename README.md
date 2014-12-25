GreenLeaf（绿叶）分布式通用型服务器端开发框架
===================================

一、引言
-----------------------------------
GreenLeaf的理念是让服务器的开发变得简单，成为服务端程序的绿叶；并且重视性能和可伸缩性，使用GreenLeaf开发出来的即时通讯服务端天生具有很强的伸缩性，扩展也很容易。我们在性能优化上也花了很多功夫，并且会持续进行，经过测试，登录可以到单台30万。

二、软件总体设计
-----------------------------------

###2.1 软件需求概括
GreenLeaf最适合的应用领域是即时通讯的服务端。当然还不仅仅是即时通讯，还可以作为任何服务器的底层通讯框架，由于之前已经考虑到业务的热更新，可以采用Python进行混合编程来实现我们所要的功能，值得一说的是GreenLeaf可以完美跨平台。

###2.2 软件整理流程图设计和描述
![image](https://github.com/GreenLeaf/raw/master/Doc/GreenLeaf_SoftwareArchitectureFigure.png) 
软件整体架构（图1）
![image](https://github.com/GreenLeaf/raw/master/Doc/GreenLeaf_SingleRegionArchitectureFigure.png)
单地域服务器架构（图2）
![image](https://github.com/GreenLeaf/raw/master/Doc/GreenLeaf_CrossDomainArchitectureFigure.png)
跨地域服务器架构（图3）

三、软件功能描述
-----------------------------------

###3.1 GreenLeaf的框架组成
GreenLeaf 是基于C++/Python开发的高性能、分布式通用型服务器框架。

包括三部分:
	框架, GreenLeaf的核心, 与以往单进程的框架不同, 它是高性能的通用型服务器框架，并且使用很简单
	库, 包括了开发的常用工具库， 如连接管理、连接池等
	工具包, 包括日志打印、UUID等

###3.2 GreenLeaf特性
> 快速、易上手的开发模型和api
> 高可伸缩的多进程架构， 可以采用Python混合编程
> 方便的服务器扩展机制，可快速扩展服务器类型和数量
> 方便的请求、响应、广播、服务器通讯机制， 无需任何配置
> 注重性能，在性能、可伸缩性上做了大量的测试、优化
> 提供了完整的demo代码，可以作为很好的开发参考
> 基于boost.asio开发，支持boost.asio支持的多种操作系统

###3.3 为什么使用GreenLeaf
高并发、高实时的即时通讯服务器的开发是很复杂的工作。跟web应用一样， 一个好的开源容器或开发框架可以大大减少开发的复杂性，让开发变得更加容易。
遗憾的是目前在即时通讯服务器开发领域一直没有太好的开源解决方案。 GreenLeaf将填补这个空白， 打造一款完全开源的高性能（并发）通用型服务器框架。
GreenLeaf的优势有以下几点：
* 1．架构的可伸缩性好。 采用多进程多线程的运行架构，扩展服务器非常方便， boost的asio优势提供了高可伸缩性。
* 2．提供完整的开源消息服务器demo参考。 一个超过5千行代码的demo，使开发者可以随时借鉴demo的设计与开发思路。

四、软件使用说明
-----------------------------------
GreenLeaf框架主要有四个模块：GLUtils、GLDiskIO、GLDBIO、GLNetIO。
使用者只需要包含相应的.h文件和调用.dll或.so即可使用相应的功能。

###GLUtils
GLUtils是框架的底层工具库，部分接口如下：

    void setThreadNumber(const std::size_t& num);
    const std::size_t threadNumber() const;
    boost::asio::io_service& ioService() const;

    void run() const;
    void stop() const;

    const std::string randUuidToString() const;
    const std::string randUuidToStringWithBraces() const;

    const std::string localDatatimeF() const;
    const std::string localDatatimeT() const;
    const std::string localDatatimeFT() const;
    const std::string localDatatimeFTZ() const;

    const std::string& currentPath() const;
    const bool createPaths(const std::string& path) const;
    const std::vector<std::string> splitString(const std::string& src,
            const std::string token);

    void initLogger(const LoggerLevel& lev, std::ostream* out) const;
    template<class A1>
    void wirteLog(const LoggerLevel& lev, A1 a1) {
        Logger::instance().log(lev, a1);
    }

* setTheardNumber()：设置工作线程的数量，默认根据当前计算机的CPU数量来计算出最好的数量；
* run()：启动服务端程序；
* stop()：停止服务端程序；
* randUuidToString()：获取uuid的字符串；
* localDataTimeF()：获取本地的时间和日期，如：2014-12-12；
* localDataTimeFT()：获取本地的时间和日期，如：2014-12-12 12:00:00；
* localDatatimeFTZ()： 获取本地的时间和日期，如：2014-12-12 12:00:00 CST；
* currentPath()：获取当前运行程序的路径；
* wirteLog()：打印日志；

###GLDiskIO
GLDiskIO是框架的本地数据解析库，部分接口如下：

    const bool loadIniFile(const std::string& inputFile);
    void saveIniFile(const char* outputFile);
    template<typename Type>
    Type iniData(const Properties::path_type& path, const Type& defaultValue =
            Type()) {
        return IniParse::instance().get(path, defaultValue);
    }
    template<typename Type>
    void setIniData(const Properties::path_type& path, const Type& newValue) {
        return IniParse::instance().set(path, newValue);
    }

    const bool loadXmlFile(const std::string& inputFile);
    void saveXmlFile(const char* outputFile);
    template<typename Type>
    Type xmlData(const Properties::path_type& path, const Type& defaultValue =
            Type()) {
        return XmlParse::instance().get(path, defaultValue);
    }
    template<typename Type>
    void setXmlData(const Properties::path_type& path, const Type& newValue) {
        return XmlParse::instance().set(path, newValue);
    }

    const bool loadJsonFile(const std::string& inputFile);
    void saveJsonFile(const char* outputFile);
    template<typename Type>
    Type jsonData(const Properties::path_type& path, const Type& defaultValue =
            Type()) {
        return JsonParse::instance().get(path, defaultValue);
    }
    template<typename Type>
    void setJsonData(const Properties::path_type& path, const Type& newValue) {
        return JsonParse::instance().set(path, newValue);
    }

* loadIni()：载入ini文件数据；
* saveIni()：保持数据到ini文件；
* iniData()：获取ini文件里的具体数据；
* setIniData()：设置ini文件里的具体数据；
* loadXml()：载入xml文件数据；
* saveXml ()：保持数据到xml文件；
* xmlData()：获取xml文件里的具体数据；
* setXmlData()：设置xml文件里的具体数据；
* loadJson()：载入json文件数据；
* saveJson ()：保持数据到json文件；
* jsonData()：获取json文件里的具体数据；
* setJsonData()：设置json文件里的具体数据；

###GLDBIO
GLDBIO是框架的数据库操作库，部分接口如下：

    const bool initMySqlConnectionPool(const std::string& serverAddr,
            const std::string& username,
            const std::string& passwd,
            const std::string& dbname,
            const std::size_t& maxSize);

    const std::vector<std::string> selectData(DatabaseType type, std::string& query);
    const bool insertData(DatabaseType type, const std::string& query);
    const bool deleteData(DatabaseType type, const std::string& query);
    const bool updateData(DatabaseType type, const std::string& query);
    const bool exec(DatabaseType type, const std::string& query);

* initMySqlConnectionPool()：初始化mysql连接池；
* selectData()：查询MySQL数据；
* insertData()：插入MySQL数据；
* deleteData()：删除MySQL数据；
* updateData()：更新MySQL数据；
* exec()：发送SQL语句；

###GLNetIO
GLNetIO是框架的网络通信库，部分接口如下：

    void tcpAcceptor(const unsigned short& port,
            boost::function<void(boost::shared_ptr<TcpConnection>)> operation =
                    boost::function<void(boost::shared_ptr<TcpConnection>)>());
    TcpConnectionPtr connection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType);
    void addConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType,
            const TcpConnectionPtr conn);
    void removeConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType);
    void modifyConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType,
            const TcpConnectionPtr conn);
    const std::string connectionNumber();
    const std::string singalUserConnectionNumber(const std::string& userID);

* tcpAcceptor()：监听指定端口；
* connection()：获取指定连接；
* addConnection()：添加连接；
* removeConnection()：删除连接；
* modifyConnection()：更改连接；
* connectionNumber()：获取总连接数；
* singalUserConnectionNumber()：获取指定用户所拥有的连接数；



