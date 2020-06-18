#include "spotscountdialog.h"
#include "ui_spotscountdialog.h"

spotscountDialog::spotscountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spotscountDialog)
{
    ui->setupUi(this);
}

spotscountDialog::~spotscountDialog()
{
    delete ui;
}

void spotscountDialog::on_buttonBox_accepted()
{
    done(ui->spinBox->value());
}
