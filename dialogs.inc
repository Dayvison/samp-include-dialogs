#if defined dialog_included
	#endinput
#endif
#define dialog_included

#if !defined DIALOG_PROTECT_INPUT
	#define DIALOG_PROTECT_INPUT		(1)
#endif

#if !defined DIALOG_MAX_CAPTION
	#define DIALOG_MAX_CAPTION			(64)
#endif
#if !defined DIALOG_MAX_INFO
	#define DIALOG_MAX_INFO				(4096)
#endif
#if !defined DIALOG_MAX_BUTTON
	#define DIALOG_MAX_BUTTON			(128)
#endif

#define INVALID_DIALOG_STYLE			(-1)
#define DIALOG_DEFAULT_ID				(25635)

#if !defined isnull
	#define isnull(%1) \
		((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define Dialog:%0(%1) \
	forward dialog_%0(%1); public dialog_%0(%1)

#define CreateDialog:%0(%1,%2,%3[],%4[],%5[],%6[]) \
	forward DL_F@%0(%1); public DL_F@%0(%1) { DL_f@%0(%1,DL_@style,DL_@caption,DL_@info,DL_@button1,DL_@button2); } \
	stock DL_f@%0(%1,&%2,%3[DIALOG_MAX_CAPTION],%4[DIALOG_MAX_INFO],%5[DIALOG_MAX_BUTTON],%6[DIALOG_MAX_BUTTON])


#define ShowDialog(%0,%1) ShowDialog@(%0,#%1)

static
	DL_@Name[MAX_PLAYERS][32 char],
	bool:DL_@Open[MAX_PLAYERS char]
;
new
	DL_@style,
	DL_@caption[DIALOG_MAX_CAPTION],
	DL_@info[DIALOG_MAX_INFO],
	DL_@button1[DIALOG_MAX_BUTTON],
	DL_@button2[DIALOG_MAX_BUTTON]
;
#if defined OnDialogPerformed
	forward OnDialogPerformed(playerid, dialog[], response, success);
#endif
forward _@_DL_funcinc_@_();
public _@_DL_funcinc_@_()
{
	format("", 0, "");
}
stock bool:DialogIsOpen(playerid)
{
	if(!IsPlayerConnected(playerid))
		return false;
	return DL_@Open{playerid};
}

stock ShowDialog@(playerid, function[], style=INVALID_DIALOG_STYLE, caption[]="", info[]="", button1[]="", button2[]="", {Float,_}:...)
{
	static args;
	if(style==INVALID_DIALOG_STYLE)
	{
		new
			funcname[32]
		;
		funcname = "DL_F@";
		strcat(funcname, function);
		if(funcidx(funcname) == -1)
		{
			printf("[DIALOG ERROR]: None dialog created with name \"%s\"", function);
			return 0;
		}
		strpack(DL_@Name[playerid], function, sizeof(DL_@Name[]));
		CallLocalFunction(funcname, "d", playerid);
		ShowPlayerDialog(playerid, DIALOG_DEFAULT_ID, DL_@style, DL_@caption, DL_@info, DL_@button1, DL_@button2);
	}
	else
	{
		if ((args = numargs()) > 7)
		{
		    while (--args >= 7)
			{
				#emit LCTRL 5
				#emit LOAD.alt args
				#emit SHL.C.alt 2
				#emit ADD.C 12
				#emit ADD
				#emit LOAD.I
				#emit PUSH.pri
			}
			#emit PUSH.S info
			#emit PUSH.C 4096
			#emit PUSH.C DL_@info

			#emit LOAD.S.pri 8
			#emit CONST.alt 16
			#emit SUB
			#emit PUSH.pri

			#emit SYSREQ.C format
			#emit LCTRL 5
			#emit SCTRL 4
			ShowPlayerDialog(playerid, DIALOG_DEFAULT_ID, style, caption, DL_@info, button1, button2);
		}
		else
			ShowPlayerDialog(playerid, DIALOG_DEFAULT_ID, style, caption, info, button1, button2);

		strpack(DL_@Name[playerid], function, sizeof(DL_@Name[]));
	}
	DL_@Open{playerid} = true;
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#if defined DIALOG_PROTECT_INPUT && DIALOG_PROTECT_INPUT == 1
	for(new i, j = strlen(inputtext); i < j; ++i)
		if(inputtext[i] == '%');
			inputtext[i] = '#';
	#endif
	if(dialogid == DIALOG_DEFAULT_ID)
	{
		if(DL_@Open{playerid})
		{
			new funcname[32] = "dialog_";
			strcat(funcname, DL_@Name[playerid]);

			DL_@Name[playerid]{0} = 0;
			DL_@Open{playerid} = false;

			#if defined OnDialogPerformed
			if(OnDialogPerformed(playerid, funcname[7], response, (funcidx(funcname) != -1)))
		 		CallLocalFunction(funcname, "ddds", playerid, response, listitem, (!inputtext[0]) ? ("\1") : (inputtext));
			#else
		 	CallLocalFunction(funcname, "ddds", playerid, response, listitem, (!inputtext[0]) ? ("\1") : (inputtext));
			#endif
		}
	}
	#if defined DL_@OnDialogResponse
	    return DL_@OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
	    return 0;
	#endif
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif

#define OnDialogResponse DL_@OnDialogResponse

#if defined DL_@OnDialogResponse
	forward DL_@OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif
