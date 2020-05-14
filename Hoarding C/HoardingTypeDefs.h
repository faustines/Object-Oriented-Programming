//
// Created by mfbut on 12/31/2017.
//

#ifndef HOARDING_HOARDINGTYPEDEFS_H
#define HOARDING_HOARDINGTYPEDEFS_H
#include <stdbool.h>
#include <stdio.h>

// declare all my types
typedef struct BoardStruct Board;
typedef struct GameStateStruct GameState;
typedef struct PlayerStruct Player;
typedef struct PropertyStruct Propty;
typedef struct PropertyManagerStruct PropertyManager;
typedef struct PropertySetStruct PropertySet;
typedef struct RulesStruct Rules;
typedef enum{go, property_space} SpaceType;
typedef struct SpaceStruct Space;
typedef struct MoveStruct Move;
typedef enum {end_turn, roll, inspect_player, leave_game, error_move}MoveType;

// define the types
struct PropertyStruct{
  Player* owner;

  char* name;
  //int id;
  int set_id, intra_set_id;
  //int num_properties_in_set;

  int cost_to_purchase;
  int cost_to_buy_house;
  int cost_to_buy_hotel;

  int rent;
  int one_house_rent;
  int hotel_rent;

  int num_houses_on;
  int num_hotels_on;

  bool is_morgated;
};
struct SpaceStruct{
  SpaceType type;
  bool is_purchasable;
  Propty* property;
};
struct BoardStruct{
  int max_space_name_width;
  int num_spaces;
  Space* spaces;
};

struct RulesStruct{
  int starting_cash;

  int num_dice_rolled;
  int max_dice_value;

  int num_houses_before_hotel;
  bool must_build_evenly;

  bool is_turn_limit;
  int turn_limit;

  int num_players_left_to_end_game;

  int property_set_multiplier;
  bool put_money_in_free_parking;
  bool auction_properties;
  int salary_multiplier_for_landing_on_go;
};

struct GameStateStruct{
  Board board;
  Rules rules;
  FILE* random_numbers_file;
  int num_players;
  Player* players;

  int turn_count;
  int player_turn;
  bool change_turn;
};

struct PropertySetStruct{
  int total_properties_in_set;
  int num_properties_owned;
  Propty** properties;
};

struct PropertyManagerStruct{
  int num_property_sets;
  PropertySet* property_sets;
};

struct PlayerStruct{
  int player_name;
  int cash;
  int location;
  bool has_rolled_this_turn;
  PropertyManager property_manager;
};

struct MoveStruct{
  MoveType type;
  bool ends_turn;
  int move_data;
};




#endif //HOARDING_HOARDINGTYPEDEFS_H
