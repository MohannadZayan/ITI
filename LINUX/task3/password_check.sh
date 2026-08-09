#!/bin/bash

read -p "Enter your password: " password

length=${#password}
score=0

echo ""
echo "Password Strength Report"
echo ""

if [ "$length" -ge 8 ]; then
    echo "Length          : OK"
    ((score++))
else
    echo "Length          : Missing"
fi

if [[ "$password" =~ [A-Z] ]]; then
    echo "Uppercase       : OK"
    ((score++))
else
    echo "Uppercase       : Missing"
fi

if [[ "$password" =~ [a-z] ]]; then
    echo "Lowercase       : OK"
    ((score++))
else
    echo "Lowercase       : Missing"
fi

if [[ "$password" =~ [0-9] ]]; then
    echo "Digit           : OK"
    ((score++))
else
    echo "Digit           : Missing"
fi

if [[ "$password" =~ [^a-zA-Z0-9] ]]; then
    echo "Special Char    : OK"
    ((score++))
else
    echo "Special Char    : Missing"
fi

echo ""
if [ "$score" -eq 5 ]; then
    echo "Overall: Strong"
elif [ "$score" -ge 3 ]; then
    echo "Overall: Medium"
else
    echo "Overall: Weak"
fi
