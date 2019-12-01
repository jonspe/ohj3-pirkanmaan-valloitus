#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>

namespace Ui {
class EndDialog;
}

/**
 * @brief The class for game ending dialog, which displays
 * statistics about the game.
 */
class EndDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndDialog(unsigned int winning_player,
                       unsigned int winning_turn,
                       QWidget *parent = nullptr);
    ~EndDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EndDialog *m_ui;
    unsigned int m_winner;
    unsigned int m_turn;
};

#endif // ENDDIALOG_H
