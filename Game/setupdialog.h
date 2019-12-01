#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>

namespace Ui {
class SetupDialog;
}

/**
 * @brief The SetupDialog class, which is the initial
 * dialog when running the game. Has some input fields
 * that affect gameplay.
 */
class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = nullptr);
    ~SetupDialog();

    unsigned int getSize();
    unsigned int getSeed();
    unsigned int getPlayers();

private slots:
    void on_AcceptButton_released();

    void on_MapSizeDropdown_currentTextChanged(const QString &arg1);

    void on_SeedInput_textChanged(const QString &arg1);

    void on_PlayersDropdown_currentIndexChanged(const QString &arg1);

private:
    Ui::SetupDialog *ui;
    unsigned int map_size = 20;
    unsigned int seed = 1337;
    unsigned int player_amount = 1;
};

#endif // SETUPDIALOG_H
