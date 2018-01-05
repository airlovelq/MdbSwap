#include "stdafx.h"
#include "mdbswap.h"

MdbSwap::MdbSwap(QWidget *parent)
	: QMainWindow(parent)
{
	m_op = NULL;
	ui.setupUi(this);
	connect(ui.BtnSel,SIGNAL(clicked()), this, SLOT(OnSelectFile()));
	connect(ui.BtnToSqlite,SIGNAL(clicked()), this, SLOT(OnSwap()));

	ui.comboType->addItem("SQLITE");
}

MdbSwap::~MdbSwap()
{
	if ( m_op )
	{
		delete m_op;
		m_op = NULL;
	}
}

void MdbSwap::OnSwap()
{
	if ( m_op )
	{
		delete m_op;
		m_op = NULL;
	}
	switch (ui.comboType->currentIndex())
	{
	case SQLITE:
	    m_op = new CSqliteSwapOp();
		break;
	default:
		break;
	}
	m_op->SetMdb(m_mdbfilename);
	QString strSwapFileName = m_mdbfilename.left(m_mdbfilename.indexOf("."))+QString(".db");
	m_op->SetSwapDb(strSwapFileName);
	m_op->DoSwap();
}

void MdbSwap::OnSelectFile()
{
	QString filetype;
	m_mdbfilename = QFileDialog::getOpenFileName(this,"请选择文件",m_OpenPath,"数据库文件(*.mdb)",&filetype);
	
	if ( !m_mdbfilename.isNull() )
	{
		m_OpenPath.clear();
		QStringList strlist = m_mdbfilename.split(QString("/"));
		for ( int i=0 ; i<strlist.size()-1 ; i++ )
		{
			m_OpenPath = m_OpenPath + strlist.at(i) + QString("/");
		}
	}
	ReadFile();
}

void MdbSwap::ReadFile()
{
	/*
	QStringList drivers = QSqlDatabase::drivers();
	for ( int k=0 ; k<drivers.length() ; k++ )
	{
		QString driver = drivers.at(k);
		driver;
	}
	*/

	QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC","PRE");
	QString str1;
#ifdef WIN64STATIC
	str1 = "DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=";
#else
	str1 = "DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=";
#endif
	str1 = str1+m_mdbfilename;
    m_db.setDatabaseName(str1);

	QSqlRecord record;
    bool b = m_db.open();
    if(b)
	{//success
		ui.labelDbName->setText(QString(tr("当前数据库："))+m_mdbfilename);

		ui.tab->clear();
        //读数据库中的表
        QStringList tables;
        QString tabName,sqlString;
		tables = m_db.tables();
		//ui.tabWidget->set
        //读表中记录
        for (int i = 0; i < tables.size(); ++i)
		{
            tabName = tables.at(i);
			QWidget *tabWidget = new QWidget();
			
			tabWidget->setGeometry(ui.tab->geometry().x(),ui.tab->geometry().y(),ui.tab->geometry().width()-5,ui.tab->geometry().height()-25);
			QTableWidget *tableWidget = new QTableWidget(tabWidget);
			//tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
			QVBoxLayout *vLay = new QVBoxLayout(tabWidget);
			vLay->addWidget(tableWidget);
			tableWidget->setGeometry(tabWidget->geometry().x(),tabWidget->geometry().y(),tabWidget->geometry().width(),tabWidget->geometry().height());
			//tableWidget->horizontalScrollBar()->setEnabled(true);
			//tableWidget->verticalScrollBar()->setEnabled(true);
			//tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
			//tableWidget->setHorizontalScrollBar( new QScrollBar() );
			ui.tab->addTab(tabWidget,tabName);
			//ui.tabWidget->setCurrentIndex(i);
			//QWidget *tabWidget = ui.tabWidget->currentWidget();
			//ui.tabWidget->setTabText(i,tabName);
			//ui.tabWidget->setcu
            sqlString = "select * from " + tabName;
            QSqlQuery q(sqlString,m_db);
			
            //QSqlQuery q("select * from product");
		
            QSqlRecord rec = q.record();
            int fieldCount = rec.count();
			//int recordCount = q.numRowsAffected();
            tableWidget->setColumnCount(fieldCount);
			//tableWidget->setRowCount(q.size());
			int nRow = 0;
			tableWidget->setRowCount(nRow);
            QString fieldName;
			QStringList fieldNameList;
            for(int j=0;j<fieldCount;j++)
			{
				QSqlField dd = rec.field(rec.fieldName(j));
				QVariant ddddd = dd.type();
                fieldName = rec.fieldName(j);
				fieldNameList.append(fieldName);
				QVariant variant = rec.value(j);
				QString value = rec.value(j).toString();
				tableWidget->setItem(0,j,new QTableWidgetItem(value));
				
            }
			while ( q.next() )
			{
				nRow++;
				tableWidget->setRowCount(nRow);
				rec = q.record();
				for(int j=0;j<fieldCount;j++)
			    {
				    QVariant variant = rec.value(j);
				    QString value = rec.value(j).toString();
				    tableWidget->setItem(nRow-1,j,new QTableWidgetItem(value));
				}
			}
			tableWidget->setHorizontalHeaderLabels(fieldNameList);
			//滚动区域
            //QScrollArea *s = new QScrollArea(this);
			//s->setGeometry(tabWidget->geometry());
			//s->setWidget(tableWidget);
		}
		try
		{
		    m_db.close();
		    QString cnnName = m_db.connectionName();
		    QSqlDatabase::removeDatabase(cnnName);
		}
		catch(...)
		{

		}
	}
       
}
