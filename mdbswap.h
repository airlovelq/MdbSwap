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
//  brief 	:  MdbSwap��������
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
	enum DbType          //ת�����ݿ�����ö�٣���ֻ֧��Sqlite
	{
		SQLITE
	};
private:
	Ui::MdbSwapClass ui;
	CSwapOp *m_op;       //ת��������

protected:
	QString m_mdbfilename;    //Ҫת�������ݿ��ļ�·��
	QString m_OpenPath;       //ǰһ�δ򿪵�·��
	void ReadFile();          //��ȡҪת�������ݿ⣬��ʾ�ڴ���table��

public slots:
	void OnSwap();            //ת��
	void OnSelectFile();      //ѡ�����ݿ��ļ�
};

#endif // MDBSWAP_H
