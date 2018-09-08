// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

namespace ArduinoJson {

namespace Internals {

// Enumerated type to know the current type of a JsonVariant.
// The value determines which member of JsonVariantContent is used.
enum JsonVariantType {
  JSON_NULL,     // JsonVariant has not been initialized
  JSON_RAW,      // JsonVariant contains a raw string that should not be escaped
  JSON_STRING,   // JsonVariant stores a const char*
  JSON_BOOLEAN,  // JsonVariant stores a bool
  JSON_POSITIVE_INTEGER,  // JsonVariant stores an JsonUInt
  JSON_NEGATIVE_INTEGER,  // JsonVariant stores an JsonUInt that must be negated
  JSON_ARRAY,             // JsonVariant stores a pointer to a JsonArrayData
  JSON_OBJECT,            // JsonVariant stores a pointer to a JsonObjectData
  JSON_FLOAT              // JsonVariant stores a JsonFloat
};
}  // namespace Internals
}  // namespace ArduinoJson
