// Copyright Benoit Blanchon 2014-2017
// MIT License
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!

#include <ArduinoJson.h>
#include <catch.hpp>

using namespace Catch::Matchers;

TEST_CASE("JsonArray::set()") {
  DynamicJsonArray _array;
  _array.add(0);

  SECTION("SizeIsUnchanged") {
    _array.set(0, "hello");
    REQUIRE(1U == _array.size());
  }

  SECTION("int") {
    _array.set(0, 123);
    REQUIRE(123 == _array[0].as<int>());
    REQUIRE(_array[0].is<int>());
    REQUIRE_FALSE(_array[0].is<bool>());
  }

  SECTION("double") {
    _array.set(0, 123.45);
    REQUIRE(123.45 == _array[0].as<double>());
    REQUIRE(_array[0].is<double>());
    REQUIRE_FALSE(_array[0].is<int>());
  }

  SECTION("bool") {
    _array.set(0, true);
    REQUIRE(true == _array[0].as<bool>());
    REQUIRE(_array[0].is<bool>());
    REQUIRE_FALSE(_array[0].is<int>());
  }

  SECTION("const char*") {
    _array.set(0, "hello");
    REQUIRE_THAT(_array[0].as<const char*>(), Equals("hello"));
    REQUIRE(_array[0].is<const char*>());
    REQUIRE_FALSE(_array[0].is<int>());
  }

  SECTION("nested array") {
    DynamicJsonArray arr;

    _array.set(0, arr);

    // TODO: requires array comparison
    // REQUIRE(&arr == &_array[0].as<JsonArray&>());
    REQUIRE(_array[0].is<JsonArray&>());
    REQUIRE_FALSE(_array[0].is<int>());
  }

  SECTION("nested object") {
    DynamicJsonObject obj;

    _array.set(0, obj);

    // TODO: requires object comparison
    // REQUIRE(&obj == &_array[0].as<JsonObject&>());
    REQUIRE(_array[0].is<JsonObject&>());
    REQUIRE_FALSE(_array[0].is<int>());
  }

  SECTION("array subscript") {
    DynamicJsonArray arr;
    arr.add("hello");

    _array.set(0, arr[0]);

    REQUIRE_THAT(_array[0].as<char*>(), Equals("hello"));
  }

  SECTION("object subscript") {
    DynamicJsonObject obj;
    obj["x"] = "hello";

    _array.set(0, obj["x"]);

    REQUIRE_THAT(_array[0].as<char*>(), Equals("hello"));
  }
}
