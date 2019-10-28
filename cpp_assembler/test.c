#include <stdlib.h>
#include <stdio.h>

char get_message ()
{
	char *mymessage;
	mymessage = malloc (sizeof (char) * 15);
	
	mymessage = "Hello World";
	
	return *mymessage;
}

int main (int argc, char *argv [])
{
	char *message;
	message = malloc (sizeof (char) * 15);
	
	*message = get_message ();
	
	printf ("%s\n", message); //this returns output of: H

	return 0;
}