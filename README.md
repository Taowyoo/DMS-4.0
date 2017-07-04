#DMS4.0#
##Project Background：##
DMS4.0：Data Mining System 4.0.
In the telecom business, there is a Unix lab(server) rental business. As long as the user apply for a Unix account from the telecom operators, one can remotely log Unix  laboratory(server) and use Unix systems. Users need to pay certain fee for the  Unix labor services provided by telecom operators therefore telecom operators need a set of data mining system to collect time-length data of user login information in the laboratory as the basis of the charges.

##project implementation：##
For the project, we require its data mining system must collect  the following information: login user name, login time, logout time, login total online time, login lab IP, user's Terminal IP and other information from the Unix system log file "/var/adm/wtmpx" .

So DMS project needs to develop such a common data mining system program to collect the Unix machine records, the user's original records of login and logout, and parse these records into matched user login records, and then sent to the data collection server. Finally the server keep these data in the database in date and integrate the data to formed daily reports, monthly reports or annual reports.

##项目背景：##
DMS4.0即：通用数据挖掘系统 4.0。
在电信的业务中，有一种Unix实验室出租业务。只要用户向电信运营商申请一个Unix帐号，就可以远程登录Unix实验室，并使用Unix系统。用户使用电信运营商提供的Unix实验室的服务需要缴纳一定的费用，电信运营商需要一套数据采集系统，把用户登录实验室的时间长度数据采集起来，便于在指定的时间范围内作为对用户的收费依据。

##项目实现：##
对于项目要求其数据采集系统必须从Unix系统日志文件/var/adm/wtmpx采集如下信息：登录用户名，登录的时间，登出的时间，登录总的在线时间，登录的实验室IP，用户的终端IP等信息。

DMS项目需要开发这样一个通用的数据采集系统程序，来采集Unix机器记录的用户登入和登出的原始记录，并将这些记录解析匹配成用户的登录记录，然后发送给数据采集服务器，在服务器端将这些数据以日期为单位保存在数据库中，然后整合这些数据形成日报表，月报表和年报表。