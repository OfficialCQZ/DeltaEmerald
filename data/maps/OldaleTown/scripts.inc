OldaleTown_MapScripts:: @ 81E8EA2
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_OnTransition
	.byte 0

OldaleTown_OnTransition: @ 81E8EA8
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_VISITED_OLDALE_TOWN
	call_if_unset FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_BlockWestEntrance
	call_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MoveMartEmployee
	call_if_set FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_SetOldaleState
	end

@ This script seems pointless because nothing uses VAR_OLDALE_TOWN_STATE. In this Delta Hack, it should be used.
OldaleTown_EventScript_SetOldaleState:: @ 81E8ECC
	setvar VAR_OLDALE_TOWN_STATE, 1
	return

OldaleTown_EventScript_BlockWestEntrance:: @ 81E8ED2
	setobjectxyperm 3, 1, 11
	setobjectmovementtype 3, MOVEMENT_TYPE_FACE_LEFT
	return

OldaleTown_EventScript_MoveMartEmployee:: @ 81E8EDE
	setobjectxyperm 2, 10, 12
	setobjectmovementtype 2, MOVEMENT_TYPE_FACE_DOWN
	setvar VAR_0x8008, 7
	return

OldaleTown_EventScript_MoveMartEmployeeBack:: @ 81E8EDE
	setobjectxyperm 2, 13, 7
	setobjectmovementtype 2, MOVEMENT_TYPE_FACE_DOWN
	return

OldaleTown_EventScript_CitySign:: @ 81E8EEA
	msgbox OldaleTown_Text_CitySign, MSGBOX_SIGN
	end

OldaleTown_EventScript_Girl:: @ 81E8EF3
	msgbox OldaleTown_Text_SavingMyProgress, MSGBOX_NPC
	end

OldaleTown_EventScript_Mart0::
	setvar VAR_0x8008, 0
	goto_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MartEmployee
	return

OldaleTown_EventScript_Mart1::
	setvar VAR_0x8008, 1
	goto_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MartEmployee
	return

OldaleTown_EventScript_Mart2::
	setvar VAR_0x8008, 2
	goto_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MartEmployee
	return

OldaleTown_EventScript_Mart3::
	setvar VAR_0x8008, 3
	goto_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MartEmployee
	return

OldaleTown_EventScript_MartApproach0::
	compare VAR_0x8008, 7
	call_if_eq OldaleTown_EventScript_Mart0
	releaseall
	end

OldaleTown_EventScript_MartApproach1::
	compare VAR_0x8008, 7
	call_if_eq OldaleTown_EventScript_Mart1
	releaseall
	end

OldaleTown_EventScript_MartApproach2::
	compare VAR_0x8008, 7
	call_if_eq OldaleTown_EventScript_Mart2
	releaseall
	end

OldaleTown_EventScript_MartApproach3::
	compare VAR_0x8008, 7
	call_if_eq OldaleTown_EventScript_Mart3
	releaseall
	end

OverlyComplicatedMartCode::
	setvar VAR_0x8008, 14
	releaseall
	end

OldaleTown_EventScript_MartEmployee_Static::
	goto_if_set FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_ExplainPotion
	releaseall
	end

OldaleTown_EventScript_MartEmployee::
@ ----------- Let's just set it imemdiately so it doesn't trigger again.
	setflag FLAG_RECEIVED_POTION_OLDALE
	setflag FLAG_TEMP_1

@ ----------- Lock the player.
	lock

@ ----------- Move the employee from the top.
	applymovement 2, OldaleTown_Movement_Employee_Delta
	waitmovement 0

@ ----------- Music, plys the [!] sound effect.
	playbgm MUS_TSURETEK, 0
	playse SE_PIN
	applymovement 2, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 2, Common_Movement_Delay48
	waitmovement 0

@ ----------- Check the variable set by the trigger.
	compare VAR_0x8008, 0
	call_if_eq Oldale_ApproachTheEmployee0
	compare VAR_0x8008, 1
	call_if_eq Oldale_ApproachTheEmployee1
	compare VAR_0x8008, 2
	call_if_eq Oldale_ApproachTheEmployee2
	compare VAR_0x8008, 3
	call_if_eq Oldale_ApproachTheEmployee3

@ ----------- "I work at the Pokémon Mart!"
	msgbox OldaleTown_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage

@ ----------- Let's have this go to another script.
	goto OldaleTown_EventScript_ExplainPokemonMart
	release
	end

Oldale_ApproachTheEmployee0::
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_Player0
	waitmovement 0
	return

Oldale_ApproachTheEmployee1::
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_Player1
	waitmovement 0
	return

Oldale_ApproachTheEmployee2::
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_Player2
	waitmovement 0
	return

Oldale_ApproachTheEmployee3::
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_Player3
	waitmovement 0
	return

