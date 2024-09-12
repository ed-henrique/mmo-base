#ifndef MODELS_H
#define MODELS_H

#ifndef NAME_SIZE
#define NAME_SIZE 64
#endif

#ifndef MESSAGE_SIZE
#define MESSAGE_SIZE 256
#endif

#ifndef MAX_GUILD_SIZE
#define MAX_GUILD_SIZE 50
#endif

typedef enum action {
  MOVE,
  HEAL,
  ATTACK
} Action;

typedef struct player {
  // Identity
  int id;
  int guild;
  char name[NAME_SIZE];

  // Stats
  int life;
  int mana;

  // Position
  int x;
  int y;
} Player;

typedef struct party {
  // Identity
  int id;
  char name[NAME_SIZE];

  // Stats
  int playercount;
  int members[MAX_GUILD_SIZE];
} Party;

typedef struct guild {
  // Identity
  int id;
  char name[NAME_SIZE];

  // Stats
  int playercount;
  int members[MAX_GUILD_SIZE];
} Guild;

typedef struct privatechat {
  // Identity
  int id;
  int sender;
  int receiver;

  // Stats
  char message[MESSAGE_SIZE];
} PrivateChat;

typedef struct partychat {
  // Identity
  int id;
  int party;
  int sender;

  // Stats
  char message[MESSAGE_SIZE];
} PartyChat;

typedef struct guildchat {
  // Identity
  int id;
  int guild;
  int sender;

  // Stats
  char message[MESSAGE_SIZE];
} GuildChat;

typedef struct localchat {
  // Identity
  int id;
  int local;
  int sender;

  // Stats
  char message[MESSAGE_SIZE];
} LocalChat;

typedef struct globalchat {
  // Identity
  int id;
  int sender;

  // Stats
  char message[MESSAGE_SIZE];
} GlobalChat;

#endif /* MODELS_H */
