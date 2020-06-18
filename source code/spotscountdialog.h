#ifndef SPOTSCOUNTDIALOG_H
#define SPOTSCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
    class spotscountDialog;
}

class spotscountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit spotscountDialog(QWidget *parent = 0);
    ~spotscountDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::spotscountDialog *ui;
};

#endif // SPOTSCOUNTDIALOG_H
