﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated file, Game
//
////////////////////////////////////////////////////////////////////////////////

using System;


namespace SF {
	public partial struct ResultCode {

		// User is already in a game 
		 public const int _GAME_ALREADY_IN_GAME = (unchecked((int)0xE7040000)); 
		public static readonly Result GAME_ALREADY_IN_GAME = new Result(_GAME_ALREADY_IN_GAME); 

		// Invalid player 
		 public const int _GAME_INVALID_PLAYER = (unchecked((int)0xE7040001)); 
		public static readonly Result GAME_INVALID_PLAYER = new Result(_GAME_INVALID_PLAYER); 

		// Game is not ready 
		 public const int _GAME_NOTREADY = (unchecked((int)0xE7040002)); 
		public static readonly Result GAME_NOTREADY = new Result(_GAME_NOTREADY); 

		// Invalid player state to do the action 
		 public const int _GAME_INVALID_PLAYER_STATE = (unchecked((int)0xE7040003)); 
		public static readonly Result GAME_INVALID_PLAYER_STATE = new Result(_GAME_INVALID_PLAYER_STATE); 

		// Failed to find matching harvest id 
		 public const int _GAME_NO_MATCHING_HARVEST_ID = (unchecked((int)0xE7040004)); 
		public static readonly Result GAME_NO_MATCHING_HARVEST_ID = new Result(_GAME_NO_MATCHING_HARVEST_ID); 

		// Invalid shop item data 
		 public const int _GAME_INVALID_SHOPITEM = (unchecked((int)0xE7040005)); 
		public static readonly Result GAME_INVALID_SHOPITEM = new Result(_GAME_INVALID_SHOPITEM); 

		// Invalid shop item id 
		 public const int _GAME_INVALID_SHOPITEMID = (unchecked((int)0xE7040006)); 
		public static readonly Result GAME_INVALID_SHOPITEMID = new Result(_GAME_INVALID_SHOPITEMID); 

		// User is already in a party 
		 public const int _GAME_ALREADY_IN_PARTY = (unchecked((int)0xE7040007)); 
		public static readonly Result GAME_ALREADY_IN_PARTY = new Result(_GAME_ALREADY_IN_PARTY); 

		// Invalid partyID 
		 public const int _GAME_INVALID_PARTYID = (unchecked((int)0xE7040008)); 
		public static readonly Result GAME_INVALID_PARTYID = new Result(_GAME_INVALID_PARTYID); 

		// Invalid player count for game 
		 public const int _GAME_INVALID_PLAYER_COUNT = (unchecked((int)0xE7040009)); 
		public static readonly Result GAME_INVALID_PLAYER_COUNT = new Result(_GAME_INVALID_PLAYER_COUNT); 

		// User doesn't have eligible privilege 
		 public const int _GAME_NO_PRIVILEGE = (unchecked((int)0xE704000A)); 
		public static readonly Result GAME_NO_PRIVILEGE = new Result(_GAME_NO_PRIVILEGE); 

		// Not enough money(gold, gem, etc) 
		 public const int _GAME_NOTENOUGH_RESOURCE = (unchecked((int)0xE704000B)); 
		public static readonly Result GAME_NOTENOUGH_RESOURCE = new Result(_GAME_NOTENOUGH_RESOURCE); 

		// Maximum notification count 
		 public const int _GAME_MAX_NOTIFICATION = (unchecked((int)0xE704000C)); 
		public static readonly Result GAME_MAX_NOTIFICATION = new Result(_GAME_MAX_NOTIFICATION); 

		// Maximum try reached 
		 public const int _GAME_MAX_TRY = (unchecked((int)0xE704000D)); 
		public static readonly Result GAME_MAX_TRY = new Result(_GAME_MAX_TRY); 

		// User is already in a chatting channel 
		 public const int _GAME_ALREADY_IN_CHAT = (unchecked((int)0xE704000E)); 
		public static readonly Result GAME_ALREADY_IN_CHAT = new Result(_GAME_ALREADY_IN_CHAT); 

		// Map object is invalid 
		 public const int _GAME_MAPOBJECT_INVALID = (unchecked((int)0xE704000F)); 
		public static readonly Result GAME_MAPOBJECT_INVALID = new Result(_GAME_MAPOBJECT_INVALID); 

		// Map object is required to be occupied 
		 public const int _GAME_OCCUPIED_MAPOBJECT_IS_REQUIRED = (unchecked((int)0xE7040010)); 
		public static readonly Result GAME_OCCUPIED_MAPOBJECT_IS_REQUIRED = new Result(_GAME_OCCUPIED_MAPOBJECT_IS_REQUIRED); 

		// Map object is already in use 
		 public const int _GAME_MAPOBJECT_ALREADY_IN_USE = (unchecked((int)0xE7040011)); 
		public static readonly Result GAME_MAPOBJECT_ALREADY_IN_USE = new Result(_GAME_MAPOBJECT_ALREADY_IN_USE); 

		// Map object is not in use 
		 public const int _GAME_MAPOBJECT_NOT_IN_USE = (unchecked((int)0xE7040012)); 
		public static readonly Result GAME_MAPOBJECT_NOT_IN_USE = new Result(_GAME_MAPOBJECT_NOT_IN_USE); 

