#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
	Q_OBJECT
private:
	Ui::MainDialog *ui;
	QString command;
	int readValue(const QString &path);
	void setBacklight(bool on);
	void setBrightness(int value);
public:
	explicit MainDialog(QWidget *parent = 0);
	~MainDialog();

private slots:
	void on_horizontalSlider_valueChanged(int value);
	void on_spinBox_valueChanged(int arg1);
	void on_checkBox_clicked(bool checked);
};

#endif // MAINDIALOG_H
