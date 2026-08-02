#!/bin/bash
echo "=====TASK 1===== "
echo "Welcome!"

date
#delete the current student
if grep "^student:" /etc/passwd > /dev/null
then
 userdel student

fi
#delete the current group
if grep "^ITI:" /etc/group > /dev/null

then
 groupdel ITI

fi
#Make new student
useradd student
echo "User 'student' was created successfully!"
#Make new group
groupadd ITI
echo "Group 'ITI was created successfully!"


#Verifying:

if grep "^student:" /etc/passwd > /dev/null
then
    echo "User verification successful."
else
    echo "User verification failed."
fi

if grep "^ITI:" /etc/group > /dev/null
then
    echo "Group verification successful."
else
    echo "Group verification failed."
fi

#Assigning student to group ITI
usermod -aG ITI student
echo "User 'student' was added to group ITI successfully!"

#Displaying members:

echo "Members of ITI group:"
getent group ITI
