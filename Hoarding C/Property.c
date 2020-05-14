//
// Created by mfbut on 12/29/2017.
//

#include <stdlib.h>
#include "Property.h"
void delete_property(Propty* property) {
  if(property->name != NULL) {
    free(property->name);
    property->name = NULL;
  }
}
