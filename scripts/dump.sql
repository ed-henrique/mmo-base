-- Table: players
CREATE TABLE players (
    player_id SERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    race_id INT REFERENCES races(race_id),
    current_map_id INT REFERENCES maps(map_id),
    level INT NOT NULL DEFAULT 1,
    experience BIGINT NOT NULL DEFAULT 0,
    creation_date TIMESTAMP DEFAULT NOW()
);

-- Table: characters
CREATE TABLE characters (
    character_id SERIAL PRIMARY KEY,
    player_id INT REFERENCES players(player_id),
    name VARCHAR(50) UNIQUE NOT NULL,
    race_id INT REFERENCES races(race_id),
    level INT NOT NULL DEFAULT 1,
    customization JSONB NOT NULL,  -- For storing customizations like hair, skin color, etc.
    current_map_id INT REFERENCES maps(map_id),
    status VARCHAR(20) NOT NULL DEFAULT 'active',
    creation_date TIMESTAMP DEFAULT NOW()
);

-- Table: races
CREATE TABLE races (
    race_id SERIAL PRIMARY KEY,
    race_name VARCHAR(50) UNIQUE NOT NULL
);

-- Table: guilds
CREATE TABLE guilds (
    guild_id SERIAL PRIMARY KEY,
    guild_name VARCHAR(50) UNIQUE NOT NULL,
    leader_id INT REFERENCES players(player_id),
    creation_date TIMESTAMP DEFAULT NOW()
);

-- Table: guild_members
CREATE TABLE guild_members (
    guild_id INT REFERENCES guilds(guild_id),
    player_id INT REFERENCES players(player_id),
    role VARCHAR(50) NOT NULL DEFAULT 'member',
    join_date TIMESTAMP DEFAULT NOW(),
    PRIMARY KEY (guild_id, player_id)
);

-- Table: parties
CREATE TABLE parties (
    party_id SERIAL PRIMARY KEY,
    leader_id INT REFERENCES players(player_id),
    creation_date TIMESTAMP DEFAULT NOW()
);

-- Table: party_members
CREATE TABLE party_members (
    party_id INT REFERENCES parties(party_id),
    player_id INT REFERENCES players(player_id),
    join_date TIMESTAMP DEFAULT NOW(),
    PRIMARY KEY (party_id, player_id)
);

-- Table: maps
CREATE TABLE maps (
    map_id SERIAL PRIMARY KEY,
    map_name VARCHAR(50) NOT NULL,
    map_data JSONB NOT NULL  -- For map-specific data (coordinates, regions, etc.)
);

-- Table: chat_messages
CREATE TABLE chat_messages (
    message_id SERIAL PRIMARY KEY,
    sender_id INT REFERENCES players(player_id),
    chat_type VARCHAR(20) NOT NULL, -- 'guild', 'party', 'private', etc.
    recipient_id INT,  -- If private chat
    message TEXT NOT NULL,
    send_time TIMESTAMP DEFAULT NOW()
);

-- Table: achievements
CREATE TABLE achievements (
    achievement_id SERIAL PRIMARY KEY,
    achievement_name VARCHAR(100) NOT NULL,
    description TEXT NOT NULL
);

-- Table: player_achievements
CREATE TABLE player_achievements (
    player_id INT REFERENCES players(player_id),
    achievement_id INT REFERENCES achievements(achievement_id),
    unlock_date TIMESTAMP DEFAULT NOW(),
    PRIMARY KEY (player_id, achievement_id)
);

-- Table: friends
CREATE TABLE friends (
    player_id INT REFERENCES players(player_id),
    friend_id INT REFERENCES players(player_id),
    PRIMARY KEY (player_id, friend_id)
);

-- Table: events
CREATE TABLE events (
    event_id SERIAL PRIMARY KEY,
    event_name VARCHAR(100) NOT NULL,
    event_data JSONB NOT NULL,
    start_time TIMESTAMP NOT NULL,
    end_time TIMESTAMP NOT NULL
);

-- Table: buffs
CREATE TABLE buffs (
    buff_id SERIAL PRIMARY KEY,
    buff_name VARCHAR(50) NOT NULL,
    effect JSONB NOT NULL, -- Store the effect of the buff in JSONB format
    duration INT NOT NULL  -- Duration in seconds
);

-- Table: debuffs
CREATE TABLE debuffs (
    debuff_id SERIAL PRIMARY KEY,
    debuff_name VARCHAR(50) NOT NULL,
    effect JSONB NOT NULL, -- Store the effect of the debuff in JSONB format
    duration INT NOT NULL  -- Duration in seconds
);

-- Table: sessions
CREATE TABLE sessions (
    session_id SERIAL PRIMARY KEY,
    player_id INT REFERENCES players(player_id),
    session_token VARCHAR(255) NOT NULL UNIQUE,
    start_time TIMESTAMP DEFAULT NOW(),
    end_time TIMESTAMP
);

-- Table: auction_houses
CREATE TABLE auction_houses (
    auction_id SERIAL PRIMARY KEY,
    seller_id INT REFERENCES players(player_id),
    item_id INT REFERENCES items(item_id),
    price DECIMAL(10, 2) NOT NULL,
    start_time TIMESTAMP DEFAULT NOW(),
    end_time TIMESTAMP NOT NULL,
    status VARCHAR(20) DEFAULT 'open'
);

-- Table: vendors
CREATE TABLE vendors (
    vendor_id SERIAL PRIMARY KEY,
    vendor_name VARCHAR(100) NOT NULL,
    location JSONB NOT NULL  -- Store vendor's location or map coordinates
);

-- Table: items
CREATE TABLE items (
    item_id SERIAL PRIMARY KEY,
    item_name VARCHAR(100) NOT NULL,
    item_type VARCHAR(50) NOT NULL, -- E.g., 'weapon', 'armor', 'potion'
    properties JSONB NOT NULL -- To store various properties such as stats, effects, etc.
);

-- Table: player_items (Inventory)
CREATE TABLE player_items (
    player_id INT REFERENCES players(player_id),
    item_id INT REFERENCES items(item_id),
    quantity INT NOT NULL DEFAULT 1,
    PRIMARY KEY (player_id, item_id)
);

-- Table: pets
CREATE TABLE pets (
    pet_id SERIAL PRIMARY KEY,
    player_id INT REFERENCES players(player_id),
    pet_name VARCHAR(50) NOT NULL,
    pet_type VARCHAR(50) NOT NULL,
    pet_level INT NOT NULL DEFAULT 1
);

-- Table: quests
CREATE TABLE quests (
    quest_id SERIAL PRIMARY KEY,
    quest_name VARCHAR(100) NOT NULL,
    quest_description TEXT NOT NULL,
    quest_rewards JSONB NOT NULL  -- Store rewards as a JSON (items, experience, etc.)
);

-- Table: player_quests (Quest progress)
CREATE TABLE player_quests (
    player_id INT REFERENCES players(player_id),
    quest_id INT REFERENCES quests(quest_id),
    progress JSONB NOT NULL,  -- Track progress (steps completed, etc.)
    status VARCHAR(20) NOT NULL DEFAULT 'incomplete',
    PRIMARY KEY (player_id, quest_id)
);

-- Table: analytics (Gameplay analytics)
CREATE TABLE analytics (
    analytic_id SERIAL PRIMARY KEY,
    player_id INT REFERENCES players(player_id),
    action VARCHAR(100) NOT NULL,
    action_data JSONB NOT NULL,
    action_time TIMESTAMP DEFAULT NOW()
);
