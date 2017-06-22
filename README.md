[![Project Status: WIP – Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.](http://www.repostatus.org/badges/latest/wip.svg)](http://www.repostatus.org/#wip)

# 概述

在电信的业务中，有一种Unix实验室出租业务。只要用户向电信运营商申请一个Unix帐号，就可以远程登录Unix实验室，并使用Unix系统。

用户使用电信运营商提供的Unix实验室的服务需要缴纳一定的费用，电信运营商需要一套数据采集系统，把用户登录实验室的时间长度数据采集起来，便于在指定的时间范围内作为对用户的收费依据。

要求数据采集系统必须采集如下信息：登录用户名，登录的时间，登出的时间，登录总的在线时间，登录的实验室IP，用户的终端IP等信息。

DMS3.0项目需要开发这样一个通用的数据采集系统程序，来采集Unix机器记录的用户登入和登出的原始记录，并将这些记录解析匹配成用户的登录记录，然后发送给数据采集服务器，在服务器端将这些数据以日期为单位保存在数据库中，然后整合这些数据形成日报表，月报表和年报表。

本仓库为DMS系统的**服务器端程序**。

# 核心功能

DMS3.0系统主要实现以下核心功能：数据读取，数据匹配，数据发送，数据接收，数据存储，数据整合。服务器端程序主要负责：数据接收，数据存储，数据整合。

## 数据接收

该模块的主要任务是建立服务器端网络连接，从客户端读取匹配好的用户登录记录字符串。

## 数据存储

该模块的主要任务是将数据接收模块接收到的数据保存到指定的数据库表中。

## 数据整合

整合这些数据形成日报表，月报表和年报表。

# 开发

## 开发环境

IDE: Qt Creator 3.0.1
编译器: GCC 4.8.2, 64bit
操作系统：Ubuntu 14.04 LTS
数据库：oracle10g

或者

IDE: Qt Creator 1.3.1
编译器: gcc (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3
操作系统：Ubuntu 10.04 LTS
数据库：oracle10g

## .pc文件的编译

使用下面的命令编译生成cpp文件即可：

```
proc proc/oracle_dao.pc header/oracle_dao.h oname=src/oracle_dao.cpp parse=none code=cpp
```

# 运行

## 数据库创建表格

运行下列sql语句即可创建该程序所需要的表：

```
create table matched_record(log_id VARCHAR2(32) Primary key, log_name VARCHAR2(32), pid number, login_time number, logout_time number, duration number, log_ip VARCHAR2(32));
```
