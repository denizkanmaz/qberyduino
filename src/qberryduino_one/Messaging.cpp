//  Copyright (c) 2018-present, Deniz Kanmaz. All rights reserved.
//  This source code is licensed under the GNU GENERAL PUBLIC
//  LICENCE V3. Use of this source code is governed by a license
//  that can be found in the LICENSE file.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  LICENSE file for more details.

//  You should have received a copy of the LICENSE file along with
//  this program. If not, see <http://www.gnu.org/licenses/>.

//  E-mail: denizkanmaz@gmail.com

//  Description: "Messaging.cpp" is a helper class that includes
//  functions to create appropriate messages for server using
//  declared version in the local variable named PROTOCOL_VERSION.

#include "Arduino.h"
#include "Messaging.h"

// Creates message based on given message.
// (This is the last step of preparing a message to send to
// the server.)
String Messaging::message(String msg) {
  return
    String(MARKER)
    + String(msg)
    + String(SPLITTER)
    + String(MARKER);
}

// Creates partition for given value.
String Messaging::keyval(int key, char val[]) {
  return
    String(SPLITTER)
    + String(key)
    + String(SPLITTER)
    + String(val);
}

// Creates partition for given value.
String Messaging::keyval(int key, String val) {
  return
    String(SPLITTER)
    + String(key)
    + String(SPLITTER)
    + val;
}

// Creates ready to send "HOLA" message with given parameters.
String Messaging::hola(char devId[],
                       char secret[],
                       char devModel[]) {
  return
    message(
      keyval(MESSAGE_TYPE_KEY, HOLA)
      + keyval(DEV_ID_KEY, devId)
      + keyval(SECRET_KEY, secret)
      + keyval(DEV_MODEL_KEY, devModel)
      + keyval(PROTOCOL_VERSION_KEY, PROTOCOL_VERSION)
    );
}

// Creates ready to send "CURR" message for CGNS with given
// parameters.
String Messaging::currCGNS(char devId[],
                           char secret[],
                           char devModel[],
                           String cgnsData[]) {

  t =   keyval(MESSAGE_TYPE_KEY, CURR)
        + keyval(DEV_ID_KEY, devId)
        + keyval(SECRET_KEY, secret)
        + keyval(PROTOCOL_VERSION_KEY, PROTOCOL_VERSION);

  lineI = CGNSS_START_INDEX;
  for (i = 0; i < CGNSS_LINES_LENGTH; i++) {
    t += keyval(lineI, cgnsData[i]);
    lineI++;
  }
  return message(t);
}

// Creates ready to send "CURR" message for Battery with given
// parameters.
String Messaging::currBatt(char devId[],
                           char secret[],
                           char devModel[],
                           String battData[]) {

  t =   keyval(MESSAGE_TYPE_KEY, CURR)
        + keyval(DEV_ID_KEY, devId)
        + keyval(SECRET_KEY, secret)
        + keyval(PROTOCOL_VERSION_KEY, PROTOCOL_VERSION);

  lineI = BATT_START_INDEX;
  for (i = 0; i < BATT_LINES_LENGTH; i++) {
    t += keyval(lineI, battData[i]);
    lineI++;
  }
  return message(t);
}
