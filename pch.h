// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H
#import "C://Program Files//Common Files//System//ado//msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")

class AdoSql
{
public:
    AdoSql();
    virtual ~AdoSql();

    void InitialConn();  //连接数据库
    void ExitConn();     //断开数据库
    void GetRecordSet(CString bstrSqlCmd);  //获得记录集
    void ExcuteCmd(CString bstrSqlCmd);     //执行sql语句

public:
    _bstr_t m_bstrConn;  //存储连接数据库的字符串
    _bstr_t m_sqlCmd;    //存储sql语句
    _ConnectionPtr m_pConnection;  //连接数据库对象指针
    _RecordsetPtr  m_pRecordSet;   //数据集对象指针
};
