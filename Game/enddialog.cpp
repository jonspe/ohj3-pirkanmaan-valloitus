#include "enddialog.h"
#include "ui_enddialog.h"

EndDialog::EndDialog(unsigned int winning_player,
                     unsigned int winning_turn,
                     QWidget *parent):
    QDialog(parent),
    m_ui(new Ui::EndDialog),
    m_winner(winning_player),
    m_turn(winning_turn)
{
    m_ui->setupUi(this);

    setWindowTitle("Victory!");

    QString winner_qstring = QString::number(m_winner);
    QString turn_qstring = QString::number(m_turn);
    QString end_text = QString("Player %1 wins by being the first to construct the monument on turn %2!").arg(winner_qstring, turn_qstring);

    m_ui->label->setText(end_text);
}

EndDialog::~EndDialog()
{
    delete m_ui;
}

void EndDialog::on_pushButton_clicked()
{
    accept();
}
