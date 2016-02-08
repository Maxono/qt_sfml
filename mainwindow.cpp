#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CODE_VALIDATOR_LINE_SLIDER(line_name, slider_name) \
    { \
        int minValue = ui->slider_name->minimum(); \
        int maxValue = ui->slider_name->maximum(); \
        ui->line_name->setValidator(new QIntValidator(minValue, maxValue, this)); \
    }

#define CODE_SLIDER_TEXT(NAME, setterName) \
    void MainWindow::set##NAME(int value) \
    { \
        int minValue = ui->slider##NAME->minimum() ;\
        int maxValue = ui->slider##NAME->maximum(); \
        if (value >= minValue && value <= maxValue) \
        { \
            ui->lineEdit##NAME->setText(QString::number(value)); \
            ui->slider##NAME->setValue(value); \
            ui->SFMLWidget->setterName(value); \
        } \
        else if (value < minValue) \
        { \
            this->set##NAME(minValue); \
        } \
        else if (value > maxValue) \
        { \
            this->set##NAME(maxValue); \
        } \
    } \
    void MainWindow::on_lineEdit##NAME ##_editingFinished() \
    { \
        int value = ui->lineEdit##NAME->text().toInt(); \
        set##NAME(value); \
    }


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->SFMLWidget, SIGNAL(rotationChanged(int)), this, SLOT(setRotation(int)));
    QObject::connect(ui->SFMLWidget, SIGNAL(rangeChanged(int)), this, SLOT(setRange(int)));
    QObject::connect(ui->SFMLWidget, SIGNAL(colorChanged(uint8_t,uint8_t,uint8_t)), this, SLOT(setColor(uint8_t,uint8_t,uint8_t)));
    QObject::connect(ui->SFMLWidget, SIGNAL(amountChanged(int)), this, SLOT(setAmount(int)));
    QObject::connect(ui->SFMLWidget, SIGNAL(speedChanged(int)), this, SLOT(setSpeed(int)));
    QObject::connect(ui->SFMLWidget, SIGNAL(lifeChanged(int)), this, SLOT(setLife(int)));

    // validators
    CODE_VALIDATOR_LINE_SLIDER(lineEditRange, sliderRange);
    CODE_VALIDATOR_LINE_SLIDER(lineEditRotation, sliderRotation);
    CODE_VALIDATOR_LINE_SLIDER(lineEditAmount, sliderAmount);
    CODE_VALIDATOR_LINE_SLIDER(lineEditSpeed, sliderSpeed);
    CODE_VALIDATOR_LINE_SLIDER(lineEditLife, sliderLife);

    // standard values
    setRange(360);
    setRotation(0);
    setAmount(200);
    setSpeed(100);
    setLife(3);
    setColor(255, 0, 0);
}

CODE_SLIDER_TEXT(Range, setRange)
CODE_SLIDER_TEXT(Rotation, setRotation)
CODE_SLIDER_TEXT(Amount, setAmount)
CODE_SLIDER_TEXT(Speed, setSpeed)
CODE_SLIDER_TEXT(Life, setLife)

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *e)
{
    ui->SFMLWidget->showEvent(e);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    ui->SFMLWidget->paintEvent(e);
}

void MainWindow::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    QColor color = QColor(red, green, blue);
    ui->SFMLWidget->setColor(red, green, blue);
    ui->lineEditColor->setText(color.name());
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_toolButtonColor_clicked()
{
    const QColor color = QColorDialog::getColor();
    if (color.isValid())
    {
        int red, green, blue, alpha;
        color.getRgb(&red, &green, &blue, &alpha);
        ui->lineEditColor->setText(color.name());
        this->setColor(red, green, blue);
    }
}

void MainWindow::on_lineEditColor_editingFinished()
{
    QColor color;
    color.setNamedColor(ui->lineEditColor->text());
    if (color.isValid())
    {
        int red, green, blue, alpha;
        color.getRgb(&red, &green, &blue, &alpha);

        this->setColor(red, green, blue);
    }
    else
    {
        QColor oldColor = ui->SFMLWidget->getColor();
        ui->lineEditColor->setText(oldColor.name());
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString selectedFilter;
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save file"), NULL, (JSON_FILTER + ";; " + ALL_FILTER), &selectedFilter);
    if (!filepath.isNull() && !filepath.isEmpty())
    {
        if (selectedFilter == JSON_FILTER && !filepath.endsWith(JSON_EXT, Qt::CaseInsensitive))
        {
            filepath += JSON_EXT;
        }

        if (!ui->SFMLWidget->saveJson(filepath))
        {
           QMessageBox::critical(this, "File error", "Couldn't save " + filepath);
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString selectedFilter;
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"), NULL, (JSON_FILTER + ";; " + ALL_FILTER), &selectedFilter);
    if (!filepath.isNull() && !filepath.isEmpty())
    {
        if (selectedFilter == JSON_FILTER && !filepath.endsWith(JSON_EXT, Qt::CaseInsensitive))
        {
            filepath += JSON_EXT;
        }

        if (!ui->SFMLWidget->openJson(filepath))
           QMessageBox::critical(this, "File error", "Couldn't open " + filepath);

    }
}

void MainWindow::on_actionClear_triggered()
{
    ui->SFMLWidget->clearParticles();
}
