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

void Calculator::inputOperator(const QString &op)
{
    // lock in the number that was just typed as the left side of the calculation
    m_left = m_currentNumber.toDouble();
    m_pendingOperator = op;

    // remember what to show on screen, e.g. "5" + "+" becomes "5+"
    m_expression = m_currentNumber + " " + op;

    // next digit pressed should start a new number, not continue this one
    m_waitingForOperand = true;

    updateDisplay();
}

void Calculator::equals()
{
    double right = m_currentNumber.toDouble();

    try {
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

        // show the full equation, e.g. "5+3 = 8"
        setDisplay(m_expression + m_currentNumber + " = " + QString::number(result));

        // reset so the next digit typed starts a fresh calculation
        m_currentNumber = QString::number(result);
    } catch (const std::exception &error) {
        // show the error message on screen instead of the equation
        setDisplay(QString(error.what()));
        m_currentNumber = "0";
    }

    m_expression = "";
    m_pendingOperator = "";
    m_waitingForOperand = true;
}

void Calculator::calculateTrig(const QString &function)
{
    double degrees = m_currentNumber.toDouble();
    double radians = degrees * kPi / 180.0;
    double result = 0.0;

    if (function == "sin")
        result = std::sin(radians);
    else if (function == "cos")
        result = std::cos(radians);
    else if (function == "tan")
        result = std::tan(radians);

    setDisplay(function + "(" + m_currentNumber + ") = " + QString::number(result));

    m_currentNumber = QString::number(result);
    m_expression = "";
    m_pendingOperator = "";
    m_waitingForOperand = true;
}

void Calculator::clear()
{
    m_currentNumber = "0";
    m_expression = "";
    m_left = 0.0;
    m_pendingOperator = "";
    m_waitingForOperand = true;
    setDisplay("0");
}
