# Dialogs-Samp
Include to make easy your life with dialogs.

|  Total downloads | Latest release |
| :---: | :---: | 
[![All Releases](https://img.shields.io/github/downloads/Dayvison/Dialogs-Samp/total.svg?maxAge=86400)]()  |  [![latest release](https://img.shields.io/github/release/Dayvison/Dialogs-Samp.svg?maxAge=86400)](https://github.com/Dayvison/Dialogs-Samp/releases) <br> [![Github Releases](https://img.shields.io/github/downloads/Dayvison/Dialogs-Samp/latest/total.svg?maxAge=86400)](https://github.com/Dayvison/Dialogs-Samp/releases)  |  

## Features
* Response for dialogs(Like ZCMD processor)
* Create dynamic dialogs
* Format the info directly in the dialog, without need use format.
* A new callback `OnDialogPerformed`, called before showing dialog to player

## Examples

### Creating and show the dialog for player
```pawn
CreateDialog:Dialog(playerid, style, caption[], info[], button1[], button2[])
{
	style = DIALOG_STYLE_MSGBOX;
	caption = "Hello World!";
	button1 = "Hello";
	button2 = "World";
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(info, sizeof(info), "Hello %s. What you think about?", name);
}
public OnPlayerConnect(playerid)
{
	ShowDialog(playerid, Dialog);
}
Dialog:Dialog(playerid, dialogid, response, listitem, inputtext[])
{
	SendClientMessage(playerid, -1, response ? "You clicked at button 1" :  "You clicked at button 0");
	return true;
}
```

### Show dialog without create
```pawn
public OnPlayerConnect(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	ShowPlayerDialog(playerid, Dialog, DIALOG_STYLE_MSGBOX, "Hello World!", "Hello %s. What you think about?", "Hello", "World", name);
}
Dialog:Dialog(playerid, dialogid, response, listitem, inputtext[])
{
	SendClientMessage(playerid, -1, response ? "You clicked at button 1" :  "You clicked at button 0");
	return true;
}
```
