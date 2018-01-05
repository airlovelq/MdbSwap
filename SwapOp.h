#pragma once
// ***************************************************************
//  CSwapOp   Version:  1.0 
//  -------------------------------------------------------------------------------------------
//  author:  LQ
//  date 	:  2018-01-05
//  brief 	:  CSwapOp数据库转换操作抽象基类
//  		
//  -------------------------------------------------------------------------------------------
// ***************************************************************
// ***************************************************************
class CSwapOp
{
public:
	virtual ~CSwapOp(void);

	void SetMdb(QString mdbfilename);                       //设置要转换的数据库
	virtual void SetSwapDb(QString SwapDbfilename) = 0;     //设置转换后的目标数据库
	virtual int DoSwap() = 0;                               //进行转换
protected:
	CSwapOp(void);        //抽象基类，不允许直接新建基类对象
	
protected:
	QSqlDatabase m_mdb;
	QSqlDatabase m_swapdb;
};


// ***************************************************************
//  CSqliteSwapOp   Version:  1.0 
//  -------------------------------------------------------------------------------------------
//  author:  LQ
//  date 	:  2018-01-05
//  brief 	:  CSqliteSwapOp数据库转换操作类，转换成Sqlite数据库
//  		
//  -------------------------------------------------------------------------------------------
// ***************************************************************
// ***************************************************************
class CSqliteSwapOp : public CSwapOp
{
public:
	CSqliteSwapOp();
	~CSqliteSwapOp();
public:
	virtual void SetSwapDb( QString SwapDbfilename );
	virtual int DoSwap();
};

