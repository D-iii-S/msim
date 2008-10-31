/*
 * Copyright (c) 2008 Martin Decky
 * All rights reserved.
 *
 * Distributed under the terms of GPL.
 *
 */

#include "../stdin.h"

#ifdef __WIN32__

#include <winbase.h>
#include <wincon.h>

bool stdin_poll(char *key)
{
	HANDLE stdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inrec;
	DWORD rd;
	
	do {
		if (!PeekConsoleInput(stdin, &inrec, 1, &rd))
			return false;
		
		if (rd > 0) {
			if (!ReadConsoleInput(stdin, &inrec, 1, &rd))
				return false;
			
			if ((rd > 0) && (inrec.EventType == KEY_EVENT)
				&& (inrec.Event.KeyEvent.bKeyDown)) {
				*key = inrec.Event.KeyEvent.bKeyDown.uChar.AsciiChar;
				return true;
			}
		}
	} while (rd > 0);
	
	return false;
}

#endif /* __WIN32__ */