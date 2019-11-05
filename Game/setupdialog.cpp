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
    srand(time(NULL));
    seed = rand()%1000000; // create seed based on current time in case no seed is given
    ui->SeedInput->setValidator( new QIntValidator(0, 1000000, this) );
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::on_AcceptButton_released()
{
    accept();
}

void SetupDialog::on_PlayersDropdown_currentIndexChanged(const QString &arg1)
{
    unsigned int amount = arg1.toInt();
    player_amount = amount;
}

void SetupDialog::on_MapSizeDropdown_currentTextChanged(const QString &arg1)
{
    std::string size = arg1.toStdString();

    if (size == "Small"){
        map_size = 60;
    }else if (size == "Medium"){
        map_size = 100;
    }else if (size == "Large"){
        map_size = 130;
    }else if (size == "Humongous"){
        map_size = 200;
    }

}

void SetupDialog::on_SeedInput_textChanged(const QString &arg1)
{
        unsigned int input = arg1.toInt();
        seed = input;

}

