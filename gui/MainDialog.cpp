#include "MainDialog.h"
#include "ui_MainDialog.h"

#include <QFile>
#include <QProcess>

MainDialog::MainDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MainDialog)
{
	ui->setupUi(this);
	setFixedSize(500, height());

	command = "/usr/local/bin/backlight";

	setBacklight(true); // force on

	int power = readValue("/sys/class/backlight/rpi_backlight/bl_power");
	int brightness = readValue("/sys/class/backlight/rpi_backlight/brightness");

	if (brightness < 50) brightness = 50;

	ui->checkBox->setChecked(power == 0);
	ui->horizontalSlider->setValue(brightness);
	ui->spinBox->setValue(brightness);
}

MainDialog::~MainDialog()
{
	delete ui;
}

int MainDialog::readValue(QString const &path)
{
	QFile file(path);
	if (file.open(QFile::ReadOnly)) {
		QString line = file.readLine();
		bool ok = false;
		int v = line.toInt(&ok);
		file.close();
		if (ok) return v;
	}
	return -1;
}



void MainDialog::setBacklight(bool on)
{
	QString cmd = command + (on ? " on" : " off");
	QProcess::execute(cmd);
}

void MainDialog::setBrightness(int value)
{
	if (ui->horizontalSlider->value() != value) {
		ui->horizontalSlider->setValue(value);
	}
	if (ui->spinBox->value() != value) {
		ui->spinBox->setValue(value);
	}
	if (value < 0) value = 0;
	else if (value > 255) value = 255;
	QString cmd = command + ' ' + QString::number(value);
	QProcess::execute(cmd);
}

void MainDialog::on_checkBox_clicked(bool checked)
{
	setBacklight(checked);
}

void MainDialog::on_horizontalSlider_valueChanged(int value)
{
	setBrightness(value);
}

void MainDialog::on_spinBox_valueChanged(int value)
{
	setBrightness(value);
}




