#ifndef MDBSWAP_H
#define MDBSWAP_H

#include <QtWidgets/QMainWindow>
#include "ui_mdbswap.h"
#include "SwapOp.h"
// ***************************************************************
//  MdbSwap   Version:  1.0 
//  -------------------------------------------------------------------------------------------
//  author:  LQ
//  date 	:  2018-01-05
//  brief 	:  MdbSwap主窗口类
//  		
//  -------------------------------------------------------------------------------------------
// ***************************************************************
// ***************************************************************
class MdbSwap : public QMainWindow
{
	Q_OBJECT

public:
	MdbSwap(QWidget *parent = 0);
	~MdbSwap();
public:
	enum DbType          //转换数据库类型枚举，暂只支持Sqlite
	{
		SQLITE
	};
private:
	Ui::MdbSwapClass ui;
	CSwapOp *m_op;       //转换操作类

protected:
	QString m_mdbfilename;    //要转换的数据库文件路径
	QString m_OpenPath;       //前一次打开的路径
	void ReadFile();          //读取要转换的数据库，显示于窗口table中

public slots:
	void OnSwap();            //转换
	void OnSelectFile();      //选择数据库文件
};

#endif // MDBSWAP_H
