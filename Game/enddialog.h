#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>

namespace Ui {
class EndDialog;
}

class EndDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndDialog(QWidget *parent = nullptr,
                       unsigned int winning_player = 8,
                       unsigned int winning_turn = 888);
    ~EndDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EndDialog *ui;
    unsigned int winner = 8;
    unsigned int turn = 888;
};

#endif // ENDDIALOG_H
