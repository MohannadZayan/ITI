#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>
#include <QQmlEngine>

class Calculator : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    // Q_PROPERTY exposes display as a named property QML can bind to directly (text: calc.display); READ names the getter, NOTIFY names the signal QML listens to so bindings auto-update when the value changes.
    Q_PROPERTY(QString display READ display NOTIFY displayChanged)

public:
    explicit Calculator(QObject *parent = nullptr);

    QString display() const;

    // Q_INVOKABLE exposes a normal C++ method to be called directly from QML/JS (e.g. calc.inputDigit(5)); without it QML can't see the method at all.
    Q_INVOKABLE void inputDigit(int digit);   // appends/starts a digit on the current number being typed
    Q_INVOKABLE void inputDecimal();          // inserts a "." into the current number, if not already present
    Q_INVOKABLE void inputOperator(const QString &op); // stores +/-/*// and queues the current number as the left-hand operand
    Q_INVOKABLE void equals();                // performs the pending operation and shows the result
    Q_INVOKABLE void clear();                 // resets display and internal state back to "0"

    // begins entering a trig function ("sin", "cos", or "tan"): shows "sin(" on screen and waits for a number to be typed, computed on equals()
    Q_INVOKABLE void calculateTrig(const QString &function);

signals:
    void displayChanged(); // emitted whenever m_display changes; this is what makes QML bindings on "display" refresh automatically

private:
    void setDisplay(const QString &text); // updates m_display and emits displayChanged(), kept in one place so every method doesn't repeat this
    void updateDisplay();                 // rebuilds m_display from m_expression + m_currentNumber, call after either one changes
    double trigValue(const QString &function, double degrees) const; // computes sin/cos/tan of a degree value, shared by equals() and inputOperator()

    QString m_display;          // the text currently shown on screen, e.g. "5+3" or "5+3 = 8"
    QString m_currentNumber;    // just the number currently being typed, e.g. "3"
    QString m_expression;       // the part already locked in, e.g. "5+", empty if no operator pressed yet
    double m_left;               // the number on the left side of the operator, e.g. the 5 in "5+3"
    QString m_pendingOperator;  // the operator waiting to be applied ("+","-","*","/","^"), empty if none queued
    QString m_pendingFunction;  // the trig function waiting to be applied ("sin","cos","tan"), empty if none queued
    bool m_waitingForOperand;   // true right after an operator/equals, so the next digit starts a new number instead of appending
};

#endif // CALCULATOR_H
