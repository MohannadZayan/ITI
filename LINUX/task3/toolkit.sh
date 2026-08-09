#!/bin/bash

show_date() {
    date
}

show_uptime() {
    uptime
}

show_users() {
    who
}

show_pwd() {
    pwd
}

show_disk() {
    df -h
}

show_memory() {
    free -h
}

list_files() {
    ls -l
}

while true
do
    echo ""
    echo "====================="
    echo "Linux Toolkit"
    echo "====================="
    echo "1) Show Date"
    echo "2) Show Uptime"
    echo "3) Show Logged Users"
    echo "4) Show Current Directory"
    echo "5) Show Disk Usage"
    echo "6) Show Memory Usage"
    echo "7) List Files"
    echo "8) Exit"
    read -p "Choose an option: " choice

    case $choice in
        1) show_date ;;
        2) show_uptime ;;
        3) show_users ;;
        4) show_pwd ;;
        5) show_disk ;;
        6) show_memory ;;
        7) list_files ;;
        8) echo "Goodbye!"; break ;;
        *) echo "Invalid option, try again." ;;
    esac
done
