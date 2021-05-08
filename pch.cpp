// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
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
        m_bstrConn = "Provider=SQLOLEDB.1;Password=ZOUzzh93419YR+;Persist Security Info=True;User ID=sa;Initial Catalog=SMSS;Data Source=独霸青楼";

        hr = m_pConnection->Open(m_bstrConn, "sa", "ZOUzzh93419YR+", adModeUnknown);
        if (!SUCCEEDED(hr)) {
            AfxMessageBox(_T("连接数据库失败"));
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