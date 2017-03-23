#include <a_samp>
#include <core>
#include <float>
#include <dialogs>

#pragma tabsize 0

main()
{
	print("\n----------------------------------");
	print("  Bare Script\n");
	print("----------------------------------\n");
}

public OnPlayerConnect(playerid)
{
	GameTextForPlayer(playerid,"~w~SA-MP: ~r~Bare Script",5000,5);
	return 1;
}
const Dialog_3 = 1;
public OnPlayerCommandText(playerid, cmdtext[])
{
	new idx;
	new cmd[256];
	
	cmd = strtok(cmdtext, idx);

	if(strcmp(cmd, "/dialog-1", true) == 0) {
		ShowDialog(playerid, Dialog_1);
    	return 1;
	}
	else if(strcmp(cmd, "/dialog-2", true) == 0) {
		new name[MAX_PLAYER_NAME];
		GetPlayerName(playerid, name, sizeof(name));
		ShowDialog(playerid, Dialog_2, DIALOG_STYLE_MSGBOX, "Dialog_2", "Hi %s!\nHow are you?", "button1", "button2", name);
    	return 1;
	}
	else if(strcmp(cmd, "/dialog-3", true) == 0) {
		new name[MAX_PLAYER_NAME], info[21 + MAX_PLAYER_NAME];
		GetPlayerName(playerid, name, sizeof(name));
		format(info, sizeof(info), "Hi %s!\nHow are you?", name);
		ShowPlayerDialog(playerid, Dialog_3, DIALOG_STYLE_MSGBOX, "Dialog_3", info, "button1", "button2");
    	return 1;
	}

	return 0;
}
CreateDialog:Dialog_1(playerid, style, caption[], info[], button1[], button2[])
{
	style = DIALOG_STYLE_MSGBOX;
	caption = "Dialog_1";
	button1 = "button1";
	button2 = "button2";
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(info, sizeof(info), "Hi %s!\nHow are you?", name);
}
Dialog:Dialog_1(playerid, dialogid, response, listitem, inputtext[])
{
    SendClientMessage(playerid, -1, response ? ("Dialog_1 response: You clicked at button 1") :  ("Dialog_1 response: You clicked at button 0"));
    return true;
}
Dialog:Dialog_2(playerid, dialogid, response, listitem, inputtext[])
{
    SendClientMessage(playerid, -1, response ? ("Dialog_2 response: You clicked at button 1") :  ("Dialog_2 response: You clicked at button 0"));
    return true;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == Dialog_3)
	{
	    SendClientMessage(playerid, -1, response ? ("Dialog_3 OnDialogResponse: You clicked at button 1") :  ("Dialog_3 OnDialogResponse: You clicked at button 0"));
    	return true;
	}
	return true;
}
public OnPlayerSpawn(playerid)
{
	SetPlayerInterior(playerid,0);
	TogglePlayerClock(playerid,0);
	SendClientMessage(playerid, -1, "To test this include use:");
	SendClientMessage(playerid, -1, "{0000FF}/dialog-1{FFFFFF} to test the pre-created dialog.");
	SendClientMessage(playerid, -1, "{0000FF}/dialog-2{FFFFFF} to test the normal dialog, using ShowDialog.");
	SendClientMessage(playerid, -1, "{0000FF}/dialog-3{FFFFFF} to test the normal dialog, using ShowPlayerDialog.");
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
   	return 1;
}

SetupPlayerForClassSelection(playerid)
{
 	SetPlayerInterior(playerid,14);
	SetPlayerPos(playerid,258.4893,-41.4008,1002.0234);
	SetPlayerFacingAngle(playerid, 270.0);
	SetPlayerCameraPos(playerid,256.0815,-43.0475,1004.0234);
	SetPlayerCameraLookAt(playerid,258.4893,-41.4008,1002.0234);
}

public OnPlayerRequestClass(playerid, classid)
{
	SetupPlayerForClassSelection(playerid);
	return 1;
}

public OnGameModeInit()
{
	SetGameModeText("Bare Script");
	ShowPlayerMarkers(1);
	ShowNameTags(1);
	AllowAdminTeleport(1);

	AddPlayerClass(265,1958.3783,1343.1572,15.3746,270.1425,0,0,0,0,-1,-1);

	return 1;
}

strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}