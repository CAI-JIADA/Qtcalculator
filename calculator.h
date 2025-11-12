#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void operatorClicked();
    void equalClicked();
    void clearClicked();
    void deleteClicked();

private:
    void createUI();
    QPushButton* createButton(const QString &text, const char *slot);
    void updateProcessDisplay();
    
    QLineEdit *processDisplay;
    QLineEdit *display;
    QString currentValue;
    QString storedValue;
    QString operation;
    bool waitingForOperand;
};

#endif // CALCULATOR_H
