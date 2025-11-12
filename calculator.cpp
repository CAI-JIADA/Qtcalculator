#include "calculator.h"
#include <QDebug>
#include <cmath>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), waitingForOperand(false)
{
    createUI();
}

Calculator::~Calculator()
{
}

void Calculator::createUI()
{
    // Create display
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    
    QFont font = display->font();
    font.setPointSize(20);
    display->setFont(font);
    display->setMinimumHeight(50);
    
    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(display);
    
    // Create button grid layout
    QGridLayout *gridLayout = new QGridLayout;
    
    // Create number buttons (0-9)
    QPushButton *button0 = createButton("0", SLOT(digitClicked()));
    QPushButton *button1 = createButton("1", SLOT(digitClicked()));
    QPushButton *button2 = createButton("2", SLOT(digitClicked()));
    QPushButton *button3 = createButton("3", SLOT(digitClicked()));
    QPushButton *button4 = createButton("4", SLOT(digitClicked()));
    QPushButton *button5 = createButton("5", SLOT(digitClicked()));
    QPushButton *button6 = createButton("6", SLOT(digitClicked()));
    QPushButton *button7 = createButton("7", SLOT(digitClicked()));
    QPushButton *button8 = createButton("8", SLOT(digitClicked()));
    QPushButton *button9 = createButton("9", SLOT(digitClicked()));
    
    // Create operation buttons
    QPushButton *buttonAdd = createButton("+", SLOT(operatorClicked()));
    QPushButton *buttonSub = createButton("-", SLOT(operatorClicked()));
    QPushButton *buttonMul = createButton("×", SLOT(operatorClicked()));
    QPushButton *buttonDiv = createButton("÷", SLOT(operatorClicked()));
    QPushButton *buttonEqual = createButton("=", SLOT(equalClicked()));
    QPushButton *buttonClear = createButton("C", SLOT(clearClicked()));
    QPushButton *buttonDelete = createButton("⌫", SLOT(deleteClicked()));
    QPushButton *buttonDecimal = createButton(".", SLOT(digitClicked()));
    
    // Set button sizes
    QSize buttonSize(70, 50);
    button0->setMinimumSize(buttonSize);
    button1->setMinimumSize(buttonSize);
    button2->setMinimumSize(buttonSize);
    button3->setMinimumSize(buttonSize);
    button4->setMinimumSize(buttonSize);
    button5->setMinimumSize(buttonSize);
    button6->setMinimumSize(buttonSize);
    button7->setMinimumSize(buttonSize);
    button8->setMinimumSize(buttonSize);
    button9->setMinimumSize(buttonSize);
    buttonAdd->setMinimumSize(buttonSize);
    buttonSub->setMinimumSize(buttonSize);
    buttonMul->setMinimumSize(buttonSize);
    buttonDiv->setMinimumSize(buttonSize);
    buttonEqual->setMinimumSize(buttonSize);
    buttonClear->setMinimumSize(buttonSize);
    buttonDelete->setMinimumSize(buttonSize);
    buttonDecimal->setMinimumSize(buttonSize);
    
    // Set button fonts
    QFont buttonFont;
    buttonFont.setPointSize(14);
    button0->setFont(buttonFont);
    button1->setFont(buttonFont);
    button2->setFont(buttonFont);
    button3->setFont(buttonFont);
    button4->setFont(buttonFont);
    button5->setFont(buttonFont);
    button6->setFont(buttonFont);
    button7->setFont(buttonFont);
    button8->setFont(buttonFont);
    button9->setFont(buttonFont);
    buttonAdd->setFont(buttonFont);
    buttonSub->setFont(buttonFont);
    buttonMul->setFont(buttonFont);
    buttonDiv->setFont(buttonFont);
    buttonEqual->setFont(buttonFont);
    buttonClear->setFont(buttonFont);
    buttonDelete->setFont(buttonFont);
    buttonDecimal->setFont(buttonFont);
    
    // Layout buttons in grid (calculator style)
    // Row 0: Clear and Delete
    gridLayout->addWidget(buttonClear, 0, 0, 1, 2);
    gridLayout->addWidget(buttonDelete, 0, 2);
    gridLayout->addWidget(buttonDiv, 0, 3);
    
    // Row 1: 7, 8, 9, ×
    gridLayout->addWidget(button7, 1, 0);
    gridLayout->addWidget(button8, 1, 1);
    gridLayout->addWidget(button9, 1, 2);
    gridLayout->addWidget(buttonMul, 1, 3);
    
    // Row 2: 4, 5, 6, -
    gridLayout->addWidget(button4, 2, 0);
    gridLayout->addWidget(button5, 2, 1);
    gridLayout->addWidget(button6, 2, 2);
    gridLayout->addWidget(buttonSub, 2, 3);
    
    // Row 3: 1, 2, 3, +
    gridLayout->addWidget(button1, 3, 0);
    gridLayout->addWidget(button2, 3, 1);
    gridLayout->addWidget(button3, 3, 2);
    gridLayout->addWidget(buttonAdd, 3, 3);
    
    // Row 4: 0, ., =
    gridLayout->addWidget(button0, 4, 0, 1, 2);
    gridLayout->addWidget(buttonDecimal, 4, 2);
    gridLayout->addWidget(buttonEqual, 4, 3);
    
    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);
    
    setWindowTitle("Calculator");
    resize(320, 400);
}

