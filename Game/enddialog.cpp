#include "enddialog.h"
#include "ui_enddialog.h"

EndDialog::EndDialog(QWidget *parent,
                     unsigned int winning_player,
                     unsigned int winning_turn) :
    QDialog(parent),
    ui(new Ui::EndDialog),
    winner(winning_player),
    turn(winning_turn)
{
    ui->setupUi(this);

    QString winner_qstring = QString::number(winner);
    QString turn_qstring = QString::number(winning_turn);
    QString end_text_qstring = QString("Player %1 wins by being the first to construct the monument on turn %2!").arg(winner_qstring, turn_qstring);

    ui->label->setText(end_text_qstring);
}



EndDialog::~EndDialog()
{
    delete ui;
}


void EndDialog::on_pushButton_clicked()
{
    accept();
}