OldaleTown_EventScript_ExplainPokemonMart::
@ ----------- Spawn the camera object so we can direct it to the Poké Mart.
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, OldaleTown_Movement_Camera_ShowMart
	waitmovement 0

@ ----------- This is the Pokémon Mart etc.
	msgbox OldaleTown_Text_ThisIsAPokemonMart, MSGBOX_DEFAULT
	closemessage

@ ----------- Fade to black, remove the camera once it returns.
	fadescreen FADE_TO_BLACK

	applymovement OBJ_EVENT_ID_CAMERA, OldaleTown_Movement_Camera_GoBack
	waitmovement 0
	special RemoveCameraObject

@ ----------- Fade from black.
	fadescreen FADE_FROM_BLACK

@ ----------- Give the player 10 potions
	giveitem ITEM_POTION, 10

@ ----------- Check if the bag is full. Should never be the case because you have to go through this dude.
	@ compare VAR_RESULT, 0
	@ goto_if_eq OldaleTown_EventScript_BagIsFull

@ ----------- Explain what the potion does.
	msgbox OldaleTown_Text_PotionExplanation, MSGBOX_DEFAULT
	closemessage

@ ----------- Alright. Let's go to the Pokémon Center.
	applymovement 2, OldaleTown_Movement_Employee_PokemonCenter
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerFollowEmployee
	waitmovement 0

@ ----------- This is the Pokémon Center!
	msgbox OldaleTown_Text_ThisIsPokemonCenter, MSGBOX_DEFAULT
	closemessage

@ ----------- What we do is go back, back, back...
	applymovement 2, OldaleTown_Movement_Employee_GoBack
	waitmovement 0

@ ----------- Fade to black, have the dude go off camera.
	fadescreen FADE_TO_BLACK
	applymovement 2, OldaleTown_Movement_Employee_GoBack2
	waitmovement 0

@ ----------- Now, this should move the employee back! ...but I can't seem to get this work.
	call_if_set FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MoveMartEmployeeBack
	fadescreen FADE_FROM_BLACK

@ ----------- Do a second check.
	call_if_set FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MoveMartEmployeeBack
	fadedefaultbgm

@ ----------- I'm just gonna do some tiresome, complicated code just because I can't seem to get the other thing to work.
	release
	return

OldaleTown_EventScript_ExplainPotion:: @ 81E8FB9
	msgbox OldaleTown_Text_PotionExplanation, MSGBOX_NPC
	release
	end

OldaleTown_EventScript_BagIsFull:: @ 81E8FC3
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	fadedefaultbgm
	release
	end

OldaleTown_Movement_Camera_ShowMart:
	walk_up
	walk_up
	walk_up
	walk_diag_northeast
	walk_diag_northeast
	walk_diag_northeast
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_Movement_Camera_GoBack:
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	step_end

OldaleTown_Movement_Employee_Delta:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OldaleTown_Movement_Employee_PokemonCenter:
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_right
	step_end

OldaleTown_Movement_Employee_GoBack:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

OldaleTown_Movement_Employee_GoBack2:
	walk_fastest_right
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	face_down
	step_end

OldaleTown_Movement_EmployeeEast: @ 81E8FCE
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

OldaleTown_Movement_EmployeeSouth: @ 81E8FD7
	walk_left
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

OldaleTown_Movement_EmployeeNorth: @ 81E8FE2
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

OldaleTown_Movement_Unknown1: @ 81E8FEB
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	walk_in_place_fastest_down
	step_end

OldaleTown_Movement_Player0:
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

OldaleTown_Movement_Player1:
	walk_up
	walk_right
	walk_up
	step_end

OldaleTown_Movement_Player2:
	walk_up
	walk_up
	step_end

OldaleTown_Movement_Player3:
	walk_up
	walk_left
	walk_up
	step_end

OldaleTown_Movement_PlayerFollowEmployee:
	delay_16
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

OldaleTown_Movement_Unknown2: @ 81E9013
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_EventScript_FootprintsMan:: @ 81E901F
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_NotBlockingPath
	msgbox OldaleTown_Text_DiscoveredFootprints, MSGBOX_DEFAULT
	closemessage
	applymovement 3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

OldaleTown_EventScript_BlockedPath:: @ 81E903F
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
	applymovement 3, OldaleTown_Movement_BackUp
	waitmovement 0
	msgbox OldaleTown_Text_WaitDontComeInHere, MSGBOX_DEFAULT
	closemessage
	applymovement 3, OldaleTown_Movement_ReturnToOriginalPosition
	waitmovement 0
	releaseall
	end

