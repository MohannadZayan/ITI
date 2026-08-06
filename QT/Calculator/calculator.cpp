#include "calculator.h"
#include <cmath>
#include <stdexcept>

static const double kPi = 3.14159265358979323846;

Calculator::Calculator(QObject *parent) : QObject(parent)
{
    m_display = "0";
    m_currentNumber = "0";
    m_expression = "";
    m_left = 0.0;
    m_pendingOperator = "";
    m_pendingFunction = "";
    m_waitingForOperand = true;
}

QString Calculator::display() const
{
    return m_display;
}

void Calculator::setDisplay(const QString &text)
{
    if (m_display == text)
        return;

    m_display = text;
    emit displayChanged();
}

void Calculator::updateDisplay()
{
    // whatever is already locked in, followed by the number currently being typed
    setDisplay(m_expression + m_currentNumber);
}

void Calculator::inputDigit(int digit)
{
    if (m_waitingForOperand) {
        // starting a brand new number, so overwrite whatever was there
        m_currentNumber = QString::number(digit);
        m_waitingForOperand = false;
    } else {
        // still typing the same number, so just add the digit to the end
        m_currentNumber += QString::number(digit);
    }
    updateDisplay();
}

void Calculator::inputDecimal()
{
    if (m_waitingForOperand) {
        // starting a brand new number with a decimal point, so show it as "0."
        m_currentNumber = "0.";
        m_waitingForOperand = false;
    } else if (!m_currentNumber.contains(".")) {
        // only add the "." if the number being typed doesn't already have one
        m_currentNumber += ".";
    }
    updateDisplay();
}

double Calculator::trigValue(const QString &function, double degrees) const
{
    double radians = degrees * kPi / 180.0;

    if (function == "sin")
        return std::sin(radians);
    if (function == "cos")
        return std::cos(radians);
    if (function == "tan")
        return std::tan(radians);
    return 0.0;
}

void Calculator::inputOperator(const QString &op)
{
    QString leftText;

    if (!m_pendingFunction.isEmpty()) {
        // a trig function was still open (e.g. "tan(45"), close it and compute it now
        // instead of leaving it dangling for equals() to misinterpret later
        m_left = trigValue(m_pendingFunction, m_currentNumber.toDouble());
        leftText = m_pendingFunction + "(" + m_currentNumber + ")"; // "tan(45)"
        m_pendingFunction = "";
    } else {
        // lock in the plain number that was just typed as the left side of the calculation
        m_left = m_currentNumber.toDouble();
        leftText = m_currentNumber;
    }

    m_pendingOperator = op;

    // remember what to show on screen, e.g. "tan(45)" + "+" becomes "tan(45) + "
    m_expression = leftText + " " + op + " ";

    // the old number has now been locked in above, so clear it so it doesn't
    // still show up on screen (e.g. "1+" instead of "1+1") until a new digit is typed
    m_currentNumber = "";

    // next digit pressed should start a new number, not continue this one
    m_waitingForOperand = true;

    updateDisplay();
}

void Calculator::equals()
{
    double right = m_currentNumber.toDouble();

    try {
        if (!m_pendingFunction.isEmpty()) {
            // a trig function is waiting, e.g. m_expression is "sin(" and m_currentNumber is "30"
            double result = trigValue(m_pendingFunction, right);

            // "sin(" + "30" + ")" + " = " + "0.5" -> "sin(30) = 0.5"
            setDisplay(m_expression + m_currentNumber + ")" + " = " + QString::number(result));
            m_currentNumber = QString::number(result);
        } else {
            double result = 0.0;

            if (m_pendingOperator == "+")
                result = m_left + right;
            else if (m_pendingOperator == "-")
                result = m_left - right;
            else if (m_pendingOperator == "*")
                result = m_left * right;
            else if (m_pendingOperator == "/") {
                if (right == 0.0)
                    throw std::runtime_error("Cannot divide by zero");
                result = m_left / right;
            } else if (m_pendingOperator == "^")
                result = std::pow(m_left, right);
            else
                result = right; // no operator was pressed, nothing to calculate

            // "5+" + "3" + " = " + "8" -> "5+3 = 8"
            setDisplay(m_expression + m_currentNumber + " = " + QString::number(result));
            m_currentNumber = QString::number(result);
        }
    } catch (const std::exception &error) {
        // show the error message on screen instead of the equation
        setDisplay(QString(error.what()));
        m_currentNumber = "0";
    }

    m_expression = "";
    m_pendingOperator = "";
    m_pendingFunction = "";
    m_waitingForOperand = true;
}

void Calculator::calculateTrig(const QString &function)
{
    // start entering a function call, e.g. pressing "sin" shows "sin(" and waits for the number
    m_pendingFunction = function;
    m_expression = function + "(";
    m_currentNumber = "";
    m_waitingForOperand = true;

    updateDisplay();
}

void Calculator::clear()
{
    m_currentNumber = "0";
    m_expression = "";
    m_left = 0.0;
    m_pendingOperator = "";
    m_pendingFunction = "";
    m_waitingForOperand = true;
    setDisplay("0");
}
