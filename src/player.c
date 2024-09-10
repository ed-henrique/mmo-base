enum Action {
  MOVE,
  HEAL,
  ATTACK
};

typedef struct {
  // Identity
  int id;
  char username;

  // Position
  double x;
  double y;
} Player;
