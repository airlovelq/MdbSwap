#include "stdafx.h"
#include "mdbswap.h"
#include <QtWidgets/QApplication>
#ifdef WIN64STATIC
#pragma comment(lib,"qwindowsd.lib")
#pragma comment(lib,"qsqlodbcd.lib")
Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin);
Q_IMPORT_PLUGIN (/*sqlodbc*/QODBCDriverPlugin);
#endif
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MdbSwap w;
	w.show();
	return a.exec();
}
