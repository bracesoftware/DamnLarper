/* Discord Connector
 * Version @DCC_VERSION@
 * made by maddinat0r
 */


#if defined dcconnector_included
	#endinput
#endif
#define dcconnector_included

#define PERMISSION_CREATE_INSTANT_INVITE 			0x1
#define PERMISSION_KICK_MEMBERS 					0x2
#define PERMISSION_BAN_MEMBERS 						0x4
#define PERMISSION_ADMINISTRATOR 					0x8
#define PERMISSION_MANAGE_CHANNELS 					0x10
#define PERMISSION_MANAGE_GUILD 					(1 << 5)//0x20
#define PERMISSION_ADD_REACTIONS 					0x40
#define PERMISSION_VIEW_AUDIT_LOG 					0x80
#define PERMISSION_PRIORITY_SPEAKER 				0x100
#define PERMISSION_STREAM 							0x200
#define PERMISSION_VIEW_CHANNEL						0x400
#define PERMISSION_SEND_MESSAGES 					0x800
#define PERMISSION_SEND_TTS_MESSAGES 				0x1000
#define PERMISSION_MANAGE_MESSAGES 					0x2000
#define PERMISSION_EMBED_LINKS 						0x4000
#define PERMISSION_ATTACH_FILES 					0x8000
#define PERMISSION_READ_MESSAGE_HISTORY 			0x10000
#define PERMISSION_MENTION_EVERYONE 				0X20000
#define PERMISSION_USE_EXTERNAL_EMOJIS				0x40000
#define PERMISSION_VIEW_GUILD_INSIGHTS              0x80000
#define PERMISSION_CONNECT                          0x100000
#define PERMISSION_SPEAK                            0x200000
#define PERMISSION_MUTE_MEMBERS                     0x400000
#define PERMISSION_DEAFEN_MEMBERS                   0x800000
#define PERMISSION_MOVE_MEMBERS                     0x1000000
#define PERMISSION_USE_VAD                          0x2000000
#define PERMISSION_CHANGE_NICKNAME	                0x4000000
#define PERMISSION_MANAGE_NICKNAMES                 0x8000000
#define PERMISSION_MANAGE_ROLES                     0x10000000
#define PERMISSION_MANAGE_WEBHOOKS                  0x20000000
#define PERMISSION_MANAGE_EMOJIS_AND_STICKERS       0x40000000
#define PERMISSION_USE_APPLICATION_COMMANDS         0x80000000
#define PERMISSION_REQUEST_TO_SPEAK                 0x100000000
#define PERMISSION_MANAGE_EVENTS                    0x200000000
#define PERMISSION_MANAGE_THREADS                   0x400000000
#define PERMISSION_CREATE_PUBLIC_THREADS            0x800000000
#define PERMISSION_CREATE_PRIVATE_THREADS           0x1000000000
#define PERMISSION_USE_EXTERNAL_STICKERS            0x2000000000
#define PERMISSION_SEND_MESSAGES_IN_THREADS         0x4000000000
#define PERMISSION_USE_EMBEDDED_ACTIVITIES          0x8000000000
#define PERMISSION_MODERATE_MEMBERS                 0x10000000000

enum DCC_ChannelType
{
	GUILD_TEXT = 0,
	DM = 1,
	GUILD_VOICE = 2,
	GROUP_DM = 3,
	GUILD_CATEGORY = 4
};

enum DCC_UserPresenceStatus
{
	INVALID = 0,
	ONLINE = 1,
	IDLE = 2,
	DO_NOT_DISTURB = 3,
	OFFLINE = 4
};

enum DCC_BotPresenceStatus
{
	INVALID = 0,
	ONLINE,
	IDLE,
	DO_NOT_DISTURB,
	INVISIBLE,
	OFFLINE
};

enum DCC_MessageReactionType
{
	REACTION_ADD = 0, // Sent when a user adds a reaction to a message.
	REACTION_REMOVE, // Sent when a user removes a reaction from a message.
	REACTION_REMOVE_ALL, // Sent when a user explicitly removes all reactions from a message.
	REACTION_REMOVE_EMOJI // Sent when a bot removes all instances of a given emoji from the reactions of a message.
};

#define DCC_INVALID_CHANNEL DCC_Channel:0
#define DCC_INVALID_USER DCC_User:0
#define DCC_INVALID_ROLE DCC_Role:0
#define DCC_INVALID_GUILD DCC_Guild:0

#define DCC_ID_SIZE (20 + 1)
#define DCC_USERNAME_SIZE (32 + 1)
#define DCC_NICKNAME_SIZE (32 + 1)
#define DCC_EMOJI_NAME_SIZE (32 + 1)
#define DCC_COMMAND_SIZE (32 + 1)
#define DCC_COMMAND_DESCRIPTION_SIZE (32 + 1)
