/*
Header file for Wanda Library
*/


#ifndef _WANDA_H_INCLUDED_
#define _WANDA_H_INCLUDED_

#include <RF24.h>



//Variable declaration

//64 bit integer: addresses used for node communication. LL means Long Long type.
typedef enum { role_ping_out = 1, role_pong_back } role_e; //role names
extern const char* role_friendly_name[]; //easier debug names
extern int ce_pin;
extern int csn_pin;
extern const uint64_t pipes[2];
extern const uint64_t wAddress[];


#define WHICH_NODE 2


class Wanda
{
  public:
      Wanda(){};
      void ping_setup(uint64_t pipes[2]);
      void ping_loop();
      void pong_method();
      void hello_world_transmitter_setup();
      void hello_world_transmitter_loop();
      void hello_world_receiver_setup();
      void hello_world_receiver_loop();
};

#endif
