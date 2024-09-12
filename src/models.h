#ifndef MODELS_H
#define MODELS_H

#include "proto/message.pb-c.h"

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
  CHAT,
  MOVE
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

typedef struct chat {
  // Identity
  int id;
  int sender;
  int recipient;

  // Stats
  Msg__V1__ChatMessage__Scope scope;
  char content[MESSAGE_SIZE];
} Chat;

#endif /* MODELS_H */
