#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = nullptr);
    ~SetupDialog();

    unsigned int map_size = 60;
    unsigned int seed = 1337;
    unsigned int player_amount = 1;

private slots:
    void on_AcceptButton_released();

    void on_MapSizeDropdown_currentTextChanged(const QString &arg1);

    void on_SeedInput_textChanged(const QString &arg1);

    void on_PlayersDropdown_currentIndexChanged(const QString &arg1);

private:
    Ui::SetupDialog *ui;
};

#endif // SETUPDIALOG_H
