all: fileserver fileclient

fileserver: fileserver.c
	gcc -Wall -o fileserver fileserver.c

fileclient: fileclient.c
	gcc -o fileclient fileclient.c