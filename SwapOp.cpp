#include "stdafx.h"
#include "SwapOp.h"

/*
    CSwapOp类开始
*/
CSwapOp::CSwapOp(void)
{
}


CSwapOp::~CSwapOp(void)
{
}

void CSwapOp::SetMdb(QString mdbfilename)
{
	//设置mdb数据库类对象
	m_mdb = QSqlDatabase::addDatabase("QODBC","SWPBASE");
	QString strDbName;
#ifdef WIN64STATIC
	strDbName = "DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=";
#else   //32位
	strDbName = "DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=";
#endif
	strDbName = strDbName+mdbfilename;
    m_mdb.setDatabaseName(strDbName);
	
}
/*
    CSwapOp类结束
*/


/*
    CSqliteSwapOp类开始
*/
CSqliteSwapOp::CSqliteSwapOp()
{

}

CSqliteSwapOp::~CSqliteSwapOp()
{

}

void CSqliteSwapOp::SetSwapDb( QString SwapDbfilename )
{
	
	QFile f;
	f.setFileName(SwapDbfilename);
	if ( !f.open(QFile::ReadWrite | QFile::Truncate))
	{
		return;
	}
	f.close();
	QStringList lst = QSqlDatabase::drivers();

	//设置要转换的数据库类对象
	m_swapdb = QSqlDatabase::addDatabase("QSQLITE","SWPTO");
    m_swapdb.setDatabaseName(SwapDbfilename);
}

int CSqliteSwapOp::DoSwap()
{
	bool b = m_mdb.open()&&m_swapdb.open();
    if(b)
	{
        //读数据库中的表
        QStringList tables = m_mdb.tables();
        //读表中记录
        for (int i = 0; i < tables.size(); ++i)
		{
            QString tabName = tables.at(i);
            QString sqlString = "select * from " + tabName;
            QSqlQuery q(m_mdb);
			q.exec(sqlString);

			q.next();             //移至第一条记录
            QSqlRecord rec = q.record();
            int fieldCount = rec.count();
            QString fieldName;
			//QStringList fieldNameList;

			//进度对话框
			//int o = q.numRowsAffected();
			QProgressDialog pd("进度","取消",0,2);
            pd.setWindowTitle(QString("转换表")+tabName);    //设置标题
            pd.setWindowModality(Qt::WindowModal);           //模态对话框
            pd.show();
			

			QString sqlCreateTbl("CREATE TABLE ");
			sqlCreateTbl += QString("D");
			sqlCreateTbl += tabName;
			sqlCreateTbl += QString("(");

			QString sqlInsert("INSERT INTO ");
			sqlInsert += QString("D");
			sqlInsert += tabName;
			//sqlInsert += QString(" VALUES(");
			sqlInsert += QString(" SELECT ");
            for(int j=0;j<fieldCount;j++)
			{
				//QSqlField dd = rec.field(rec.fieldName(j));
				//QVariant ddddd = dd.type();
                fieldName = rec.fieldName(j);
				//fieldNameList.append(fieldName);
				QVariant variant = rec.value(j);
				QString value = rec.value(j).toString();

				sqlCreateTbl += fieldName;
				//目前先只支持整型，浮点，字符串三种
				switch (variant.type())
				{
				case QVariant::Int:
					sqlCreateTbl += QString(" int,");
					sqlInsert += value;
					sqlInsert += QString(",");
					break;
				case QVariant::Type::String:
					sqlCreateTbl += QString(" ntext,");
					sqlInsert += QString("'");
					value.replace("'","''");               //可能存在',需替换成''
					sqlInsert += value;
					sqlInsert += QString("'");
					sqlInsert += QString(",");
					break;
				case QVariant::Type::Double:
					sqlCreateTbl += QString(" float,");
					sqlInsert += value;
					sqlInsert += QString(",");
					break;
				default:
					break;
				}	
				pd.setValue(1);
				QCoreApplication::processEvents();
            }
			sqlCreateTbl = sqlCreateTbl.left(sqlCreateTbl.length()-1);
			sqlCreateTbl += QString(")");
			sqlInsert = sqlInsert.left(sqlInsert.length()-1);
			//sqlInsert += QString(")");
			sqlInsert += QString(" UNION ALL");
			QSqlQuery q2(m_swapdb);
			q2.exec(sqlCreateTbl);
			//q2.exec(sqlInsert);

			int count = 1;
			while ( q.next() )
			{
				rec = q.record();
				//sqlInsert = ("INSERT INTO ");
			    //sqlInsert += QString("D");
			    //sqlInsert += tabName;
			    //sqlInsert += QString(" VALUES(");
				sqlInsert += QString(" SELECT ");
				for(int j=0;j<fieldCount;j++)
			    {
				    QVariant variant = rec.value(j);
				    QString value = rec.value(j).toString();
					//目前先只支持整型，浮点，字符串三种
					switch (variant.type())
				    {
				    case QVariant::Int:
					    sqlInsert += value;
					    sqlInsert += QString(",");
					    break;
				    case QVariant::Type::String:
					    sqlInsert += QString("'");
						value.replace("'","''");               //可能存在',需替换成''
					    sqlInsert += value;
					    sqlInsert += QString("'");
					    sqlInsert += QString(",");
					    break;
				    case QVariant::Type::Double:
					    sqlInsert += value;
					    sqlInsert += QString(",");
					    break;
				    default:
					    break;
				    }				
				}
				sqlInsert = sqlInsert.left(sqlInsert.length()-1);
			    //sqlInsert += QString(")");
				sqlInsert += QString(" UNION ALL");
				//q2.exec(sqlInsert);
				count++;
				if ( count % SQLITELIMIT == 0 )                           //条目超过上限，则达到固定数量后推送一次insert
				{
					sqlInsert = sqlInsert.left(sqlInsert.length()-10);
			        q2.exec(sqlInsert);
					sqlInsert = ("INSERT INTO ");
			        sqlInsert += QString("D");
			        sqlInsert += tabName;
				}
				
				//pd.setValue(count);
			}
			sqlInsert = sqlInsert.left(sqlInsert.length()-10);
			bool ddd = q2.exec(sqlInsert);
			pd.setValue(2);
		}
		
		//关闭数据库并断开
		m_mdb.close();
		m_swapdb.close();
		QString cnnName = m_mdb.connectionName();
		QSqlDatabase::removeDatabase(cnnName);
		cnnName = m_swapdb.connectionName();
		QSqlDatabase::removeDatabase(cnnName);
		//QSqlDatabase::removeDatabase(m_mdb.connectionName());
		return 1;
	}
	return 0;
}
/*
    CSqliteSwapOp类结束
*/