		// Map object is already in use 
		 public const int _GAME_MAPOBJECT_NOT_FOUND = (unchecked((int)0xE7040013)); 
		public static readonly Result GAME_MAPOBJECT_NOT_FOUND = new Result(_GAME_MAPOBJECT_NOT_FOUND); 

		// Map object is not occupied by the player 
		 public const int _GAME_MAPOBJECT_NOT_OCCUPIED_BY_PLAYER = (unchecked((int)0xE7040014)); 
		public static readonly Result GAME_MAPOBJECT_NOT_OCCUPIED_BY_PLAYER = new Result(_GAME_MAPOBJECT_NOT_OCCUPIED_BY_PLAYER); 

		// Invalid NPC id 
		 public const int _GAME_INVALID_NPCID = (unchecked((int)0xE7040015)); 
		public static readonly Result GAME_INVALID_NPCID = new Result(_GAME_INVALID_NPCID); 

		// Unexpected table value 
		 public const int _GAME_UNEXPECTED_TABLE_VALUE = (unchecked((int)0xE7040016)); 
		public static readonly Result GAME_UNEXPECTED_TABLE_VALUE = new Result(_GAME_UNEXPECTED_TABLE_VALUE); 

		// Not enough currency 
		 public const int _GAME_NOT_ENOUGH_CURRENCY = (unchecked((int)0xE7040017)); 
		public static readonly Result GAME_NOT_ENOUGH_CURRENCY = new Result(_GAME_NOT_ENOUGH_CURRENCY); 

		// Not enough stamina 
		 public const int _GAME_NOT_ENOUGH_STAMINA = (unchecked((int)0xE7040018)); 
		public static readonly Result GAME_NOT_ENOUGH_STAMINA = new Result(_GAME_NOT_ENOUGH_STAMINA); 

		// The player is busy 
		 public const int _GAME_PLAYER_IS_BUSY = (unchecked((int)0xE7040019)); 
		public static readonly Result GAME_PLAYER_IS_BUSY = new Result(_GAME_PLAYER_IS_BUSY); 

		// The player is too far away 
		 public const int _GAME_PLAYER_TOO_FAR_AWAY = (unchecked((int)0xE704001A)); 
		public static readonly Result GAME_PLAYER_TOO_FAR_AWAY = new Result(_GAME_PLAYER_TOO_FAR_AWAY); 

		// Invalid gold value has been specified 
		 public const int _GAME_INVALID_GOLD_VALUE = (unchecked((int)0xE704001B)); 
		public static readonly Result GAME_INVALID_GOLD_VALUE = new Result(_GAME_INVALID_GOLD_VALUE); 

		// Invalid player role 
		 public const int _GAME_INVALID_ROLE = (unchecked((int)0xE704001C)); 
		public static readonly Result GAME_INVALID_ROLE = new Result(_GAME_INVALID_ROLE); 

		// Not ready for next game play state 
		 public const int _GAME_NOT_READY_FOR_NEXT_STATE = (unchecked((int)0xE704001D)); 
		public static readonly Result GAME_NOT_READY_FOR_NEXT_STATE = new Result(_GAME_NOT_READY_FOR_NEXT_STATE); 

		// Invalid vote type 
		 public const int _GAME_INVALID_VOTETYPE = (unchecked((int)0xE704001E)); 
		public static readonly Result GAME_INVALID_VOTETYPE = new Result(_GAME_INVALID_VOTETYPE); 

		// Invalid vote state 
		 public const int _GAME_INVALID_VOTE_STATE = (unchecked((int)0xE704001F)); 
		public static readonly Result GAME_INVALID_VOTE_STATE = new Result(_GAME_INVALID_VOTE_STATE); 

		// Invalid vote target 
		 public const int _GAME_INVALID_VOTE_TARGET = (unchecked((int)0xE7040020)); 
		public static readonly Result GAME_INVALID_VOTE_TARGET = new Result(_GAME_INVALID_VOTE_TARGET); 

		// No suffrage 
		 public const int _GAME_NO_SUFFRAGE = (unchecked((int)0xE7040021)); 
		public static readonly Result GAME_NO_SUFFRAGE = new Result(_GAME_NO_SUFFRAGE); 

		// Invalid game state 
		 public const int _GAME_INVALID_GAMESTATE = (unchecked((int)0xE7040022)); 
		public static readonly Result GAME_INVALID_GAMESTATE = new Result(_GAME_INVALID_GAMESTATE); 

		// Doesn't have enough stamina 
		 public const int _GAME_LOW_STAMINA = (unchecked((int)0xE7040023)); 
		public static readonly Result GAME_LOW_STAMINA = new Result(_GAME_LOW_STAMINA); 

		// Invalid cost table id 
		 public const int _GAME_INVALID_COSTID = (unchecked((int)0xE7040024)); 
		public static readonly Result GAME_INVALID_COSTID = new Result(_GAME_INVALID_COSTID); 

		// Invalid bot talk table 
		 public const int _GAME_INVALID_BOTTALK_TABLE = (unchecked((int)0xE7040025)); 
		public static readonly Result GAME_INVALID_BOTTALK_TABLE = new Result(_GAME_INVALID_BOTTALK_TABLE); 

		// Request has expired 
		 public const int _GAME_REQUEST_HAS_EXPIRED = (unchecked((int)0xE7040026)); 
		public static readonly Result GAME_REQUEST_HAS_EXPIRED = new Result(_GAME_REQUEST_HAS_EXPIRED); 

	}
}



