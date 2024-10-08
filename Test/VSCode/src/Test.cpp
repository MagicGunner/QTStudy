#include "Test.h"

Test::Test(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_Test)
{
    ui->setupUi(this);
}

Test::~Test()
{
    delete ui; 
}