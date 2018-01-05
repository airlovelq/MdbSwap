#include "stdafx.h"
#include "SwapOp.h"

/*
    CSwapOp�࿪ʼ
*/
CSwapOp::CSwapOp(void)
{
}


CSwapOp::~CSwapOp(void)
{
}

void CSwapOp::SetMdb(QString mdbfilename)
{
	//����mdb���ݿ������
	m_mdb = QSqlDatabase::addDatabase("QODBC","SWPBASE");
	QString strDbName;
#ifdef WIN64STATIC
	strDbName = "DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=";
#else   //32λ
	strDbName = "DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=";
#endif
	strDbName = strDbName+mdbfilename;
    m_mdb.setDatabaseName(strDbName);
	
}
/*
    CSwapOp�����
*/


/*
    CSqliteSwapOp�࿪ʼ
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

	//����Ҫת�������ݿ������
	m_swapdb = QSqlDatabase::addDatabase("QSQLITE","SWPTO");
    m_swapdb.setDatabaseName(SwapDbfilename);
}

int CSqliteSwapOp::DoSwap()
{
	bool b = m_mdb.open()&&m_swapdb.open();
    if(b)
	{
        //�����ݿ��еı�
        QStringList tables = m_mdb.tables();
        //�����м�¼
        for (int i = 0; i < tables.size(); ++i)
		{
            QString tabName = tables.at(i);
            QString sqlString = "select * from " + tabName;
            QSqlQuery q(m_mdb);
			q.exec(sqlString);

			q.next();             //������һ����¼
            QSqlRecord rec = q.record();
            int fieldCount = rec.count();
            QString fieldName;
			//QStringList fieldNameList;

			//���ȶԻ���
			//int o = q.numRowsAffected();
			QProgressDialog pd("����","ȡ��",0,2);
            pd.setWindowTitle(QString("ת����")+tabName);    //���ñ���
            pd.setWindowModality(Qt::WindowModal);           //ģ̬�Ի���
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
				//Ŀǰ��ֻ֧�����ͣ����㣬�ַ�������
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
					value.replace("'","''");               //���ܴ���',���滻��''
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
					//Ŀǰ��ֻ֧�����ͣ����㣬�ַ�������
					switch (variant.type())
				    {
				    case QVariant::Int:
					    sqlInsert += value;
					    sqlInsert += QString(",");
					    break;
				    case QVariant::Type::String:
					    sqlInsert += QString("'");
						value.replace("'","''");               //���ܴ���',���滻��''
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
				if ( count % SQLITELIMIT == 0 )                           //��Ŀ�������ޣ���ﵽ�̶�����������һ��insert
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
		
		//�ر����ݿⲢ�Ͽ�
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
    CSqliteSwapOp�����
*/