QPushButton* Calculator::createButton(const QString &text, const char *slot)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, slot);
    return button;
}

void Calculator::digitClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString digit = button->text();
    
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    
    if (display->text() == "0" && digit != ".") {
        display->setText(digit);
    } else {
        // Don't allow multiple decimal points
        if (digit == "." && display->text().contains(".")) {
            return;
        }
        display->setText(display->text() + digit);
    }
}

void Calculator::operatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString op = button->text();
    
    double currentDisplayValue = display->text().toDouble();
    
    if (!operation.isEmpty()) {
        // Perform pending operation
        double storedVal = storedValue.toDouble();
        double result = 0.0;
        
        if (operation == "+") {
            result = storedVal + currentDisplayValue;
        } else if (operation == "-") {
            result = storedVal - currentDisplayValue;
        } else if (operation == "×") {
            result = storedVal * currentDisplayValue;
        } else if (operation == "÷") {
            if (currentDisplayValue != 0.0) {
                result = storedVal / currentDisplayValue;
            } else {
                display->setText("Error");
                storedValue.clear();
                operation.clear();
                waitingForOperand = true;
                return;
            }
        }
        
        display->setText(QString::number(result));
        storedValue = QString::number(result);
    } else {
        storedValue = display->text();
    }
    
    operation = op;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    if (operation.isEmpty()) {
        return;
    }
    
    double currentDisplayValue = display->text().toDouble();
    double storedVal = storedValue.toDouble();
    double result = 0.0;
    
    if (operation == "+") {
        result = storedVal + currentDisplayValue;
    } else if (operation == "-") {
        result = storedVal - currentDisplayValue;
    } else if (operation == "×") {
        result = storedVal * currentDisplayValue;
    } else if (operation == "÷") {
        if (currentDisplayValue != 0.0) {
            result = storedVal / currentDisplayValue;
        } else {
            display->setText("Error");
            storedValue.clear();
            operation.clear();
            waitingForOperand = true;
            return;
        }
    }
    
    display->setText(QString::number(result));
    storedValue.clear();
    operation.clear();
    waitingForOperand = true;
}

void Calculator::clearClicked()
{
    display->setText("0");
    storedValue.clear();
    operation.clear();
    waitingForOperand = false;
}

void Calculator::deleteClicked()
{
    QString text = display->text();
    if (text.length() > 1) {
        text.chop(1);
        display->setText(text);
    } else {
        display->setText("0");
    }
}
