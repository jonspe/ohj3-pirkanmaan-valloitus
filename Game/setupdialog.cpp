#include "setupdialog.h"
#include "ui_setupdialog.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    setWindowTitle("Game Config");

    srand(static_cast<unsigned int>(time(nullptr)));

    seed = rand()%1000000; // create seed based on current time in case no seed is given
    ui->SeedInput->setValidator( new QIntValidator(0, 1000000, this) );
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

unsigned int SetupDialog::getSize()
{
    return map_size;
}

unsigned int SetupDialog::getSeed()
{
    return seed;
}

unsigned int SetupDialog::getPlayers()
{
    return player_amount;
}

void SetupDialog::on_AcceptButton_released()
{
    accept();
}

void SetupDialog::on_PlayersDropdown_currentIndexChanged(const QString &arg1)
{
    unsigned int amount = arg1.toUInt();
    player_amount = amount;
}

void SetupDialog::on_MapSizeDropdown_currentTextChanged(const QString &arg1)
{
    std::string size = arg1.toStdString();

    if (size == "Small"){
        map_size = 20;
    }else if (size == "Medium"){
        map_size = 30;
    }else if (size == "Large"){
        map_size = 45;
    }else if (size == "Humongous"){
        map_size = 60;
    }

}

void SetupDialog::on_SeedInput_textChanged(const QString &arg1)
{
    unsigned int input = arg1.toUInt();
    seed = input;
}

