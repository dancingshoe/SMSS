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
AdoSql::AdoSql()
{
    m_pConnection = NULL;
    m_pRecordSet = NULL;
    InitialConn();
}

AdoSql::~AdoSql()
{

}

void AdoSql::InitialConn()
{
    //初始化COM组件
    ::CoInitialize(NULL);
    HRESULT hr = NULL;

    try
    {
        hr = m_pConnection.CreateInstance("ADODB.Connection");  //创建Connection对象
        //hr = m_pConnection.CreateInstance(__uuidof(Connection));作用同上

        //1、新建一个文件，名字任意取，后缀名必须为udl（如何hello.udl）
        //2、双击hello.udl文件，进入数据连接属性面板，填写好数据源（选择自己创建的数据源名字的）
        //3、再以记事本方式打开，第三行的数据就是连接字符

        //m_bstrConn = "Provider=SQLNCLI10.1;Integrated Security="";Persist Security Info=False;User ID=sa;Password=123456;Initial Catalog=WORK;Data Source="";Initial File Name="";Server SPN=""";
        m_bstrConn = "Provider=SQLNCLI10.1;Integrated Security="";Persist Security Info=False;Initial Catalog=WORK;Data Source="";Initial File Name="";Server SPN=""";

        hr = m_pConnection->Open(m_bstrConn, "sa", "ZOUzzh93419YR+", adModeUnknown);
        if (!SUCCEEDED(hr)) {
            AfxMessageBox(TEXT("连接数据库失败"));
        }
    }
    catch (_com_error e)
    {
        CString strErr;
        strErr.Format(_T("连接数据库失败\n%s"), e.ErrorMessage());
        AfxMessageBox(strErr);
    }
}

void AdoSql::GetRecordSet(CString bstrSqlCmd)
{
    m_sqlCmd = _bstr_t(bstrSqlCmd);
    //创建记录集指针对象实例
    m_pRecordSet.CreateInstance(__uuidof(Recordset));
    //打开记录集
    m_pRecordSet->Open(m_sqlCmd, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
}

void AdoSql::ExcuteCmd(CString bstrSqlCmd)
{
    m_sqlCmd = _bstr_t(bstrSqlCmd);
    _variant_t RecordsAffected;

    try {
        m_pRecordSet = m_pConnection->Execute(m_sqlCmd, &RecordsAffected, adCmdText);
    }
    catch (_com_error e) {
        AfxMessageBox(e.ErrorMessage());
    }
}

void AdoSql::ExitConn()
{
    //关闭记录集和连接
    if (m_pRecordSet != NULL)
    {
        m_pRecordSet->Close();
    }
    m_pConnection->Close();
    ::CoUninitialize();
}