OldaleTown_EventScript_NotBlockingPath:: @ 81E9066
	msgbox OldaleTown_Text_FinishedSketchingFootprints, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_Rival:: @ 81E9070
	lockall
	applymovement 4, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_0x8009, 0
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger1:: @ 81E9086
	lockall
	applymovement 4, OldaleTown_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger2:: @ 81E90A6
	lockall
	applymovement 4, OldaleTown_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger3:: @ 81E90C6
	lockall
	applymovement 4, OldaleTown_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_ShowRivalMessage:: @ 81E90E6
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq OldaleTown_EventScript_ShowMayMessage
	compare VAR_RESULT, FEMALE
	goto_if_eq OldaleTown_EventScript_ShowBrendanMessage
	end

OldaleTown_EventScript_ShowMayMessage:: @ 81E90FE
	msgbox OldaleTown_Text_MayLetsGoBack, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_RivalFinish
	end

OldaleTown_EventScript_ShowBrendanMessage:: @ 81E910C
	msgbox OldaleTown_Text_BrendanLetsGoBack, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_RivalFinish
	end

OldaleTown_EventScript_RivalFinish:: @ 81E911A
	closemessage
	compare VAR_0x8009, 0
	call_if_eq OldaleTown_EventScript_DoExitMovement1
	compare VAR_0x8009, 1
	call_if_eq OldaleTown_EventScript_DoExitMovement2
	applymovement 4, OldaleTown_Movement_RivalExit
	waitmovement 0
	removeobject 4
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	releaseall
	end

OldaleTown_EventScript_DoExitMovement1:: @ 81E9148
	compare VAR_FACING, DIR_SOUTH
	goto_if_ne OldaleTown_EventScript_DoExitMovement2
	applymovement 4, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_EventScript_DoExitMovement2:: @ 81E915E
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_WatchRivalExit
	applymovement 4, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_Movement_RivalApproachPlayer1: @ 81E9170
	walk_left
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer2: @ 81E9173
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer3: @ 81E9175
	face_left
	step_end

OldaleTown_Movement_RivalExit: @ 81E9177
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OldaleTown_Movement_WatchRivalExit: @ 81E917E
	delay_8
	delay_4
	walk_in_place_fastest_down
	step_end

OldaleTown_Movement_PlayerStepBack: @ 81E9182
	delay_8
	walk_right
	step_end

OldaleTown_Movement_BackUp: @ 81E9185
	walk_fast_up
	walk_in_place_fastest_left
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

OldaleTown_Movement_ReturnToOriginalPosition: @ 81E918B
	walk_down
	walk_left
	step_end

OldaleTown_Text_SavingMyProgress: @ 81E918E
	.string "I want to take a rest, so I'm saving my\n"
	.string "progress.$"

OldaleTown_Text_IWorkAtPokemonMart: @ 81E91C0
	.string "Hi!\n"
	.string "I work at a POKéMON MART.\p"
	.string "Can I get you to come with me?$"

OldaleTown_Text_ThisIsAPokemonMart: @ 81E91FD
	.string "This is a POKéMON MART.\n"
	.string "Just look for our blue roof.\p"
	.string "We sell a variety of goods including\n"
	.string "POKé BALLS for catching POKéMON.\p"
	.string "Here, I'd like you to have this as\n"
	.string "a promotional item.$"

OldaleTown_Text_PotionExplanation: @ 81E92AF
	.string "A POTION can be used anytime, so it's\n"
	.string "even more useful than a POKéMON CENTER\l"
	.string "in certain situations.$"

OldaleTown_Text_WaitDontComeInHere: @ 81E9313
	.string "Aaaaah! Wait!\n"
	.string "Please don't come in here.\p"
	.string "I just discovered the footprints of\n"
	.string "a rare POKéMON!\p"
	.string "Wait until I finish sketching\n"
	.string "them, okay?$"

OldaleTown_Text_DiscoveredFootprints: @ 81E939A
	.string "I just discovered the footprints of\n"
	.string "a rare POKéMON!\p"
	.string "Wait until I finish sketching\n"
	.string "them, okay?$"

OldaleTown_Text_FinishedSketchingFootprints: @ 81E93F8
	.string "I finished sketching the footprints of\n"
	.string "a rare POKéMON.\p"
	.string "But it turns out they were only my\n"
	.string "own footprints…$"

OldaleTown_Text_MayLetsGoBack: @ 81E9462
	.string "MAY: {PLAYER}{KUN}!\n"
	.string "Over here!\l"
	.string "Let's hurry home!$"

OldaleTown_Text_BrendanLetsGoBack: @ 81E948A
	.string "BRENDAN: I'm heading back to my dad's\n"
	.string "LAB now.\l"
	.string "{PLAYER}, you should hustle back, too.$"

OldaleTown_Text_CitySign: @ 81E94DA
	.string "OLDALE TOWN\n"
	.string "“Where things start off scarce.”$"

OldaleTown_Text_ThisIsPokemonCenter: @ 81E94DA
	.string "this is a pokémon center.\n"
	.string "test string$"

